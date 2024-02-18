#ifndef BOT_HPP
#define BOT_HPP

#include "deck.hpp"
#include "chips.hpp"

class Bot {
    public:
        Bot(Deck d);
    private:
        Chip chips;
};

#endif // BOT_HPP
