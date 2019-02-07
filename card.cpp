//File Name: card.h
//
//Written by Owen Astrachan and Roger Priebe
// This class represents a playing card, i.e., "ace of spades"
// a Card is constructed from a rank (int in range 1..13)
// and a suit (Card::spades, Card::hearts, Card::diamonds,
// Card::clubs)
//
// Cards should be created by a Deck (see deck.h), a Deck returns
// good cards
// The function toString() converts a card to a string, e.g., to print
//
// Accessor functions include
//
// int GetRank()      -- returns 1, 2, ..., 13 for ace, two, ..., king
//
// bool SameSuitAs(c) -- returns true if same suit as Card c
//
// string suitString() -- returns "s", "h", "d" or "c"
//
// Note that the Ace is represented by 1 and the King by 13

//#ifndef _CARD_H
//#define _CARD_H

#include <iostream>
#include <string>
#include <sstream>
#include "card.h"

using namespace std;

//Card Constructor with no input parameters
//PreConditions: none
//creates a card object of the ace of spades
Card::Card(){
    myRank = 1;
    mySuit = Card::spades;
}

//Card Constructor with input parameters
//Preconditions: none
//creates card object with input rank and suit
Card::Card(int rank, Suit s){
    myRank = rank;
    mySuit = s;
}

//toString
//PreConditions: Card object
//returns a string of the value of the card
string Card::toString() const{
    string _suit = suitString(mySuit);
    string _rank = rankString(myRank);
    string value = _rank + _suit;
    return(value);
}

//sameSuitAs
//PreConditions: Card Object
//returns true if input card has same suit as caller card
bool Card::sameSuitAs(const Card& c) const{
    if (mySuit == c.mySuit)
        return true;
    else
        return false;
}

//getRank
//PreConditions: Card object
//returns rank of card as int
int  Card::getRank() const{
    return myRank;
}

//suitString
//Preconditions: Card object, suit variable
//returns string of suit as single letter
string Card::suitString(Suit s) const{
    if (s == Card::spades)
        return "s";
    if (s == Card::hearts)
        return "h";
    if (s == Card::clubs)
        return "c";
    if (s == Card::diamonds)
        return "d";
}

//rankString
//PreConditions: Card object
//returns rank of card as string
string Card::rankString(int r) const{
	switch(r){
		case 1:
			return ("A");
		case 11:
			return ("J");
		case 12:
			return ("Q");
		case 13:
			return ("K");
		default:
			stringstream ss;
			ss << r;
			return (ss.str());
	}
}

//operator ==
//PreConditions: Card object
//returns true if rank of both cards are equal
bool Card::operator ==(const Card& rhs) const{
    return (myRank == rhs.myRank);
}

//operator !=
//PreConditions: Card object
//returns true if rank of both cards are not equal
bool Card::operator !=(const Card& rhs) const{
    return (myRank != rhs.myRank);
}

//ostream <<
//PreConditions: iostream, Card object
//allows usage of cout for Card objects
ostream& operator << (ostream& out, const Card& c){
    out << c.toString();
    return out;
}