#include <iostream>
#include <string>
#include <array>
#include <ctime>
#include "card.h"
#include "blackjack.h"

using namespace card;
using namespace blackjack;

bool wantsToPlayGame()
{
	char choice;
	do
	{
		// Console input error checking performed here
		std::cout << "Do you want to play a game of blackjack [y/n]? ";
		std::cin >> choice;
		if (std::cin.fail())
		{
			std::cin.clear();
		}
		else if (choice != 'y' && choice != 'n')
		{
			std::cout << "Please type in 'y' or 'n', only!" << '\n';
		}
		std::cin.ignore(32767, '\n');
	} while (choice != 'y' && choice != 'n');

	if (choice == 'y')
	{
		return true;
	}
	return false;
}

int main()
{
    srand(static_cast<unsigned int>(time(0))); // set initial seed value to system clock
    // get rid of first static value (bug?)
    rand();

    std::array<Card, numberOfDeckCards> deck;
    deck = initializeDeck();

    // Check if the player wants to play a game of blackjack.
    bool playGame = true;
    do
    {
    	playGame = wantsToPlayGame();
    	if (playGame)
    	{
    		shuffleDeck(deck);
    		playBlackjack(deck);
    		std::cout << '\n';
    	}
    } while (playGame);

    return 0;
}
