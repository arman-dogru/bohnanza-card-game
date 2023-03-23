#ifndef C_PROJECT_DISCARDPILE_H
#define C_PROJECT_DISCARDPILE_H

#include "CardFactory.h"
#include <vector>

using namespace std;

class DiscardPile {
private:
    vector<Card*> pile;
public:
    DiscardPile() = default; // default constructor
    DiscardPile(istream&, CardFactory*); // constructor that takes an input stream and a card factory
    DiscardPile& operator+=(Card*);// add a card to the discard pile, this function returns a reference to the discard pile
    Card* pickUp();// remove the top card from the discard pile and return it
    Card* top() const;// return the top card from the discard pile
    void print(ostream&);// print the discard pile to the output stream
    friend ostream& operator<<(ostream&, DiscardPile&);// print the top card of the discard pile to the output stream

    //Extra functions for ease of use
    bool empty() const; // is empty method
    void pileShuffle(); // to ensure cards are in random order
};

#endif