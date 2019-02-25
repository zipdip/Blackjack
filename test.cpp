#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <fstream>
#include <windows.h>
#include <string.h>
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;

int main(){
   /* Player tester("Tester", 1000);
    Card a(9, Card::spades);
    Card b(4, Card::spades);
    Card c(12, Card::spades);
    Card d(12, Card::spades);
    //tester.addCard(a);
    //tester.addCard(b);
    tester.addCard(c);
    tester.addCard(d);

    int score = tester.getSimScore();
    cout << "score = " << score << endl;*/
    Deck d;
    for (int i=0; i < d.size(); i++){
        cout << d.dealCard() << endl;
    }
}