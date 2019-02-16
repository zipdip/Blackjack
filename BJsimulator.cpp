#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <fstream>
#include <windows.h>
#include <string.h>
#include "card.h"
#include "player.h"
#include "deck.h"
#define NONE 0
#define TIE 1
#define PLAYER_W 2
#define DEALER_W 3
#define HALFSEC 500

using namespace std;

bool isNumber(string &s){
	string::iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) 
		it++;
	return (!s.empty() && it == s.end());
}

void dealHand(Deck &d, Player &p, int numCards)
{
   for (int i=0; i < numCards; i++)
      p.addCard(d.dealCard());
}

string playerDecision(int &pHand, int &dCard, bool &firstHit){
    string decision;
    string d = "d";
    string s = "s";
    string h = "h";
    string r = "r";
    if (pHand <= 8){
        decision = h;
    }
    else if (pHand == 9){
        decision = h;
        if(firstHit && (dCard == 2 || dCard >= 7) )
            decision = d;
    }
    else if (pHand == 10){
        decision = h;
        if(firstHit && dCard <= 9 )
            decision = d;
    }
    else if (pHand == 11){
        decision = h;
        if(firstHit)
            decision = d;
    }
    else if (pHand == 12){
        decision = h;
        if(dCard >= 4 && dCard <= 6)
            decision = s;
    }
    else if (pHand >= 13 && pHand <= 16){
        decision = s;
        if(dCard >= 7){
            decision = h;
            if (firstHit){
                if ( (pHand == 15 && dCard > 10)||(pHand == 16 && dCard > 9))
                    decision = r;
            }
        }
    }
    else if (pHand >= 17 && pHand <= 21){
        decision = s;
        if ( (pHand == 17 && dCard == 11) && firstHit)
            decision = r;
    }
    else if (pHand >= 112 && pHand <= 116){
        decision = h;
        if (firstHit){
            if (dCard == 5 || dCard == 6)
                decision = d;
            if (pHand >= 114 && dCard == 4)
                decision = d;
            if (pHand == 116 && dCard == 3)
                decision = d;
        }
    }
    else if (pHand == 117){
        if (dCard >= 3 && dCard <= 6){
            if(firstHit)
                decision = d;
            else
                decision = s;
        }
        else if (dCard >= 9)
            decision = h;
        else 
            decision = s;
    }
    else if (pHand >= 118)
        decision = s;
    else 
        decision = "INVALID";
    
    return decision;
}

int main (){
	Player dealer("Dealer", 0);
	string pname;
	string scash;
	int cash;
	
	
	Player player1("Tester", 1000);
	//cout << "Welcome " << player1.getName() << " to Zipper's blackjack casino!" << endl << endl;
	
	bool game = true;
    int rounds = 100;
	int handNum = 0;
    Deck d;
    d.shuffle();
	while (game){
		int winner = NONE;
		if (d.size() < 26){
            d.reset();
            d.shuffle();
        }
		bool BJ = false;
		handNum ++;
		
		
		int bet = 20;		
		if (bet > player1.showCash()){
			cout << "Out of Cash" << endl;
            exit(0);
		}
		
		dealHand(d, dealer, 2);
		dealHand(d, player1, 2);
		
        cout << "P: " << player1.showHand() << " ";
        cout << "D: " << dealer.showHand() << " - ";

		if(dealer.getScore() == 21){
				//Sleep(4 * HALFSEC);
				//cout << endl << "Dealer has blackjack" << endl;
			if (player1.getScore() == 21){
				//Sleep(4 * HALFSEC);
				//cout << endl << "Player also has blackjack" << endl;
				winner = TIE;
			}
			else
				winner = DEALER_W;	
		}
		
		else if(player1.getScore() == 21){
			//Sleep(4 * HALFSEC);
			//cout << endl << "Player has blackjack" << endl;
			winner = PLAYER_W;
			BJ = true;
		}		
		
	
		string decision;
		bool firstHit = true;

		
        while (decision != "s" && winner == NONE){
            int pHand = player1.getSimScore();
            //cout << pHand << " ";
            int dCard = dealer.getSimCard();
            decision = playerDecision(pHand, dCard, firstHit);
            //cout << decision << " - ";
            if (decision == "INVALID"){
                cout << "Error: Invalid Decision" << endl;
                exit(0);
            }
			if (decision == "d"){
				if (!firstHit){
					cout << "Error: Attempt to DD not on the first hit" << endl;
                    exit(0);
                }
				if(player1.showCash() < bet*2)
					bet = bet / 2;
                bet += bet;
                //cout << "You choose to Double Down!" << endl;
                Card newCard = d.dealCard();
                //Sleep(4 * HALFSEC);
                //cout << "You get dealt " << newCard << endl;
                player1.addCard(newCard);
                //cout << "Your hand - " << player1.showHand() << endl;
                decision = "s";
			}
            if (decision == "r"){
                bet = bet / 2;
                winner = (DEALER_W);
            }
			if (decision == "h"){
				Card newCard = d.dealCard();
				//cout << newCard << endl;
				player1.addCard(newCard);
				//cout << "Your hand - " << player1.showHand() << endl;
				firstHit = false;
			}
			if (player1.getScore() > 21){
				winner = DEALER_W;
				//cout << "Busted" << endl;
			}
        }	
		//Sleep(4 * HALFSEC);
		//cout << "Dealer has " << dealer.showHand() << endl;
		bool dealerbust = false;
		while (dealer.getScore() < 17){
			dealer.addCard(d.dealCard());
			//Sleep(4 * HALFSEC);
			//cout << "Dealer Hits" << endl;
			//cout << dealer.showHand() << endl;
			if (dealer.getScore() > 21){
				if(player1.getScore() > 21 || decision == "r")
					winner = DEALER_W;
				else
					winner = PLAYER_W;
				//Sleep(4 * HALFSEC);
				//cout << "Dealer Busts." << endl;
				dealerbust = true;
            }
		}
		if (!dealerbust){
			//Sleep(4 * HALFSEC);
			//cout << "Dealer Stays." << endl;
		}
		//Sleep(4 * HALFSEC);
		//cout << endl;
		//cout << "Dealer's hand - " << dealer.showHand() << endl;
		//cout << "Your hand     - " << player1.showHand() << endl;
		if (winner == NONE){
			if (player1.getScore() < dealer.getScore())
				winner = DEALER_W;
			if (player1.getScore() > dealer.getScore())
				winner = PLAYER_W;
			if (player1.getScore() == dealer.getScore())
				winner = TIE;
		}
		
		//Sleep(4 * HALFSEC);
		if (winner == DEALER_W){
			//cout << "Dealer Wins!" << endl;
			player1.removeCash(bet);
		}
		
		if (winner == PLAYER_W){
			//cout << "You Win!" << endl;
			if(BJ)
				bet += (bet/2);
			player1.depositCash(bet);
		}
		
		if (winner == TIE){
			//cout << "Push." << endl;
		}
		
		cout << player1.showCash();
        cout << " P: " << player1.showHand() << " ";
        cout << "D: " << dealer.showHand() << endl;
		dealer.clearHand();
		player1.clearHand();
		
		Sleep(HALFSEC);
		rounds --;
		if (rounds <= 0)
			game = false;
						
	}
}