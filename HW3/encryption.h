#ifndef _encryption
#define _encryption
#define encryptXdataPath "decryption_seed_file_x.bin"


void encryptData(void* arg, int bytes);
int decryptData(void* arg, int bytes, char* filepath, int deleteSeedAfterDecryption);
void encryptByte(unsigned char* target, int x);
void decryptByte(unsigned char* target, int x);

#endif