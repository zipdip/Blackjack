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

int main (){
	Player dealer("Dealer", 0);
	string pname;
	string scash;
	int cash;
	
	cout << "Name: ";
	cin >> pname;
	cout << "Cash: ";
	cin >> scash;
	while (!isNumber(scash)){
		cout << "Invalid Input. Enter a decimal number: ";
		cin >> scash;
	}
	cash = stoi(scash);
	Player player1(pname, cash);
	cout << "Welcome " << player1.getName() << " to Zipper's blackjack casino!" << endl << endl;
	
	bool game = true;
	int handNum = 0;
	while (game){
		int winner = NONE;
		Deck d;
		d.shuffle();
		bool BJ = false;
		handNum ++;
		
		cout << "Round " << handNum << endl;
		cout << "Enter Bet: ";
		string sbet;
		cin >> sbet;
		while (!isNumber(sbet)){
			cout << "Invalid Input. Enter a decimal number: ";
			cin >> sbet;
		}
		int bet = stoi(sbet);		
		while (bet > player1.showCash() || bet < 1){
			cout << "Not enough money to bet, try again: ";
			cin >> sbet;
			while (!isNumber(sbet)){
				cout << "Invalid Input. Enter a decimal number: ";
				cin >> sbet;
			}
			bet = stoi(sbet);
		}
		cout << "Bet is $" << bet << ". Let's play!" << endl << endl;
		
		dealHand(d, dealer, 2);
		dealHand(d, player1, 2);
		cout << "Dealer shows " << dealer.showCard(0) << endl;
		cout << "Your hand  - " << player1.showHand() << endl;
		
		if(dealer.getScore() == 21){
				Sleep(4 * HALFSEC);
				cout << endl << "Dealer has blackjack" << endl;
			if (player1.getScore() == 21){
				Sleep(4 * HALFSEC);
				cout << endl << "Player also has blackjack" << endl;
				winner = TIE;
			}
			else
				winner = DEALER_W;	
		}
		
		else if(player1.getScore() == 21){
			Sleep(4 * HALFSEC);
			cout << endl << "Player has blackjack" << endl;
			winner = PLAYER_W;
			BJ = true;
		}		
		
	
		string decision;
		bool firstHit = true;
		while (decision != "s" && winner == NONE){
			if (firstHit)
				cout << "'h' to hit, 'd' to double down, 's' to stay: ";
			else
				cout << "'h' to hit, 's' to stay: ";
			cin >> decision;
			while (decision != "h" && decision != "s" && decision != "d"){
				cout << "Invalid Input, try again: ";
				cin >> decision;
			}
			if (decision == "d"){
				if (!firstHit)
					cout << "Cannot Double Down after you have already hit, try again" << endl;
				if(player1.showCash() < bet*2)
					cout << "You do not have enough money to Double Down!" << endl;
				else{
					bet += bet;
					cout << "You choose to Double Down!" << endl;
					Card newCard = d.dealCard();
					Sleep(4 * HALFSEC);
					cout << "You get dealt " << newCard << endl;
					player1.addCard(newCard);
					cout << "Your hand - " << player1.showHand() << endl;
					decision = "s";
				}
			}
			if (decision == "h"){
				Card newCard = d.dealCard();
				cout << newCard << endl;
				player1.addCard(newCard);
				cout << "Your hand - " << player1.showHand() << endl;
				firstHit = false;
			}
			if (player1.getScore() > 21){
				winner = DEALER_W;
				cout << "Busted" << endl;
			}	
		}
		
		Sleep(4 * HALFSEC);
		cout << "Dealer has " << dealer.showHand() << endl;
		bool dealerbust = false;
		while (dealer.getScore() < 17){
			dealer.addCard(d.dealCard());
			Sleep(4 * HALFSEC);
			cout << "Dealer Hits" << endl;
			cout << dealer.showHand() << endl;
			if (dealer.getScore() > 21){
				if(player1.getScore() > 21)
					winner = DEALER_W;
				else
					winner = PLAYER_W;
				Sleep(4 * HALFSEC);
				cout << "Dealer Busts." << endl;
				dealerbust = true;
			}
		}
		if (!dealerbust){
			Sleep(4 * HALFSEC);
			cout << "Dealer Stays." << endl;
		}
		Sleep(4 * HALFSEC);
		cout << endl;
		cout << "Dealer's hand - " << dealer.showHand() << endl;
		cout << "Your hand     - " << player1.showHand() << endl;
		if (winner == NONE){
			if (player1.getScore() < dealer.getScore())
				winner = DEALER_W;
			if (player1.getScore() > dealer.getScore())
				winner = PLAYER_W;
			if (player1.getScore() == dealer.getScore())
				winner = TIE;
		}
		
		Sleep(4 * HALFSEC);
		if (winner == DEALER_W){
			cout << "Dealer Wins!" << endl;
			player1.removeCash(bet);
		}
		
		if (winner == PLAYER_W){
			cout << "You Win!" << endl;
			if(BJ)
				bet += (bet/2);
			player1.depositCash(bet);
		}
		
		if (winner == TIE){
			cout << "Push." << endl;
		}
		
		cout << "Your current Bank Account  is $" << player1.showCash() << endl << endl;
		dealer.clearHand();
		player1.clearHand();
		
		Sleep(4 * HALFSEC);
		cout << "Press 'd' to deal again or any other key to quit: ";
		string playagain;
		cin >> playagain;
		if (playagain != "d")
			game = false;
						
	}
}