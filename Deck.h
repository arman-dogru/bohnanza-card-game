#ifndef C_PROJECT_DECK_H
#define C_PROJECT_DECK_H

#include "Card.h"
#include <vector>
#include <sstream>
#include <iostream>

class Deck : public std::vector<Card*> { // Deck is a vector of Card pointers
public:
    Deck() = default;
    Deck(std::istream&, class CardFactory*); //constructor that is to be used during load game
    Card* draw(); //draws a card returns nullptr if deck is empty
    friend std::ostream& operator<<(std::ostream&, Deck&); //insertion operator to insert all the cards in the deck to an std::ostream

    //extra functions for ease of use
    void addCard(Card*); //adds a card to the deck
};

#endif