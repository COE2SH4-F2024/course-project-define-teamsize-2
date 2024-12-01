#include "GameMechs.h"
#include <stdlib.h>
#include <time.h>

GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    input = '\0';
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    input = '\0';
}

// do you need a destructor?
GameMechs::~GameMechs()
{
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    if (input != '\0')
        input = '\0';
}

// More methods should be added here
void GameMechs::generateFood(objPosArrayList *blockoff)
{
    srand(time(NULL));

    int randX, randY;
    bool overlap;

    do
    {
        randX = rand() % (boardSizeX - 2) + 1;
        randY = rand() % (boardSizeY - 2) + 1;
        overlap = false;

        // Check for overlap with any element in the playerPosList
        for (int i = 0; i < blockoff->getSize(); ++i)
        {
            if (blockoff->getElement(i).pos->x == randX && blockoff->getElement(i).pos->y == randY)
            {
                overlap = true;
                break;
            }
        }
    } while (overlap);

    food.pos->x = randX;
    food.pos->y = randY;
    food.symbol = 'F';
}

objPos GameMechs::getFoodPos() const
{
    return food;
}