
//EDEN DUPONT 204808596

#include <stdio.h>
#include "hotel.h"
#include "room.h"
#include "functions.h"
#include "encryption.h"

void main(int argc, char* argv[])
{

	printf("\n---------------------------------\nHW3 By Eden Dupont 204808596\n---------------------------------\n");
	time_t t;
	srand((unsigned)time(&t));	//generates a new randomizer for rand() with current-time as seed

	Hotel california;
	if (argc > 1)	//load hotel from file if true
		menu(&california, argv[1]);
	else
		menu(&california, NULL);

}

