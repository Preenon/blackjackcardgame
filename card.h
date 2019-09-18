#include <iostream>
#include <string>
#include <array>
#include <cstdlib>

#ifndef CARD_H
#define CARD_H

namespace card
{
    const int numberOfDeckCards = 52;

    enum CardRank
    {
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE,
        MAX_RANK
    };

    enum CardSuit
    {
        CLUBS,
        DIAMONDS,
        HEARTS,
        SPADES,
        MAX_SUIT
    };

    enum BlackJackStatus
    {
        STATUS_ACE_ONE,
        STATUS_ACE_ELEVEN,
        STATUS_NOT_ACE
    };

    struct Card
    {
        CardRank rankOfCard;
        CardSuit suitOfCard;
    };

    int getCardValue(const Card &card)
    {
        int cardValue = 0;
        switch (card.rankOfCard)
        {
            case ACE:
                cardValue = 11;
                break;
            case JACK:
            case QUEEN:
            case KING:
                cardValue = 10;
                break;
            default:
                cardValue = card.rankOfCard + 2;
        }
        return cardValue;
    }

    std::string cardSymbol(const Card &card)
    {
        std::string rankChar = "";
        switch (card.rankOfCard)
        {
            case TWO:
                rankChar = "2";
                break;
            case THREE:
                rankChar = "3";
                break;
            case FOUR:
                rankChar = "4";
                break;
            case FIVE:
                rankChar = "5";
                break;
            case SIX:
                rankChar = "6";
                break;
            case SEVEN:
                rankChar = "7";
                break;
            case EIGHT:
                rankChar = "8";
                break;
            case NINE:
                rankChar = "9";
                break;
            case TEN:
                rankChar = "0";
                break;
            case JACK:
                rankChar = "J";
                break;
            case QUEEN:
                rankChar = "Q";
                break;
            case KING:
                rankChar = "K";
                break;
            case ACE:
                rankChar = "A";
                break;
            default:
                rankChar = "?";
        }
        std::string suitChar = "";
        switch (card.suitOfCard)
        {
            case CLUBS:
                suitChar = "C";
                break;
            case DIAMONDS:
                suitChar = "D";
                break;
            case HEARTS:
                suitChar = "H";
                break;
            case SPADES:
                suitChar = "S";
                break;
            default:
                suitChar = "?";
        }
        // Convert card value to std::string and append it
        std::string cardSymbol = rankChar + suitChar;
        return cardSymbol;
    }


    void printDeck(const std::array<Card, 52> &deck)
    {
        for (const auto &current : deck)
        {
            std::cout << cardSymbol(current);
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    void swapCard(Card &firstCard, Card &secondCard)
    {
        Card holding = firstCard;
        firstCard = secondCard;
        secondCard = holding;
    }

    // Generate a random number between min and max (inclusive)
    // Assumes srand() has already been called
    int getRandomNumber(int min, int max)
    {

        // static used for efficiency, so we only calculate this value once
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        // evenly distribute the random number across our range
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
    }

    std::array<Card, numberOfDeckCards> initializeDeck()
    {
        std::array<Card, numberOfDeckCards> deck;
        int card = 0;
        for (int suit = 0; suit < MAX_SUIT; ++suit)
        {
            for (int rank = 0; rank < MAX_RANK; ++rank)
            {
                deck[card].suitOfCard = static_cast<CardSuit>(suit);
                deck[card].rankOfCard = static_cast<CardRank>(rank);
                ++card;
            }
        }
        return deck;
    }

    void shuffleDeck(std::array<Card, numberOfDeckCards> &deck)
    {

        for (int i = 0; i < numberOfDeckCards; i++)
        {
            int randomIndex = getRandomNumber(0, numberOfDeckCards - 1);
            swapCard(deck[i], deck[randomIndex]);
        }
    }

}

#endif // CARD_H
