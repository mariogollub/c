#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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


uint32_t generateEntities(entity_t *e, uint8_t om[MAX_X_POS][MAX_Y_POS])
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

					om[x][y] = 1;

					entityCount++;
				}
				else
				{
					om[x][y] = 0;
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

void moveEntities(entity_t *e, uint8_t om[MAX_X_POS][MAX_Y_POS])
{
	uint32_t counter = 0;

	for(uint32_t i=0; i < entityCount; i++)
	{
		/*
			if (e[counter].entityPositionX == x)
			{
				if (e[counter].entityPositionY == y)
				{
					printf("E");
					counter++;
				}
			}
		*/
	}
}

int main(void)
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	entity_t myEntity[MAX_ENTITY_COUNT];
//	entity_t *pEntity = &myEntity[0];

	entity_t *pEntity = malloc(sizeof(entity_t) * MAX_ENTITY_COUNT);
	uint8_t myOccupationMatrix[MAX_X_POS][MAX_Y_POS];


	entityCount = generateEntities(pEntity, myOccupationMatrix);

	renderEntities(pEntity);
	printf("\nEntity Count: %d\n", entityCount);

	for(uint32_t i=0; i<10; i++)
	{
		_sleep(1);
		moveEntities(pEntity, myOccupationMatrix);
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


	return 0;
}
