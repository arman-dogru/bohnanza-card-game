#include "Player.h"
#include "Card.h"
#include "CardFactory.h"
#include "Chain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

Player::Player(istream& is, CardFactory* cardFactory){
    //https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
    string line;
    getline(is, line);
    istringstream reader(line);
    int nameSize = 0;
    while (reader.get() != ':')
        ++nameSize; //we need to get the length of the name so we can read it in properly, the way we save the game is with a colon after the name
    reader.seekg(0); //we need to reset the stream to the beginning
    string tempString(nameSize, '\0'); //create a string of the correct length
    reader.read(&tempString[0], nameSize + 1); //read the name in
    name = tempString; //set the name to the string we just read in
    string coin;  reader >> coin; //read in the number of coins
    numCoins = stoi(coin); //convert the string to an int
    
    for (int i = 0; i < 3; ++i) {
        char cardChar;
        for (int i = 0; i < 2; ++i)
            is.get(cardChar); //we need to get the 2nd character of the line to see what type of chain it is
        if (cardChar == 'B') {chains[i] = new Chain<Blue>(is, cardFactory);}
        else if (cardChar == 'C') {chains[i] = new Chain<Chili>(is, cardFactory);}
        else if (cardChar == 'S') {chains[i] = new Chain<Stink>(is, cardFactory);}
        else if (cardChar == 'G') {chains[i] = new Chain<Green>(is, cardFactory);}
        else if (cardChar == 's') {chains[i] = new Chain<soy>(is, cardFactory);}
        else if (cardChar == 'b') {chains[i] = new Chain<black>(is, cardFactory);}
        else if (cardChar == 'R') {chains[i] = new Chain<Red>(is, cardFactory);}
        else if (cardChar == 'g') {chains[i] = new Chain<garden>(is, cardFactory);}
        if (i == 2) 
            isThereThirdChain = true; //if we are on the third chain, we can isThereThirdChain the fourth
        if (cardChar == '(') { //if the chain is empty
            chains[i] = new Chain_Base();
            if (is.get() == 'e') { //if the next character is e, then we are on the third chain and we can set isThereThirdChain to true
                if (i == 2) 
                    isThereThirdChain = true;
                else 
                    isThereThirdChain = false;
            }
            else 
                isThereThirdChain = false;
            getline(is, line);  // Go to next line
        }
    }
    hand = new Hand(is, cardFactory);//read in the hand
}

string Player::getName() const{return name;}

int Player::getNumCoins() const{return numCoins;}

Player& Player::operator+=(int coins){
    numCoins += coins;
    return *this;
}

int Player::getMaxNumChains() const {
    if (isThereThirdChain)
        return 3;
    return 2;
}

int Player::getNumChains() const{
    int size = 0;
    for (auto &card : chains) {
        if (!card->empty())
            ++size;
    }
    return size;
}

Chain_Base& Player::operator[](int i){
    if (i >= getMaxNumChains())
        throw exception();
    else
        return *(chains[i]);
}

void Player::buyThirdChain(){
    if (numCoins < 3)
        throw exception();
    numCoins -= 3;
    isThereThirdChain = true;
}

void Player::printHand(ostream& os, bool printAll){
    if (hand->top() == nullptr) {
        os << "You do not have enough cards!\n";
        return;
    }
    if (!printAll)
        os << hand->top()->getName();
    else
        os << *hand;
}

void Player::startNewChain(int i, const char& cardChar){
    delete chains[i]; //delete the old chain
    if (cardChar == 'B') {chains[i] = new Chain<Blue>();}
    else if (cardChar == 'C') {chains[i] = new Chain<Chili>();}
    else if (cardChar == 'S') {chains[i] = new Chain<Stink>();}
    else if (cardChar == 'G') {chains[i] = new Chain<Green>();}
    else if (cardChar == 's') {chains[i] = new Chain<soy>();}
    else if (cardChar == 'b') {chains[i] = new Chain<black>();}
    else if (cardChar == 'R') {chains[i] = new Chain<Red>();}
    else if (cardChar == 'g') {chains[i] = new Chain<garden>();}
    else chains[i] = new Chain_Base();
}

Hand* Player::getHand(){return hand;
}

Player::~Player(){ //destructor
    for (auto& chainPtr : chains) 	//delete all the chains
        delete chainPtr;
    delete hand; //delete the hand
}

ostream& operator<<(ostream& os, Player& player){ //print the player
    os << player.name << ": " << player.numCoins << " coins" << endl; //print the name and number of coins
    for (int i = 0; i < 3; ++i) { //print out all the chains
        if (i==2 && !player.isThereThirdChain)
            os << "-(there isn't a third chain)" << endl;
        else
            os << "-" << *(player.chains[i]) << endl;
    }
    return os;
}



void Player::addCard(Card* card){hand->addCard(card);}

void Player::addCoins(int coins){numCoins += coins;}

void Player::removeCoins(int coins){numCoins -= coins;}

//void Player::removeCard(Card* card){hand->removeCard(card);}

//void Player::removeCard(int i){hand->removeCard(i);}

void Player::removeChain(Chain_Base* chain){
    for (int i = 0; i < 3; ++i) {
        if (chains[i] == chain) {
            delete chains[i];
            chains[i] = new Chain_Base();
        }
    }
}

void Player::addChain(Chain_Base* chain){
    for (int i = 0; i < 3; ++i) {
        if (chains[i]->empty()) {
            delete chains[i];
            chains[i] = chain;
            return;
        }
    }
}

void Player::removeChain(int i){
    delete chains[i];
    chains[i] = new Chain_Base();
}