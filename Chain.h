#ifndef C_PROJECT_CHAIN_H
#define C_PROJECT_CHAIN_H

#include "CardFactory.h"
#include <vector>
#include <sstream>

using namespace std;

class Chain_Base {
protected:
    virtual void printChain(ostream& os) const { os << "!the Chain is empty"; } //this method will be overridden in the derived classes
public:
    Chain_Base() = default; //default constructor
    virtual ~Chain_Base() = default; //this is a virtual destructor
    virtual Chain_Base& operator+=(Card*) { return *this; } // Accesses to derived classes
    virtual int sell() { return 0; } //There is nothing to sell
    virtual bool empty() const { return true; } //It is always empty
    virtual Card* removeCard() { return nullptr; } //nothing to remove

    friend ostream& operator<<(ostream& os, const Chain_Base& cb) { //this is the insertion operator
        cb.printChain(os);
        return os;
    }
};

template<typename T>
class Chain: public Chain_Base {
    vector<T*> cardsVector;
protected:
    virtual void printChain(ostream& os) const override; //prints all cards in the chain
public:
    Chain() = default;
    Chain(istream&, CardFactory*);
    Chain_Base& operator+=(Card*) override; //adds a card to the chain and returns a reference to the chain
    int sell() override; //Returns the number of coins using getCardsPerCoin()
    friend ostream& operator<<(ostream& os, Chain<T>& chain)//prints the chain using the insertion operator
    {
        chain.printChain(os);
        return os;
    }

    //For ease of programming in the main.cpp
    T* getCard(int index) { return cardsVector[index]; } //returns the card at the given index
    bool empty() const override { return cardsVector.empty(); } //checks if the chain is empty
    Card* removeCard() override; //removes the top card from the chain
    int size() { return cardsVector.size(); } //returns the size of the chain
};

template<typename T>
void Chain<T>::printChain(ostream& os) const
{
    Card* topCard = dynamic_cast<Card*>(cardsVector.front());
    os << topCard->getName() << " ";
    for (auto card : cardsVector) {card->print(os);}
}

//This is the constructor which accepts an istream and reconstructs the chain from file when a game is resumed.
template<typename T>
Chain<T>::Chain(istream& is, CardFactory* factory)
{
    //move the indicator to the next line
    string line;
    getline(is, line);
    istringstream chainLine(line);
    char ch;
    while (chainLine.get(ch)) {
        T* card = dynamic_cast<T*>(factory->getCard(ch));
        if (card && ch != ' ')  cardsVector.push_back(card);
    }
}

//adds a card to the chain and returns a reference to the chain
template<typename T>
Chain_Base& Chain<T>::operator+=(Card* card)
{
    T* newCard = dynamic_cast<T*>(card);
    if (newCard) cardsVector.push_back(newCard);
    else throw IllegalType();
    return *this;
}

//Returns the number of coins using getCardsPerCoin()
template<typename T>
int Chain<T>::sell()
{
    int numCards = cardsVector.size();
    // If chain is empty, simply return 0
    if (cardsVector.empty()) return 0;
    else {
        int coins= 1; //coins to be returned
        Card* topCard = dynamic_cast<Card*>(cardsVector.front());
        if (numCards < topCard->getCardsPerCoin(coins))
            return 0;
        while (numCards > topCard->getCardsPerCoin(coins)) {
            if (numCards >= topCard->getCardsPerCoin(coins + 1))
                ++coins;
            else break;
        }
        return coins;
    }
}

template<typename T>
Card* Chain<T>::removeCard()
{
    if (cardsVector.empty()) return nullptr;
    else {
        Card* card = cardsVector.back();
        cardsVector.pop_back();
        return card;
    }
}
#endif
