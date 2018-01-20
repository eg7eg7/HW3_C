
#ifndef _hotel_struct
#define _hotel_struct
#include "room.h"

#define defaultHotelSavePath "hw3_hotel.bin"

typedef struct hotel_struct
{
	int num_floors;
	int num_rooms_in_floor;
	Room** rooms;
} Hotel;
void freeHotel(Hotel* hotel);				//free hotel from memory
void initHotel(Hotel* hotel, char* path);
void printHotel(Hotel* hotel, int constraint);
void encryptAndSaveHotel(Hotel* hotel, char* filepath, int notDefault);	//notDefault acts as a flag that dictates if filepath is not the default
int readDecryptHotelFromFile(Hotel* hotel, char* path);
#endif // !_hotel_struct
