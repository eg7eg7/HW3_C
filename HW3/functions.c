#include "functions.h"
#include <stdio.h>


void menu(Hotel* hotel, char* path)
{
	char userInput = 'a';
	int feature;
	initHotel(hotel, path);
	if (hotel->num_rooms_in_floor > 2)
	{
		printf("Hotel has more than 3 rooms per floor, demonstrating question 2.e in the pdf...\nPrinting the rooms using the vararg function that have a terrace\n");
		printRoomListWithFeature(R_TERRACE, &(hotel->rooms[0][0]), &(hotel->rooms[0][1]), &(hotel->rooms[0][2]), NULL);
	}
	while (userInput != '0')
	{
		printf("Welcome to hotel.\nChoose one of the following options:\n");
		printf("*Press 1 to print Hotel rooms information.\n");
		printf("*Press 2 to print all rooms with a certain feature.\n");
		printf("*Press 0 to exit. \n//WARNING : EXITING BRUTALLY DOES NOT SAVE HOTEL DATA TO FILE.//\n");
		printf("USER: ");
		scanf(" %c", &userInput);
		printf("\n");
		switch (userInput)
		{
		case '1':
			printHotel(hotel, -1);	//print all rooms, no constraints.
			break;
		case '2':
			printf("\nChoose which feature you want in the rooms:\n");
			printf("Type %d for all rooms with a view to the pool.\n", R_VIEW);
			printf("Type %d for all rooms with a terrace.\n", R_TERRACE);
			printf("Type %d for all rooms with a kettle.\n", R_KETTLE);
			printf("Type %d for all rooms with free wifi.\n", R_WIFI);
			printf("Type %d for all rooms with extendable couch.\n", R_COUCH);
			printf("Type %d for all rooms with a TV.\n", R_TV);
			printf("Type %d for all rooms which are free.\n", R_OCCUPIED);
			printf("Type -1 to return to main menu.\n");
			printf("USER: ");
			scanf("%d", &feature);
			printf("\n");
			if (feature != -1)
				printHotel(hotel, feature);
			break;
		case '3':

			break;
		case '0':
			if (path == NULL)
				encryptAndSaveHotel(hotel, defaultHotelSavePath,0);
			else
				encryptAndSaveHotel(hotel, path,1);
			freeHotel(hotel);
			break;
		}
	}

}




void printByte(unsigned char byte)
{
	unsigned char temp;
	for (int i = 0; i < 8; i++)
	{
		temp = byte << i;
		temp = temp >> 7;
		printf("%d", temp);
	}
	printf("\n");
}


void rotateByteRight(unsigned char* target, int x)
{
	for (int i = 0; i < x; i++)
	{
		unsigned char bit = getBitAtIndex(*target, 0);
		*target = *target >> 1;
		bit = bit << 7;
		*target = *target | bit;
	}
}

void setBitAtIndex(char* target, int index, unsigned char value)
{
	unsigned char mask = 1;	//00000001
	mask = mask << index;	//shifting the 1 to index 00010000 for example (index=4) 
	mask = ~mask;		//negates all bits	11101111
	*target = *target & mask;	//zeros the bit at index
	*target = *target | (value << index);	//puts the value at index
}
unsigned char getBitAtIndex(unsigned char target, int x)
{

	target = target << (7 - x);
	target = target >> 7;
	return target;
}

int fileExist(char* path)
{
	FILE* f;
	if (f = fopen(path, "r"))
	{
		fclose(f);
		return 1;
	}
	return 0;
}