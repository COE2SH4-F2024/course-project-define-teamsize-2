#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

int objPosArrayList::getSize() const{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos){

    if (listSize >= ARRAY_MAX_CAP) return;


    //Starting from i = 0 will overwrite the values in the array
    for (int i = listSize;i>=1;i--)
        aList[i]=aList[i-1];
    
    //aList[0] = thisval;
    listSize++;
}

void objPosArrayList::removeHead(){
    if(listSize == 0) return;

    for(int i = 0; i<listSize-1;i++)
        aList[i] = aList[i+1];

    listSize--;
}
