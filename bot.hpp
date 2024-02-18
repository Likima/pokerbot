#ifndef BOT_HPP
#define BOT_HPP
//NOTE: if increasing number of people playing, make sure to change sample size in probability.
#include "deck.hpp"
#include "chips.hpp"

#include <vector>

bool isStraight(std::vector<int>& hand){
    // Has yet to be tested.
    //Takes a sorted hand of unsuited cards and returns true if a straight is found
    if (hand.size() < 5)
        return false;
    int consecutiveCount = 1;
    for (size_t i = 1; i < hand.size(); ++i) {
        if (hand[i] == hand[i - 1] + 1) {
            consecutiveCount++;
            if (consecutiveCount == 5)
                return true; // Found a straight
        } else if (hand[i] != hand[i - 1]) {
            consecutiveCount = 1; // Reset consecutive count if there's a gap
        }
    }
    return false; // No straight found
}

float probStraight(std::vector<int>& hand){
    std::vector<int> modHand;
    for (int i = 0; i < hand.size(); i++) {
        modHand.push_back((hand[i] % 13)+1);
    }
    std::sort(modHand.begin(), modHand.end());

    if (isStraight(modHand)) return 1;
    

}

class Bot {
    public:
        Bot();
        void setHand(std::pair<int,int>);
        void bet(int);
        float analyzeHand(std::vector<int>);
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

float Bot::analyzeHand(std::vector<int> river = {}){

    std::vector<int> handAndRiver = river;
    handAndRiver.push_back(hand.first);
    handAndRiver.push_back(hand.second);

}

#endif // BOT_HPP
