#include "deck.hpp"
#include "chips.hpp"
#include "bot.hpp"

#include <string>

int main(){
    Deck d;
    Chip c;
    std::pair<int,int> hand;
    d.shuffle();
    d.print();
    while(1){
        hand = d.deal();
        printHand(hand);
        break;
    }
    return 0;
}

// Mapping of 0-51 to cards:
// 0-12: Ace of Diamonds, 2 of Diamonds, 3 of Diamonds, ..., King of Diamonds
// 13-25: Ace of Clubs, 2 of Clubs, 3 of Clubs, ..., King of Clubs
// 26-38: Ace of Hearts, 2 of Hearts, 3 of Hearts, ..., King of Hearts
// 39-51: Ace of Spades, 2 of Spades, 3 of Spades, ..., King of Spades
