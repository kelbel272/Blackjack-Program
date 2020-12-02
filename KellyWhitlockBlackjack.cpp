/*Create a Blackjack (21) game. 
Your version of the game will imagine only a SINGLE suit of cards,
so 13 unique cards, {2,3,4,5,6,7,8,9,10,J,Q,K,A}.

{1 (A), 2,3,4,5,6,7,8,9,10, 11(J), 12(Q), 13(K)}
Upon starting, you will be given two cards from the set, non-repeating. 

Your program MUST then tell you the odds of receiving a beneficial card 
(that would put your value at 21 or less), and the odds of receiving a 
detrimental card (that would put your value over 21). 

Recall that the J, Q, and K cards are worth ‘10’ points, 
the A card can be worth either ‘1’ or ‘11’ points, and the other cards are worth their numerical values.
*/

#include <iostream>
#include <random>
#include <ctime>

void addTotal(int firstCard, int secondCard);
bool checkAce(int card);
bool checkFace(int card);
void displayCard(int card);
void Odds(int total, int firstCard, int secondCard);
void thirdTotal(int total, int thirdCard);

using namespace std;

int total = 0;												 //Total of cards starts at 0
int cards[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 }; // {1 (A), 2,3,4,5,6,7,8,9,10, 11(J), 12(Q), 13(K)}

int main() {

	int firstCard;		//First card drawn randomly 
	int secondCard;		//Second card drawn randomly 
	int thirdCard;		//Third card drawn randomly 

	//Display program name 
	cout << "Blackjack Game" << endl;
	cout << "**********************************" << endl;

	//Generates random seed value 
	srand(time(NULL)); 

	cout << "Drawing cards....." << endl << endl;

	//Draw first card 
	firstCard = rand() % 13 + 1;

	//Draw second card;
	secondCard = rand() % 13 + 1;

	//If duplicate card, draw again 
	while (secondCard == firstCard) 
	{
		secondCard = rand() % 13 + 1;
	}

	//Display cards to user 
	cout << "Here is your hand: "; displayCard(firstCard);
	cout << "  "; displayCard(secondCard); cout << endl;

	//Add the total 
	addTotal(firstCard, secondCard);

	//Display the total 
	cout << "Total: " << total << endl << endl;

	//Show the odds (never tell me the odds)
	Odds(total,firstCard,secondCard);

	//Pull third card 
	cout << endl << "Drawing third card....." << endl << endl;
	thirdCard = rand() % 13 + 1;


	//If thirdCard is repeat of firstCard or secondCard, draw again until different 
	while (thirdCard == firstCard || thirdCard == secondCard) 
	{
		thirdCard = rand() % 13 + 1;
	}

	//Display new hand to user 
	cout << "Here is your new hand: "; displayCard(firstCard);
	cout << "  "; displayCard(secondCard); cout << "  "; displayCard(thirdCard); cout << endl;
	

	//Calculate new total and display
	thirdTotal(total,thirdCard);

}


void addTotal(int firstCard, int secondCard) 
{
	//Check if the first card is an ace 
	if (checkAce(firstCard) == true) 
	{

		//If the first card is an ace & second card is face card. BlackJack!!!!
		if (checkFace(secondCard) == true) 
		{
			total = 21;
			cout << "BLACKJACK!!!" << endl;
		}

		//If the second card isnt a face card, add 1 + value of second card
		else 
		{
			total = firstCard + secondCard;

			//If the total is less than 11, make Ace worth 11 by adding 10 to the total.
			if (total <= 11) 
			{
				total += 10;
			}
		}
	}

	//If second card is ace 
	else if (checkAce(secondCard) == true) {

		//If the second card is an ace & first card is face card. BlackJack!!!!
		if (checkFace(firstCard) == true)
		{
			total = 21;
			cout << "BLACKJACK!!!" << endl;
		}

		//If the first card isnt a face card, add 1 + value of first card
		else
		{
			total = firstCard + secondCard;

			//If the total is less than 11, make Ace worth 11 by adding 10 to the total.
			if (total <= 11)
			{
				total += 10;
			}
		}
	}
	//If the first and second cards are worth 10, the Total is 20;
	else if (checkFace(firstCard) == true && checkFace(secondCard) == true)
	{
		total += 20;

	} 
	//If one of the cards is worth 10
	else if (checkFace(firstCard) == true || checkFace(secondCard) == true)
	{
		//If the first card is worth 10, add 10 + value of second card
		if (checkFace(firstCard) == true)
		{
			total = secondCard + 10;
		}
		//If the second card is worth 10, add 10 + value of first card
		else if (checkFace(secondCard) == true)
		{
			total = firstCard + 10;
		}
	}
	//If no face values or aces were pulled, add the cards together
	else 
	{
		total = firstCard + secondCard;
	}

}



//Checks if the card pulled was an Ace, returns bool vaule
bool checkAce(int card) {

	//1 = Ace 
	if (card == 1) {

		return true;
	}
	//Is not Ace 
	else {

		return false;
	}
}

//Checks if the card pulled was a Face card, returns bool value 
bool checkFace(int card) {

	//If card is 11, 12, or 13. It is a face
	if (card >= 11)
	{
		return true;
	}
	//Card isnt a face 
	else
	{
		return false;
	}

}


//Displays correct name of card to user 
void displayCard(int card) {

	//If Ace, Display A
	if (checkAce(card) == true) 
	{
		cout << "A";
	}

	//If Face, Display Card Name
	else if (card > 10)
	{
		//If 11, Display Jack
		if (card == 11) 
		{
			cout << "J";
		}

		//If 12, Display Queen
		else if (card == 12)
		{
			cout << "Q";
		}

		//If 13, Display King
		else
		{
			cout << "K";
		}
	}

	//If card between 2 - 10, display number 
	else {

		cout << card;
	}

}

void Odds(int total, int firstCard, int secondCard) {

	float benefitCard = 0;
	float detrimentalCard = 0;
	float benefitOdds = 0;
	float detrimentalOdds = 0;

	//For the cards valued from 2 to 9
	for (int i = 0; i <= 9; i++) {

		//If cards were already pulled, skip
		if (cards[i] == firstCard || cards[i] == secondCard) {

			continue;
		}

		//If the total + card value is less than or equal to 21. Add to benefit card total 
		if ((total + cards[i]) <= 21) {

			benefitCard++;
		}
		//If the total + card value is greater than 21. Add to detrimental card total 
		else if ((total + cards[i]) > 21) {

			detrimentalCard++;
		}
	}

	//For the face value cards, set values to 10, then add to total; 
	for (int i = 10; i <= 12; i++) {

		//If cards were already pulled, skip
		if (cards[i] == firstCard || cards[i] == secondCard) {

			continue;
		}

		//Set card value to 10
		cards[i] = 10;

		//If the total + card value is less than or equal to 21. Add to benefit card total 
		if ((total + cards[i]) <= 21) {

			benefitCard++;
		}

		//If the total + card value is greater than 21. Add to detrimental card total 
		else if ((total + cards[i]) > 21) {

			detrimentalCard++;
		}

	}


	//Calculate the odds
	benefitOdds = 100 * (benefitCard / 11);
	detrimentalOdds = 100 * (detrimentalCard / 11);

	//Display the odds 
	cout << "Odds of recieving benefit card: " <<  benefitOdds << "%" << endl;
	cout << "Odds of recieving detrimental card: " << detrimentalOdds << "%" << endl << endl;

	//If benefit odds are in your favor, suggest to draw another card 
	if (benefitOdds > detrimentalOdds)
	{
		cout << "You should draw another card." << endl;
	}
	//If benefit odds are against you, suggest to stand
	else 
	{
		cout << "You should not draw another card. " << endl;
	}

}

//Takes the thirdCard, determines value and adds to total. 
//If user goes over 21, displays Bust
void thirdTotal(int total, int thirdCard)
{

	//If third card is Ace, add 1 to total 
	if (checkAce(thirdCard) == true)
	{
		total = total + thirdCard;

		//If total is less than or equal to 1, make Ace worth 11 
		if (total <= 11)
		{
			total += 10;
		}
	}
	//If third card is a Face 
	else if (checkFace(thirdCard) == true)
	{

		total = total + 10;
	}
	//If card is not face 
	else
	{
		total = total + thirdCard;
	}

	cout << "New total: " << total << endl;

	//If over 21, BUST 
	if (total > 21)
	{
		cout << "BUST!" << endl;
	}

}