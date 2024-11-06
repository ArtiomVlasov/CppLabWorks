#include <string>
#include <list>

class Cell
{
public:
    virtual void action() const = 0;
    virtual ~Cell() = default;
};

Cell::Cell(/* args */)
{
}

Cell::~Cell()
{
}

class Player
{
private:
    std::string name;
    int balance;
    int position;
    std::list<Property> listOfProperty;

public:
    Player();
    void makeMove(int prevPos);
    ~Player();
};

class Property
{
private:
    std::string name;
    enum colour
    {
        brown,
        white,
        pink,
        orange,
        red,
        yellow,
        green,
        blue
    }; // only for streets, change then
    int price;
    int rent;
    std::string owner;

public:
    Property(/* args */);
    ~Property();
};

class Board
{
private:
public:
    Board();
    ~Board();
};

class Game
{
private:
    /* data */
public:
    Game(/* args */);
    ~Game();
};
