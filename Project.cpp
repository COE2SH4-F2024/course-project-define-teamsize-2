#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *mainGameMechsRef = new GameMechs();
Player *player = new Player(mainGameMechsRef);

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    Initialize();

    while (mainGameMechsRef->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    mainGameMechsRef->getExitFlagStatus() == false;
}

void GetInput(void)
{
    if (MacUILib_hasChar() != 0){
        mainGameMechsRef->setInput(MacUILib_getChar());
    }
  
    
}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    for (int i = 0; i < mainGameMechsRef->getBoardSizeY(); i++)
    {
        for (int j = 0; j < mainGameMechsRef->getBoardSizeX(); j++)
        {
            if (i == 0 || i == mainGameMechsRef->getBoardSizeY() - 1 || j == 0 || j == mainGameMechsRef->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }
            else if (i == player->getPlayerPos().pos->y && j == player->getPlayerPos().pos->x)
            {
                MacUILib_printf("%c", player->getPlayerPos().symbol);
            }
            else
            {
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();

    MacUILib_uninit();

    delete mainGameMechsRef;
    delete player;
}