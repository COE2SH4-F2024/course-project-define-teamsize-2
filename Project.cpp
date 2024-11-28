#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *gameMechs = NULL;
objPos object[5];
objPos player(6,6,'*'); //Take this out later and replace with Player.h variables when ready
enum Dir
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STOP
    } dir; // Take this out later and replace with Player.h when ready

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    Initialize();

    while (gameMechs->getExitFlagStatus() == 0)
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

    //Allocate Memory for Game Mechanics
    gameMechs = new GameMechs();
    dir = STOP;

    for (int i = 0; i < 5; i++)
    {
        object[i] = objPos(i + 1, i + 1, 65 + i);
    }

}

void GetInput(void)
{
    if (MacUILib_hasChar() != 0){
        gameMechs->setInput(MacUILib_getChar());
    }
    
}

void RunLogic(void)
{
    char input = gameMechs->getInput();
    int boardWidth = gameMechs->getBoardSizeX();
    int boardLength = gameMechs->getBoardSizeY();
    
    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case ' ':  // exit
                gameMechs->setExitTrue();
                break;    

            case 'W':
            case 'w':
                if (dir == LEFT || dir == RIGHT || dir == STOP){
                    dir = UP;
                }
                break;
            case 'A':
            case 'a':
                if (dir == UP || dir == DOWN || dir == STOP){
                    dir = LEFT;
                }
                break;
            case 'S':
            case 's':
                if (dir == LEFT || dir == RIGHT || dir == STOP){
                    dir = DOWN;
                }
                break;
            case 'D':
            case 'd':
                if (dir == UP || dir == DOWN || dir == STOP){
                    dir = RIGHT;
                }
                break;
            default:
                break;
        }
        input = '\0'; //Set input back to null to avoid unnecessary program actions
    }

    //CHANGE WITH PLAYER.H->updatePlayerDir(); when ready
    if (dir == UP){
        player.pos->x--;
    }
    else if (dir == LEFT){
        player.pos->y--;
    }
    else if (dir == DOWN){
        player.pos->x++;
    }
    else if (dir == RIGHT){
        player.pos->y++;
    }

    //Wrap-around the boarders
    if (player.pos->x == 0){
        player.pos->x = boardWidth-2;
    }
    else if (player.pos->x == boardWidth-1){
        player.pos->x = 1;
    }

    if (player.pos->y == 0){
        player.pos->y = boardLength-2;
    }
    else if (player.pos->y == boardLength-1){
        player.pos->y = 1;
    }


    //Clear the input within the object once the direction is updated to avoid double-processing
    gameMechs->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    int insert = 0;
    int boardWidth = gameMechs->getBoardSizeX();
    int boardLength = gameMechs->getBoardSizeY();

    for (int i = 0; i < boardWidth; i++)
    {
        for (int j = 0; j < boardLength; j++)
        {
            if (i == 0 || i == boardWidth-1 || j == 0 || j == boardLength-1)
            {
                MacUILib_printf("#");
            }
            else if (i==player.pos->x && j==player.pos->y){
                MacUILib_printf("%c", player.symbol);
            }
            else
            {
                for (int k = 0; k < 5; k++)
                {
                    if (i == object[k].pos->x && j == object[k].pos->y)
                    {
                        MacUILib_printf("%c", object[k].symbol);
                        insert = 1;
                    }
                }
                if (!insert)
                    MacUILib_printf(" ");
            }
            insert = 0;
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
    delete gameMechs;

    MacUILib_uninit();
}
