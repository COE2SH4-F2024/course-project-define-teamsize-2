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

    mainGameMechsRef->generateFood(&player->getPlayerPos());
}

void GetInput(void)
{
    if (MacUILib_hasChar() != 0)
    {
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

    objPosArrayList currPlayerPos = player->getPlayerPos();
    objPosArrayList foodBucket = mainGameMechsRef->getFoodPos();

    int size = currPlayerPos.getSize();
    int foodSize = foodBucket.getSize();
    int check = 0;

    for (int i = 0; i < mainGameMechsRef->getBoardSizeY(); i++)
    {
        for (int j = 0; j < mainGameMechsRef->getBoardSizeX(); j++)
        {
            if (i == 0 || i == mainGameMechsRef->getBoardSizeY() - 1 || j == 0 || j == mainGameMechsRef->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }
            else
            {
                for (int l = 0; l < foodSize && !check; l++)
                {
                    if (i == foodBucket.getElement(l).pos->y && j == foodBucket.getElement(l).pos->x)
                    {
                        MacUILib_printf("%c", foodBucket.getElement(l).symbol);
                        check = 1;
                    }
                }
                for (int k = 0; k < size && !check; k++)
                {
                    if (i == currPlayerPos.getElement(k).pos->y && j == currPlayerPos.getElement(k).pos->x)
                    {
                        MacUILib_printf("%c", currPlayerPos.getElement(k).symbol);
                        check = 1;
                    }
                }
                if (!check)
                    MacUILib_printf("%c", ' ');
            }
            check = 0;
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("\nScore: %d\n", mainGameMechsRef->getScore());
    MacUILib_printf("\nf is normal food\nF is special food - Increases Score by 2 without increasing the length\n");

    if (mainGameMechsRef->getExitFlagStatus() && mainGameMechsRef->getLoseFlagStatus())
        MacUILib_printf("\nYou have lost!\n");
    else if (mainGameMechsRef->getExitFlagStatus())
        MacUILib_printf("\nGame exited\n");
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{

    MacUILib_uninit();

    delete mainGameMechsRef;
    delete player;
}