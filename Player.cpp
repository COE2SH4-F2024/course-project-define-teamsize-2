#include "Player.h"
#include <iostream>

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList;

    // more actions to be included
    objPos head((mainGameMechsRef->getBoardSizeX())/2,(mainGameMechsRef->getBoardSizeY())/2,'*');
    objPos head2(16,7,'*');
    objPos head3(17,7,'*');
    playerPosList->insertHead(head3);
    playerPosList->insertHead(head2);
    playerPosList->insertHead(head);
    
}

Player::~Player()
{
    // delete any heap members here

    delete mainGameMechsRef;
    delete playerPosList;
}

objPosArrayList& Player::getPlayerPos() const
{
    // return the reference to the playerPos array list

    return *playerPosList;
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

        case 'f': //debug key
            mainGameMechsRef->generateFood(playerPosList->getHeadElement());
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
    int nextPosX,nextPosY,currPosX = playerPosList->getHeadElement().pos->x, currPosY = playerPosList->getHeadElement().pos->y;

    if (myDir == UP)
    {
       nextPosY = --currPosY;
       if (nextPosY == 0)
            nextPosY = mainGameMechsRef->getBoardSizeY() - 2;

       objPos newHead(currPosX,nextPosY,'*');
       playerPosList->insertHead(newHead);
       playerPosList->removeTail();

    }
    else if (myDir == DOWN)
    {
       nextPosY = ++currPosY;
       if (nextPosY == mainGameMechsRef->getBoardSizeY() - 1)
            nextPosY = 1;

       objPos newHead(currPosX,nextPosY,'*');
       playerPosList->insertHead(newHead);
       playerPosList->removeTail();

    }
    else if (myDir == LEFT)
    {
        nextPosX = --currPosX;
        if (nextPosX == 0)
            nextPosX = mainGameMechsRef->getBoardSizeX() - 2;

        objPos newHead(nextPosX,currPosY,'*');
       playerPosList->insertHead(newHead);
       playerPosList->removeTail();
    }
    else if (myDir == RIGHT)
    {
       nextPosX = ++currPosX;
       if (nextPosX == mainGameMechsRef->getBoardSizeX() - 1)
            nextPosX = 1;
        
       objPos newHead(nextPosX,currPosY,'*');
       playerPosList->insertHead(newHead);
       playerPosList->removeTail();
    }

    
}

// More methods to be added