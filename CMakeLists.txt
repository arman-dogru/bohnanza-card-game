cmake_minimum_required(VERSION 3.24)
project(C___Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(C___Project
        CardFactory.cpp
        CardFactory.h
        Chain.h
        Deck.cpp
        Deck.h
        DiscardPile.cpp
        DiscardPile.h
        Card.cpp
        Card.h
        Hand.cpp
        Hand.h
        main.cpp
        Player.cpp
        Player.h
        Table.cpp
        Table.h
        TradeArea.cpp
        TradeArea.h)
