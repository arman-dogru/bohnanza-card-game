#ifndef C_PROJECT_CARDFACTORY_H
#define C_PROJECT_CARDFACTORY_H

#include <vector>
#include <string>
#include <iostream>
#include <array>
#include "Deck.h"
#include "Card.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>

using namespace std;

class CardFactory {
private:
    CardFactory(); //constructor
    CardFactory(const CardFactory&); //copy constructor
    CardFactory& operator=(const CardFactory&); //copy constructor and assignment operator
    ~CardFactory(); //destructor
    Deck deck; //deck of cards
    Deck outDeck; //deck of cards that have been used
public:
    Deck getDeck(); //returns a shuffled deck
    static CardFactory* getCardFactory(); //returns a pointer to the card factory
    Card* getCard(const char&); //returns a card, and moves it to the outDeck
};

#endif