♠ Blackjack Simulator ♥️

A simple command-line Blackjack game written in C++.

This project simulates a game of Blackjack using a standard 52-card deck, including deck creation, shuffling, card dealing, player decisions, dealer behavior, score calculation, and replaying the game.

Features

Creates a standard 52-card deck

Represents each card with:

Suit

Rank

Blackjack value

Randomly shuffles the deck

Converts the shuffled card array into a stack<card>

Deals cards to the player and dealer

Hides the dealer's first card until the dealer's turn

Allows the player to:

Hit — draw another card

Stand — keep the current hand

Automatically handles Aces as either 11 or 1 when necessary

Dealer continues drawing until reaching at least 17

Detects player and dealer busts

Determines a win, loss, or push

Allows the player to start another game

Includes simple terminal animations using delays and screen clearing

