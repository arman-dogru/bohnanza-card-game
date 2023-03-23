#pragma once
#ifndef TABLE_H
#define TABLE_H

#include "Player.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include <iostream>
#include <string>
#include <array>

using namespace std;

class Table { // Table class, the main classes will be stored in this class(Card Factory, discardPile and deck)
    Player* player1;
    Player* player2;
    Deck* deck; // Deck pointer
    DiscardPile* discardPile; // DiscardPile pointer
    TradeArea* tradeArea; // TradeArea pointer
public:
    Table(string, string); // Constructor
    Table(istream&, CardFactory*); // load game constructor
    ~Table();// Destructor
    bool win(string&) const; // Check if the game is over
    void print(ostream&);
    friend ostream& operator<<(ostream&, Table&); // Print the table

    //Extra methods for ease of use(Getters and setters mostly)
    Player* getPlayer1();
    Player* getPlayer2();
    void setPlayers(array<Player*, 2> players);
    Deck* getDeck();
    void setDeck(Deck* deck);
    DiscardPile* getDiscardPile();
    void setDiscardPile(DiscardPile* discardPile);
    TradeArea* getTradeArea();
    void setTradeArea(TradeArea* tradeArea);
};

#endif