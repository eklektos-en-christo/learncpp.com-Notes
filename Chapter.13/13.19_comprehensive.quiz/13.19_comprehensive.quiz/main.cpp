//
//  main.cpp
//  13.19_comprehensive.quiz
//
//  Created by Εκλεκτός εν Χριστώ on 7/18/23.
//

/*
 -------------------------------------------------------------------------------------------
 REVIEW:
 -------------------------------------------------------------------------------------------
 Classes: allow to create own data types, that bundle both data and functions that work on
 that data
 
 Members: Data and functions inside the class
 
 Members: are selected by using the .operator or -> if accessing member through a pointer
 
 Access specifiers: allow to specify who can access the members of a class
 
 Public members: can be accessed directly by anybody
 
 Private members: can only be accessed by other members of the class
 
 By default: all members of a class are private
 
 By default: all members of a struct are public
 
 Encapsulation: process of making all the member data private, so it can't be accessed
 directly, this prevents class from misuse
 
 Constructors: special type of member functions that allow you to initialize the objects of
 the class
 
 Default Constructor: that takes no parameters or has all default parameters
 
 Default Constructor: is used if no initialization value are provided by the user
 
 Constructor: at least one should be provided for the classes
 
 Member initializer list: allows to initialize the member variables from within a
 constructor rather than assigning the member variables values
 
 Non-static member initialization: allow to directly specify default values for member
 variables when they are declared
 
 Delegating Constructors/constructor chaining: that are allowed to call other constructors
 
 Destructor: another type of special member function, allow the class to clean up after
 itself
 
 Any kind of deallocation or shutdown routines: should be executed from the destructor
 
 *this pointer: all member functions have it, it points at the class object being modified
 
 Header file: it is good style to put all class definitions in a header file of the same
 name as the class' name
 
 .cpp file: define class functions in this file, name should be same as the class', this
 helps avoid circular dependencies
 
 Member functions: can and should be made const if they don't modify the state of the class
 
 Const objects: can only call const member functions
 
 Static member variables: are shared among all objects of the class
 
 Static member variables: can also be accessed directly via the ::operator
 
 Static member functions: that have no *this pointer, they can only access static member
 variables
 
 Friend functions: that are treated like member functions of the class, thus can access the
 private data of the class directly
 
 Friend classes: where all members of the class are considered friend functions
 
 Anonymous objects: possible to create, for the purpose of evaluation in an expression, or
 passing or returning a value
 
 Nesting types: types can also be nested within a class, often used with enums related to
 class, but can be done with other types if desired
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <cmath>
#include <string>
#include <string_view>
#include "Random.h"
#include <array>
#include <algorithm>
#include <cassert>
#include <ctime>
#include <random>

/*-----------------------------------QUESTION 1-------------------------------------------*/
class Point2d
{
private:
    double m_x {};
    double m_y {};
    
public:
    Point2d(double x = 0.0, double y = 0.0) : m_x{ x }, m_y{ y } {}
    
    friend double distance_from(const Point2d& first, const Point2d& second);
    
    void print() { std::cout << "Point2d(" << m_x << ", " << m_y << ")\n"; }
};

double distance_from(const Point2d& first, const Point2d& second)
{
    return std::sqrt((first.m_x - second.m_x) * (first.m_x - second.m_x) + (first.m_y - second.m_y) * (first.m_y - second.m_y));
}
/*-----------------------------------END of Q1--------------------------------------------*/



/*-----------------------------------QUESTION 2-------------------------------------------*/
class HelloWorld
{
private:
    char* m_data{};
    
public:
    HelloWorld()
    {
        m_data = new char[14];
        const char* init{ "Hello, World!" };
        for (int i{ 0 }; i < 14; ++i)
            m_data[i] = init[i];
    }
    
    ~HelloWorld()
    {
        delete[] m_data;
    }
    
    void print() const
    {
        std::cout << m_data << '\n';
    }
};
/*-----------------------------------END of Q2--------------------------------------------*/



/*-----------------------------------QUESTION 3-------------------------------------------*/
class Monster
{
public:
    enum Type
    {
        dragon,
        goblin,
        ogre,
        orc,
        skeleton,
        troll,
        vampire,
        zombie,
        max_monster_types,
    };
    
private:
    Type m_type{};
    std::string m_name{};
    std::string m_roar{};
    int m_hitpoints{};
    
public:
    Monster(Type type, std::string_view name, std::string_view roar, int hitpoints)
    : m_type{ type }, m_name{ name }, m_roar{ roar }, m_hitpoints{ hitpoints }
    {
    }
    
    std::string_view get_type_string() const
    {
        switch (m_type)
        {
            case Type::dragon:      return "dragon";
            case Type::goblin:      return "goblin";
            case Type::ogre:        return "orc";
            case Type::orc:         return "orc";
            case Type::skeleton:    return "skeleton";
            case Type::troll:       return "troll";
            case Type::vampire:     return "vampire";
            case Type::zombie:      return "zombie";
            default:                return "??????";
        }
    }
    
    void print()
    {
        std::cout << m_name << " the " << get_type_string() << " has ";
        std::cout << m_hitpoints << " hit points and says " << m_roar << '\n';
    }
};

namespace monster_generator
{

    Monster generate()
    {
        int max_index { Monster::Type::max_monster_types - 1 };
        auto type{ static_cast<Monster::Type>(Random::get(0, max_index)) };
        int hit_points{ Random::get(0, 100) };
        
        static constexpr std::array s_names{ "Blarg", "Moog", "Pksh", "Tyrn", "Mort", "Hans" };
        static constexpr std::array s_roars{ "*ROAR*", "*peep*", "*squeal*", "*whine*", "*hum*", "*burp*" };
        
        auto name { s_names[Random::get<std::size_t>(0, s_names.size() - 1)] };
        auto roar { s_roars[Random::get<std::size_t>(0, s_roars.size() - 1)] };
        
        return Monster{ type, name, roar, hit_points };
    }

};
/*-----------------------------------END of Q3--------------------------------------------*/



/*-----------------------------------QUESTION 4-------------------------------------------*/

// Maximum score before losing.
constexpr int g_maximumScore{ 21 };

// Minimum score that the dealer has to have.
constexpr int g_minimumDealerScore{ 17 };

class Card
{
public:
    enum Suit
    {
        club,
        diamond,
        heart,
        spade,

        max_suits
    };

    enum Rank
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

        max_ranks
    };

private:
    Rank m_rank{};
    Suit m_suit{};

public:
    Card() = default;

    Card(Rank rank, Suit suit)
        : m_rank{ rank }, m_suit{ suit }
    {
    }

    void print() const
    {
        switch (m_rank)
        {
        case rank_2:        std::cout << '2';   break;
        case rank_3:        std::cout << '3';   break;
        case rank_4:        std::cout << '4';   break;
        case rank_5:        std::cout << '5';   break;
        case rank_6:        std::cout << '6';   break;
        case rank_7:        std::cout << '7';   break;
        case rank_8:        std::cout << '8';   break;
        case rank_9:        std::cout << '9';   break;
        case rank_10:       std::cout << 'T';   break;
        case rank_jack:     std::cout << 'J';   break;
        case rank_queen:    std::cout << 'Q';   break;
        case rank_king:     std::cout << 'K';   break;
        case rank_ace:      std::cout << 'A';   break;
        default:
            std::cout << '?';
            break;
        }

        switch (m_suit)
        {
        case club:          std::cout << 'C';   break;
        case diamond:       std::cout << 'D';   break;
        case heart:         std::cout << 'H';   break;
        case spade:         std::cout << 'S';   break;
        default:
            std::cout << '?';
            break;
        }
    }

    int value() const
    {
        switch (m_rank)
        {
        case rank_2:        return 2;
        case rank_3:        return 3;
        case rank_4:        return 4;
        case rank_5:        return 5;
        case rank_6:        return 6;
        case rank_7:        return 7;
        case rank_8:        return 8;
        case rank_9:        return 9;
        case rank_10:       return 10;
        case rank_jack:     return 10;
        case rank_queen:    return 10;
        case rank_king:     return 10;
        case rank_ace:      return 11;
        default:
            assert(false && "should never happen");
            return 0;
        }
    }
};

class Deck
{
public:
    using DeckType = std::array<Card, 52>;
    using Index = DeckType::size_type;

private:
    DeckType m_deck{};
    Index m_cardIndex{ 0 };

public:
    Deck()
    {
        Index index{ 0 };

        for (int suit{ 0 }; suit < Card::max_suits; ++suit)
        {
            for (int rank{ 0 }; rank < Card::max_ranks; ++rank)
            {
                m_deck[index] = { static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit) };
                ++index;
            }
        }
    }

    void print() const
    {
        for (const auto& card : m_deck)
        {
            card.print();
            std::cout << ' ';
        }

        std::cout << '\n';
    }

    void shuffle()
    {
        static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

        std::shuffle(m_deck.begin(), m_deck.end(), mt);

        m_cardIndex = 0;
    }

    const Card& dealCard()
    {
        assert(m_cardIndex < m_deck.size());

        return m_deck[m_cardIndex++];
    }
};

class Player
{
private:
    int m_score{};

public:
    int drawCard(Deck& deck)
    {
        int value = deck.dealCard().value();
        m_score += value;
        return value;
    }

    int score() const
    {
        return m_score;
    }

    bool isBust() const
    {
        return (m_score > g_maximumScore);
    }

};

bool playerWantsHit()
{
    while (true)
    {
        std::cout << "(h) to hit, or (s) to stand: ";

        char ch{};
        std::cin >> ch;

        switch (ch)
        {
        case 'h':
            return true;
        case 's':
            return false;
        }
    }
}

// Returns true if the player went bust. False otherwise.
bool playerTurn(Deck& deck, Player& player)
{
    while (true)
    {
        if (player.isBust())
        {
            // This can happen even before the player had a choice if they drew 2
            // aces.
            std::cout << "You busted!\n";
            return true;
        }
        else
        {
            if (playerWantsHit())
            {
                auto playerCard = player.drawCard(deck);
                std::cout << "You were dealt a " << playerCard << " and now have " << player.score() << '\n';
            }
            else
            {
                // The player didn't go bust.
                return false;
            }
        }
    }
    return false;
}

// Returns true if the dealer went bust. False otherwise.
bool dealerTurn(Deck& deck, Player& dealer)
{
    while (dealer.score() < g_minimumDealerScore)
    {
        auto dealerCard { dealer.drawCard(deck) };
        std::cout << "The dealer turned up a " << dealerCard << " and now has " << dealer.score() << '\n';
    }

    if (dealer.isBust())
    {
        std::cout << "The dealer busted!\n";
        return true;
    }
    return false;
}

bool playBlackjack(Deck& deck)
{
    Player dealer{};
    dealer.drawCard(deck);

    std::cout << "The dealer is showing: " << dealer.score() << '\n';

    Player player{};
    player.drawCard(deck);
    player.drawCard(deck);

    std::cout << "You have: " << player.score() << '\n';

    if (playerTurn(deck, player))
    {
        return false;
    }

    if (dealerTurn(deck, dealer))
    {
        return true;
    }

    return (player.score() > dealer.score());
}
/*-----------------------------------END of Q4--------------------------------------------*/



int main()
{
    Point2d first{};
    Point2d second{ 3.0, 4.0 };
    first.print();
    second.print();
    
    /*std::cout << "Distance between two points: " << first.distance_to(second) << '\n';*/
    
    std::cout << "Distance between two points: " << distance_from(first, second) << '\n';
    
    HelloWorld hello{};
    hello.print();
    
    Monster skeleton{ Monster::skeleton, "Bones", "*rattle*", 4 };
    skeleton.print();
    
    Monster m{ monster_generator::generate() };
    m.print();
    
    Deck deck{};

    deck.shuffle();

    if (playBlackjack(deck))
    {
        std::cout << "You win!\n";
    }
    else
    {
        std::cout << "You lose!\n";
    }
    
    return 0;
}
