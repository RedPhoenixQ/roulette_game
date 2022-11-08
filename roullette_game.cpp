#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

void askQuestion(string question, string &output);
void askQuestion(string question, int &output);
void invalidInput(string err);
void invalidInput();

int main() {
    
    // Main player choice that can be "red", "black" or a number that will be parsed by the code into int chosen_number
    string choice,
    // What color a give random roulette number represents
        color,
    // For yes or no questions
        yes_no;
    // For number betting
    int chosen_number,
        // For multiple choice input
        input,
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
                invalidInput("please choose a number between 1 and 3");
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
            askQuestion("Please choose a color (\e[1m[r]ed\e[0m or \e[1m[b]lack\e[0m) or choose a \e[1mnumber\e[0m (1-36): ", choice);
            
            try {
                chosen_number = stoi(choice.c_str());
                if (chosen_number < 1) {
                    invalidInput("number is too low");
                } else if (chosen_number > 36) {
                    invalidInput("number is too high");
                } else {
                    break;
                }
            } catch (...){
                if (choice[0] == 'r' || choice[0] == 'b'){
                    // Reset chosen number so that winning number payout isn't accidentally given 
                    chosen_number = 0;
                    break;
                }
                invalidInput();  
            }  
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
        if (choice[0] == color[0]) {
            win = true;
            bet *= 2;
            cout << endl << setw(20)
                 << "You won on color \e[1m" << color << "!\e[0m\n\n";
        }
        else if (chosen_number == random)
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
        while (true){
            askQuestion("Do you want to continue playing? [y]es / [n]o: ", yes_no);
            if (yes_no[0] == 'n' || yes_no[0] == 'y') 
                break; 
            invalidInput();
        }
        if (yes_no[0] == 'n') {
            cout << "Goodbye!\n";
            break;
        }
    }
    return 0;
}

void askQuestion(string question, string& output) {
    cout << question;
    cin >> output;
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
            invalidInput("please input a number");
        }
    }
}

void invalidInput(string err)
{
    cout << "Invalid input, " << err << endl;
}

void invalidInput()
{
    cout << "Invalid input, please try again" << endl;
}