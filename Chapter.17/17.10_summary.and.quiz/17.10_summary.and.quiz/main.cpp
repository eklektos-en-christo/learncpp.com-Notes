//
//  main.cpp
//  17.10_summary.and.quiz
//
//  Created by Εκλεκτός εν Χριστώ on 10/19/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 SUMMARY:
 
 Inheritance allows us to model an is-a relationship between two objects
 
 Object being inherited from is called the parent/base/super class
 
 Object doing the inheriting is called the child/derived/sub class
 
 When a dervied class inherits from a base class, the derived class acquires all of the members of the base
 
 When a derived class is constructed, the base portion of the class is constructed first, then the derived
 portion is constructed
 
 Construction in detail:
 - memory for the derived class is set aside(enough for both base and derived portions)
 - appropriate derived class constructor is called
 - base class object is constructed first using the appropriate base class constructor
 - if no base constructor is specified, the default constructor will be used
 - the initialization list of the derived class initializes members of the derived class
 - the body of the derived class constructor executes
 - control is returned to the caller
 
 Destruction happens in the opposite order, from most-derived to most-base class
 
 C++ has 3 access specifiers - public, protected & private
 
 Protected access specifier allows the class the member belongs to, friends and derived classes to access
 protected members, but not the public(outside of classes)
 
 Classes can inherit froma another class publicly, privately and protectedly
 
 Class almost always inherit publicly
 
 Derived classes can add new functions, change the way functions that exist in the base class work in the
 derived class, change an inherited member's access level or hide functionality
 
 Multiple inheritance enalbe a derived class to inherit members from more than one parent
 
 Generally avoid multiple inheritance unless alternatives lead to more complexity
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include <cstdlib>
#include <ctime>
#include <sstream> // for std::stringstream

class Fruit
{
private:
    std::string m_name{};
    std::string m_color{};
    
public:
    Fruit(std::string_view name, std::string_view color) : m_name{ name }, m_color{ color }
    {
    }
    
    const std::string& get_name() const { return m_name; }
    const std::string& get_color() const { return m_color; }
};

class Apple : public Fruit
{
protected:
    Apple(std::string_view name, std::string_view color) : Fruit{ name, color }
    {
    }
    
public:
    Apple(std::string_view color="red") : Fruit{ "apple", color }
    {
    }
};

class Banana : public Fruit
{
public:
    Banana() : Fruit{ "banana", "yellow" }
    {
    }
};

class GrannySmith : public Apple
{
public:
    GrannySmith() : Apple{ "Granny Smith apple", "green" }
    {
    }
};

/*--------------------------------------------------------------------------------------------------------*/

int getRandomNumber(int min, int max)
{
    static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

class Potion
{
public:
    // All possible types of potions
    enum PotionType
    {
        health,
        strength,
        poison,

        // For random potion generation
        max_type
    };

    enum PotionSize
    {
        small,
        medium,
        large,

        max_size
    };


private:
    PotionType m_type{};
    PotionSize m_size{};

public:
    Potion(PotionType type, PotionSize size)
        : m_type{ type },
        m_size{ size }
    {
    }

    PotionType getType() const { return m_type; }
    PotionSize getSize() const { return m_size; }

    // The names of potions are compile-time literals, we can
    // return a std::string_view.
    static std::string_view getPotionTypeName(PotionType type)
    {
        static constexpr std::array names{
          "Health",
          "Strength",
          "Poison"
        };

        return names.at(static_cast<std::size_t>(type));
    }

    static std::string_view getPotionSizeName(PotionSize size)
    {
        static constexpr std::array names{
          "Small",
          "Medium",
          "Large"
        };

        return names.at(static_cast<std::size_t>(size));
    }

    std::string getName() const
    {
        // We use a std::stringstream, but this could also be solved using
        // std::string.
        // We first used std::stringstream in lesson 7.13.
        std::stringstream result{};

        result << getPotionSizeName(getSize()) << " potion of " << getPotionTypeName(getType());

        // We can extract the string from an std::stringstream by using the str()
        // member function.
        return result.str();
    }

    static Potion getRandomPotion()
    {
        return {
          static_cast<PotionType>(getRandomNumber(0, static_cast<int>(PotionType::max_type) - 1)),
          static_cast<PotionSize>(getRandomNumber(0, static_cast<int>(PotionSize::max_size) - 1))
        };
    }
};

class Creature
{
protected:
    std::string m_name;
    char m_symbol{};
    int m_health{};
    int m_damage{};
    int m_gold{};

public:
    Creature(std::string_view name, char symbol, int health, int damage, int gold)
        : m_name{ name }
        , m_symbol{ symbol }
        , m_health{ health }
        , m_damage{ damage }
        , m_gold{ gold }
    {
    }

    char getSymbol() const { return m_symbol; }
    const std::string& getName() const { return m_name; }
    bool isDead() const { return m_health <= 0; }
    int getGold() const { return m_gold; }
    void addGold(int gold) { m_gold += gold; }
    void reduceHealth(int health) { m_health -= health; }
    int getHealth() const { return m_health; }
    int getDamage() const { return m_damage; }
};

class Player : public Creature
{
    int m_level{ 1 };

public:
    Player(std::string_view name)
        : Creature{ name, '@', 10, 1, 0 }
    {
    }

    void levelUp()
    {
        ++m_level;
        ++m_damage;
    }

    int getLevel() const { return m_level; }
    bool hasWon() const { return m_level >= 20; }

    // Applies a potion's effect to the player
    void drinkPotion(const Potion& potion)
    {
        switch (potion.getType())
        {
        case Potion::health:
            // Only a health potion's size affects its power. All other
            // potions are independent of size.
            m_health += ((potion.getSize() == Potion::large) ? 5 : 2);
            break;
        case Potion::strength:
            ++m_damage;
            break;
        case Potion::poison:
            reduceHealth(1);
            break;
            // Handle max_type to silence the compiler warning. Don't use default:
            // because we want the compiler to warn us if we add a new potion but
            // forget to implement its effect.
        case Potion::max_type:
            break;
        }
    }
};

class Monster : public Creature
{
public:
    enum class Type
    {
        dragon,
        orc,
        slime,
        max_types
    };

private:
    static const Creature& getDefaultCreature(Type type)
    {
        static const std::array<Creature, static_cast<std::size_t>(Type::max_types)> monsterData{
          { { "dragon", 'D', 20, 4, 100 },
            { "orc", 'o', 4, 2, 25 },
            { "slime", 's', 1, 1, 10 } }
        };

        return monsterData.at(static_cast<std::size_t>(type));
    }

public:
    Monster(Type type)
        : Creature{ getDefaultCreature(type) }
    {
    }

    static Monster getRandomMonster()
    {
        int num{ getRandomNumber(0, static_cast<int>(Type::max_types) - 1) };
        return Monster{ static_cast<Type>(num) };
    }
};

// We moved this out of attackMonster() to keep the function shorter.
void onMonsterKilled(Player& player, const Monster& monster)
{
    std::cout << "You killed the " << monster.getName() << ".\n";
    player.levelUp();
    std::cout << "You are now level " << player.getLevel() << ".\n";
    std::cout << "You found " << monster.getGold() << " gold.\n";
    player.addGold(monster.getGold());

    // 30% chance of finding a potion
    constexpr int potionChance{ 30 };
    if (getRandomNumber(1, 100) <= potionChance)
    {
        // Generate a random potion
        auto potion{ Potion::getRandomPotion() };

        std::cout << "You found a mythical potion! Do you want to drink it? [y/n]: ";
        char choice{};
        std::cin >> choice;

        if (choice == 'Y' || choice == 'y')
        {
            // Apply the effect
            player.drinkPotion(potion);
            // Reveal the potion type and size
            std::cout << "You drank a " << potion.getName() << ".\n";
        }
    }
}

void attackMonster(Player& player, Monster& monster)
{
    if (player.isDead())
        return;

    std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage.\n";

    monster.reduceHealth(player.getDamage());

    if (monster.isDead())
    {
        // Reward the player
        onMonsterKilled(player, monster);
    }
}

void attackPlayer(const Monster& monster, Player& player)
{
    if (monster.isDead())
        return;

    player.reduceHealth(monster.getDamage());
    std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage.\n";
}

void fightMonster(Player& player)
{
    Monster monster{ Monster::getRandomMonster() };
    std::cout << "You have encountered a " << monster.getName() << " (" << monster.getSymbol() << ").\n";

    while (!monster.isDead() && !player.isDead())
    {
        std::cout << "(R)un or (F)ight: ";
        char input;
        std::cin >> input;
        if (input == 'R' || input == 'r')
        {
            if (getRandomNumber(1, 2) == 1)
            {
                std::cout << "You successfully fled.\n";
                return;
            }
            else
            {
                std::cout << "You failed to flee.\n";
                attackPlayer(monster, player);
                continue;
            }
        }

        if (input == 'F' || input == 'f')
        {
            attackMonster(player, monster);
            attackPlayer(monster, player);
        }
    }
}
/*--------------------------------------------------------------------------------------------------------*/

int main()
{
    Apple a{ "red" };
    Banana b{};
    GrannySmith c{};
    
    std::cout << "My " << a.get_name() << " is " << a.get_color() << ".\n";
    std::cout << "My " << b.get_name() << " is " << b.get_color() << ".\n";
    std::cout << "My " << c.get_name() << " is " << c.get_color() << ".\n";
    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::rand();

    std::cout << "Enter your name: ";
    std::string playerName;
    std::cin >> playerName;

    Player player{ playerName };
    std::cout << "Welcome, " << player.getName() << '\n';

    while (!player.isDead() && !player.hasWon())
        fightMonster(player);

    if (player.isDead())
    {
        std::cout << "You died at level " << player.getLevel() << " and with " << player.getGold() << " gold.\n";
        std::cout << "Too bad you can't take it with you!\n";
    }
    else
    {
        std::cout << "You won the game with " << player.getGold() << " gold!\n";
    }
    
    return 0;
}
