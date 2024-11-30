#include "game.h"

using namespace std;

DuelGame::DuelGame(int maxAttempts, bool isSinglePlayer)
    : maxAttempts(maxAttempts), remainingAttempts(maxAttempts), isSinglePlayer(isSinglePlayer) {}

void DuelGame::setSecretWord(const string &word) {
    secretWord = word;
    currentWord = string(secretWord.size(), '_');
    guessedLetters.clear();
}

bool DuelGame::loadRandomWord(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open word file: " << filename << endl;
        return false;
    }

    vector<string> words;
    string word;
    while (file >> word) {
        if (word.size() >= 3) {
            words.push_back(word);
        }
    }

    if (words.empty()) {
        cerr << "Error: No valid words found in file." << endl;
        return false;
    }

    srand(static_cast<unsigned>(time(0)));
    secretWord = words[rand() % words.size()];
    setSecretWord(secretWord);

    return true;
}

void DuelGame::displayState() const {
    cout << "\nCurrent word: ";
    for (char c : currentWord) {
        cout << c << " ";
    }
    cout << "\nGuessed letters: ";
    for (char c : guessedLetters) {
        cout << c << " ";
    }
    cout << "\nRemaining attempts: " << remainingAttempts << "\n";
}

void DuelGame::drawCartoonHead() const {
    static const char *stages[] = {
        "", // Stage 0 (no incorrect guesses)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / / 
)", // Stage 1 (2 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / / 
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
)", // Stage 2 (4 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / / 
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
    \ \| |            | |/ /    
     \_\ |            | /_/     
)", // Stage 3 (6 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / / 
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
    \ \| |            | |/ /    
     \_\ |            | /_/     
      __\_\_ ______ _/_/__      
   __|______|______|______|__   
)", // Stage 4 (8 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / / 
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
    \ \| |            | |/ /    
     \_\ |            | /_/     
      __\_\_ ______ _/_/__      
   __|______|______|______|__   
  / /  / _ \|  \/  |/ _ \  \ \  
 | |  | | | | \  / | | | |  | | 
)", // Stage 5 (10 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / / 
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
    \ \| |            | |/ /    
     \_\ |            | /_/     
      __\_\_ ______ _/_/__      
   __|______|______|______|__   
  / /  / _ \|  \/  |/ _ \  \ \  
 | |  | | | | \  / | | | |  | | 
 | |  | | | | |\/| | | | |  | | 
 | |  | |_| | |  | | |_| |  | | 
)", // Stage 6 (12 lines of the head)
        R"(
__      __          __      __ 
 \ \    / /          \ \    / / 
  \ \  | |            | |  / /  
   \ \ | |            | | / /   
    \ \| |            | |/ /    
     \_\ |            | /_/     
      __\_\_ ______ _/_/__      
   __|______|______|______|__   
  / /  / _ \|  \/  |/ _ \  \ \  
 | |  | | | | \  / | | | |  | | 
 | |  | | | | |\/| | | | |  | | 
 | |  | |_| | |  | | |_| |  | | 
 | |  _\___/|_|  |_|\___/_  | | 
  \_\|______|      |______|/_/ 
)" // Stage 7 (14 lines, complete head)
    };

    int stageIndex = maxAttempts - remainingAttempts;
    if (stageIndex >= 0 && stageIndex < 8) {
        cout << stages[stageIndex] << "\n";
    }
}

bool DuelGame::playTurn(char guess) {
    guess = tolower(guess);
    if (guessedLetters.count(guess)) {
        cout << "You already guessed that letter. Try again.\n";
        return false;
    }

    guessedLetters.insert(guess);
    bool correct = false;

    for (size_t i = 0; i < secretWord.size(); ++i) {
        if (tolower(secretWord[i]) == guess) {
            currentWord[i] = secretWord[i];
            correct = true;
        }
    }

    if (!correct) {
        --remainingAttempts;
        cout << "Wrong guess!\n";
        drawCartoonHead();
    } else {
        cout << "Correct guess!\n";
    }

    return true;
}

bool DuelGame::isGameWon() const {
    return currentWord == secretWord;
}

bool DuelGame::isGameLost() const {
    return remainingAttempts <= 0;
}

void DuelGame::printResult() const {
    if (isGameWon()) {
        cout << "Congratulations! You guessed the word: " << secretWord << "\n";
    } else {
        cout << "You lost! The word was: " << secretWord << "\n";
    }
}

void DuelGame::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
