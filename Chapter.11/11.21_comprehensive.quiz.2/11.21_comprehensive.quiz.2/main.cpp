//
//  main.cpp
//  11.21_comprehensive.quiz.2
//
//  Created by Εκλεκτός εν Χριστώ on 6/4/23.
//
#include <iostream>
#include <array>
#include <ctime>
#include <random>
#include <algorithm>
#include <cassert>

enum class Card_Suit
{
    club,
    diamond,
    heart,
    spade,
    
    max_suits,
};

enum class Card_Rank
{
    rank_2,
    rank_3,
    rank_4,
    rank_5,
    rank_6,
    rank_7,
    rank_8,
    rank_9,
    rank_10,
    rank_jack,
    rank_queen,
    rank_king,
    rank_ace,
    
    max_ranks,
};

struct Card
{
    Card_Rank rank{};
    Card_Suit suit{};
};

void print_card(const Card& card)
{
    switch (card.rank)
    {
        case Card_Rank::rank_2:             std::cout << '2';  break;
        case Card_Rank::rank_3:             std::cout << '3';  break;
        case Card_Rank::rank_4:             std::cout << '4';  break;
        case Card_Rank::rank_5:             std::cout << '5';  break;
        case Card_Rank::rank_6:             std::cout << '6';  break;
        case Card_Rank::rank_7:             std::cout << '7';  break;
        case Card_Rank::rank_8:             std::cout << '8';  break;
        case Card_Rank::rank_9:             std::cout << '9';  break;
        case Card_Rank::rank_10:            std::cout << 'T';  break;
        case Card_Rank::rank_jack:          std::cout << 'J';  break;
        case Card_Rank::rank_queen:         std::cout << 'Q';  break;
        case Card_Rank::rank_king:          std::cout << 'K';  break;
        case Card_Rank::rank_ace:           std::cout << 'A';  break;
        default:                            std::cout << '?';  break;
    }
    
    switch (card.suit)
    {
        case Card_Suit::club:               std::cout << 'C'; break;
        case Card_Suit::diamond:            std::cout << 'D'; break;
        case Card_Suit::heart:              std::cout << 'H'; break;
        case Card_Suit::spade:              std::cout << 'S'; break;
        default:                            std::cout << '?'; break;
    }
}

using Deck = std::array<Card, 52>;
using Index = Deck::size_type;

Deck create_deck()
{
    Deck deck{};
    
    Index index{ 0 };
    
    for (int suit{ 0 }; suit < static_cast<int>(Card_Suit::max_suits); ++suit)
    {
        for (int rank{ 0 }; rank < static_cast<int>(Card_Rank::max_ranks); ++rank)
        {
            deck[index].suit = static_cast<Card_Suit>(suit);
            deck[index].rank = static_cast<Card_Rank>(rank);
            ++index;
        }
    }
    
    return deck;
}

void print_deck(const Deck& deck)
{
    for (const auto& card : deck)
    {
        print_card(card);
        std::cout << ' ';
    }
    
    std::cout << '\n';
}

void shuffle_deck(Deck& deck)
{
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    
    std::shuffle(deck.begin(), deck.end(), mt);
}

int get_card_value(const Card& card)
{
    switch (card.rank)
    {
        case Card_Rank::rank_2:             return 2;
        case Card_Rank::rank_3:             return 3;
        case Card_Rank::rank_4:             return 4;
        case Card_Rank::rank_5:             return 5;
        case Card_Rank::rank_6:             return 6;
        case Card_Rank::rank_7:             return 7;
        case Card_Rank::rank_8:             return 8;
        case Card_Rank::rank_9:             return 9;
        case Card_Rank::rank_10:            return 10;
        case Card_Rank::rank_jack:          return 10;
        case Card_Rank::rank_queen:         return 10;
        case Card_Rank::rank_king:          return 10;
        case Card_Rank::rank_ace:           return 11;
        default:
            assert(false && "should never happen");
            return 0;
    }
}

int main()
{
    auto deck{ create_deck() };
    
    shuffle_deck(deck);
    
    print_deck(deck);
    
    return 0;
}
