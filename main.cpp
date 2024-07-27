#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void encryptFile(const std::string& filename, int key);
void decryptFile(const std::string& filename, int key);
std::vector<int> stringToNumbers(const std::string& text);
std::string numbersToBeanCode(const std::vector<int>& numbers, int key);
std::vector<int> beanCodeToNumbers(const std::string& beanCode, int key);
std::string numbersToString(const std::vector<int>& numbers);

int main() {
    int choice;
    std::string filename;
    int key;

    std::cout << "Choose an option:\n1. Encrypt a file\n2. Decrypt a file\n";
    std::cin >> choice;

    std::cout << "Enter the filename: ";
    std::cin >> filename;

    std::cout << "Enter the key: ";
    std::cin >> key;

    if (choice == 1) {
        encryptFile(filename, key);
    } else if (choice == 2) {
        decryptFile(filename, key);
    } else {
        std::cout << "Invalid choice." << std::endl;
    }

    return 0;
}

void encryptFile(const std::string& filename, int key) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "File not found." << std::endl;
        return;
    }

    std::ostringstream buffer;
    buffer << infile.rdbuf();
    std::string text = buffer.str();
    infile.close();

    std::vector<int> numbers = stringToNumbers(text);
    std::string encryptedText = numbersToBeanCode(numbers, key);

    std::ofstream outfile(filename);
    outfile << encryptedText;
    outfile.close();

    std::cout << "File encrypted and saved as " << filename << std::endl;
}

void decryptFile(const std::string& filename, int key) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "File not found." << std::endl;
        return;
    }

    std::ostringstream buffer;
    buffer << infile.rdbuf();
    std::string beanCode = buffer.str();
    infile.close();

    std::vector<int> numbers = beanCodeToNumbers(beanCode, key);
    std::string decryptedText = numbersToString(numbers);

    std::ofstream outfile(filename);
    outfile << decryptedText;
    outfile.close();

    std::cout << "File decrypted and saved as " << filename << std::endl;
}

std::vector<int> stringToNumbers(const std::string& text) {
    std::vector<int> numbers;
    for (char c : text) {
        if (std::isalpha(c)) {
            numbers.push_back((std::tolower(c) - 'a' + 1) * 61);
        } else if (c == ' ') {
            numbers.push_back(0); // Use 0 to represent spaces
        }
    }
    return numbers;
}

std::string numbersToBeanCode(const std::vector<int>& numbers, int key) {
    std::ostringstream result;
    for (size_t i = 0; i < numbers.size(); ++i) {
        int encryptedNumber = numbers[i] * key;
        if (encryptedNumber == 0) {
            result << " ";
        } else {
            for (int j = 0; j < encryptedNumber; ++j) {
                result << "beans";
            }
            if (i < numbers.size() - 1) {
                result << " ";
            }
        }
    }
    return result.str();
}

std::vector<int> beanCodeToNumbers(const std::string& beanCode, int key) {
    std::vector<int> numbers;
    std::istringstream stream(beanCode);
    std::string beanCountStr;

    while (std::getline(stream, beanCountStr, ' ')) {
        int count = 0;
        size_t pos = 0;

        while ((pos = beanCountStr.find("beans", pos)) != std::string::npos) {
            count++;
            pos += 5; // Move past "beans"
        }

        numbers.push_back(count / key);
    }

    return numbers;
}

std::string numbersToString(const std::vector<int>& numbers) {
    std::ostringstream result;
    for (int number : numbers) {
        if (number == 0) {
            result << " ";
        } else {
            char c = static_cast<char>((number / 61) + 'a' - 1);
            result << c;
        }
    }
    return result.str();
}

