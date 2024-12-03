#include "Player.h"
#include <iostream>

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList;

    objPos head((mainGameMechsRef->getBoardSizeX()) / 2, (mainGameMechsRef->getBoardSizeY()) / 2, '*'); // Initial player head position (approx. middle of the board)

    playerPosList->insertHead(head);
}

Player::~Player()
{
    delete mainGameMechsRef;
    delete playerPosList;
}

objPosArrayList &Player::getPlayerPos() const
{
    return *playerPosList; // Return the reference to the playerPos array list
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic

    if (mainGameMechsRef->getInput() != '\0')
    {
        switch (mainGameMechsRef->getInput())
        {
        case ' ':
            mainGameMechsRef->setExitTrue();
            break;

        case 'w':
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
                myDir = UP;
            break;

        case 'a':
            if (myDir == UP || myDir == DOWN || myDir == STOP)
                myDir = LEFT;
            break;

        case 's':
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
                myDir = DOWN;
            break;

        case 'd':
            if (myDir == UP || myDir == DOWN || myDir == STOP)
                myDir = RIGHT;
            break;

        case 'f': // debug key
            mainGameMechsRef->generateFood(playerPosList);
            break;

        default:
            break;
        }

        mainGameMechsRef->clearInput();
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    int nextPosX, nextPosY, currPosX = playerPosList->getHeadElement().pos->x, currPosY = playerPosList->getHeadElement().pos->y;
    int X, Y = 0; // X and Y are the coordinates of the next head position

    if (myDir != STOP)
    {
        if (myDir == UP)
        {
            nextPosY = --currPosY;
            if (nextPosY == 0)
                nextPosY = mainGameMechsRef->getBoardSizeY() - 2;
        }
        else if (myDir == DOWN)
        {
            nextPosY = ++currPosY;
            if (nextPosY == mainGameMechsRef->getBoardSizeY() - 1)
                nextPosY = 1;
        }
        else if (myDir == LEFT)
        {
            nextPosX = --currPosX;
            if (nextPosX == 0)
                nextPosX = mainGameMechsRef->getBoardSizeX() - 2;
        }
        else if (myDir == RIGHT)
        {
            nextPosX = ++currPosX;
            if (nextPosX == mainGameMechsRef->getBoardSizeX() - 1)
                nextPosX = 1;
        }

        if (myDir == UP || myDir == DOWN)
        {
            X = currPosX;
            Y = nextPosY;
        }
        else if (myDir == LEFT || myDir == RIGHT)
        {
            X = nextPosX;
            Y = currPosY;
        }

        objPos newHead(X, Y, '*'); // New player head position

        if (checkFoodConsumption())
        {
            if (mainGameMechsRef->getSpecialFood())
            {
                for (int i = 0; i < 2; i++)
                    mainGameMechsRef->incrementScore();

                mainGameMechsRef->setSpecialFood(false);
                mainGameMechsRef->generateFood(playerPosList);
            }
            else
            {
                increasePlayerLength();
                mainGameMechsRef->incrementScore();
                mainGameMechsRef->generateFood(playerPosList);
            }
        }
        else
        {
            playerPosList->insertHead(newHead);
            playerPosList->removeTail();
        }
    }

    if (checkSelfCollision())
    {
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
    }
}

bool Player::checkFoodConsumption()
{
    objPosArrayList foodPos = mainGameMechsRef->getFoodPos();
    objPos playerHead = playerPosList->getHeadElement();

    for (int i = 0; i < foodPos.getSize(); i++)
    {
        if (foodPos.getElement(i).pos->x == playerHead.pos->x && foodPos.getElement(i).pos->y == playerHead.pos->y)
        {
            if (foodPos.getElement(i).symbol == 'F')
                mainGameMechsRef->setSpecialFood(true);
            return true;
        }
    }
    return false;
}

void Player::increasePlayerLength()
{
    objPos newHead(playerPosList->getHeadElement().pos->x, playerPosList->getHeadElement().pos->y, '*');
    playerPosList->insertHead(newHead);
}

bool Player::checkSelfCollision()
{
    for (int i = playerPosList->getSize(); i > 1; i--) // Iterate through the playerPosList starting from the tail going to the head
    {
        if (playerPosList->getHeadElement().pos->x == playerPosList->getElement(i).pos->x && playerPosList->getHeadElement().pos->y == playerPosList->getElement(i).pos->y)
            return true;
    }

    return false;
}