#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <time.h>
using namespace std;

class playGame {
    int balance = 50;
    int bet = 0;
    int rolling_total = 0;
    int dealer_total = 0;
    vector<string> dealer_hand;;
    vector<string> cards = createDeck();
    vector<string> hand;
    unsigned int delay = 2000;

    vector<string> createDeck() {
        string suits[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        string royalty[4] = {"10 :Jack", "10 :Queen", "10 :King", "11 Ace"};
        vector<std::string> deck;
        for (auto &i : royalty) {
            for (auto &suit : suits) {
                deck.push_back(i + " of " + suit);
            }
        }
        for (int i = 2; i <= 10; i++) {
            for (auto &suit : suits) {
                deck.push_back(std::to_string(i) + " :of " + suit);
            }
        }
        std::shuffle(deck.begin(), deck.end(), mt19937(std::random_device()()));
        return deck;
    }

    void gameLoop() {
        cout << "Your balance is now: " << balance << endl;
        int index = 2;
        Sleep(delay);
        cout << "The dealer deals the first 2 cards..." << endl;
        Sleep(delay);
        for (int i = 0; i < 2; i++)
        {
            string x = cards[rand() % cards.size()];

            if (stoi(x) == 11)
            {
                string suit;
                int track = 0;
                for (char const &c: x) {
                    track += 1;
                    if (track > 10)
                        suit += c;
                }
                int value_chosen;
                cout << "You drew an Ace of " << suit << "!" <<  endl;
                cout << "Do you want your ace to be worth 1 or 11?" << endl;
                cin >> value_chosen;
                hand.push_back(to_string(value_chosen) + " :ace of " + suit);
                x.erase();
            }
            else{
                hand.push_back(x);
                x.erase();
            }
        }
        for (int i = 0; i < 2; i++)
        {
            string y = cards[rand() % cards.size()];
            dealer_hand.push_back(y);
            y.erase();
        }
        rolling_total += stoi(hand[0]) + stoi(hand[1]);
        dealer_total += stoi(dealer_hand[0]) + stoi(dealer_hand[1]);
        cout << "You draw a " << hand[0] << endl;
        Sleep(delay);
        cout << "You also draw a " << hand[1] << endl;
        Sleep(delay);
        cout << "The Dealer draws a " << dealer_hand[0] << endl;
        Sleep(delay);
        cout << "The Dealer also draws a ??? (ooh what is it!!!)" << endl;
        Sleep(delay);
        while (rolling_total < 21) {
            cout << "You have a total of " << to_string(rolling_total) << ". What would you like to do?" << endl;
            cout << "1: Hit" << endl;
            cout << "2: Stay" << endl;
            cout << "3: Quit" << endl;
            int answer;
            cin >> answer;
            switch (answer) {
                case 1:
                    hand.push_back(cards[rand() % cards.size()]);
                    cout << "You Draw a " << hand[index] << "." << endl;
                    Sleep(delay);
                    rolling_total += stoi(hand[index]);
                    if (rolling_total <= 21) {
                        cout << "Your rolling total is now " << rolling_total << "." << endl;
                    }
                    index += 1;
                    break;
                case 2:
                    cout << "You stay on " << rolling_total << "." << endl;
                    dealers_turn();
                    return;
                case 3:
                    exit(1);
                default:
                    return;
            }
        }
        if (rolling_total == 21) {
            cout << "Wow that's a 21!!! You win!!!" << endl;
            balance += (bet * 2);
            Sleep(delay);
            cout << "New Balance: " << balance << endl;
        } else {
            cout << "You Lose! " << rolling_total << " is greater than 21!" << endl;
        }
        play_again();
    }

    void play_again() {
        cout << "Would you like to play again?" << endl;
        cout << "1: Play again" << endl;
        cout << "2: Quit" << endl;
        int decision;
        cin >> decision;
        if (decision == 1) {
            hand.clear();
            dealer_hand.clear();
            mainMenu();
        } else {
            exit(1);
        }
    }

public: void mainMenu() {
        cards = createDeck();
        bet = 0;
        rolling_total = 0;
        dealer_total = 0;
        if (balance > 0) {
            cout << "This is the main menu" << endl;
            cout << "Balance: " << balance << endl;
            cout << "How Much Would You Like To Wager?" << endl;
            int decision = 0;
            cin >> decision;
            if (decision <= balance) {
                bet = decision;
                balance -= decision;
                gameLoop();
            } else {
                cout << "You don't have enough cash" << endl;
                mainMenu();
            }
        }
        else{
            cout << "You are skint!!! Game Over!" << endl;
            exit(1);
        }
    }

    void dealers_turn()
    {
        cout << "The Dealer already had a " << dealer_hand[0] << endl;
        Sleep(delay);
        cout << "But what else did he have..." << endl;
        Sleep(delay);
        cout << "Here it comes..." << endl;
        Sleep(delay);
        cout << "It was a " << dealer_hand[1] << "!" << endl;
        while (true) {
            if (dealer_total == 21) {
                cout << "WOAH HE GOT A FUCKIN' 21 BOYO!!! BAD LUCK! NEW BALANCE: " << balance << endl;
                play_again();
            } else if (dealer_total > rolling_total && dealer_total < 21) {
                cout << "Oh No! That's a fat L for you big boy! You have lost " << bet << " moneys!" << endl;
                play_again();
            }
            else if (dealer_total > 21)
            {
                balance += bet * 2;
                cout << "EASY DUB CHUM!!! YOU HAVE WON " << bet * 2 << " MONIES!!!" << endl;
                play_again();
            }
            else {
                string x = cards[rand() % cards.size()];
                dealer_hand.push_back(x);
                dealer_total += stoi(x);
                cout << "There is hope for you yet!!! He still needs to beat you!" << endl;
                Sleep(delay);
                cout << "He drew a " << x << "!" << endl;
                Sleep(delay);
                cout << "His new total is: " << dealer_total << endl;
                Sleep(delay);
                x.erase();
            }
        }
    }
};

int main() {
    srand(time(NULL));
    playGame game;
    game.mainMenu();
    return 0;
}
