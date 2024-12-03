#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
public:
    enum Dir
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STOP
    }; // This is the direction state

    Player(GameMechs *thisGMRef);
    Player();
    ~Player();

    objPosArrayList &getPlayerPos() const;
    void updatePlayerDir();
    void movePlayer();

    bool checkFoodConsumption();
    void increasePlayerLength();

    bool checkSelfCollision();

private:
    objPosArrayList *playerPosList;
    enum Dir myDir;

    // Need a reference to the Main Game Mechanisms
    GameMechs *mainGameMechsRef;
};

#endif