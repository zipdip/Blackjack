#ifndef _CARDCOUNTER_H
#define _CARDCOUNTER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

class CardCounter{

    public:

        CardCounter();

        int getRC();
        int getTC(int decks);
        void updateCount(int rank);
        void resetCount();
        void turnOff();
        void turnOn();

    private:

        int RC;
        bool shouldCount;

};

CardCounter::CardCounter(){
    RC = 0;
    shouldCount = false;
}

int CardCounter::getRC(){
    return RC;
}

int CardCounter::getTC(int decks){
    int TC=0;
    if (shouldCount)
        TC = RC / decks;
    return (TC);
}

void CardCounter::updateCount(int rank){
    if (rank == 1 || rank >= 10)
        RC--;
    else if(rank > 1 && rank < 7)
        RC ++;
}

void CardCounter::resetCount(){
    RC = 0;
}

void CardCounter::turnOff(){
    shouldCount = false;
}

void CardCounter::turnOn(){
    shouldCount = true;
}

#endif