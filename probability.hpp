#ifndef PROBABILITY_HPP
#define PROBABILITY_HPP

#include <vector>
#include <random>
#include <algorithm>

bool isStraight(std::vector<int>& hand){
    // Has yet to be tested.
    // Takes a sorted hand of unsuited cards and returns true if a straight is found
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

bool isFlush(std::vector<int>& hand){
    // Takes a hand of unsuited cards and returns true if a flush is found
    if (hand.size() < 5)
        return false;
    std::vector<int> suits(4, 0);
    for (int card : hand) {
        suits[card / 13]++;
    }
    for (int count : suits) {
        if (count >= 5)
            return true; // Found a flush
    }
    return false; // No flush found
}

bool isStraightFlush(std::vector<int>& hand){
    if(!isFlush(hand))
        return false;
    std::vector<int> modulusCards;
    for (int card : hand) {
        modulusCards.push_back(card % 13);
    }
    if(!isStraight(modulusCards))
        return false;
    return true;
}

bool isRoyalFlush(std::vector<int>& hand){
    // Takes a hand of unsuited cards and returns true if a royal flush is found
    std::vector<int> modulusCards;
    for (int card : hand) {
        modulusCards.push_back(card % 13);
    }
    if (hand.size() < 5)
        return false;
    std::vector<int> suits(4, 0);
    for (int card : hand) {
        suits[card / 13]++;
    }
    for (int suit = 0; suit < 4; suit++) {
        if (suits[suit] >= 5) {
            std::vector<int> royalFlushCards = {9, 10, 11, 12, 0}; // Cards for a royal flush (10, J, Q, K, A)
            for (int card : royalFlushCards) {
                if (std::find(modulusCards.begin(), modulusCards.end(), suit * 13 + card) == modulusCards.end()) {
                    return false; // Not a royal flush
                }
            }
            return true; // Found a royal flush
        }
    }
    return false; // No royal flush found
}

void saveScoresToFile(const std::vector<double>& odds, int numTests) {
    std::ofstream file("saved_scores.txt");
    if (file.is_open()) {
        file << "Number of tests run: " << numTests << std::endl;
        file << "Straight Percentage: " << odds[0] << std::endl;
        file << "Flush Percentage: " << odds[1] << std::endl;
        file << "Royal Flush Percentage: " << odds[2] << std::endl;
        file << "Straight Flush Percentage: " << odds[3] << std::endl;
        file.close();
    }
}


std::vector<double> experimental_odds(std::vector<int>& cards) {
    cards.clear(); //for making a large test file.
    int handSize = cards.size();
    std::vector<double> odds;
    int straight_count = 0;
    int flush_count = 0;
    int total_count = 0;
    int royal_flush_count = 0;
    int straight_flush_count = 0;
    int runs = 0;
    double straight_percentage;
    double flush_percentage;
    double royal_flush_percentage;
    double straight_flush_percentage;

    while (runs < 5000000) {
        std::vector<int> deck(52);
        std::iota(deck.begin(), deck.end(), 1);
        for (int card : cards) {
            deck.erase(std::remove(deck.begin(), deck.end(), card), deck.end());
        }
        std::shuffle(deck.begin(), deck.end(), std::random_device());

        std::vector<int> predefined_cards = cards;  // Use the provided cards

        for (int i = 0; i < 7-handSize; i++) {
            int card = deck.back();
            deck.pop_back();
            predefined_cards.push_back(card);
        }

        std::sort(predefined_cards.begin(), predefined_cards.end());

        if (isFlush(predefined_cards)) {
            flush_count++;
        }

        if (isRoyalFlush(predefined_cards)){
            flush_count--; straight_count--;
            royal_flush_count++;
        }

        if (isStraightFlush(predefined_cards)){
            flush_count--; straight_count--;
            straight_flush_count++;   
        }

        for (int i = 0; i < predefined_cards.size(); i++) {
            predefined_cards[i] = predefined_cards[i] % 13;
        }

        std::sort(predefined_cards.begin(), predefined_cards.end());

        if (isStraight(predefined_cards)) {
            straight_count++;
        }

        total_count++;
        straight_percentage = (static_cast<double>(straight_count) / total_count);
        flush_percentage = (static_cast<double>(flush_count) / total_count);
        royal_flush_percentage = (static_cast<double>(royal_flush_count) / total_count);
        straight_flush_percentage = (static_cast<double>(straight_flush_count) / total_count);
        runs++;
    }
    odds = {straight_percentage, flush_percentage, royal_flush_percentage, straight_flush_percentage};
    saveScoresToFile(odds, runs);
    return odds;
}

#endif // PROBABILITY_HPP