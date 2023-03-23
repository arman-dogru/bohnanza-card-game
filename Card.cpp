#include "Card.h"
using namespace std;

//Name getters and print functions

Red::Red() {}
Blue::Blue() {}
Green::Green() {}
Stink::Stink() {}
Chili::Chili() {}
soy::soy() {}
black::black() {}
garden::garden() {}
//generate destructor

ostream& operator<<(ostream &os, Card& card){
    card.print(os);
    return os;
}

//Blue
string Blue::getName() const {return "Blue";}
void Blue::print(ostream& out) {out << "B  ";}

//Chili
string Chili::getName() const {return "Chili";}
void Chili::print(ostream& out) {out << "C  ";}

//Green
string Stink::getName() const {return "Stink";}
void Stink::print(ostream& out) {out << "S  ";}

//Green
string Green::getName() const {return "Green";}
void Green::print(ostream& out) {out << "G  ";}

//soy
string soy::getName() const {return "soy";}
void soy::print(ostream& out) {out << "Y  ";}

//black
string black::getName() const {return "Black";}
void black::print(ostream& out) {out << "K  ";}

//Red
string Red::getName() const {return "Red";}
void Red::print(ostream& out) {out << "R  ";}

//garden
string garden::getName() const {return "Garden";}
void garden::print(ostream& out) {out << "G  ";}

//Get Cards Per Coin functions for each card type
int Blue::getCardsPerCoin(int coins) {
    if (coins == 1) {
        return 1;
    } else if (coins == 2) {
        return 3;
    } else if (coins == 3) {
        return 6;
    } else if (coins == 4) {
        return 10;
    } else {
        return 0;
    }
}

int Chili::getCardsPerCoin(int coins) {
    if (coins == 1) {
        return 3;
    } else if (coins == 2) {
        return 6;
    } else if (coins == 3) {
        return 8;
    } else if (coins == 4) {
        return 9;
    } else {
        return 0;
    }
}

int Stink::getCardsPerCoin(int coins) {
    if (coins == 1) {
        return 3;
    } else if (coins == 2) {
        return 5;
    } else if (coins == 3) {
        return 7;
    } else if (coins == 4) {
        return 8;
    } else {
        return 0;
    }
}

int Green::getCardsPerCoin(int coins) {
    if (coins == 1) {
        return 3;
    } else if (coins == 2) {
        return 5;
    } else if (coins == 3) {
        return 6;
    } else if (coins == 4) {
        return 7;
    } else {
        return 0;
    }
}

int soy::getCardsPerCoin(int coins) {
    if (coins == 1) {
        return 2;
    } else if (coins == 2) {
        return 4;
    } else if (coins == 3) {
        return 6;
    } else if (coins == 4) {
        return 7;
    } else {
        return 0;
    }
}

int black::getCardsPerCoin(int coins) {
    if (coins == 1) {
        return 2;
    } else if (coins == 2) {
        return 4;
    } else if (coins == 3) {
        return 6;
    } else if (coins == 4) {
        return 7;
    } else {
        return 0;
    }
}

int Red::getCardsPerCoin(int coins) {
    if (coins == 1) {
        return 2;
    } else if (coins == 2) {
        return 3;
    } else if (coins == 3) {
        return 4;
    } else if (coins == 4) {
        return 5;
    } else {
        return 0;
    }
}


int garden::getCardsPerCoin(int coins)  {
    if (coins == 2) {
        return 2;
    } else if (coins == 3) {
        return 3;
    } else {
        return 0;
    }
}