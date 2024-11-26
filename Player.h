#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

public:
    enum Dir
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STOP
    }; // This is the direction state

<<<<<<< HEAD
        Player(GameMechs* thisGMRef);
        Player();
        ~Player();
=======
    Player(GameMechs *thisGMRef);
    ~Player();
>>>>>>> 0cac7c2f49ca2185e8f3824bfb4b6c122eb37bd5

    objPos getPlayerPos() const; // Upgrade this in iteration 3.
    void updatePlayerDir();
    void movePlayer();

    // More methods to be added here

private:
    objPos playerPos; // Upgrade this in iteration 3.
    enum Dir myDir;

    // Need a reference to the Main Game Mechanisms
    GameMechs *mainGameMechsRef;
};

#endif