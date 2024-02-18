#include <vector>

class Chip {
public:
    Chip();
    int bet(int);
private:
    std::vector<std::pair<int, int>> chips;
    int total;
};

Chip::Chip() : chips {
    {20, 1},
    {20, 5},
    {10, 10},
    {5, 25},
    {5, 100}
} {total = 845;}

int Chip::bet(int money){
    if(money > total)
        return -1;
    
    int remaining = money;
    std::vector<std::pair<int, int>> betChips;
    
    for(auto it = chips.rbegin(); it != chips.rend(); ++it){
        int chipValue = it->first;
        int chipCount = it->second;
        
        int numChipsToBet = remaining / chipValue;
        if(numChipsToBet > chipCount)
            numChipsToBet = chipCount;
        
        remaining -= numChipsToBet * chipValue;
        betChips.push_back({chipValue, numChipsToBet});
        
        if(remaining == 0)
            break;
    }
    
    if(remaining > 0)
        return -1; // Not enough chips to cover the bet
    
    // Update the chip counts
    for(auto& betChip : betChips){
        int chipValue = betChip.first;
        int numChipsToBet = betChip.second;
        
        for(auto& chip : chips){
            if(chip.first == chipValue){
                chip.second -= numChipsToBet;
                break;
            }
        }
    }
    
    total -= money;
    return 0; // Bet successful
}


/*
Chip Distributions
White(1) - 20 chips
Red(5) - 20 chips
Blue(10) - 10 chips
Green(25) - 5 chips
Black(100) - 5 chips
*/