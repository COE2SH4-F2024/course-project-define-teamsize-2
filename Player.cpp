#include "Player.h"
#include <iostream>

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    playerPos.pos->x = (mainGameMechsRef->getBoardSizeX()) / 2;
    playerPos.pos->y = (mainGameMechsRef->getBoardSizeY()) / 2;
    playerPos.symbol = '*';
}

Player::~Player()
{
    // delete any heap members here

    delete mainGameMechsRef;
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos array list

    return playerPos;
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

        default:
            break;
        }

        mainGameMechsRef->clearInput();
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    if (myDir == UP)
    {
        playerPos.pos->y--;
        if (playerPos.pos->y == 0)
            playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
    }
    else if (myDir == DOWN)
    {
        playerPos.pos->y++;
        if (playerPos.pos->y == mainGameMechsRef->getBoardSizeY() - 1)
            playerPos.pos->y = 1;
    }
    else if (myDir == LEFT)
    {
        playerPos.pos->x--;
        if (playerPos.pos->x == 0)
            playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
    }
    else if (myDir == RIGHT)
    {
        playerPos.pos->x++;
        if (playerPos.pos->x == mainGameMechsRef->getBoardSizeX() - 1)
            playerPos.pos->x = 1;
    }
}

// More methods to be added