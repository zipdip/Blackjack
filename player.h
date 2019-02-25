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
		double myCash;
		vector<Card> myHand;
		
	public:
		
		Player();
		Player(string name, int cash);
		
		string getName();
		double showCash();
		void removeCash(double cash);
		void depositCash(double cash);
		
		void addCard(Card c);
		void removeCard(Card c);
		void clearHand();
		string showCard(int i);
		int showCardValue(int i);
		string showHand();
		bool getStatus();
		int getScore();
		int getSimScore();
		int getSimCard();
		Card showCardClass(int i);
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

double Player::showCash(){
	return myCash;
}

void Player::removeCash(double cash){
	myCash -= cash;
	return;
}

void Player::depositCash(double cash){
	myCash += cash;
	return;
}

void Player::addCard(Card c){
	myHand.push_back(c);
	return;
}

void Player::removeCard(Card c){
	for (int i=0; i < myHand.size(); i++){
		if (myHand[i] == c)
			myHand.erase(myHand.begin() + i);
	}
}

string Player::showCard(int i){
	return (myHand[i].toString());
}

int Player::showCardValue(int i){
	return (myHand[i].getRank());
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

int Player::getSimScore(){
	int simScore = 0;
	if (myHand.size() == 2){
		if (myHand[0].getRank() == myHand[1].getRank()){
			simScore = myHand[0].getRank() * 10 + myHand[1].getRank();
			if (simScore == 55)
				simScore = 10;
			else if (simScore == 11)
				simScore = 1111;
		}
		if (myHand[0].getRank() > 10 && myHand[1].getRank() > 10)
			simScore = 110;
	}
	if (simScore == 0){
		int aces = 0;
		for (int i=0; i < myHand.size(); i++){
			if (myHand[i].getRank() == 1)
				aces ++;
			else{
				if (myHand[i].getRank() > 10)
					simScore += 10;
				else
					simScore += myHand[i].getRank();
			}
	}
		for (int i=0; i < aces; i++){
			if (simScore + 11 < 21)
				simScore += 110;
			else if (simScore + 11 == 21)
				simScore = 21;
			else 
				simScore += 1;
		}
		if (simScore == 120)
			simScore = 21;
	}
	return simScore;
}

int Player::getSimCard(){
	int simCard = 0;
	if (myHand[0].getRank() == 1)
		simCard = 11;
	else if (myHand[0].getRank() > 10)
		simCard = 10;
	else 
		simCard = myHand[0].getRank();
	return simCard;
}

Card Player::showCardClass(int i){
	return myHand[i];
}

#endif	
	
