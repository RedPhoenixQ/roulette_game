#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

void invalidInput() {
    cout << "\nInvalid input, please try again\n";
}

void askQuestion(string question, int& output) {
    string answer;
    while (true)
    {
        askQuestion(question, answer);
        try {
            output = stoi(answer.c_str());
            break;
        } catch (...) {
            continue;
        }
    }
}

void askQuestion(string question, char& output) {
    string answer;
    askQuestion(question, answer);
    output = answer[0];

}

void askQuestion(string question, string output) {
    cout << question;
    cin >> output;
}

int main() {
    // Main player choice that can be "red", "black" or "number"
    char choice,
        // For yes or no questions
        yes_no;
    // What color a give random roulette number represents
    string color;
    // For number betting
    int chosen_number,
        // For multiple choice input
        input = 0,
        // For amount of money in the bet
        bet,
        // Amount of money a pleyer has, defaults to 1000kr
        account = 1000,
        // Random number from roulette wheel
        random;
    // I a given round was won or not
    bool win = false;

    // Seed rand with current time
    srand(time(0));

    // Welcome message
    cout << endl << setw(25) << "Welcome to Roulette!\n\n";
    
    // Show balance at the start of the game
    cout << "Your balance is: \e[1m" << account << "\e[0mkr\n";

    // Loop the roulette game until stopped
    while (true)
    {
        // Get valid bet
        while (true) {
            askQuestion("\nHow much do you want to bet?: \n    [1] 100kr\n    [2] 300kr\n    [3] 500kr\n: ", input);

            if (input == 1) 
            {
                bet = 100;
            }
            else if (input == 2)
            {
                bet = 300;
            }
            else if (input == 3)
            {
                bet = 500;
            } else {
                invalidInput();
                continue;
            }

            // Can't bet more than you have
            if (bet > account) {
                cout << "You do not hav enough money for that bet. Your current balance is \e[1m" << account << "\e[0mkr.\n";
            } else {
                account -= bet;
                cout << "You've bet \e[1m" << bet << "\e[0m!\n";
                break;
            }
        }

        // Get valid bet input
        while (true)
        {
            askQuestion("Please choose a color (\e[1m[r]ed\e[0m or \e[1m[b]lack\e[0m) or choose a \e[1m[n]umber\e[0m: ", choice);
            
            if ((choice == 'r') || (choice == 'b') || (choice == 'n'))
                break;
            invalidInput(); 
        }

        // Get a valid number if number is choosen
        if (choice == 'n') {
            while (true)
            {
                askQuestion("Please choose a number (1-36): ", chosen_number);
                if (chosen_number >= 1 || chosen_number <= 36) {
                    break;
                }
                invalidInput();
            };
        }

        // Create a random number and get the winning color
        random = rand() % 36 + 1;
        if (random % 2 == 0) {
            color = "black";
        }
        else
        {
            color = "red";
        }

        // Diplay winning number
        cout  << endl << setw(25) << "The winning number is: \e[1m" << random << " " << color << "\e[0m\n";

        // Check if player won and multiply bet by multiplier for color and number bets
        if (choice == color[0]) {
            win = true;
            bet *= 2;
            cout << endl << setw(20)
                 << "You won on color \e[1m" << color << "!\e[0m\n\n";
        }
        else if (choice == 'n' && chosen_number == random)
        {
            win = true;
            bet *= 10;
            cout << endl << setw(20)
                 << "You \e[1mWON\e[0m with the number \e[1m" << chosen_number << "!\e[0m\n\n";
        } else {
            cout << "\n\n\e[1m"
                 << setw(25)
                 << "You Lost\e[0m\n\n";
        }

        // Display winnings and add bet to money
        if (win) {
            win = false;
            account += bet;
            cout << "Your winnings: \e[1m" << bet << "\e[0mkr\n";
        }

        // Display balance
        cout << endl << "Your balance is: \e[1m" << account << "\e[0mkr\n";

        // Exit game and display bankrupt message if money <= 0
        if (account <= 0)
        {
            cout << endl << "You have gone backrupt. Please come back another time\n\n";
            break;
        }

        // Checks if player wants to exit the game. Only continues if answer is 'y'
        askQuestion("Do you want to continue playing? [n/y]: ", yes_no);
        if (yes_no != 'y') {
            cout << "Goodbye!\n";
            break;
        }
    }
    return 0;
}