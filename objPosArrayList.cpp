#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

objPosArrayList::objPosArrayList(const objPosArrayList &d)
{
    listSize = d.listSize;
    arrayCapacity = d.arrayCapacity;

    aList = new objPos[arrayCapacity];

    for (int i = 0; i < listSize; ++i)
    {
        aList[i] = d.aList[i];
    }
}

objPosArrayList &objPosArrayList::operator=(const objPosArrayList &d)
{
    if (this != &d)
    {
        delete[] aList; // Deallocate memory before assigning new memory

        listSize = d.listSize;
        arrayCapacity = d.arrayCapacity;

        aList = new objPos[arrayCapacity];

        for (int i = 0; i < listSize; ++i)
        {
            aList[i] = d.aList[i];
        }
    }
    return *this;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize < arrayCapacity && listSize != 0) // If the list is not empty
    {
        for (int i = listSize; i > 0; i--) // Shift all elements to the right
        {
            aList[i] = aList[i - 1];
        }

        aList[0] = thisPos;
        listSize++;
    }
    else if (listSize == 0)
    {
        aList[0] = thisPos;
        listSize++;
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize < arrayCapacity) // If the list is not full
    {
        aList[listSize] = thisPos;
        listSize++;
    }
}

void objPosArrayList::removeHead()
{
    if (listSize > 0)
    {
        for (int i = 0; i < listSize - 1; i++) // Shift all elements to the left
        {
            aList[i] = aList[i + 1];
        }

        listSize--;
    }
}

void objPosArrayList::removeTail()
{
    if (listSize > 0)
        listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}