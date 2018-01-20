#include <stdio.h>
#include <stdlib.h>
#include "hotel.h"
#include "encryption.h"
#include "functions.h"
void initHotel(Hotel* hotel, char* path)
{
	int new = 0;
	int user=0;
	if ((path != NULL && fileExist(path)) || fileExist(defaultHotelSavePath) )	//if args at main have path for older hotel
	{
		if (path == NULL)
			path = defaultHotelSavePath;
		new = readDecryptHotelFromFile(hotel, path);
		if (new == 0)
			printf("Hotel files do not exist, creating new hotel...\n");
	}

	if (new == 0)
	{
		int num_floors, num_rooms;
		printf("creating a new hotel..\n");
		printf("How many floors are in the hotel?\nUSER : ");
		scanf("%d", &num_floors);
		printf("How many rooms are on each floor?\nUSER : ");
		scanf("%d", &num_rooms);
		//create new hotel
		hotel->num_floors = num_floors;
		hotel->num_rooms_in_floor = num_rooms;
		hotel->rooms = (Room**)calloc(num_floors, sizeof(Room*)*num_rooms);	//allocates memory for num_floors floors in the hotel with num_rooms in each floor

		for (int i = 0; i < num_floors; i++)
		{
			*(hotel->rooms + i) = (Room*)calloc(num_rooms, sizeof(Room));
			for (int j = 0; j < num_rooms; j++)
			{
				initRoomWithRandomParameters(&(hotel->rooms[i][j]));
			}
		}
	}
}

int readDecryptHotelFromFile(Hotel* hotel, char* path)
{	
	int decryptionPossible;
	int flagDefault = 0;
	FILE* f = fopen(path, "r");
	if (f == NULL)
	{
		if (fileExist(defaultHotelSavePath))
		{
			f = fopen(defaultHotelSavePath, "r");
			flagDefault = 1;
		}
		if (f == NULL)
			return 0;	//could not open file, return 0 to initiate new hotel
	}
	printf("Reading hotel content from file %s..\n\n", flagDefault == 1 ? defaultHotelSavePath : path);
	fscanf(f, "%d", &hotel->num_floors);
	fscanf(f, "%d", &hotel->num_rooms_in_floor);
	decryptionPossible = decryptData(&hotel->num_floors, sizeof(int), encryptXdataPath, 0);
	if (decryptionPossible == 0)
		return 0;
	decryptData(&hotel->num_rooms_in_floor, sizeof(int), encryptXdataPath, 0);

	hotel->rooms = (Room**)calloc(hotel->num_floors, sizeof(Room*)*hotel->num_rooms_in_floor);
	for (int i = 0; i < hotel->num_floors; i++)
	{
		*(hotel->rooms + i) = (Room*)calloc(hotel->num_rooms_in_floor, sizeof(Room));
	}

	for (int i = 0; i < hotel->num_floors; i++)
	{
		for (int j = 0; j < hotel->num_rooms_in_floor; j++)
		{
			fscanf(f, "%d%hhu", &hotel->rooms[i][j].num_beds, &hotel->rooms[i][j].info);//%hhu for reading unsigned char
			decryptData(&hotel->rooms[i][j].info, sizeof(unsigned char), encryptXdataPath, 0);
			decryptData(&hotel->rooms[i][j].num_beds, sizeof(int), encryptXdataPath, 0);
		}
	}
	decryptData(hotel, 0, encryptXdataPath, 1);	//pseudo command to delete the X file (size 0 - decryption won't work, 1 as "deleteSeedFileAfterDecryption")
	fclose(f);
	if (!flagDefault)
		remove(path);
	else
		remove(defaultHotelSavePath);
	printf("hotel loaded successfully.\n\n");
	return 1;	//reading hotel successfully
}


void encryptAndSaveHotel(Hotel* hotel, char* filepath, int notDefault)
{
	//encrypting and saving order: number of floors, [number of rooms in floor, number of beds in room, info byte in room (for all rooms)]
	int user = 0;
	if (notDefault)
	{
		while (user > 2 || user < 1)
		{
			printf("\n\n**SYSTEM : Save at default file location or at given filePath?\nchoose number:\n");
			printf("1. %s\n2. %s\n", filepath, defaultHotelSavePath);
			scanf("%d", &user);
			if (user == 2)
				filepath = defaultHotelSavePath;
		}
	}
	FILE* fhotel = fopen(filepath, "wb");
	int floors = hotel->num_floors;
	int rooms = hotel->num_rooms_in_floor;
	encryptData(&hotel->num_floors, sizeof(int));
	encryptData(&hotel->num_rooms_in_floor, sizeof(int));
	fprintf(fhotel, "%d %d ", hotel->num_floors, hotel->num_rooms_in_floor);

	for (int i = 0; i < floors; i++)
	{
		for (int j = 0; j < rooms; j++)
		{

			encryptData(&hotel->rooms[i][j].num_beds, sizeof(int));
			encryptData(&hotel->rooms[i][j].info, sizeof(unsigned char));
			fprintf(fhotel, "%d %hhu ", hotel->rooms[i][j].num_beds, hotel->rooms[i][j].info);
		}
	}
	fclose(fhotel);
}

void printHotel(Hotel* hotel, int constraint)	//prints all hotel rooms who have the constraint, if constraint == -1 prints all rooms
{
	int count = 0;
	for (int i = 0; i < hotel->num_floors; i++)
	{
		for (int j = 0; j < hotel->num_rooms_in_floor; j++)
		{
			if (constraint == -1 || hasInRoom(&hotel->rooms[i][j], constraint))
			{
				printf("Room %d\n", i * 100 + j);
				printRoom(&hotel->rooms[i][j]);
				count++;
			}
		}
	}
	printf("\nTOTAL %d/%d ROOMS INCLUDE THIS FEATURE - PRINTED\n", count, hotel->num_floors*hotel->num_rooms_in_floor);
	printf("Hotel has %d Floors, and %d rooms on each floor\n\n", hotel->num_floors, hotel->num_rooms_in_floor);
}

void freeHotel(Hotel* hotel)	//free hotel from memory after alloc
{
	for (int i = 0; i < hotel->num_floors; i++)
	{
		free(*(hotel->rooms + i));
	}

	free(hotel->rooms);
}