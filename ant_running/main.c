#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h>

#define MAX_ENTITY_COUNT 10
#define MAX_X_POS 10
#define MAX_Y_POS 5

HANDLE hConsole;


uint32_t entityCount;

typedef struct entity{
	uint32_t fieldNumber;
	uint32_t entityPositionX;
	uint32_t entityPositionY;
}entity_t;

entity_t aEntities[MAX_ENTITY_COUNT];
 
void generateEntities(uint8_t om[MAX_X_POS][MAX_Y_POS])
{
	srand((unsigned int)time(NULL));
	entityCount = 0;

	for(uint32_t y=0; y < MAX_Y_POS; y++)
	{
		for(uint32_t x=0; x<MAX_X_POS; x++)
		{
			if(entityCount == MAX_ENTITY_COUNT)
			{
				return;
			}
			else
			{
				int randomNumber = rand();
				if((randomNumber % 20) == 0)
				{
					aEntities[entityCount].fieldNumber = ((y * MAX_X_POS) + x);
					aEntities[entityCount].entityPositionX = x;
					aEntities[entityCount].entityPositionY = y;

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
}

void renderEntities(void)
{
	uint32_t counter = 0;

//    COORD pos = {0, 0};
//    SetConsoleCursorPosition(hConsole, pos);

	//    WriteConsole(hConsole, "Hello", 5, NULL, NULL);

	for(uint32_t y=0; y < MAX_Y_POS; y++)
	{
		for(uint32_t x=0; x<MAX_X_POS; x++)
		{
			if (aEntities[counter].entityPositionX == x)
			{
				if (aEntities[counter].entityPositionY == y)
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

	for(uint32_t counter; counter < entityCount; counter++)
	{
		printf("fieldNumber:      %d\n", aEntities[counter].fieldNumber);
		printf("entityPosistionX: %d\n", aEntities[counter].entityPositionX);
		printf("entityPosistionY: %d\n", aEntities[counter].entityPositionY);
		printf("\n");
	}

}


void moveEntities(uint8_t om[MAX_X_POS][MAX_Y_POS])
{
	//srand((unsigned int)time(NULL));

	for(uint32_t counter=0; counter < entityCount; counter++)
	{
		int randomNumber = rand();
		switch(randomNumber % 4)
		{
			case 0:	// move up
				if (aEntities[counter].entityPositionY != 0)
				{
					aEntities[counter].entityPositionY--;
					printf("%d --> ", aEntities[counter].fieldNumber);
					aEntities[counter].fieldNumber = ((aEntities[counter].entityPositionY * MAX_X_POS) + aEntities[counter].entityPositionX);
					printf("%d = (%d * %d) + %d)\n", aEntities[counter].fieldNumber, aEntities[counter].entityPositionY, MAX_X_POS, aEntities[counter].entityPositionX);
				}
				break;
			case 1:	// move right
				if (aEntities[counter].entityPositionX != MAX_X_POS)
				{
					aEntities[counter].entityPositionX++;
					printf("%d --> ", aEntities[counter].fieldNumber);
					aEntities[counter].fieldNumber = ((aEntities[counter].entityPositionY * MAX_X_POS) + aEntities[counter].entityPositionX);
					printf("%d = (%d * %d) + %d)\n", aEntities[counter].fieldNumber, aEntities[counter].entityPositionY, MAX_X_POS, aEntities[counter].entityPositionX);
				}
				break;
			case 2:	// move down
				if (aEntities[counter].entityPositionY != MAX_Y_POS)
				{
					aEntities[counter].entityPositionY++;
					printf("%d --> ", aEntities[counter].fieldNumber);
					aEntities[counter].fieldNumber = ((aEntities[counter].entityPositionY * MAX_X_POS) + aEntities[counter].entityPositionX);
					printf("%d = (%d * %d) + %d)\n", aEntities[counter].fieldNumber, aEntities[counter].entityPositionY, MAX_X_POS, aEntities[counter].entityPositionX);
				}
				break;
			case 3:	// move left
				if (aEntities[counter].entityPositionX != 0)
				{
					aEntities[counter].entityPositionX--;
					printf("%d --> ", aEntities[counter].fieldNumber);
					aEntities[counter].fieldNumber = ((aEntities[counter].entityPositionY * MAX_X_POS) + aEntities[counter].entityPositionX);
					printf("%d = (%d * %d) + %d)\n", aEntities[counter].fieldNumber, aEntities[counter].entityPositionY, MAX_X_POS, aEntities[counter].entityPositionX);
				}
				break;
		}
	}
	//bubblesort(e);

	uint32_t tempField, tempX, tempY;

	for (uint32_t i = 1; i < entityCount; i++)
	{
		for (uint32_t j = 0; j < entityCount - i; j++) 
		{
			if (aEntities[j].fieldNumber > aEntities[j + 1].fieldNumber)
			{
				printf("array[%d].fieldNumber (%d) > array[%d].fieldNumber (%d)\n", j, aEntities[j].fieldNumber, (j+1), aEntities[j+1].fieldNumber);
				tempField = aEntities[j].fieldNumber;
				aEntities[j].fieldNumber = aEntities[j + 1].fieldNumber;
				aEntities[j + 1].fieldNumber = tempField;

				tempX = aEntities[j].entityPositionX;
				aEntities[j].entityPositionX = aEntities[j + 1].entityPositionX;
				aEntities[j + 1].entityPositionX = tempX;

				tempY = aEntities[j].entityPositionY;
				aEntities[j].entityPositionY = aEntities[j + 1].entityPositionY;
				aEntities[j + 1].entityPositionY = tempY;


				
			}
			else
			{
				printf("array[%d].fieldNumber (%d) < array[%d].fieldNumber (%d)\n", j, aEntities[j].fieldNumber, (j+1), aEntities[j+1].fieldNumber);
			}
		}
		printf("\n");
	}
}

int main(void)
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//entity_t *pEntity = malloc(sizeof(entity_t) * MAX_ENTITY_COUNT);

	uint8_t myOccupationMatrix[MAX_X_POS][MAX_Y_POS];

	generateEntities(myOccupationMatrix);

	renderEntities();
	printf("\nEntity Count: %d\n", entityCount);

	for(uint32_t i=0; i<1; i++)
	{
		_sleep(1);
		moveEntities(myOccupationMatrix);
		renderEntities();
	}





//	COORD pos2 = {0,22};
//	SetConsoleCursorPosition(hConsole, pos2);


	return 0;
}
