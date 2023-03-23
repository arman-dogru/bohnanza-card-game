#include <string>
#include <iostream>
#include "Table.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "Card.h"
#include <vector>

using namespace std;

int main() {
    //set up the game
    std::string player1Name, player2Name;
    Table table(player1Name, player2Name);

    //Does the player want to load the game
    cout << "Do you want to load a saved game? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        string filename;
        cout << "Enter the name of the file: ";
        cin >> filename;
        ifstream ldfile(filename);
        if (ldfile) {
            // Reconstruct the table from input file stream(SavedData.txt)
            table.~Table();
            new (&table) Table(ldfile, CardFactory::getCardFactory());
            cout << "> Saved data has been loaded.\n\n";
        }  else {
            // If no saved file exists, simply start a new game
            cout << "> No saved data was found! Starting a new game... \n\n";
            goto newGame;
        }
    } else {
        newGame:
        //create the players
        cout << "Enter the name of player 1: ";
        cin >> player1Name;
        cout << "Enter the name of player 2: ";
        cin >> player2Name;

        //create the table
        table.~Table();
        new (&table) Table(player1Name, player2Name);
        //get player 1 from table
        Player* player1 = table.getPlayer1();
        //get player 2 from table
        Player* player2 = table.getPlayer2();

        for (auto i = 0; i < 5; ++i) {
            *(player1->getHand()) += (table.getDeck()->draw());
            *(player2->getHand()) += (table.getDeck()->draw());
        }
        cout << "\nEach player has 5 cards\n";
    }

    string winner; //name of the winner
    Player* player1 = table.getPlayer1(); //get player 1 from table
    Player* player2 = table.getPlayer2(); //get player 2 from table
    TradeArea* tradeArea = table.getTradeArea();  // trade area on this table
    DiscardPile* discardPile = table.getDiscardPile();  // discard pile on this table
    Deck* deck = table.getDeck();   // Deck on this table

    while (!deck->empty()) { //new round
        cout << "Do you want to pause and save the game? (y/n): ";
        cin >> choice;
        if (choice == 'y') {
            string filename;
            cout << "Enter the name of the file: ";
            cin >> filename;
            ofstream out(filename);
            table.print(out);//save the game
            out.close();
            break; //break out of the loop, end the game
        }
        //create a vector of pointers to the players
        vector<Player*> players;
        players.push_back(player1);
        players.push_back(player2);

        for (auto& player : players) { //start the round
            cout << table << endl; //print the table
            cout << "> Player: " << player->getName() << " is chosing...\n";
            if (player->getMaxNumChains() == 2) {
                string answer;
                cout << "Purchase a third chain? (y/n): ";
                cin >> answer;

                // if wants to buy a third chain:
                if (answer == "y") {
                    if (player->getNumCoins() < 3) { cout << "You don't have enough coins, returning"; }
                    else {
                        player->buyThirdChain();
                        cout << "You have purchased a third chain!\n";
                    }
                }
            }

            *(player->getHand()) += (deck->draw()); //draw a card from the deck
            cout << "\n" << " You drew a card from the deck. \n";

            // if trade area is not empty
            if (tradeArea->numCards()) {// Add bean cards from tradeArea to chains or discard them

                string answer;
                cout << "Do you want to keep and chain the cards on the trade area? (y/n): \n";
                cin >> answer;
                while (!(answer == "y" || answer == "n")) {
                    do {
                        cout << "Invalid answer! Please enter 'y' or 'n':  ";
                        cin >> answer;
                    } while (!(answer == "y" || answer == "n"));
                }

                std::vector<std::string> tradingCards; //vector of cards to be traded
                for (auto& card : tradeArea->getTradeCards()) { //get the cards from the trade area
                    tradingCards.push_back(card->getName()); //add the cards to the vector
                }

                if (answer == "y") {
                    for (std::string& tradingCard : tradingCards) {
                        Card* tradeCard = tradeArea->trade(tradingCard);
                        // check if the played card can be tied to any of the chain
                        bool canChain = false;
                        for (auto i = 0; i < player->getMaxNumChains(); ++i) {
                            if ((*player)[i].empty()) 	player->startNewChain(i, tradingCard[0]);
                            try {
                                (*player)[i] += tradeCard;
                                canChain = true;  break;
                            }
                            catch (IllegalType) {
                                // If the card type doesn't match the chain type, do nothing;
                                // continue checking the next available chain
                            }
                        }
                        if (canChain) {
                            cout << "> The card: " << tradingCard << " has been successfully chained!!\n\n";
                        }
                        else {
                            cout << "> This card: " << tradingCard << " matches none of your chains, ";
                            cout << "and it will be discarded.\n\n";
                            (*discardPile) += tradeCard;
                        }
                    }
                    cout << "> Now you have the following chains: \n";
                    for (int i = 0; i < player->getMaxNumChains(); ++i) {
                        cout << "  [" << i << "]" << (*player)[i] << endl;
                    }
                    cout << endl;
                }
                    // if answer is "no"
                else {
                    // Discard all cards from trade area to the discard pile
                    for (auto& tc : tradingCards) {
                        (*discardPile) += tradeArea->trade(tc);
                    }
                    cout << "> All the cards from trade area have been discarded.\n\n";
                }
            }

            // Let player play the topmost card from Hand, and ask if wanting to repeat once
            bool repeat;  int numRepeat = 1;
            do {
                cout << "> Now you're about to play your topmost card: ";
                player->printHand(cout, false); cout << " from your hand...\n";
                // Play top-most card from hand; could be nullptr/
                if (player->getHand()->top()) {
                    Card* playedCard = player->getHand()->play();
                    // check if the played card can be tied to any of the chain
                    bool canChain = false;
                    for (int i = 0; i < player->getMaxNumChains(); ++i) {
                        if ((*player)[i].empty()) 	player->startNewChain(i, playedCard->getName()[0]);
                        try {
                            (*player)[i] += playedCard;
                            canChain = true;  break;
                        }
                        catch (IllegalType) {
                            // If the card type doesn't match the chain type, do nothing;
                            // continue checking the next available chain
                        }
                    }
                    // if no chains has the same name as the played card:
                    if (!canChain) {
                        string answer;
                        cout << "None of your chains can match\n";
                        cout << "Please enter an index of the chain you want to sell: ";
                        cin >> answer;
                        // let the player choose the chain he wants to sell:

                        //**************************************************************
                        int index;
                        askIndex:
                        try {
                            index = std::stoi(answer);  // May throw invalid_argument exception
                        }
                        catch (std::exception&) {
                            cout << "Please enter a valid index:  ";
                            cin >> answer;
                            goto askIndex;
                        }
                        startNewChain:
                        try {
                            int earnedCoin = (*player)[index].sell(); // may throw IndexOutOfBound exception
                            // Put all cards in chain into discard pile and shuffle discard pile
                            while (!(*player)[index].empty()) {
                                (*discardPile) += (*player)[index].removeCard();
                            }
                            discardPile->pileShuffle();
                            // Start a new chain with the given card type
                            player->startNewChain(index, playedCard->getName()[0]);
                            (*player)[index] += playedCard;
                            // Add to the earned coins
                            (*player) += earnedCoin;
                            cout << "> You sold your chain";
                            cout << "and earned " << earnedCoin << " coins!\n";
                        }
                        catch (exception) {
                            cout << "> Error" << endl;
                            cout << "> Please re-enter an index:  ";
                            goto startNewChain;
                        }
                        //**************************************************************

                        cout << "> And you have played your top card: " << playedCard->getName() << endl;
                    }  else  cout << "> You have chained the card: " << playedCard->getName() << "! \n";
                }  else cout << "> You got no cards in hand\n";
                // Print out the chains the player currently owns, and the topmost card on his hand
                cout << "> Your Chains: \n";
                for (int i = 0; i < player->getMaxNumChains(); ++i) {
                    cout << "  [" << i << "]" << (*player)[i] << endl;
                }
                cout << "> Now the top card on your hand: "; player->printHand(cout, false); cout << "\n\n";

                //Ask if player wants to repeat
                repeat = false;
                if (numRepeat) {
                    string answer;
                    cout << "Do you want to play your top card again?(y/n) ";
                    cin >> answer;
                    if (answer == "y") {
                        repeat = true;  --numRepeat;
                    }
                }
            } while (repeat);

            // Ask if the player decides to show his full hand and select an arbitrary card
            string answer;
            cout << "Show your full hand and discard an arbitrary card? (y/n): ";
            cin >> answer;
            while (!(answer == "y" || answer == "n")){
                do {
                    cout << "Invalid answer! Please enter (y/n):  ";
                    cin >> answer;
                } while (!(answer == "y" || answer == "n"));
            }

            // If yes, show player's full hand and let player choose the arbitrary card he/she wants to discard
            if (answer == "y") {
                cout << "Player's hand:" << player->getName() << endl;
                player->printHand(cout, true);
                cout << endl;

                Card* discarded = nullptr;
                cout << "Enter the index of the card you want to discard  ";
                input_valid_index:

                int index;
                askIndex2:
                try {
                    index = std::stoi(answer);  // May throw invalid_argument exception
                }
                catch (std::exception&) {
                    cout << "Please enter a valid index:  ";
                    cin >> answer;
                    goto askIndex2;
                }

                try {
                    discarded = (*(player->getHand()))[index];
                }
                catch (exception) {
                    cout << "> Error" << endl;
                    cout << "> Please re-enter an index:  ";
                    goto input_valid_index;
                }

                // Then place the card on the discard pile
                (*discardPile) += discarded;
                cout << "> You have discarded: " << discarded->getName() << ". \n";
            }

            // Draw 3 cards from deck and place them in the trade area
            for (int i = 0; i < 3; ++i)  (*tradeArea) += (deck->draw());
            cout << "\n" << "> 3 cards have been placed into the trade area.\n\n";

            // While top card of discard pile matches an existing card on the trade area
            while (tradeArea->legal(discardPile->top())) {
                // Removes the top card from pile and push it into the trade area
                Card* topDiscarded = discardPile->pickUp();
                (*tradeArea) += topDiscarded;
                cout << topDiscarded->getName();
                cout << " has been added to the trade area.\n\n";
            }

            // For all cards in the trade area(if non-empty), ask the player if he/she wants to chain the card
            if (tradeArea->numCards()) {
                do {
                    string answer;
                    cout << "\n> Trade area has the following cards: " << *tradeArea;
                    cout << "\n> Please enter the character of which card you'd like to chain, to cancel write 'n': ";
                    input_answer:
                    cin >> answer;
                    if (answer == "n") break;
                    else {  // If choose one of cards to chain
                        Card* card = nullptr;
                        if (answer[0] == 'B') card = tradeArea->trade("Blue");
                        else if (answer[0] == 'C') card = tradeArea->trade("Chili");
                        else if (answer[0] == 'S') card = tradeArea->trade("Stink");
                        else if (answer[0] == 'G') card = tradeArea->trade("Green");
                        else if (answer[0] == 's') card = tradeArea->trade("soy");
                        else if (answer[0] == 'b') card = tradeArea->trade("black");
                        else if (answer[0] == 'R') card = tradeArea->trade("Red");
                        else if (answer[0] == 'g') card = tradeArea->trade("garden");
                        else {
                            cout << "Please enter a valid character: ";
                            goto input_answer;
                        }
                        if (!card) {
                            cout << "Please enter your choice again: ";
                            goto input_answer;
                        }
                        else {
                            // check if the chosen card can be tied to any of the chain
                            bool chainFlag = false;
                            for (int i = 0; i < player->getMaxNumChains(); ++i) {
                                if ((*player)[i].empty()) 	player->startNewChain(i, card->getName()[0]);
                                try {
                                    (*player)[i] += card;
                                    chainFlag = true;  break;
                                }
                                catch (IllegalType) {
                                    // If the card type doesn't match the chain type, do nothing;
                                    // continue checking the next available chain
                                }
                            }
                            // if no chains has the same name as the played card:
                            if (!chainFlag) {
                                cout << "None of your chains matches this card!\n";
                                cout << "Select the chain you want to sell by entering the index of chain:  ";
                                // let the player choose the chain he wants to sell:
                                //****************************************************************************************************
                                int index;
                                askIndex3:
                                try {
                                    index = std::stoi(answer);  // May throw invalid_argument exception
                                }
                                catch (std::exception&) {
                                    cout << "Please enter a valid index:  ";
                                    cin >> answer;
                                    goto askIndex3;
                                }
                                startNewChain2:
                                try {
                                    int earnedCoin = (*player)[index].sell(); // may throw IndexOutOfBound exception
                                    // Put all cards in chain into discard pile and shuffle discard pile
                                    while (!(*player)[index].empty()) {
                                        (*discardPile) += (*player)[index].removeCard();
                                    }
                                    discardPile->pileShuffle();
                                    // Start a new chain with the given card type
                                    player->startNewChain(index, card->getName()[0]);
                                    (*player)[index] += card;
                                    // Add to the earned coins
                                    (*player) += earnedCoin;
                                    cout << "> You sold your chain";
                                    cout << "and earned " << earnedCoin << " coins!\n";
                                }
                                catch (exception) {
                                    cout << "> Error" << endl;
                                    cout << "> Please re-enter an index:  ";
                                    goto startNewChain2;
                                }
                                //****************************************************************************************************
                                cout << "> Played your topmost card: " << card->getName() << endl;
                            }
                            else {
                                cout << "> You have chained the card: " << card->getName() << "\n";
                                cout << "> Your chains are: " << endl;
                            }
                            for (int i = 0; i < player->getMaxNumChains(); ++i) {
                                cout << "  '" << i << "'" << (*player)[i] << endl;
                            }
                        }
                    }
                } while (tradeArea->numCards());
                cout << "> Ended chaining.\n\n";
            }

            // Player draws 2 cards from deck
            for (int i=0;i<2;++i)  *(player->getHand()) += (deck->draw());
            cout << "> The player have finished this turn. 2 Cards were drawn\n\n";
        }
    }

    cout << "\n\nGAME OVER" << endl;
    if (winner == "No one") {  // If 2 players have same number of coins
        cout << "It is a draw!" << endl;
    } else {
        cout << "The player: " << winner << " wins!" << endl;
    }
    return 0;
}
/***
            cout << "Do you want to play the topmost card from your hand? (y/n): ";
            cin >> choice;
            if (choice == 'y') {
                player->play();
                if (player->getChains().size() > 0) {
                    cout << "Do you want to play the topmost card from your hand? (y/n): ";
                    cin >> choice;
                    if (choice == 'y') {
                        player->play();
                    }
                }
            }
            cout << "Do you want to removeCard a card from your hand? (y/n): ";
            cin >> choice;
            if (choice == 'y') {
                cout << "Your hand: " << player->showHand() << endl;
                cout << "Enter the index of the card you want to removeCard: ";
                int index;
                cin >> index;
                player->discard(index);
            }
            player->draw(*deck);
            player->draw(*deck);
            player->draw(*deck);
            for (int i = 0; i < 3; i++) {
                player->buyCard(*tradeArea, 0);
            }
            while (discardPile->top()->getName() == tradeArea->top()->getName()) {
                tradeArea->push_back(discardPile->top());
                discardPile->pop_back();
            }
for (int i = 0; i < tradeArea->numCards(); i++) {
                cout << "Do you want to chain the " << tradeArea->top()->getName() << "? (y/n): ";
                cin >> choice;
                if (choice == 'y') {
                    player->buyCard(*tradeArea, 0);
                } else {
                    tradeArea->push_back(tradeArea->top());
                    tradeArea->pop_back();
                }
            }
            player->draw(*deck);
            player->draw(*deck);
        }
    }
    cout << *table << endl;
    if (player1->getCoins() > player2->getCoins()) {
        cout << player1->getName() << " wins!" << endl;
    } else if (player2->getCoins() > player1->getCoins()) {
        cout << player2->getName() << " wins!" << endl;
    } else {
        cout << "It's a tie!" << endl;
    }
    return 0;
}
 **/
