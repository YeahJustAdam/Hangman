# Hangman Game

This is a simple Hangman game implemented in C.

## How to Compile

To compile the Hangman game, you need to have `gcc` installed. You can compile the game using the provided Makefile. Open a terminal and navigate to the directory containing the source code and run:

```sh
make
```

This will generate an executable file named `hangman`.

## How to Run

To run the Hangman game, use the following command:

```sh
./hangman
```

## How to Play

The game will randomly select a word from the `words.txt` file. You need to guess the word by entering letters or the whole word. You have a limited number of attempts to guess the word correctly.

## Cleaning Up

To clean up the compiled files, run:

```sh
make clean
```

This will remove the object files and the executable.

## License

This project is licensed under the MIT License.