

#ifndef  _room_struct
#define _room_struct
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
//number defines index in byte
#define R_OCCUPIED 6			//ROOM IS OCCUPIED - FOR ROOM_POS(POSITIVE VALUE)
#define R_TV 5				//ROOM HAS TV - FOR ROOM_POS(POSITIVE VALUE)
#define R_COUCH 4			//ROOM HAS COUCH - FOR ROOM_POS(POSITIVE VALUE)
#define R_WIFI 3			//ROOM HAS FREE WIFI - FOR ROOM_POS(POSITIVE VALUE)
#define R_KETTLE 2			//ROOM HAS KETTLE - FOR ROOM_POS(POSITIVE VALUE)
#define R_TERRACE 1			//ROOM HAS A TERRACE - FOR ROOM_POS(POSITIVE VALUE)
#define R_VIEW 0			//ROOM HAS A POOL VIEW - FOR ROOM_POS(POSITIVE VALUE)

#define ROOM_POS 1			//BIT IS POSITIVE IF 1
#define ROOM_NEG 0

#define MAX_BEDS_IN_ROOM 8

typedef struct room_struct
{
	int num_beds;			//number of beds
	unsigned char info;		//info contains boolean info for the room : {(MSB) unused bit ,occupied, has TV, extendable couch, free wifi, has kettle, terrace, pool view (LSB) }
} Room;

void initRoom(Room* room, int num_beds, unsigned char occupied, unsigned char tv, unsigned char couch, unsigned char wifi, unsigned char kettle, unsigned char terrace, unsigned char p_view);
void printRoom(Room* room);
int hasInRoom(Room* room, int field);
void initRoomWithRandomParameters(Room* room);
void printRoomListWithFeature(int feature, Room* room, ...);
#endif // ! _room_struct

