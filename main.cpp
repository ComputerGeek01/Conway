#include "LifeTile.hpp"



int main(int argv, char* argc[])
{
    srand(time(NULL));

    sf::Time MyTime;
    int WindowSize = 700;
    sf::RenderWindow Window(sf::VideoMode(WindowSize, WindowSize), "It's Life");
    Window.setFramerateLimit(60);

    sf::Vector2i WindowPos = Window.getPosition();
    sf::Vector2i MouseCords;
    sf::FloatRect Test;

    int TileSize = 20;
    int Limit = 25;
    const int ArrSize = Limit * Limit;
    int Living = 500;

    sf::Clock Clock;

    Tile TileArray[Limit][Limit];

    std::cout << "Array Size: " << ArrSize << std::endl;

    for(int y = 0; y < Limit; ++y)
    {
        for(int x = 0; x < Limit; ++x)
        {
            int X = TileSize + (TileSize * x) % (Limit * TileSize);
            int Y = TileSize + y * TileSize;

            TileArray[x][y].Place(sf::Vector2f(X, Y));
        }
    }

    for(int i = 0; i < Living; ++i)
    {
        int ThatOneBase = rand() % ArrSize;
        int ThatOneX = ThatOneBase % Limit;
        int ThatOneY = ThatOneBase / Limit;

        std::cout << ThatOneX << "," << ThatOneY << std::endl;

        TileArray[ThatOneX][ThatOneY].Spawn();
    }

    while(Window.isOpen())
    {
        sf::Event event;
        while(Window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    Window.close();
                break;

                case sf::Event::MouseButtonPressed:
                    MouseCords = sf::Mouse::getPosition(Window);

                    for(int y = 0; y < Limit; ++y)
                    {
                        for(int x = 0; x < Limit; ++x)
                        {
                            Test = TileArray[x][y].tile.getGlobalBounds();

                            if(MouseCords.x > Test.left && MouseCords.x < (Test.left + Test.width) && MouseCords.y >= Test.top && MouseCords.y <= (Test.top + Test.height))
                            {
                                std::cout << "Tile " << x << "," << y << " Has Neighbors: " << TileArray[x][y].Neighbors() << "\n";
                                std::cout << "Left: " << Test.left << " Right: " << (Test.left + Test.width) << " Top: " << Test.top << " Bottom: " << (Test.top + Test.height) << std::endl;
                                //TileArray[x][y].Status();
                                if(!TileArray[x][y].alive())
                                {
                                    TileArray[x][y].Spawn();
                                }
                                else
                                {
                                    TileArray[x][y].dying();
                                }
                            }
                        }
                    }

                break;
            }
        }

                //case sf::Event::KeyPressed:
                    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    //{
                    if(Clock.getElapsedTime().asSeconds() >= .75)
                    {
                        Clock.restart();
                        for(int y = 0; y < Limit; ++y)
                        {
                            for(int x = 0; x < Limit; ++x)
                            {
                                TileArray[x][y].Resolve();
                                TileArray[x][y].Clear();
                                if(y > 0)
                                {
                                    if(x > 0)
                                    {
                                        if(TileArray[(x - 1)][(y - 1)].alive())
                                        {
                                            TileArray[x][y].UPLEFT = true;
                                        }
                                    }

                                    if(TileArray[(x)][(y - 1)].alive())
                                    {
                                        TileArray[x][y].UP = true;
                                    }

                                    if(x != (Limit - 1))
                                    {
                                        if(TileArray[(x + 1)][(y - 1)].alive())
                                        {
                                            TileArray[x][y].UPRIGHT = true;
                                        }
                                    }
                                }

                                if(x > 0)
                                {
                                    if(TileArray[(x - 1)][y].alive())
                                    {
                                        TileArray[x][y].LEFT = true;
                                    }
                                }

                                if(x != (Limit - 1))
                                {
                                    if(TileArray[(x + 1)][y].alive())
                                    {
                                        TileArray[x][y].RIGHT = true;
                                    }
                                }

                                if(y != (Limit - 1))
                                {
                                    if(x != 0)
                                    {
                                        if(TileArray[(x - 1)][(y + 1)].alive())
                                        {
                                            TileArray[x][y].DNLEFT = true;
                                        }
                                    }

                                    if(TileArray[(x)][(y + 1)].alive())
                                    {
                                        TileArray[x][y].DOWN = true;
                                    }

                                    if(x != (Limit - 1))
                                    {
                                        if(TileArray[(x + 1)][(y + 1)].alive())
                                        {
                                            TileArray[x][y].DNRIGHT = true;
                                        }
                                    }
                                }
                            }
                        }

                        for(int y = 0; y < Limit; ++y)
                        {
                            for(int x = 0; x < Limit; ++x)
                            {
                                if(TileArray[x][y].alive())
                                {
                                    switch(TileArray[x][y].Neighbors())
                                    {
                                        case 0:
                                            std::cout << x << "," << y << " Has 0 Neighbors And DIES\n";
                                            TileArray[x][y].dying();
                                        break;

                                        case 1:
                                            std::cout << x << "," << y << " Has 1 Neighbor And DIES\n";
                                            TileArray[x][y].dying();
                                        break;

                                        case 2:
                                            std::cout << x << "," << y << " Has 2 Neighbors And LIVES\n";
                                            TileArray[x][y].Live();
                                        break;

                                        case 3:
                                            std::cout << x << "," << y << " Has 3 Neighbors And LIVES\n";
                                            TileArray[x][y].Live();
                                        break;

                                        default:
                                            std::cout << x << "," << y << " Has Too Many Neighbors And Dies\n";
                                            TileArray[x][y].dying();
                                        break;
                                    }
                                }
                                else if(TileArray[x][y].Neighbors() == 3)
                                {
                                    std::cout << x << "," << y << " Has Spawned\n";
                                    TileArray[x][y].Spawn();
                                }
                            }
                        }
                    }
                    //}//If Space Is Pressed

                //}//Switch Case For Events

            //}//While Event Loop

        Window.clear(sf::Color::White);

        for(int y = 0; y < Limit; ++y)
        {
            for(int x = 0; x < Limit; ++x)
            {
                Window.draw(TileArray[x][y].tile);
            }
        }

        Window.display();

    }//While Window Is Open

    return 0;
}
