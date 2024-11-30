#include "game.h"

void displayMenu() {
    std::cout << R"(
  _____             _          __   _   _           __          __           _       _ _ _ 
 |  __ \           | |        / _| | | | |          \ \        / /          | |     | | | |
 | |  | |_   _  ___| |   ___ | |_  | |_| |__   ___   \ \  /\  / /__  _ __ __| |___  | | | |
 | |  | | | | |/ _ \ |  / _ \|  _| | __| '_ \ / _ \   \ \/  \/ / _ \| '__/ _` / __| | | | |
 | |__| | |_| |  __/ | | (_) | |   | |_| | | |  __/    \  /\  / (_) | | | (_| \__ \ |_|_|_|
 |_____/ \__,_|\___|_|  \___/|_|    \__|_| |_|\___|     \/  \/ \___/|_|  \__,_|___/ (_|_|_)
    )";
    std::cout << "\n1. Single-Player\n2. Multiplayer\n3. Quit\n";
}

int main() {
    int choice;
    do {
        displayMenu();
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (choice == 1) {
            HangmanGame game(7, true);
            if (game.loadRandomWord("word.txt")) {
                while (!game.isGameWon() && !game.isGameLost()) {
                    game.displayState();
                    char guess;
                    std::cout << "\nEnter your guess: ";
                    std::cin >> guess;
                    game.playTurn(guess);
                }
                game.printResult();
            }
        } else if (choice == 2) {
            HangmanGame game(7, false);
            std::string word;
            std::cout << "Player 1, enter a word for Player 2 to guess: ";
            std::cin >> word;
            game.setSecretWord(word);
            game.clearScreen();

            while (!game.isGameWon() && !game.isGameLost()) {
                game.displayState();
                char guess;
                std::cout << "\nPlayer 2, enter your guess: ";
                std::cin >> guess;
                game.playTurn(guess);
            }
            game.printResult();
        }
    } while (choice != 3);

    std::cout << "Thanks for playing Duel of the Words!\n";
    return 0;
}
