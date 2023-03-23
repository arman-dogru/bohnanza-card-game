#pragma once
#ifndef C_PROJECT_CARD_H
#define C_PROJECT_CARD_H

#include <iostream>
#include <string>
#include <exception>

using namespace std;

class Card {
public:
	Card() = default; // default constructor
	virtual ~Card() = default; // virtual destructor
	Card(const Card&) = delete; // copy constructor
	Card& operator=(const Card&) = delete; // copy assignment operator  //Card card1 = card2;

	virtual int getCardsPerCoin(int coins) = 0; // returns the number of cards needed to earn the associated number of coins
	virtual string getName() const = 0; // returns the name of the card
	friend ostream& operator<<(ostream& os, Card& card); // friend function to print the card
    virtual void print(ostream& out) = 0; // prints the card
};

class Blue : public Card {
	friend class CardFactory; // friend class to access the private constructor
private:
    Blue(); // private constructor
public:
	int getCardsPerCoin(int coins) override; // returns the number of cards needed to earn the associated number of coins
	string getName() const override; // returns the name of the card
	void print(ostream& out) override; // prints the card to the ostream
};

//Exact same for all other subclasses of Card
class Chili : public Card {
	friend class CardFactory;
private:
    Chili();
public:
	int getCardsPerCoin(int coins) override;
	string getName() const override;
	void print(ostream& out) override;
};

class Stink : public Card {
	friend class CardFactory;
private:
    Stink();
public:
	int getCardsPerCoin(int coins) override;
	string getName() const override;
	void print(ostream& out) override;
};

class Green : public Card {
	friend class CardFactory;
private:
    Green();
public:
	int getCardsPerCoin(int coins) override;
	string getName() const override;
	void print(ostream& out) override;
};

class soy : public Card {
	friend class CardFactory;
private:
    soy();
public:
	int getCardsPerCoin(int coins) override;
	string getName() const override;
	void print(ostream& out) override;
};

class black : public Card {
	friend class CardFactory;
private:
    black();
public:
	int getCardsPerCoin(int coins) override;
	string getName() const override;
	void print(ostream& out) override;
};

class Red : public Card {
	friend class CardFactory;
private:
    Red();
public:
	int getCardsPerCoin(int coins) override;
	string getName() const override;
	void print(ostream& out) override;
};

class garden : public Card {
	friend class CardFactory;
private:
    garden();
public:
	int getCardsPerCoin(int coins) override;
	string getName() const override;
	void print(ostream& out) override;
};

class IllegalType : private exception { // exception class for illegal type of card being created
public:
	string showMessage(); // returns the error message
};
#endif