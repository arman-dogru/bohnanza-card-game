#include "Deck.h"
#include "CardFactory.h"
#include <algorithm>
#include <sstream>

using namespace std;

//https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c //used this
Deck::Deck(istream &in, CardFactory *cardFactory) { //constructor that is to be used during load game
    Deck deck;
    string line;	getline(in, line);
    istringstream record(line);
    char cardChar;
    while (record.get(cardChar)) {
        if (cardChar != ' ')
            deck.push_back(cardFactory->getCard(cardChar));
    }
    new (&(*this)) Deck(deck);//placement new
}

Card* Deck::draw() { //draws a card returns nullptr if deck is empty
    if (empty())
        return nullptr;
    Card* card = this->back();
    this->pop_back();
    return card;
}

std::ostream& operator<<(ostream& os, Deck& deck) { //insertion operator to insert all the cards in the deck to an std::ostream
    for (auto& card : deck) {os << *card;}
    return os;
}

void Deck::addCard(Card* card) { //adds a card to the deck
    this->push_back(card);
}

