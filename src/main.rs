use std::io;

fn main() {
    let mut input = String::new();

    io::stdin()
        .read_line(&mut input)
        .expect("cant read");
    let numbers: Vec<u32> = input.chars().map(|c| c as u32).collect();

    println!("{:?}",numbers);
}
