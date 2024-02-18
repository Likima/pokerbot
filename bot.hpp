#ifndef BOT_HPP
#define BOT_HPP

#include "deck.hpp"
#include "chips.hpp"

class Bot {
    public:
        Bot();
        void setHand(std::pair<int,int>);
        void bet(int);
    private:
        Chip chips;
        std::pair<int,int> hand;
};

Bot::Bot(){}

void Bot::setHand(std::pair<int, int> deal){
    hand = deal;
    printHand(hand);
}

void Bot::bet(int b){
    chips.bet(b);
}

#endif // BOT_HPP
