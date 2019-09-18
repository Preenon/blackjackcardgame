#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <cstdlib>
#include "card.h"

#ifndef BLACKJACK_H
#define BLACKJACK_H

namespace blackjack
{
    using namespace card;

    const int blackjackThreshold = 21;
    const int blackjackDealerStandPoint = 17;

    char hitOrStand()
    {
        char choice;
        do
        {
        	// Console input error checking performed here
            std::cout << "Hit [h] or stand [s]? ";
            std::cin >> choice;
            if (std::cin.fail())
            {
                std::cin.clear();
            }
            else if (choice != 'h' && choice != 's')
            {
                std::cout << "Please type in 'h' or 's', only!" << '\n';
            }
            std::cin.ignore(32767, '\n');
        } while (choice != 'h' && choice != 's');
        return choice;
    }

    int analyzeCard(const int score, const Card &card)
    {
            // Is it an ace?
            if (card.rankOfCard == ACE)
            {
                // Could this ace cause a bust?
                int predictedScore = score + card.rankOfCard;
                if (predictedScore > blackjackThreshold)
                {
                    return STATUS_ACE_ONE;
                }
                else
                {
                    return STATUS_ACE_ELEVEN;
                }
            }
            else
            {
                return STATUS_NOT_ACE;
            }
    }

    std::string blackJackCardSymbol(const Card &card)
    {
        std::string symbol = cardSymbol(card);
        symbol += "(";
        std::string valueAsString;
        std::ostringstream convert;
        convert << getCardValue(card);
        valueAsString = convert.str();
        symbol = symbol + valueAsString;
        symbol += ")";
        return symbol;
    }

    void initializeGame(const Card *&cardPtr, int &playerScore, int &dealerScore)
    {
        // Initialize dealer card
        std::cout << "Initializing Blackjack..." << '\n';
        int dealerValue = getCardValue(*cardPtr++);
        dealerScore += dealerValue;
        std::cout << "Dealer drew a " << blackJackCardSymbol(*(cardPtr - 1)) << "!" << '\n';

        // Initialize player cards
        int firstValue = getCardValue(*cardPtr++);
        std::string firstDealtCard = blackJackCardSymbol(*(cardPtr - 1));

        int secondValue = getCardValue(*cardPtr++);
        std::string secondDealtCard = blackJackCardSymbol(*(cardPtr - 1));

        playerScore += firstValue;
        playerScore += secondValue;

        std::cout << "Player drew a " << firstDealtCard <<
        " and a " << secondDealtCard << "!" << '\n';

        // Print scores for each participant
        std::cout << "Player score: " << playerScore << '\n';
        std::cout << "Dealer score: " << dealerScore << '\n';
    }

    // *&cardPtr because we want to increment the outside cardPtr in here, not make a copy.
    void hitAndUpdate(const Card *&cardPtr, bool &hit, int &score, bool isPlayer)
    {
        hit = true;
        int value = getCardValue(*cardPtr++);

        // Analyze cards
        int status;
        status = analyzeCard(score, *(cardPtr - 1));

        // Add ace (counting as one) condition
        if (status == STATUS_ACE_ONE)
        {
            value = 1;
            score += value;
            std::string oneMessage = blackJackCardSymbol(*(cardPtr - 1)) + "(counted as 1)";
            if (isPlayer)
            {
                std::cout << "Player drew a " << oneMessage << "!" << '\n';
            }
            else
            {
                std::cout << "Dealer drew a " << oneMessage << "!" << '\n';
            }
        }

        // Add ace (counting as eleven) condition
        else if (status == STATUS_ACE_ELEVEN)
        {
            value = 11;
            score += value;
            std::string elevenMessage = blackJackCardSymbol(*(cardPtr - 1)) + "(counted as 11)";
            if (isPlayer)
            {
                std::cout << "Player drew a " << elevenMessage << "!" << '\n';
            }
            else
            {
                std::cout << "Dealer drew a " << elevenMessage << "!" << '\n';
            }
        }

        // Add normal card
        else
        {
            score += value;
            if (isPlayer)
            {
                std::cout << "Player drew a " << blackJackCardSymbol(*(cardPtr - 1)) << "!" << '\n';
            }
            else
            {
                std::cout << "Dealer drew a " << blackJackCardSymbol(*(cardPtr - 1)) << "!" << '\n';
            }
        }
    }

    void analyzeScores(const int playerScore, const int dealerScore)
    {
        // The hand is finished here.
        std::cout << '\n' << "Hand has finished!" << '\n';

        // If playerScore > blackjackThreshold, then player loses.
        if (playerScore > blackjackThreshold)
        {
            std::cout << "Player busted! You lose...";
        }
        // If dealerScore > blackjackThreshold, then player wins
        else if (dealerScore > blackjackThreshold)
        {
            std::cout << "Dealer busted! You win!";
        }
        // Else, we check to see if playerScore > dealerScore
        else
        {
            if (playerScore > dealerScore)
            {
                std::cout << "Your score is more than the dealer's! You win!";
            }
            else
            {
                std::cout << "Your score is less than or equal to the dealer's! You lose...";
            }
        }
    }

    void playBlackjack(const std::array<Card, numberOfDeckCards> &deck)
    {
        /* *(cardPtr - 1)) means the card that was just dealt. */
        const Card *cardPtr = &deck[0];
        int playerScore = 0;
        int dealerScore = 0;
        bool playerHits(true);
        bool dealerHits(true);
        bool noStandNotificationYet(true);

        // Initialize game
        initializeGame(cardPtr, playerScore, dealerScore);

        // Repeat until player stands AND dealer stands or one of them busts
        do
        {
            std::cout << '\n';
            // Player turn
            char choice = hitOrStand();
            if (choice == 'h')
            {
                hitAndUpdate(cardPtr, playerHits, playerScore, true);
            }
            else if (choice == 's')
            {
                playerHits = false;
                std::cout << "Player stood!" << '\n';
            }

            // Dealer turn
            if (dealerScore < blackjackDealerStandPoint)
            {
                hitAndUpdate(cardPtr, dealerHits, dealerScore, false);
            }
            else
            {
                dealerHits = false;
                std::cout << "Dealer stood!" << '\n';
            }

            // Print scores
            std::cout << "Player score: " << playerScore << '\n';
            std::cout << "Dealer score: " << dealerScore << '\n';

            // Check if there's a bust.
            if (playerScore > blackjackThreshold || dealerScore > blackjackThreshold)
            {

                break;
            }

            // If needed, notify player ONCE that dealer will stand
            if (dealerScore >= blackjackDealerStandPoint && noStandNotificationYet)
            {
                std::cout << "Dealer will stand from this point on!" <<
                " Any stands by you from now on will end the game!" << '\n';
                noStandNotificationYet = false;
            }

        } while (playerHits || dealerHits);

        // Find out who won the game, and print the winner.
        analyzeScores(playerScore, dealerScore);
    }
}

#endif // BLACKJACK_H
