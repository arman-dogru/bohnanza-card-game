#include "Hand.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>


using namespace std;

Hand::Hand(istream& is, CardFactory* cardFactory){
    string line;
    getline(is, line);
    istringstream handLine(line);
    handLine >> line;
    char cardChar;
    while (handLine.get(cardChar)) {
        if (cardChar != ' ')
            handCards.push(cardFactory->getCard(cardChar));
    }
}

Hand& Hand::operator+=(Card* card){ // add card to hand
    if (card != nullptr) // If the card is  null
        handCards.push(card);
    return *this;
}

Card* Hand::play(){
    if (handCards.empty()) //exit condition
        return nullptr;
    Card* playedCard = handCards.front();
    handCards.pop();
    return playedCard;
}

Card* Hand::top() const{
    if (handCards.empty()) //exit condition
        return nullptr;
    return handCards.front();
}

Card* Hand::operator[](int index){ // since the hand is a queue we need to form temp vectors to store and edit the hand
    queue<Card*> tempQueue;
    Card* discardedCard;
    int s = handCards.size();
    int cnt = 0;
    while (!handCards.empty()) {
        if (cnt == index) {
            tempQueue.push(handCards.front());
            handCards.pop();
            break;
        }
        tempQueue.push(handCards.front());
        handCards.pop();
        cnt++;
    }
    if (handCards.empty()) {
        cout << "element not found!!" << endl;
        while (!tempQueue.empty()) {
            handCards.push(tempQueue.front());
            tempQueue.pop();
        }
    }
    else {
        discardedCard = handCards.front();
        handCards.pop();
        while (!tempQueue.empty()) {
            handCards.push(tempQueue.front());
            tempQueue.pop();
        }
        int k = s - cnt - 1;
        while (k--) {
            auto card = handCards.front();
            handCards.pop();
            handCards.push(card);
        }
    }
    return discardedCard;
}

ostream& operator<<(ostream& os, Hand& hand) {
    vector<Card*> tempVector;

    if (hand.handCards.empty()) {
        os << "Hand is empty" << endl;
        return os;
    }

    while (!hand.handCards.empty()) {
        tempVector.emplace_back(move(hand.handCards.front()));
        hand.handCards.pop();
    }

    for (auto card : tempVector) {
        card->print(os);
        hand.handCards.push(card);
    }
    return os;
}

Card* Hand::removeCard() {
    Card* card = handCards.front();
    handCards.pop();
    return card;
}

Card* Hand::getCard(int index) {
    vector<Card*> tempVec;
    while (!handCards.empty()) {
        tempVec.emplace_back(move(handCards.front()));
        handCards.pop();
    }
    Card* card = tempVec[index];
    for (auto c : tempVec) {
        handCards.push(c);
    }
    return card;
}

void Hand::printHand() {
    vector<Card*> tempHand;
    while (!handCards.empty()) {
        tempHand.emplace_back(move(handCards.front()));
        handCards.pop();
    }
    for (auto c : tempHand) {
        c->print(cout);
        handCards.push(c);
    }
}

const queue<Card *> &Hand::getHandCards() const {return handCards;}
void Hand::setHandCards(const queue<Card *> &handCards) {Hand::handCards = handCards;}
bool Hand::isEmpty() const {return handCards.empty();}
void Hand::addCard(Card* card) {handCards.push(card);}