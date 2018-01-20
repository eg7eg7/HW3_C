
#ifndef _functions
#define _functions
#include "hotel.h"
#include "encryption.h"


void menu(Hotel* hotel, char* path);
void printByte(unsigned char byte);
void setBitAtIndex(char* target, int index, unsigned char value);
unsigned char getBitAtIndex(unsigned char target, int x);
void rotateByteRight(unsigned char* target, int x);
int fileExist(char* path);


#endif // !_functions
