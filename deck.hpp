#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

struct cards{
    std::string symbol;
    std::string suit;
};

cards intToCard(int value) {
    cards card;
    int cardVal = (value % 13);

    const std::string symbols[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    card.symbol = symbols[cardVal];

    const std::string suits[] = {"Diamonds", "Clubs", "Hearts", "Spades"};
    int suitIndex = value / 13;
    card.suit = suits[suitIndex];

    return card;
}

void printHand(std::pair<int,int> p){
    cards card1 = intToCard(p.first);
    cards card2 = intToCard(p.second);
    // Print the hand
    std::cout << "Hand: " << card1.symbol << " of " << card1.suit
        << ", " << card2.symbol << " of " << card2.suit << std::endl;
}

class Deck{
    public:
        Deck();
        void shuffle();
        void print();
        std::pair<int,int> deal();
        int draw();
    private:
        std::vector<int> cards;
};
Deck::Deck(){
    for(int i = 0; i < 52; i++){
        cards.push_back(i);
    }
}
void Deck::shuffle(){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}
void Deck::print(){
    for(int i = 0; i < 52; i++){
        std::cout << cards[i] << " ";
    }
    std::cout << std::endl;
}
std::pair<int,int> Deck::deal(){
    std::pair<int,int> ret = std::make_pair(cards[0], cards[1]);
    cards.erase(cards.begin(), cards.begin()+2);
    return ret;
}

int Deck::draw(){
    int ret = cards.front();
    cards.erase(cards.begin());
    return ret;
}