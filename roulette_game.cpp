#include <iostream>
#include <string>
#include <ctime>

using namespace std;

void askQuestion(string question, string &output);
void askQuestion(string question, char &output);
// void askQuestion(string question, int &output);
void invalidInput(string err);
void invalidInput();

int main() {
    // Constants for comparisons to make the code more readable
    const char BLACK = 'b',
               RED = 'r',
               YES = 'y',
               NO = 'n';

    // Clearer code used to combine with other strings
    const string BOLD = "\e[1m",
                 NOBOLD = "\e[0m",
                 ENDL = "\n",
                 INDENT = "        ";

    // Main player choice that can be "red", "black" or a number that will be parsed by the code into int chosen_number
    string choice,
        // What color a give random roulette number represents
        color;
    // For yes or no questions
    char yes_no,
        // For multiple choice input
        input;
    // For number betting
    int chosen_number,
        // For amount of money in the bet
        bet,
        // Amount of money a player has, defaults to 1000kr
        account = 1000,
        // Random number from roulette wheel
        random;
    // If a given round was won or not
    bool win = false;

    // Seed rand with current time
    srand(time(0));

    // Welcome message
    cout << INDENT + "Welcome to Roulette!" << endl << endl;

    // Show balance at the start of the game
    cout << "Your balance is: " + BOLD << account << NOBOLD + "kr" << endl;

    // Loop the roulette game until stopped
    while (true) {
        // Get valid bet
        while (true) {
            askQuestion("How much money do you want to bet?: " + ENDL + "  [1] 100kr" + ENDL + "  [2] 300kr" + ENDL + "  [3] 500kr" + ENDL + ": ", input);

            // Translate input list number to bet value
            switch (input) {
            case '1':
                bet = 100;
                break;
            case '2':
                bet = 300;
                break;
            case '3':
                bet = 500;
                break;
            default:
                invalidInput("Please choose a number between 1 and 3");
                continue;
            }
            // Can't bet more than you have
            if (bet > account) {
                cout << "You do not have enough money for that bet. Your current balance is " + BOLD << account << NOBOLD + "kr." << endl;
            } else {
                account -= bet;
                cout << "You've bet " + BOLD << bet << NOBOLD + "kr" << endl;
                break;
            }
        }

        // Get valid bet input
        while (true) {
            askQuestion("Please choose a color (" + BOLD + "[r]ed" + NOBOLD + " or " + BOLD + "[b]lack" + NOBOLD + ") or choose a " + BOLD + "number" + NOBOLD + " (1-36): ", choice);

            try {
                chosen_number = stoi(choice.c_str());
                if (chosen_number < 1)
                    invalidInput("number is too low");
                else if (chosen_number > 36)
                    invalidInput("number is too high");
                else
                    break;
            } catch (...) {
                if (choice[0] == RED || choice[0] == BLACK) {
                    // Reset chosen number so that winning number payout isn't accidentally given
                    chosen_number = 0;
                    break;
                }
                invalidInput();
            }
        }

        // Create a random number and get the winning color
        random = rand() % 36 + 1;
        if (random % 2 == 0)
            color = "black";
        else
            color = "red";

        // Display winning number
        cout << endl << "The winning number is: " + BOLD << random << " " << color << NOBOLD << endl << endl;

        // Check if player won and multiply bet by multiplier for color and number bets
        //  First if will not accidentally be true if choice was a number since stoi() would fail if choice[0] wasn't a number
        if (choice[0] == color[0]) {
            win = true;
            bet *= 2;
            cout << INDENT + "You won on color " + BOLD << color << "!" + NOBOLD << endl << endl;
        } else if (chosen_number == random) {
            win = true;
            bet *= 10;
            cout << INDENT + "You " + BOLD + "WON" + NOBOLD + " with the number " + BOLD << chosen_number << "!" + NOBOLD << endl << endl;
        } else {
            cout << INDENT + BOLD + "You Lost" + NOBOLD << endl << endl;
        }

        // Display winnings and add bet to money
        if (win) {
            win = false;
            account += bet;
            cout << "Your winnings: " + BOLD << bet << NOBOLD + "kr" << endl;
        }

        // Display balance
        cout << "Your balance is: " + BOLD << account << NOBOLD + "kr" << endl;

        // Exit game and display bankrupt message if money <= 0
        if (account <= 0) {
            cout << "You have gone bankrupt. Please come back another time" << endl;
            break;
        }

        // Checks if player wants to exit the game. Only continues if answer is 'y'
        while (true){
            askQuestion("Do you want to continue playing? [y]es / [n]o: ", yes_no);
            if (yes_no == YES || yes_no == NO)
                break;
            invalidInput();
        }
        if (yes_no == NO) {
            cout << "Goodbye!" << endl;
            break;
        }
    }
    return 0;
}

void askQuestion(string question, string &output) {
    cout << question;
    cin >> output;
}

void askQuestion(string question, char &output) {
    string answer;
    askQuestion(question, answer);
    output = answer[0];
}

// void askQuestion(string question, int &output) {
//     string answer;
//     while (true) {
//         askQuestion(question, answer);
//         try {
//             output = stoi(answer.c_str());
//             break;
//         } catch (...) {
//             invalidInput("please input a number");
//         }
//     }
// }

void invalidInput(string err) {
    cout << "Invalid input, " << err << endl;
}

void invalidInput() {
    cout << "Invalid input, please try again" << endl;
}