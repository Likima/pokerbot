#ifndef BOT_HPP
#define BOT_HPP
//NOTE: if increasing number of people playing, make sure to change sample size in probability.

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
    std::cout<<"BOTS HAND: ";
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
