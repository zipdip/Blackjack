#include <vector>
#include <time.h>
#include <stdlib.h>
#include "deck.h"
using namespace std;

//Deck Constructor
//PreConditions: must include card class
//Creates a normal deck of 52 cards
Deck::Deck(){
    int i = 0;                          //position in deck
    Card::Suit s = Card::spades;
    for (i=1; i <= 13; i++){
        Card temp(i, s);
        myCards[i-1] = temp;
        myCards[52 + (i-1)] = temp;
        myCards[104 + (i-1)] = temp;
        myCards[156 + (i-1)] = temp;
        myCards[208 + (i-1)] = temp;
        myCards[260 + (i-1)] = temp;
        myCards[312 + (i-1)] = temp;
        myCards[364 + (i-1)] = temp;
    }
    s = Card::clubs;
    for (i=1; i <= 13; i++){
        Card temp(i, s);
        myCards[i+12] = temp;
        myCards[52 + (i+12)] = temp;
        myCards[104 + (i+12)] = temp;
        myCards[156 + (i+12)] = temp;
        myCards[208 + (i+12)] = temp;
        myCards[260 + (i+12)] = temp;
        myCards[312 + (i+12)] = temp;
        myCards[364 + (i+12)] = temp;
    }
    s = Card::hearts;
    for (i=1; i <= 13; i++){
        Card temp(i, s);
        myCards[i+25] = temp;
        myCards[52 + (i+25)] = temp;
        myCards[104 + (i+25)] = temp;
        myCards[156 + (i+25)] = temp;
        myCards[208 + (i+25)] = temp;
        myCards[260 + (i+25)] = temp;
        myCards[312 + (i+25)] = temp;
        myCards[364 + (i+25)] = temp;
    }
    s = Card::diamonds;
    for (i=1; i <= 13 ; i++){
        Card temp(i, s);
        myCards[i+38] = temp;
        myCards[52 + (i+38)] = temp;
        myCards[104 + (i+38)] = temp;
        myCards[156 + (i+38)] = temp;
        myCards[208 + (i+38)] = temp;
        myCards[260 + (i+38)] = temp;
        myCards[312 + (i+38)] = temp;
        myCards[364 + (i+38)] = temp;
    }
    myIndex = 0;
    srand(time(NULL));
}

void Deck::reset(){
    int i = 0;                          //position in deck
    Card::Suit s = Card::spades;
    for (i=1; i <= 13; i++){
        Card temp(i, s);
        myCards[i-1] = temp;
        myCards[52 + (i-1)] = temp;
        myCards[104 + (i-1)] = temp;
        myCards[156 + (i-1)] = temp;
        myCards[208 + (i-1)] = temp;
        myCards[260 + (i-1)] = temp;
        myCards[312 + (i-1)] = temp;
        myCards[364 + (i-1)] = temp;
    }
    s = Card::clubs;
    for (i=1; i <= 13; i++){
        Card temp(i, s);
        myCards[i+12] = temp;
        myCards[52 + (i+12)] = temp;
        myCards[104 + (i+12)] = temp;
        myCards[156 + (i+12)] = temp;
        myCards[208 + (i+12)] = temp;
        myCards[260 + (i+12)] = temp;
        myCards[312 + (i+12)] = temp;
        myCards[364 + (i+12)] = temp;
    }
    s = Card::hearts;
    for (i=1; i <= 13; i++){
        Card temp(i, s);
        myCards[i+25] = temp;
        myCards[52 + (i+25)] = temp;
        myCards[104 + (i+25)] = temp;
        myCards[156 + (i+25)] = temp;
        myCards[208 + (i+25)] = temp;
        myCards[260 + (i+25)] = temp;
        myCards[312 + (i+25)] = temp;
        myCards[364 + (i+25)] = temp;
    }
    s = Card::diamonds;
    for (i=1; i <= 13 ; i++){
        Card temp(i, s);
        myCards[i+38] = temp;
        myCards[52 + (i+38)] = temp;
        myCards[104 + (i+38)] = temp;
        myCards[156 + (i+38)] = temp;
        myCards[208 + (i+38)] = temp;
        myCards[260 + (i+38)] = temp;
        myCards[312 + (i+38)] = temp;
        myCards[364 + (i+38)] = temp;
    }
    myIndex = 0;
    srand(time(NULL));
}

//shuffle
//PreConditions: Deck object with at least 2 cards
//shuffles the deck
void Deck::shuffle(){
    vector<Card> temp;
    int i = 0;
    for (int p = myIndex; p < 52; p++){
        temp.push_back(myCards[p]);
    }
    for (int p = myIndex; p < 52; p++){
        int tempSize = temp.size();
        int randomNum = (rand() % tempSize);
        myCards[p] = temp[randomNum];
        temp.erase (temp.begin() + randomNum);
    }
    
}

//dealCard
//PreConditions: Deck object with at least 1 card remaining
//deals one card of the deck
Card Deck::dealCard(){
    Card dealt;
    if (myIndex < 52){
        myIndex++;
        dealt = myCards[myIndex-1];
    }
    return dealt;
}

//size
//PreConditions: Deck object
//returns current size of deck
int  Deck::size() const{
    return (52-myIndex);
}