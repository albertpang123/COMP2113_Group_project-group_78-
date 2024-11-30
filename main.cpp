#include "game.h"

using namespace std;

// Displays the name for the game
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
        displayMenu();  // Show the main menu
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            // Single-player mode
            DuelGame game(7, true);  // Initialize the game with 7 attempts
            if (game.loadRandomWord("word.txt")) {  // Load a random word from the file
                while (!game.isGameWon() && !game.isGameLost()) {
                    game.displayState();  // Display the game state
                    char guess;
                    cout << "\nEnter your guess: ";
                    cin >> guess;
                    game.playTurn(guess);  // Process the player's guess
                }
                game.printResult();  // Print the result (win/loss)
            }
        } else if (choice == 2) {
            // Multiplayer mode
            DuelGame game(7, false);  // Initialize the game with 7 attempts
            string word;
            cout << "Player 1, enter a word for Player 2 to guess: ";
            cin >> word;
            game.setSecretWord(word);  // Set the secret word
            game.clearScreen();  // Clear the screen to hide the word

            while (!game.isGameWon() && !game.isGameLost()) {
                game.displayState();  // Display the game state
                char guess;
                cout << "\nPlayer 2, enter your guess: ";
                cin >> guess;
                game.playTurn(guess);  // Process the player's guess
            }
            game.printResult();  // Print the result (win/loss)
        }
    } while (choice != 3);  // Exit the loop if the player chooses to quit

    cout << "Thanks for playing Duel of the Words!\n";
    return 0;
}
