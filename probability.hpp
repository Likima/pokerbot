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

std::vector<double> experimental_odds(std::vector<int>& cards) {
    int handSize = cards.size();
    std::vector<double> odds;
    int straight_count = 0;
    int flush_count = 0;
    int total_count = 0;
    int runs = 0;
    double straight_percentage;
    double flush_percentage;

    while (runs < 500000) {
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

        runs++;
    }
    odds = {straight_percentage, flush_percentage};
    return odds;
}

#endif // PROBABILITY_HPP