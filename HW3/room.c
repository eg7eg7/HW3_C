#include "room.h"


void initRoom(Room* room, int num_beds, unsigned char occupied, unsigned char tv, unsigned char couch, unsigned char wifi, unsigned char kettle, unsigned char terrace, unsigned char p_view)
{
	room->num_beds = num_beds;
	unsigned char info = 0;	//building info byte
	info = (occupied << R_OCCUPIED) | (tv << R_TV) | (couch << R_COUCH) | (wifi << R_WIFI) | (kettle << R_KETTLE) | (terrace << R_TERRACE) | (p_view << R_VIEW);
	room->info = info;	//gets value and shifts it to it's position in the byte(defined in room.h) and does the OR function between all of them to get a byte with all the info
}

void printRoom(Room* room)
{
	printf("Room details:\n\n");
	printf("Number of beds\t\t%d\n", room->num_beds);

	if (hasInRoom(room, R_OCCUPIED) == ROOM_POS)
		printf("status\t\t\t[OCCUPIED]\n");
	else
		printf("status\t\t\t[FREE]\n");
	if (hasInRoom(room, R_TV) == ROOM_POS)
		printf("TV\t\t\t[yes]\n");
	else
		printf("TV\t\t\t[NO]\n");
	if (hasInRoom(room, R_COUCH) == ROOM_POS)
		printf("Extendable Couch\t[YES]\n");
	else
		printf("Extendable Couch\t[NO]\n");
	if (hasInRoom(room, R_WIFI) == ROOM_POS)
		printf("Free WIFI\t\t[YES]\n");
	else
		printf("Free WIFI\t\t[NO]\n");
	if (hasInRoom(room, R_KETTLE) == ROOM_POS)
		printf("Kettle\t\t\t[YES]\n");
	else
		printf("Kettle\t\t\t[NO]\n");
	if (hasInRoom(room, R_TERRACE) == ROOM_POS)
		printf("Terrace\t\t\t[YES]\n");
	else
		printf("Terrace\t\t\t[NO]\n");
	if (hasInRoom(room, R_VIEW) == ROOM_POS)
		printf("Pool view\t\t[YES]");
	else
		printf("Pool view\t\t[NO]");
	printf("\n------------\n");
}

int hasInRoom(Room* room, int field)	//prints value of index 'field' in byte, index = 0 at LSB
{
	int shift = 7 - field;
	unsigned char temp = (room->info) << shift;
	temp = temp >> 7;
	return temp;
}


void initRoomWithRandomParameters(Room* room)	//random values for room, rand() was randomized at main
{
	initRoom(room, ((rand() % MAX_BEDS_IN_ROOM) + 1), rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 2);
}

void printRoomListWithFeature(int feature, Room* room, ...)	//question 2.e
{
	va_list roomPointers;			//sets an uninitialized list 
	va_start(roomPointers, room);	//sets the list to point to room as first argument
	while (room != NULL)			//continues to call loop until no arguments left.
	{
		if (hasInRoom(room, feature))	//prints room if it has the feature
			printRoom(room);
		room = va_arg(roomPointers, Room*);	//calls next.
	}
	//no more rooms, end
	va_end(roomPointers);
	printf("\nEnd of question 2.e demonstration\nContinuing to main menu...\n\n");
}
