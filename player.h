#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>
#include <string>
#include <vector>


#include "card.h"
using namespace std;

class Player
{
	private:
		
		string myName;
		int myCash;
		vector<Card> myHand;
		
	public:
		
		Player();
		Player(string name, int cash);
		
		string getName();
		int showCash();
		void removeCash(int cash);
		void depositCash(int cash);
		
		void addCard(Card c);
		void clearHand();
		string showCard(int i);
		string showHand();
		bool getStatus();
		int getScore();
};

Player::Player(){
	myName = "Unknown";
	myCash = 0;
}

Player::Player(string name, int cash){
	myName = name;
	myCash = cash;
}

string Player::getName(){
	return myName;
}

int Player::showCash(){
	return myCash;
}

void Player::removeCash(int cash){
	myCash -= cash;
	return;
}

void Player::depositCash(int cash){
	myCash += cash;
	return;
}

void Player::addCard(Card c){
	myHand.push_back(c);
	return;
}

string Player::showCard(int i){
	return (myHand[i].toString());
}

void Player::clearHand(){
	myHand.clear();
}

string Player::showHand(){
	string result;
	for (int i=0; i < myHand.size(); i++){
		result += myHand[i].toString();
		result += " ";
	}
	return result;
}

bool Player::getStatus(){
	int score = 0;
	for (int i=0; i < myHand.size(); i++){
		if (myHand[i].getRank() > 10)
			score += 10;
		else
			score += myHand[i].getRank();
	}
	return (score <= 21);
}

int Player::getScore(){
	int aces = 0;
	int score = 0;
	for (int i=0; i < myHand.size(); i++){
		if (myHand[i].getRank() == 1)
			aces ++;
		else{
			if (myHand[i].getRank() > 10)
				score += 10;
			else
				score += myHand[i].getRank();
		}
	}
	for (int i=0; i < aces; i++){
		if (score + 11 <= 21)
			score += 11;
		else
			score += 1;
	}
	return score;
}
#endif	
	
