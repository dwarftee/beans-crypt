use std::io;
use rand::Rng;
use std::cmp::Ordering;

fn main() {
    let numb = rand::thread_rng().gen_range(1..=100);
    loop {
        println!("guess a number: ");

        let mut guess = String::new();

        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");
    
        let guess: u32 = guess.trim().parse().expect("guess the number!");

        println!("you guessed: {}",guess);

        match guess.cmp(&numb) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big"),
            Ordering::Equal => {
                println!("you win!");
                break;
            }
        }
    }
}
