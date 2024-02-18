#ifndef BOT_HPP
#define BOT_HPP

#include "deck.hpp"
#include "chips.hpp"

class Bot {
    public:
        Bot();
        void setHand(std::pair<int,int>);
    private:
        Chip chips;
        std::pair<int,int> hand;
};

Bot::Bot(){}

void Bot::setHand(std::pair<int, int> deal){
    hand = deal;
    printHand(hand);
}

#endif // BOT_HPP
