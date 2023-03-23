#include "TradeArea.h"
#include <algorithm>
#include <iterator>

using namespace std;

ostream& operator<<(ostream& os, TradeArea& tradeArea){
    for (auto& card : tradeArea.tradeCardsList) {
        card->print(os);
    }
    return os;
}

TradeArea::TradeArea(istream& is, CardFactory* cardFactory){ //load game constructor
    string line;
    getline(is, line);
    istringstream record(line);
    char cardChar;
    while (record.get(cardChar)) {
        if (cardChar != ' ')
            tradeCardsList.push_back(cardFactory->getCard(cardChar));
    }
}

TradeArea& TradeArea::operator+=(Card* card){ //add a card to the trade area
    if (card != nullptr)
        tradeCardsList.push_back(card);//add card to trade area
    return *this;//return trade area
}

bool TradeArea::legal(Card* card){
    if (card == nullptr)  //if the card is null
        return false;
    for (auto& xCard : tradeCardsList) {
        if ((xCard->getName()) == (card->getName())) //if the card is legal
            return true;
    }
    return false;
}

Card* TradeArea::trade(string name){
    auto i = find_if(tradeCardsList.begin(), tradeCardsList.end(), [name](Card* card) { return card->getName() == name; }); //find the card in the trade area
    if (i != tradeCardsList.end()) { //if the card is found
        Card* card = *i;//get the card
        tradeCardsList.erase(i);//remove the card from the trade area
        return card;
    }
}

int TradeArea::findCardIndex(string name){
    auto iter = find_if(tradeCardsList.begin(), tradeCardsList.end(), [name](Card* card) { return card->getName() == name; });
}

int TradeArea::numCards() const{return tradeCardsList.size();}
list<Card*>& TradeArea::getTradeCards(){return tradeCardsList;}