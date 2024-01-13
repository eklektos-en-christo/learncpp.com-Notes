//
//  main.cpp
//  14.19_project.15puzzle
//
//  Created by Εκλεκτός εν Χριστώ on 7/27/23.
//

#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
#include "Random.h"

constexpr int g_console_lines{ 25 };

class Direction
{
public:
    enum Type
    {
        up,
        down,
        left,
        right,
        max_directions,
    };
    
    Direction(Type type) : m_type{ type }
    {
    }
    
    Type get_type() const
    {
        return m_type;
    }
    
    Direction operator-() const
    {
        switch (m_type)
        {
            case up:        return Direction{ down };
            case down:      return Direction{ up };
            case left:      return Direction{ right };
            case right:     return Direction{ left };
        }
        
        assert(0 && "Unsupported direction was passed!");
        return Direction{ up };
    }
    
    friend std::ostream& operator<<(std::ostream& stream, Direction dir)
    {
        switch (dir.get_type())
        {
            case Direction::up:     return (stream << "up");
            case Direction::down:   return (stream << "down");
            case Direction::left:   return (stream << "left");
            case Direction::right:  return (stream << "right");
            default:                return (stream << "unknown direction");
        }
    }
    
    static Direction get_random_direction()
    {
        Type random{ static_cast<Type>(Random::get(0, Type::max_directions - 1)) };
        return Direction{ random };
    }
    
private:
    Type m_type{};
};

struct Point
{
    int x{};
    int y{};
    
    friend bool operator==(Point p1, Point p2)
    {
        return p1.x == p2.x && p1.y == p2.y;
    }
    
    friend bool operator!=(Point p1, Point p2)
    {
        return !(p1 == p2);
    }
    
    Point get_adjacent_point(Direction dir) const
    {
        switch (dir.get_type())
        {
            case Direction::up:     return Point{ x, y - 1 };
            case Direction::down:   return Point{ x, y + 1 };
            case Direction::left:   return Point{ x - 1, y };
            case Direction::right:  return Point{ x + 1, y };
        }
        
        return *this;
    }
};

namespace user_input
{
    bool is_valid_command(char ch)
    {
        return ch == 'w' || ch == 'a' || ch == 's' || ch == 'd' || ch == 'q';
    }

    void ignore_line()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char get_character()
    {
        char operation{};
        std::cin >> operation;
        ignore_line();          /// remove any extraneous input
        return operation;
    }

    char get_command_from_user()
    {
        char ch{};
        while (!is_valid_command(ch))
            ch = get_character();
        
        return ch;
    }

    Direction char_to_direction(char ch)
    {
        switch (ch)
        {
            case 'w':   return Direction{ Direction::up };
            case 's':   return Direction{ Direction::down };
            case 'a':   return Direction{ Direction::left };
            case 'd':   return Direction{ Direction::right };
        }
        
        assert(0 && "Unsupported direction was passed!");
        return Direction{ Direction::up };
    }
};

class Tile
{
private:
    int m_num{};
    
public:
    Tile() = default;
    
    explicit Tile(int number) : m_num{ number }
    {
    }
    
    friend std::ostream& operator<<(std::ostream& stream, Tile tile)
    {
        /// if two digit number
        if (tile.m_num > 9)
            stream << " " << tile.m_num << " ";
        /// if one digit number
        else if (tile.m_num > 0)
            stream << "  " << tile.m_num << " ";
        /// if empty spot
        else if (tile.m_num == 0)
            stream << "    ";
        
        return stream;
    }
    
    bool is_empty() const
    {
        return m_num == 0;
    }
    
    int get_num() const { return m_num; }
};

class Board
{
private:
    static constexpr int SIZE{ 4 };
    Tile m_tiles[SIZE][SIZE]
    {
        Tile{ 1 }, Tile{ 2 }, Tile{ 3 }, Tile{ 4 },
        Tile{ 5 }, Tile{ 6 }, Tile{ 7 }, Tile{ 8 },
        Tile{ 9 }, Tile{ 10 }, Tile{ 11 }, Tile{ 12 },
        Tile{ 13 }, Tile{ 14 }, Tile{ 15 }, Tile{ 0 }
    };
    
public:
    Board() = default;
    
    static void print_empty_lines(int count)
    {
        for (int i{ 0 }; i < count; ++i)
            std::cout << '\n';
    }
    
    friend std::ostream& operator<<(std::ostream& stream, const Board& board)
    {
        /// Before drawing always print some empty lines
        /// so that only one board appears at a time
        /// and it's always shown at the bottom of the window
        /// because console window scrolls automatically when there is no
        /// enough space.
        print_empty_lines(g_console_lines);
        
        for (int y{ 0 }; y < SIZE; ++y)
        {
            for (int x{ 0 }; x < SIZE; ++x)
                stream << board.m_tiles[y][x];
            stream << '\n';
        }
        
        return stream;
    }
    
    Point get_empty_tile_pos() const
    {
        for (int y = 0; y < SIZE; ++y)
            for (int x = 0; x < SIZE; ++x)
                if (m_tiles[y][x].is_empty())
                    return { x, y };
        
        assert(0 && "There is no empty tile in the board!!!");
        return { -1, -1 };
    }
    
    static bool is_valid_tile_pos(Point pt)
    {
        return (pt.x >= 0 && pt.x < SIZE)
            && (pt.y >= 0 && pt.y < SIZE);
    }
    
    void swap_tiles(Point pt1, Point pt2)
    {
        std::swap(m_tiles[pt1.y][pt1.x], m_tiles[pt2.y][pt2.x]);
    }
    
    friend bool operator==(const Board& f1, const Board& f2)
    {
        for (int y{ 0 }; y < SIZE; ++y)
            for (int x{ 0 }; x < SIZE; ++x)
                if (f1.m_tiles[y][x].get_num() != f2.m_tiles[y][x].get_num())
                    return false;
        
        return true;
    }
    
    bool move_tile(Direction dir)
    {
        Point empty_tile{ get_empty_tile_pos() };
        Point adj{ empty_tile.get_adjacent_point(-dir) };
        
        if (!is_valid_tile_pos(adj))
            return false;
        
        swap_tiles(adj, empty_tile);
        return true;
    }
    
    bool player_won() const
    {
        static Board s_solved{};
        return s_solved == *this;
    }
    
    void randomize()
    {
        for (int i{ 0 }; i < 1000; ++i)
        {
            bool success = move_tile(Direction::get_random_direction());
            
            if (!success)
                --i;
        }
    }
};

int main()
{
    Board board{};
    board.randomize();
    std::cout << board;
    
    while (!board.player_won())
    {
        char ch{ user_input::get_command_from_user() };
        
        if (ch == 'q')
        {
            std::cout << "\n\nBYE\n\n";
            return 0;
        }
        
        Direction dir{ user_input::char_to_direction(ch) };
        
        bool user_moved { board.move_tile(dir) };
        if (user_moved)
            std::cout << board;
    }
    
    std::cout << "\n\nYOU WON!\n\n";
    
    return 0;
}
