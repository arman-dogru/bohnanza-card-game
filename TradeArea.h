#ifndef C_PROJECT_TRADEAREA_H
#define C_PROJECT_TRADEAREA_H


#include <list>
#include "CardFactory.h"
#include <sstream>

using namespace std;


class TradeArea {
    list<Card*> tradeCardsList;
public:
    TradeArea() = default;//default constructor
    TradeArea(istream&, CardFactory*);//constructor
    TradeArea& operator+=(Card*);//add a card to the trade area
    bool legal(Card*); //check if a card is legal
    Card* trade(string); //remove a card from the trade area using its name
    int numCards() const; //return the number of cards in the trade area
    friend ostream& operator<<(ostream&, TradeArea&); //friend function to send all cards to ostream
    list<Card*>& getTradeCards(); //getter for the tradeCardsList
    void setTradeCardsList(const list<Card *> &tradeCardsList); //setter for the tradeCardsList
    int findCardIndex(string name); //find the index of a card in the trade area by name
};
#endif
