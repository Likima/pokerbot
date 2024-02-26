#ifndef BOT_HPP
#define BOT_HPP
//NOTE: if increasing number of people playing, make sure to change sample size in probability.

const std::vector<std::vector<int>> STRAIGHTS = {
    {1,2,3,4,5}, {2,3,4,5,6}, {3,4,5,6,7}, {4,5,6,7,8}, {5,6,7,8,9}, 
    {6,7,8,9,10}, {7,8,9,10,11}, {8,9,10,11,12}, {9,10,11,12,13}, {10,11,12,13,1}
};

class Bot {
    public:
        Bot();
        void setHand(std::pair<int,int>);
        void appendHand(int);
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
    //analyzes 100k hands and returns a scaled score on how good the said hand is.
    //experimental_odds returns a vector of probabilities.
    
    std::vector<int> a = {9,10,11,12,0};
    std::vector<double> probabilities;
    std::vector<int> handAndRiver = river;
    handAndRiver.push_back(hand.first);
    handAndRiver.push_back(hand.second);

    std::cout<<"My hand is: ";
    printVec(handAndRiver);
    
    probabilities = experimental_odds(handAndRiver);
    
    std::cout<<"The probability I get a straight is: " << probabilities[0]*100 <<"%"<<std::endl;
    std::cout<<"The probability I get a flush is: " << probabilities[1]*100 <<"%"<<std::endl;
    std::cout<<"The probability I get a ROYAL flush is: " << probabilities[2]*100 <<"%"<<std::endl;
    std::cout<<"The probability I get a STRAIGHT flush is: " << probabilities[3]*100 <<"%"<<std::endl;

    return 0.0;

}

#endif // BOT_HPP
