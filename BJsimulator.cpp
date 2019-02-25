#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <fstream>
#include <windows.h>
#include <string.h>
#include <numeric>  
#include <math.h>                                                            
#include "card.h"
#include "player.h"
#include "deck.h"
#include "cardcounter.h"
#define NONE 0
#define TIE 1
#define PLAYER_W 2
#define DEALER_W 3
#define HALFSEC 500
#define MAX_HANDS 4
#define ITERATIONS 1000

using namespace std;

//Global Variables
vector<Player> players;
vector<double> bets;
int winner[MAX_HANDS];
bool firsthit[MAX_HANDS];
CardCounter counter;
double bankroll = 30000;
int minbet = 50;	
double wins = 0;
double losses = 0;
double ties = 0;
int hands = 0;
int current_iteration = 0;
int MIN_HOURS = 1000;
int MAX_HOURS = 0;
vector<int> hours;


string d = "d";
string s = "s";
string h = "h";
string r = "r";
string p = "p";

void processDecision(string &decision, bool &PLAYER_DECISION, double &bet, Player &player1, int i, Deck &d);
bool isNumber(string &s);
void dealHand(Deck &d, Player &p, int numCards);
string playerDecision(int &pHand, int &dCard, bool &firstHit, int decks);
bool getInsurance(int decks);
double Deviation(vector<int> v, double ave);


int main (){
	Player dealer("Dealer", 0);
	counter.turnOn();
	Deck d;
	int bankrupts = 0;

	cout << "--INPUTS--" << endl;
	cout << "Bankroll = " << bankroll << endl;
	cout << "Min Bet = " << minbet << endl;
	cout << "Spread is 1:12" << endl << endl;
	cout << "Caclulating..." << endl << endl;

	Player player1("Tester", bankroll);

	for (current_iteration = 0; current_iteration < ITERATIONS; current_iteration++){
	
		player1.removeCash(player1.showCash());
		player1.depositCash(bankroll);

		bool game = true;
		bool BJ;
		bool insurance;
		bool dealerbust;
		bool success = false;
		int rounds = 0;
		int handNum = 0;
		double bet;
		int decks;
		string decision;
		
		d.reset();
		d.shuffle();

		while (game){
			//cout << rounds << " " << player1.showCash();
			players.clear();
			bets.clear();
			for (int i=0; i < MAX_HANDS; i++){
				winner[i] = NONE;
				firsthit[i] = true;
			}
			if (d.size() < (78)){
				//Sleep(HALFSEC);
				//exit(0);
				counter.resetCount();
				d.reset();
				d.shuffle();
				//cout << "*********************************" << endl;
			}
			BJ = false;
			handNum ++;
			
			bet;
			decks = d.remainingDecks();
			int TC = counter.getTC(decks);
			//cout << " RC = " << counter.getRC() << " TC = ";
			if (TC > 0 && TC <=10)
				bet = minbet + (minbet * TC);
			else if (TC > 10)
				bet = minbet + (minbet * 11);
			else if (TC < -5)
				bet = 0;
			else
				bet = minbet;
			bets.push_back(bet);
			//cout << " B:" << bet;		
			if (bet > player1.showCash()){
				bet = player1.showCash();
			}
			
			dealHand(d, dealer, 2);
			counter.updateCount(dealer.showCardValue(0));
			dealHand(d, player1, 2);
			counter.updateCount(player1.showCardValue(0));
			counter.updateCount(player1.showCardValue(1));
			players.push_back(player1);
			
			//cout << "P: " << player1.showHand() << " ";
			//cout << "D: " << dealer.showHand() << " - ";

			insurance = false;
			if (dealer.getSimCard() == 11){
				insurance = getInsurance(d.remainingDecks());
			}

			if(dealer.getScore() == 21){
				if (insurance){
					player1.depositCash(bet*2);
				}
				if (player1.getScore() == 21){
					winner[0] = TIE;
				}
				else
					winner[0] = DEALER_W;	
			}
			else {
				if (insurance){
					player1.removeCash(bet);
				}
				if(player1.getScore() == 21){
					winner[0] = PLAYER_W;
					BJ = true;
				}	
			}	
			
			if (winner[0] == NONE){
				for(int i = 0; i < players.size(); i++){
					bool PLAYER_DECISION = true;

					do{
						int pHand = players[i].getSimScore();
						int dCard = dealer.getSimCard();
						decision = playerDecision(pHand, dCard, firsthit[i], d.remainingDecks());
						//cout << " " << decision;
						firsthit[i] = false;
						processDecision(decision, PLAYER_DECISION, bet, players[i], i, d);
						if (players[i].getScore() > 21){
							winner[i] = DEALER_W;
							PLAYER_DECISION = false;
						}
						if (decision == "p" || decision == "P")
							firsthit[i] = true;
					}while(PLAYER_DECISION);
				}

				dealerbust = false;
				for (int i=0; i < players.size(); i++){
					if (winner[i] == NONE){
						
						while (dealer.getScore() < 17){
							Card tempCard = d.dealCard();
							dealer.addCard(tempCard);
							counter.updateCount(tempCard.getRank());
							if (dealer.getScore() > 21){
								winner[i] = PLAYER_W;
								dealerbust = true;
							}
						}
						i = players.size();		//to break the loop
					}
				}

				for (int i=0; i < players.size(); i++){
					if (winner[i] == NONE){
						if (dealerbust)
							winner[i] = PLAYER_W;
						else if (players[i].getScore() < dealer.getScore())
							winner[i] = DEALER_W;
						else if (players[i].getScore() > dealer.getScore())
							winner[i] = PLAYER_W;
						else if (players[i].getScore() == dealer.getScore())
							winner[i] = TIE;
					}
				}
			}

			counter.updateCount(dealer.showCardValue(1));
			for (int i=0; i < players.size(); i++){
				hands ++;
				if (winner[i] == DEALER_W){
					player1.removeCash(bets[i]);
					losses ++;
					//cout << " - dealer wins";
				}
				
				if (winner[i] == PLAYER_W){
					if(BJ)
						bets[i] += (bets[i]/2);
					player1.depositCash(bets[i]);
					wins ++;
					//cout << " - player wins";
				}
				
				if (winner[i] == TIE){
					ties ++;
					//cout << " - tie";
					//cout << "Push." << endl;
				}
			//cout << player1.showCash();
			//cout << " P: " << players[i].showHand() << " ";
			}		
			//cout << "D: " << dealer.showHand();
			dealer.clearHand();
			player1.clearHand();
			//cout << endl;
			//cout << "RC is " << counter.getRC() << " and TC is " << counter.getTC(d.remainingDecks()) << endl;
			
			rounds ++;
			if (player1.showCash() >= bankroll*2){
				game = false;
				success = true;
			}
			if (player1.showCash() < minbet){
				bankrupts ++;
				game = false;
				success = false;
			}
							
		}
		if(success){
			hours.push_back(rounds / 100);
			if ( (rounds / 100) > MAX_HOURS)
				MAX_HOURS = rounds / 100;
			else if (rounds / 100 < MIN_HOURS)
				MIN_HOURS = rounds / 100;
		}

	}

	double average_hours = accumulate(hours.begin(), hours.end(), 0) / hours.size();
	double sdev = Deviation(hours, average_hours);
	double RoR = (double)bankrupts / ITERATIONS;
	cout << "--Success--" << endl;
	cout << "Average hours = " << average_hours << " hours at $" << bankroll / average_hours << " per hour" << endl;
	cout << "Max hours = " << MAX_HOURS << endl;
	cout << "Min hours = " << MIN_HOURS << endl;
	cout << "Standard Deviation = " << sdev << endl;
	cout << "Risk of Ruin = " << 100*RoR  << "%" << endl;
	//cout << "win rate = " << 100*wins/hands << "%" << endl;
	//cout << "push rate = " << 100*ties/hands << "%" << endl;
	//cout << "loss rate = " << 100*losses/hands << "%" << endl;


	
}

double Deviation(vector<int> v, double ave)
{
       double E=0;
       for(int i=0;i<v.size();i++)
               E+=(v[i] - ave)*(v[i] - ave);
       return sqrt(E / v.size());
}

void processDecision(string &decision, bool &PLAYER_DECISION, double &bet, Player &player1, int i, Deck &d){
	int intDecision;
	if (decision == "d")
		intDecision = 0;
	else if (decision == "r")
		intDecision = 1;
	else if (decision == "h")
		intDecision = 2;
	else if (decision == "s")
		intDecision = 3;
	else if (decision == "p")
		intDecision = 4;
	
	switch (intDecision)
	{
		case (0):{
			if(players[i].showCash() < bet*2)
				bets[i] = bets[i] / 2;
			bets[i] += bets[i];
			Card tempCard = d.dealCard();
			players[i].addCard(tempCard);
			counter.updateCount(tempCard.getRank());
			PLAYER_DECISION = false;
		}break;

		case (1):{
			bets[i] = bets[i] / 2;
			winner[i] = (DEALER_W);
			PLAYER_DECISION = false;
		}break;

		case (2):{
			Card tempCard = d.dealCard();
			players[i].addCard(tempCard);
			counter.updateCount(tempCard.getRank());
		}break;

		case (3):{
			PLAYER_DECISION = false;
		}break;

		case (4):{
			Card newCard = player1.showCardClass(1);
			player1.removeCard(newCard);
			Card tempCard = d.dealCard();
			player1.addCard(tempCard);
			counter.updateCount(tempCard.getRank());
			Player tempPlayer("temp", 0);
			tempPlayer.addCard(newCard);
			tempCard = d.dealCard();
			tempPlayer.addCard(tempCard);
			counter.updateCount(tempCard.getRank());
			players.push_back(tempPlayer);
			bets.push_back(bet);
			}break;
		
	
		default:{
			cout << "Error Invalid Decision - " << players[i].showHand() << endl;
			exit(0);
		}break;
	}
}

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

string playerDecision(int &pHand, int &dCard, bool &firstHit, int decks){
    string decision;
	int TC = counter.getTC(decks);
    if (pHand <= 8){
        decision = h;
    }
    else if (pHand == 9){
        decision = h;
        if(firstHit){
			if ( (dCard > 2 && dCard < 7) )
            	decision = d;
			else if ( (dCard == 2 && TC >= 1) || (dCard == 7 && TC >= 3) )
				decision = d;
		}
    }
    else if (pHand == 10){
        decision = h;
        if(firstHit){
			if (dCard < 10)
            	decision = d;
			else if (dCard == 10 && TC >= 4)
				decision = d;
		}
    }
    else if (pHand == 11){
        decision = h;
        if(firstHit){ 
			if (dCard != 11)
            	decision = d;
			else if (dCard == 11 && TC >= 1)
				decision = d;
		}
    }
    else if (pHand == 12){
        decision = s;
		if ( (dCard == 4 && TC < 0) || (dCard == 5 && TC < -2) || (dCard == 6 && TC < -1) || (dCard == 3 && TC < 2)
		 || (dCard == 2 && TC < 3) || dCard > 6)
			decision = h;
    }
    else if (pHand >= 13 && pHand < 15){
        decision = s;
		if(pHand == 13){
			if (dCard == 2 && TC < -1 )
				decision = h;
			else if (dCard == 3 && TC < -2)
				decision = h;
		}
		if(dCard >= 7){
            decision = h;
            if (firstHit){
				if (pHand == 14 && dCard == 10 && TC >= 3)
					decision = r;
            }
        }
    }

	else if (pHand == 15){
		if (firstHit){
			if (dCard == 10 && TC >= 0)
				decision = r;
			else if (dCard == 9 && TC >= 2)
				decision = r;
			else if (dCard == 11 && TC >= 1)
				decision = r;
			else if (dCard > 16)
				decision = h;
			else 
				decision = s;
		}
		else{
			if ( (dCard == 10 && TC >= 4) || dCard < 7)
				decision = s;
			else
				decision = h;
		}
	}

	else if (pHand == 16){
		
		if ( (dCard == 10 && TC > 0) || (dCard == 9 && TC > 5) || dCard < 7 )
			decision = s;
		else
			decision = h;
		if (firstHit){
			if (dCard >= 9 && dCard <= 11)
				decision = r;
		}
	}


        
    else if (pHand >= 17 && pHand <= 21){
        decision = s;
		if (firstHit){
        	if (pHand == 17 && dCard == 11) 
            	decision = r;
		}
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
    else if (pHand >= 118 && pHand < 120)
        decision = s;

	else if (pHand == 22 || pHand == 33 || pHand == 77){
		if (dCard < 8)
			decision = p;
		else
			decision = h;
	}

	else if (pHand == 44){
		if (dCard == 5 || dCard == 6)
			decision = p;
		else
			decision = h;
	}

	else if (pHand == 66){
		if (dCard < 7)
			decision = p;
		else
			decision = h;
	}

	else if (pHand == 88 || pHand == 1111){
		decision = p;
	}

	else if (pHand == 99){
		if (dCard < 7 || dCard == 8 || dCard == 9)
			decision = p;
		else
			decision = s;
	}
	else if (pHand == 110){
		decision = s;
		if (firstHit){
			if ( (dCard == 5 && TC >= 5) || (dCard == 6 && TC >= 4) )
				decision = p;
		}
	}

    else{
        decision = "INVALID";
		cout << "Invalid Decision - " << pHand << endl;
		exit(1);
	}
    
    return decision;
}

bool getInsurance(int decks){
	if (counter.getTC(decks) >= 3){
		//cout << " Insured ";
		return true;
	}
	return false;
}
