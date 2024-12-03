#include "GameMechs.h"
#include <stdlib.h>
#include <time.h>

GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    exitFlag = false;
    loseFlag = false;
    specialFood = false;
    score = 0;
    input = '\0';

    foodBucket = new objPosArrayList;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    loseFlag = false;
    specialFood = false;
    score = 0;
    input = '\0';
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    delete foodBucket;
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

bool GameMechs::getSpecialFood() const
{
    return specialFood;
}

void GameMechs::setSpecialFood(bool a)
{
    specialFood = a;
}

// More methods should be added here
void GameMechs::generateFood(objPosArrayList *blockoff)
{
    delete foodBucket;
    foodBucket = new objPosArrayList;
    int randX, randY;
    bool overlap;

    for (int k = 0; k < 5; k++){
        srand(time(NULL));

        int sizeBucket = foodBucket->getSize();

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

            overlap = false; //Reset overlap to false every iteration

            //Make sure multiple food objects do not spawn on the same location
            for (int j = 0; j < sizeBucket; j++)
            {
                while (foodBucket->getElement(j).pos->x == randX && foodBucket->getElement(j).pos->y == randY)
                {
                    randX = rand() % (boardSizeX - 2) + 1;
                    randY = rand() % (boardSizeY - 2) + 1;
                }
            }

            //Randomly Picks whether 1 or 2 "special" food objects are generated
            int randGen = (rand() % 2);
            
            //First food object within foodBucket goes the the head, the rest are inserted to the tail
            if(k==0){
                objPos foodGen(randX,randY,'F');
                foodBucket->insertHead(foodGen);
            }
            else if (k==randGen){
                objPos foodGen(randX,randY,'F');
                foodBucket->insertTail(foodGen);
            }
            else{
                objPos foodGen(randX,randY,'f');
                foodBucket->insertTail(foodGen);
            }
            
    }
}

objPosArrayList &GameMechs::getFoodPos() const
{
    return *foodBucket;
}