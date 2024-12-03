#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
private:
    char input;
    bool exitFlag;
    bool loseFlag;
    bool specialFood;
    int score;

    int boardSizeX;
    int boardSizeY;

    objPos food;
    objPosArrayList *foodBucket;

public:
    GameMechs();
    GameMechs(int boardX, int boardY);

    ~GameMechs(); // Needed to delete the foodBucket pointer created on the heap

    bool getExitFlagStatus() const;
    void setExitTrue();
    bool getLoseFlagStatus() const;
    void setLoseFlag();

    // Added functions to help with the Special Food Objects

    bool getSpecialFood() const;
    void setSpecialFood(bool a);

    char getInput() const;
    void setInput(char this_input);
    void clearInput();

    int getBoardSizeX() const;
    int getBoardSizeY() const;

    int getScore() const;
    void incrementScore();

    void generateFood(objPosArrayList *blockoff);
    objPosArrayList &getFoodPos() const;
};

#endif