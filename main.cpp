#include "game.h"

using namespace std;

void displayMenu() {
    cout << R"(
  _____             _          __   _   _           __          __           _       _ _ _ 
 |  __ \           | |        / _| | | | |          \ \        / /          | |     | | | |
 | |  | |_   _  ___| |   ___ | |_  | |_| |__   ___   \ \  /\  / /__  _ __ __| |___  | | | |
 | |  | | | | |/ _ \ |  / _ \|  _| | __| '_ \ / _ \   \ \/  \/ / _ \| '__/ _` / __| | | | |
 | |__| | |_| |  __/ | | (_) | |   | |_| | | |  __/    \  /\  / (_) | | | (_| \__ \ |_|_|_|
 |_____/ \__,_|\___|_|  \___/|_|    \__|_| |_|\___|     \/  \/ \___/|_|  \__,_|___/ (_|_|_)
    )";
    cout << "\n1. Single-Player\n2. Multiplayer\n3. Quit\n";
}

int main() {
    int choice;
    do {
        displayMenu();
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            DuelGame game(7, true);
            if (game.loadRandomWord("word.txt")) {
                while (!game.isGameWon() && !game.isGameLost()) {
                    game.displayState();
                    char guess;
                    cout << "\nEnter your guess: ";
                    cin >> guess;
                    game.playTurn(guess);
                }
                game.printResult();
            }
        } else if (choice == 2) {
            DuelGame game(7, false);
            string word;
            cout << "Player 1, enter a word for Player 2 to guess: ";
            cin >> word;
            game.setSecretWord(word);
            game.clearScreen();

            while (!game.isGameWon() && !game.isGameLost()) {
                game.displayState();
                char guess;
                cout << "\nPlayer 2, enter your guess: ";
                cin >> guess;
                game.playTurn(guess);
            }
            game.printResult();
        }
    } while (choice != 3);

    cout << "Thanks for playing Duel of the Words!\n";
    return 0;
}
