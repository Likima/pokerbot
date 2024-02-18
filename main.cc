#include "deck.hpp"
#include "chips.hpp"
#include "bot.hpp"

#include <iostream>
#include <string>
#include <vector>

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
                break;
            } else {
                // User is the small blind
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

        drawnCards.push_back(deck.draw());

        // Additional game logic goes here...

        std::cout << "First drawn card is: ";
        printCard(drawnCards[0]);

        turn++;
        break;
    }

    return 0;
}
