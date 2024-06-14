#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_ENTITY_COUNT 1000
#define MAX_X_POS 100
#define MAX_Y_POS 25

uint32_t entityCount;

typedef struct entity{
	uint32_t entityIndex;
	uint32_t entityPositionX;
	uint32_t entityPositionY;
}entity_t;


uint32_t generateEntities(entity_t *pEntity)
{
	srand((unsigned int)time(NULL));

	for(uint32_t i=0; i < MAX_Y_POS; i++)
	{
		for(uint32_t j=0; j<MAX_X_POS; j++)
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
					pEntity[entityCount].entityIndex = entityCount;
					pEntity[entityCount].entityPositionX = i;
					pEntity[entityCount].entityPositionY = j;
					//printf("E");
					entityCount++;
				}
				else
				{
					//printf(" ");
					continue;
				}
			}
		}
		//printf("\n");
	}
	return entityCount;
}

int main(void)
{
//	entity myEntity[MAX_ENTITY_COUNT];
//	struct entity *pEntity = &myEntity[0];

//	printf("sizeof(entity_t): %d\n", sizeof(entity_t));

	entity_t *pEntity = malloc(sizeof(entity_t) * MAX_ENTITY_COUNT);

	entityCount = generateEntities(pEntity);

	printf("\nEntity Count: %d\n", entityCount);

/*for(uint32_t counter; counter < entityCount; counter++)
		{
	printf("entityIndex:      %d\n", entity[counter].entityIndex);
		printf("entityPosistionX: %d\n", entity[counter].entityPositionX);
		printf("entityPosistionX: %d\n", entity[counter].entityPositionY);
		printf("\n");
	}
*/
	return 0;
}
