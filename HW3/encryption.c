#include "encryption.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>





void decryptByte(unsigned char* target, int x)
{	//reversing decryption
	int x_plus_one = (x + 1) % 8;


	rotateByteRight(target, 8 - x);	//3.c
	*target = *target ^ 0xff;	//3.b

								//3.a
	unsigned char value_x = getBitAtIndex(*target, x);		//gets bit at index x
	unsigned char value_x_plus_one = getBitAtIndex(*target, x_plus_one);	//gets bit at index x+1
	setBitAtIndex(target, x, value_x_plus_one);	//sets index x with value at index x+1
	setBitAtIndex(target, x_plus_one, value_x);	//sets index x+1 with value at index x
}

void encryptByte(unsigned char* target, int x)
{
	int x_plus_one = (x + 1) % 8;	//will switch between x and x_plus_one in byte
									//3.a
	unsigned char value_x = getBitAtIndex(*target, x);		//gets bit at index x
	unsigned char value_x_plus_one = getBitAtIndex(*target, x_plus_one);	//gets bit at index x+1
	setBitAtIndex(target, x, value_x_plus_one);	//sets index x with value at index x+1
	setBitAtIndex(target, x_plus_one, value_x);	//sets index x+1 with value at index x
												//3.b
	*target = *target ^ 0xff;	//XOR with 1 on all bits (0xff == 11111111)
								//3.c
	rotateByteRight(target, x);
}

int decryptData(void* arg, int bytes, char* filepath, int deleteSeedAfterDecryption)
{
	if (!fileExist(encryptXdataPath))	//no decryption file - can't decrypt
		return 0;
	int x, a;
	FILE* f = fopen(filepath, "rb");
	fscanf(f, "%d", &x);
	fclose(f);



	unsigned char* target = (unsigned char*)arg;
	for (int i = 0; i < bytes; i++)
	{
		decryptByte((target + i), x);
	}
	if (deleteSeedAfterDecryption)
	{
		printf("\nDeleting encryption seed file located at : %s\n", filepath);
		a = remove(filepath);
		if (a == 0)
			printf("Decryption seed file removed successfully. code %d\n", a);
		else
			printf("encryption seed file removal failed. code %d", a);
	}
	return 1;
}

void encryptData(void* arg, int bytes)
{
	int x;
	FILE* xfile;
	x = rand() % 8;		//randomize x, and define indexes to switch
	if (fileExist(encryptXdataPath))	//if x already exist , take x
	{
		xfile = fopen(encryptXdataPath, "rb");
		fscanf(xfile, "%d", &x);
		fclose(xfile);
	}
	else
	{
		xfile = fopen(encryptXdataPath, "wb");

		if (xfile == NULL)
		{
			printf("X File could not open for writing...\nnot encrypting.\n");
			return;
		}
		fprintf(xfile, "%d", x);
		fclose(xfile);
	}

	unsigned char* temp = (unsigned char*)arg;	//encrypts each byte
	for (int i = 0; i < bytes; i++)
	{
		encryptByte((temp + i), x);
	}
}

