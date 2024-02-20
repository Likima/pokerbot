#ifndef DECK_HPP
#define DECK_HPP

struct cards{
    std::string symbol;
    std::string suit;
};

cards createCardByValue(int value) {
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
    cards card1 = createCardByValue(p.first);
    cards card2 = createCardByValue(p.second);
    // Print the hand
    std::cout << "Hand: " << card1.symbol << " of " << card1.suit
        << ", " << card2.symbol << " of " << card2.suit << std::endl;
}

void printCard(int p){
    cards card = createCardByValue(p);
    std::cout << card.symbol << " of " << card.suit << std::endl;
}


class Deck {
    public:
        Deck();
        void shuffle();
        void print();
        std::pair<int,int> deal();
        int draw();
        void reset();
    private:
        std::vector<int> cardvec;
};

Deck::Deck(){
    for(int i = 0; i < 52; i++){
        cardvec.push_back(i);
    }
}

void Deck::reset(){
    cardvec.clear();
    for(int i = 0; i < 52; i++){
        cardvec.push_back(i);
    }
    shuffle();
}

void Deck::shuffle(){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cardvec.begin(), cardvec.end(), g);
}

void Deck::print(){
    for(int i = 0; i < 52; i++){
        std::cout << cardvec[i] << " ";
    }
    std::cout << std::endl;
}

std::pair<int,int> Deck::deal(){
    std::pair<int,int> ret = std::make_pair(cardvec[0], cardvec[1]);
    cardvec.erase(cardvec.begin(), cardvec.begin()+2);
    return ret;
}

int Deck::draw(){
    int ret = cardvec.front();
    cardvec.erase(cardvec.begin());
    return ret;
}

#endif // DECK_HPP
