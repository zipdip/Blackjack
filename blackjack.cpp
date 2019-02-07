#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <fstream>
#include <unistd.h>
#include "card.h"
#include "player.h"
#include "deck.h"
#define NONE 0
#define TIE 1
#define PLAYER_W 2
#define DEALER_W 3
#define HALFSEC 500000

using namespace std;

void dealHand(Deck &d, Player &p, int numCards)
{
   for (int i=0; i < numCards; i++)
      p.addCard(d.dealCard());
}

int main (){
	Player dealer("Dealer", 0);
	string pname;
	int cash;
	
	cout << "Name: ";
	cin >> pname;
	cout << "Cash: ";
	cin >> cash;
	Player player1(pname, cash);
	cout << "Welcome " << player1.getName() << " to Zipper's blackjack casino!" << endl << endl;
	
	bool game = true;
	int handNum = 0;
	int bet;
	while (game){
		int winner = NONE;
		Deck d;
		d.shuffle();
		bool BJ = false;
		handNum ++;
		
		cout << "Round " << handNum << endl;
		cout << "Enter Bet: ";
		int bet;
		cin >> bet;
		while (bet > player1.showCash() || bet < 1){
			cout << "Not enough money to bet, try again: ";
			cin >> bet;
		}
		cout << "Bet is $" << bet << ". Let's play!" << endl << endl;
		
		dealHand(d, dealer, 2);
		dealHand(d, player1, 2);
		cout << "Dealer shows " << dealer.showCard(0) << endl;
		cout << "Your hand  - " << player1.showHand() << endl;
		
		if(dealer.getScore() == 21){
				usleep(4 * HALFSEC);
				cout << endl << "Dealer has blackjack" << endl;
			if (player1.getScore() == 21){
				usleep(4 * HALFSEC);
				cout << endl << "Player also has blackjack" << endl;
				winner = TIE;
			}
			else
				winner = DEALER_W;
			
		}
		
		else if(player1.getScore() == 21){
				usleep(4 * HALFSEC);
				cout << endl << "Player has blackjack" << endl;
			if (dealer.getScore() == 21)
				winner = TIE;
			else{
				winner = PLAYER_W;
				BJ = true;
			}
		}		
		
	
		string decision;
		while (decision != "s" && winner == NONE){
			cout << "'h' to hit, 's' to stay: ";
			cin >> decision;
			while (decision != "h" && decision != "s"){
				cout << "Invalid Input, try again: ";
				cin >> decision;
			}
			if (decision == "h"){
				Card newCard = d.dealCard();
				cout << newCard << endl;
				player1.addCard(newCard);
				cout << "Your hand - " << player1.showHand() << endl;
			}
			if (player1.getScore() > 21){
				winner = DEALER_W;
				cout << "Busted" << endl;
			}	
		}
		
		usleep(4 * HALFSEC);
		cout << "Dealer has " << dealer.showHand() << endl;
		bool dealerbust = false;
		while (dealer.getScore() < 17){
			dealer.addCard(d.dealCard());
			usleep(4 * HALFSEC);
			cout << "Dealer Hits" << endl;
			cout << dealer.showHand() << endl;
			if (dealer.getScore() > 21){
				if(player1.getScore() > 21)
					winner = TIE;
				else
					winner = PLAYER_W;
				usleep(4 * HALFSEC);
				cout << "Dealer Busts." << endl;
				dealerbust = true;
			}
		}
		if (!dealerbust){
			usleep(4 * HALFSEC);
			cout << "Dealer Stays." << endl;
		}
		usleep(4 * HALFSEC);
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
		
		usleep(4 * HALFSEC);
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
		
		usleep(4 * HALFSEC);
		cout << "Press 'd' to deal again or any other key to quit: ";
		string playagain;
		cin >> playagain;
		if (playagain != "d")
			game = false;
						
	}
}