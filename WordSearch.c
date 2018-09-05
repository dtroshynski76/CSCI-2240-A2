/*
Name:
Assignment: 2
Due Date: 16 February 2016
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 50

void inputGridLetters();
int inputWords(char findThis[MAX_SIZE]);
int findMatch(char findThis[MAX_SIZE], char lookHere[MAX_SIZE][MAX_SIZE], int square, int findLength, int keys[MAX_SIZE*MAX_SIZE*2]);
void displayGrid(char displayGrid[MAX_SIZE][MAX_SIZE], int square);

char inputString[MAX_SIZE];
char inputGrid[MAX_SIZE][MAX_SIZE];
char findThis[MAX_SIZE];

int square;
int foundKeys = 0;

int main()
{
    int keys[MAX_SIZE*MAX_SIZE*2];

    size_t x, y, b;

    int findLength, save = 0;
    
    inputGridLetters();

    findLength = inputWords(findThis);

    b = 0;
    while(b < 52 )
    {
        foundKeys = findMatch(findThis, inputGrid, square, findLength, keys);
        findLength = inputWords(findThis);
        b++;
    }

    for(x = 0; x < square; x++)
    {
        for(y = 0; y < square; y++)
        {
            save = 0;
            for(b = 0; b < foundKeys; b += 2)
            {
                if(keys[b] == x && keys[b + 1] == y)
                    save = 1;
            }
            if(save == 0)
                inputGrid[x][y] = ' ';
        }
    }

    displayGrid(inputGrid, square);
    return 0;
}

int findMatch( char findThis[MAX_SIZE], char lookHere[MAX_SIZE][MAX_SIZE], int square, int findLength,
        int keys[MAX_SIZE*MAX_SIZE*2] )
{
    size_t i, j, k, y, x, noMatch, oldKeys = 0;

    for(i = 0; i < square; i++)
    {
        for(j = 0; j < square; j++)
        {
            k = 0;
            noMatch = lookHere[i][j] == findThis[k];
            if(noMatch && k < findLength)
            {
                oldKeys = foundKeys;
                keys[foundKeys++] = i;
                keys[foundKeys++] = j;

                /* EAST */
                for(y = j + 1, k = 1; y < square && k < findLength && lookHere[i][y] == findThis[k]; y++, k++)
                {
                    keys[foundKeys++] = i;
                    keys[foundKeys++] = y;
                }
                if(k < findLength)
                {
                    foundKeys = oldKeys;
                }
                else
                    oldKeys = foundKeys;


                /* WEST */
                for(y = j - 1, k = 1; y >= 0 && k < findLength && lookHere[i][y] == findThis[k]; y--, k++)
                {
                    keys[foundKeys++] = i;
                    keys[foundKeys++] = y;
                }
                if(k < findLength)
                {
                    foundKeys = oldKeys;
                }
                else
                    oldKeys = foundKeys;

                /* NORTH */
                for(x = i - 1, k = 1; x >= 0 && k < findLength && lookHere[x][j] == findThis[k]; x--, k++)
                {
                    keys[foundKeys++] = x;
                    keys[foundKeys++] = j;
                }
                if(k < findLength)
                    foundKeys = oldKeys;
                else
                    oldKeys = foundKeys;

                /* SOUTH */
                for(y = i + 1, k = 1; y < square && k < findLength && lookHere[y][j] == findThis[k]; y++, k++)
                {
                    keys[foundKeys++] = y;
                    keys[foundKeys++] = j;
                }
                if(k < findLength)
                    foundKeys = oldKeys;
                else
                    oldKeys = foundKeys;

                /* NORTHWEST */
                for(x = i - 1, y = j - 1, k = 1; x >= 0 && y >= 0 && k < findLength && lookHere[x][y] == findThis[k]; x--, y--, k++)
                {
                    keys[foundKeys++] = x;
                    keys[foundKeys++] = y;
                }
                if(k < findLength)
                    foundKeys = oldKeys;
                else
                    oldKeys = foundKeys;

                /* NORTHEAST */
                for(x = i - 1, y = j + 1, k = 1; x >= 0 && y < square && k < findLength && lookHere[x][y] == findThis[k]; x--, y++, k++)
                {
                    keys[foundKeys++] = x;
                    keys[foundKeys++] = y;
                }
                if(k < findLength)
                    foundKeys = oldKeys;
                else
                    oldKeys = foundKeys;

                /* SOUTHWEST */
                for(x = i + 1, y = j - 1, k = 1; x < square && y >= 0 && k < findLength && lookHere[x][y] == findThis[k]; x++, y--, k++)
                {
                    keys[foundKeys++] = x;
                    keys[foundKeys++] = y;
                }
                if(k < findLength)
                    foundKeys = oldKeys;
                else
                    oldKeys = foundKeys;

                /* SOUTHEAST */
                for(x = i + 1, y = j + 1, k = 1; x < square && y < square && k < findLength && lookHere[x][y] == findThis[k]; x++, y++, k++)
                {
                    keys[foundKeys++] = x;
                    keys[foundKeys++] = y;
                }
                if(k < findLength)
                    foundKeys = oldKeys;
                else
                    oldKeys = foundKeys;
            }
        }
    }
    return foundKeys;
}

void inputGridLetters()
{
    size_t x, z;
    int i;
    x = 0;

   	fgets(inputString, (MAX_SIZE + 1), stdin);

    square = 0;
    for( i = 0; i < (MAX_SIZE + 1); i++ )
    {
        if ( inputString[i] >= 65 && inputString[i] <= 90 )
        {
            inputGrid[0][square++] = inputString[i];
        }
    }

    for(x = 1; x < square; x++)
    {
        fgets(inputString, (MAX_SIZE + 1), stdin);
        for(i = 0, z = 0; i < (MAX_SIZE + 1); i++)
        {
            if(inputString[i] >= 65 && inputString[i] <= 90)
                inputGrid[x][z++] = inputString[i];
        }
    }
}

int inputWords(char findThis[MAX_SIZE])
{
    fgets(findThis, (MAX_SIZE + 1), stdin);
    return strlen(findThis) - 1;
}

void displayGrid( char displayGrid[MAX_SIZE][MAX_SIZE], int square) 
{
    size_t i, j;
    for( i = 0; i < square; i++ )
    {
        for( j = 0; j < square; j++ )
        {
            printf( "%c ", displayGrid[i][j]);
        }
        printf( "\n" );
    }
}
