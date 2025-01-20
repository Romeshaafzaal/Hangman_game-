//Romesha Afzaal 24L-3001, Hassan Ashraf 24L-3073, Iman Abid 24L-0707
 #include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

// Define maximum word count for each difficulty level
const int MAX_WORDS = 6;
string words[MAX_WORDS];
string hints[MAX_WORDS];

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void hangman(int tries, const string& message) {
    string hangman[7][6] = {
        {
            "      __________________________",
            "                 |             |",
            "                               |",
            "                               |",
            "                               |",
            "              ===========      |"
        },
        { // 5 tries left
            "      __________________________",
            "                 |             |",
            "                 O             |",
            "                               |",
            "                               |",
            "              ===========      |"
        },
        { // 4 tries left
            "      __________________________",
            "                 |             |",
            "                 O             |",
            "                 |             |",
            "                               |",
            "              ===========      |"
        },
        { // 3 tries left
            "      __________________________",
            "                 |             |",
            "                 O             |",
            "                 |\\            |",
            "                               |",
            "              ===========      |"
        },
        { // 2 tries left
            "      __________________________",
            "                 |             |",
            "                 O             |",
            "                /|\\            |",
            "                               |",
            "              ===========      |"
        },
        { // 1 try left
            "      __________________________",
            "                 |             |",
            "                 O             |",
            "                /|\\            |",
            "                  \\            |",
            "              ===========      |"
        },
        { // 0 tries left
            "      __________________________",
            "                 |             |",
            "                 O             |",
            "                /|\\            |",
            "                / \\            |",
            "              ===========      |"
        }
    };

    for (int i = 0; i < 6; i++) {
        cout << hangman[6 - tries][i];
        if (i == 0) cout << "      " << message;
        cout << endl;
    }
}

char lowercase(char input) {
    if (input >= 'A' && input <= 'Z') {
        return input + 32;
    }
    return input;
}

int check(char guess, const string& actual_word, string& hide) {
    int correct = 0;
    int length = actual_word.length();

    guess = lowercase(guess);

    for (int i = 0; i < length; i++) {
        if (guess == lowercase(actual_word[i]) && actual_word[i] != hide[i]) {
            hide[i] = actual_word[i];
            correct++;
        }
    }
    return correct;
}

void loadFile(const string& filename, string data[], int maxCount) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << filename << endl;
        exit (1);
    }

    int index = 0;
    string line;
    while (getline(file, line) && index < maxCount) {
        data[index++] = line;
    }
    file.close();
}

int main() {
    char guess;
    string word, display = " ";
    int level, index, tries = 6;
    bool use_hint = false;

    cout << "Welcome to Hangman!" << endl;
    cout << "Select difficulty level:" << endl;
    cout << "1. Easy (Days, Months)" << endl;
    cout << "2. Intermediate (Game Characters, Movies)" << endl;
    cout << "3. Hard (Cities, Brands)" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> level;

    srand(time(0));
    string wordFile, hintFile;

    switch (level) {
    case 1:
        wordFile = "Easy.txt";
        hintFile = "easy_hints.txt";
        break;
    case 2:
        wordFile = "Intermediate.txt";
        hintFile = "Inter_Hints.txt";
        break;
    case 3:
        wordFile = "Hard.txt";
        hintFile = "hard_hints.txt";
        break;
    default:
        cout << "Invalid Difficulty. Please Enter a valid number." << endl;
        return 1;
    }

    loadFile(wordFile, words, MAX_WORDS);
    loadFile(hintFile, hints, MAX_WORDS);

    index = rand() % MAX_WORDS;
    //word = words[index];
    word = "Aliyan";

    string hide(word.length(), '_');
    for (int i = 1; i < word.length(); i++) {
        if (word[i] == ' ') {
            hide[i] = ' ';
        }
    }

    while (tries > 0) {
        clearScreen();
        hangman(tries, display);
        cout << "\t\t\t\tLIVES " << tries << endl;
        cout << hide << endl;
        cout << "\t\t\t\tEnter your guess: ";
        cin >> guess;

        if (check(guess, word, hide) == 0) {
            display = "Incorrect Guess! Try Again Please!";
            tries--;
        }
        else {
            display = "Correct Guess! Good Job!";
        }

        if (!use_hint) {
            char hint;
            cout << "Would you like a hint? (y/n): ";
            cin >> hint;

            if (hint == 'y' || hint == 'Y') {
                int hint_type;
                cout << "1. Letter Reveal" << endl;
                cout << "2. Category hint" << endl;
                cout << "Choose hint type (1 or 2): ";
                cin >> hint_type;

                if (hint_type == 1) {
                    for (size_t i = 0; i < word.length(); i++) {
                        if (hide[i] == 'X') {
                            hide[i] = word[i];
                            use_hint = true;
                            cout << "A letter has been revealed!" << endl;
                            break;
                        }
                    }
                }
                else if (hint_type == 2) {
                    cout << "Hint: " << hints[index] << endl;
                    use_hint = true;
                    cin.ignore();
                    cin.get();
                }
                else {
                    cout << "Invalid choice.\n";
                }
            }
        }

        if (word == hide) {
            display = "GREAT JOB! YOU DID IT!";
            clearScreen();
            hangman(tries, display);
            cout << "    LIVES: " << tries << endl;
            cout << "    The word was: " << word << endl;
            return 0;
        }
    }

    clearScreen();
    hangman(tries, "YOU LOST!");
    cout << "    LIVES: " << tries << endl;
    cout << "    The word was: " << word << endl;
    cout << "    BETTER LUCK NEXT TIME!" << endl;
}
