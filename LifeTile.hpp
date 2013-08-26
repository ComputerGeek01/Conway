#ifndef LIFETILE_HPP_INCLUDED
#define LIFETILE_HPP_INCLUDED

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
//#include <SFML/Mouse.hpp>

void pause()
{
    std::cin.sync();
    std::cin.ignore();
}

class Tile
{
private:

    bool Alive;
    bool Dying;
    bool Spawning;

public:

    Tile()
    {
        Alive = false;
        Dying = false;
        Spawning = false;

        tile.setSize(sf::Vector2f(25,25));
        tile.setFillColor(sf::Color::White);
        tile.setOutlineColor(sf::Color::Black);
        tile.setOutlineThickness(1);

        Clear();
    }


    Tile(sf::Vector2f pos)
    {
        Alive = false;
        Dying = false;
        Pos = pos;

        tile.setPosition(Pos);

        tile.setSize(sf::Vector2f(20,20));
        tile.setFillColor(sf::Color::White);
        tile.setOutlineColor(sf::Color::Black);
        tile.setOutlineThickness(1);

    }

    bool Place(sf::Vector2f pos)
    {
        Pos = pos;
        tile.setPosition(Pos);
        Clear();

        return true;
    }

    sf::Vector2f Pos;
    sf::RectangleShape tile;

    bool UP;
    bool DOWN;
    bool LEFT;
    bool RIGHT;

    bool UPLEFT;
    bool UPRIGHT;
    bool DNLEFT;
    bool DNRIGHT;


    int Neighbors()
    {
        int Total = 0;

        if(UP)
        {
            Total++;
        }
        if(DOWN)
        {
            Total++;
        }
        if(LEFT)
        {
            Total++;
        }
        if(RIGHT)
        {
            Total++;
        }
        if(UPLEFT)
        {
            Total++;
        }
        if(UPRIGHT)
        {
            Total++;
        }
        if(DNLEFT)
        {
            Total++;
        }
        if(DNRIGHT)
        {
            Total++;
        }

        return Total;
    }

    void Clear()
    {
        UP = false;
        DOWN = false;
        LEFT = false;
        RIGHT = false;

        UPLEFT = false;
        UPRIGHT = false;
        DNLEFT = false;
        DNRIGHT = false;
    }


    void Status()
    {
        std::cout << "UPLEFT:" << UPLEFT << " UP:" << UP << " UPRIGHT:" << UPRIGHT << " LEFT:" << LEFT << " RIGHT:" << RIGHT << " DNLEFT:" << DNLEFT << " DOWN:" << DOWN << " DNRIGHT:" <<DNRIGHT << std::endl;
    }

    void Spawn()
    {
        Alive = true;
        Dying = false;
        Spawning = true;
        tile.setFillColor(sf::Color::Green);
    }

    void dying()
    {
        Alive = false;
        Spawning = false;
        Dying = true;
        tile.setFillColor(sf::Color::Red);
        //tile.setFillColor(sf::Color::White);
    }

    void Live()
    {

    }


    void Kill()
    {
        Alive = false;
        Spawning = false;
        Dying = false;
        tile.setFillColor(sf::Color::White);
    }

    bool alive()
    {
        return Alive;
    }

    void Resolve()
    {
        if(Dying)
        {
            Kill();
            return;
        }
        if(Spawning)
        {
            Alive = true;
            Dying = false;
            Spawning = false;
            tile.setFillColor(sf::Color::Black);
            return;
        }

        Live();
    }


};



#endif // LIFETILE_HPP_INCLUDED
