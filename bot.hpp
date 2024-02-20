#ifndef BOT_HPP
#define BOT_HPP
//NOTE: if increasing number of people playing, make sure to change sample size in probability.
#include "deck.hpp"
#include "chips.hpp"
#include "pokerlib.hpp"

#include <vector>

const std::vector<std::vector<int>> STRAIGHTS = {
    {1,2,3,4,5}, {2,3,4,5,6}, {3,4,5,6,7}, {4,5,6,7,8}, {5,6,7,8,9}, 
    {6,7,8,9,10}, {7,8,9,10,11}, {8,9,10,11,12}, {9,10,11,12,13}, {10,11,12,13,1}
};

void printVec(const std::vector<int>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

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

double experimental_straight(std::vector<int>& cards) {
    int straight_count = 0;
    int total_count = 0;
    int runs = 0;
    double percentage;

    while (runs < 500000) {
        std::vector<int> deck(52);
        std::iota(deck.begin(), deck.end(), 1);
        for (int card : cards) {
            deck.erase(std::remove(deck.begin(), deck.end(), card), deck.end());
        }
        std::shuffle(deck.begin(), deck.end(), std::random_device());

        std::vector<int> predefined_cards = cards;  // Use the provided cards

        for (int i = 0; i < 5; i++) {
            int card = deck.back();
            deck.pop_back();
            predefined_cards.push_back(card);
        }

        std::sort(predefined_cards.begin(), predefined_cards.end());

        for (int i = 0; i < predefined_cards.size(); i++) {
            predefined_cards[i] = predefined_cards[i] % 13;
        }
        std::sort(predefined_cards.begin(), predefined_cards.end());

        if (isStraight(predefined_cards)) {
            straight_count++;
        }

        total_count++;
        percentage = (static_cast<double>(straight_count) / total_count) * 100;

        runs++;
    }
    return percentage;
}

double probStraight(std::vector<int>& hand){
    std::vector<int> modHand = {3,4};
    std::vector<int> myVector = {0,0,0,0};
    std::vector<int> fact = {47,46,45,44};
    int index = 0; double event = 0; int prev; int size = hand.size();
    //for (int i = 0; i < hand.size(); i++) {
    //    modHand.push_back((hand[i] % 13)+1);
    //}
    std::sort(modHand.begin(), modHand.end());

    if (isStraight(modHand)) return 1.0;
    std::sort(modHand.begin(), modHand.end());
    modHand.erase(std::unique(modHand.begin(), modHand.end()), modHand.end());

    printVec(modHand);

    for(auto &v : STRAIGHTS){
        for(auto &n : modHand){
            for(auto &i : v){
                if(i == prev) continue;
                if(n==i){
                    index++;
                }
                prev = i;
            }
        }
        if(index == 0) continue;
        myVector[index-1]++;
        index = 0;
    }

    for(auto &i : myVector){
        std::cout<<i<<std::endl;
    }
    int i52c7 = nChooseK(52-size,7-size);
    for(int x = 0; x < myVector.size(); x++){
        int mult = 1;
        for(int n = 0; n < x+1; n++){
            mult*=fact[n];
        }
        std::cout<<"Mult: " << mult<<std::endl;
        event += myVector[x] * pow(4,4-x) * mult / i52c7;
        event -= myVector[x]-1 * pow(4,5-x) / i52c7;
        std::cout<<"Event: "<<event << std::endl;
    }
    std::cout<<event<<std::endl;
    return event;
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
    return 0.0;

}

#endif // BOT_HPP
