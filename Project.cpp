#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

using namespace std;

#define DELAY_CONST 100000
#define BOARD_WIDTH 10
#define BOARD_LENGTH 20

bool exitFlag;
objPos object[5];

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
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

    exitFlag = false;

    for (int i=0; i<5;i++){
        object[i]=objPos(i+1,i+1,65+i);
    }

}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  

    int insert = 0;

    for(int i=0; i<BOARD_WIDTH;i++){
        for(int j=0; j<BOARD_LENGTH;j++){
            if(i==0 || i==9 || j==0 || j ==19){
                MacUILib_printf("#");
            }
            else{
                for(int k=0;k<5;k++){
                    if (i==object[k].pos->x && j==object[k].pos->y){
                        MacUILib_printf("%c",object[k].symbol);
                        insert = 1;
                    }
                }
                if(!insert)
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

    MacUILib_uninit();
}
