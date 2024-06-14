#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <conio.h>
#include <windows.h>

#define MAX_ENTITY_COUNT 1000
#define MAX_X_POS 100
#define MAX_Y_POS 20

HANDLE hConsole;


uint32_t entityCount;

typedef struct entity{
	uint32_t entityIndex;
	uint32_t entityPositionX;
	uint32_t entityPositionY;
}entity_t;


uint32_t generateEntities(entity_t *e)
{
	srand((unsigned int)time(NULL));

	for(uint32_t y=0; y < MAX_Y_POS; y++)
	{
		for(uint32_t x=0; x<MAX_X_POS; x++)
		{
			if(entityCount == MAX_ENTITY_COUNT)
			{
				return entityCount;
			}
			else
			{
				int randomNumber = rand();
				if((randomNumber % 20) == 0)
				{
					e[entityCount].entityIndex = entityCount;
					e[entityCount].entityPositionX = x;
					e[entityCount].entityPositionY = y;
					entityCount++;
				}
				else
				{
					continue;
				}
			}
		}
	}
	return entityCount;
}

void renderEntities(entity_t *e)
{
	uint32_t counter = 0;

    
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hConsole, pos);
//    WriteConsole(hConsole, "Hello", 5, NULL, NULL);

	for(uint32_t y=0; y < MAX_Y_POS; y++)
	{
		for(uint32_t x=0; x<MAX_X_POS; x++)
		{
			if (e[counter].entityPositionX == x)
			{
				if (e[counter].entityPositionY == y)
				{
					printf("E");
					counter++;
				}
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

int main(void)
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	entity_t myEntity[MAX_ENTITY_COUNT];
//	entity_t *pEntity = &myEntity[0];

	entity_t *pEntity = malloc(sizeof(entity_t) * MAX_ENTITY_COUNT);

	entityCount = generateEntities(pEntity);

	renderEntities(pEntity);

	for(uint32_t i=0; i<10; i++)
	{
		sleep(0.5);
		moveEntities(pEntity);
		renderEntities(pEntity);
	}
/*
	for(uint32_t counter; counter < entityCount; counter++)
	{
		printf("entityIndex:      %d\n", pEntity[counter].entityIndex);
		printf("entityPosistionX: %d\n", pEntity[counter].entityPositionX);
		printf("entityPosistionX: %d\n", pEntity[counter].entityPositionY);
		printf("\n");
	}
*/


	COORD pos2 = {0,22};
	SetConsoleCursorPosition(hConsole, pos2);

	printf("\nEntity Count: %d\n", entityCount);
	return 0;
}
