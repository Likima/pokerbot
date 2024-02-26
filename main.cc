#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <fstream>
#include <sstream>

#include "deck.hpp"
#include "chips.hpp"
#include "probability.hpp"
#include "pokerlib.hpp"
#include "bot.hpp"


int main() {
    Deck deck;
    Chip chips;
    Bot bot;
    int pot = 0;
    int turn = 0;
    bool bigBlind;
    std::vector<int> drawnCards;
    std::string input;
    std::pair<int, int> hand;
    std::vector<int> handVec;

    deck.shuffle();

    while (true) {
        bigBlind = (turn % 2 == 0);
        hand = deck.deal();
        bot.setHand(deck.deal());

        while (true) {
            // Betting phase before cards are handed out
            if (bigBlind) {
                // User is the big blind
                if (chips.bet(10) == -1) {
                    std::cout << "You have lost." << std::endl;
                    return 0;
                }
                std::cout << "You are the big blind. You now have $" << chips.getTotal() << " after betting $10." << std::endl;
                bot.bet(5);
                break;
            } else {
                // User is the small blind
                bot.bet(10);
                if (chips.bet(5) == -1) {
                    std::cout << "You have lost." << std::endl;
                    return 0;
                }
                std::cout << "You are the small blind. You now have $" << chips.getTotal() << " after betting $5." << std::endl;
                break;
            }
        }

        // Print the player's hand
        printHand(hand);
        handVec.push_back(hand.first);
        handVec.push_back(hand.second);
        //printVec(experimental_odds(handVec));

        drawnCards.push_back(deck.draw());

        while(true){
            if(!bigBlind){
                std::cout<<"[R/C/F]? (Case Sensitive) ";
                std::cin>>input;
                if(input == "R") {
                    // User chooses to raise
                    int raiseAmount;
                    std::cout << "Enter the amount to raise: ";
                    std::cin >> raiseAmount;
                    if(chips.bet(raiseAmount) == -1) {
                        std::cout<<"Please bet a smaller amount. You have $" << chips.getTotal() << "in total." << std::endl;
                        continue;
                    }
                    std::cout << "You have raised $" << raiseAmount << ". You now have $" << chips.getTotal() << " in total." << std::endl;
                    pot+=raiseAmount;
                    break;
                } else if(input == "C") {
                    // User chooses to call
                    if(chips.bet(5) == -1) {
                        std::cout << "You have lost." << std::endl;
                        return 0;
                    }
                    std::cout << "You have called. You now have $" << chips.getTotal() << " in total." << std::endl;
                    break;
                } else if(input == "F") {
                    // User chooses to fold
                    std::cout << "You have folded." << std::endl;
                    break;
                } else {
                    std::cout << "Invalid input. Please enter 'R' to raise, 'C' to call, or 'F' to fold." << std::endl;
                }
            }
            //should put if not big blind here
            break;
        }

        std::cout << "First drawn card is: ";
        printCard(drawnCards[0]);
        bot.analyzeHand(drawnCards);

        turn++;
        break;
    }

    return 0;
}
