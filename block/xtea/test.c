
#include <stdio.h>

#include "xtea.h"

/*
 * XTEA tests vectors (non-official)
 */

static const unsigned char xtea_test_key[6][16] =
{
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
     0x0c, 0x0d, 0x0e, 0x0f },
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
     0x0c, 0x0d, 0x0e, 0x0f },
   { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
     0x0c, 0x0d, 0x0e, 0x0f },
   { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00 },
   { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00 },
   { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00 }
};

static const unsigned char xtea_test_pt[6][8] =
{
    { 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48 },
    { 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41 },
    { 0x5a, 0x5b, 0x6e, 0x27, 0x89, 0x48, 0xd7, 0x7f },
    { 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48 },
    { 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41 },
    { 0x70, 0xe1, 0x22, 0x5d, 0x6e, 0x4e, 0x76, 0x55 }
};

static const unsigned char xtea_test_ct[6][8] =
{
    { 0xca, 0xe7, 0x69, 0x7e, 0x00, 0x6e, 0xe9, 0x21 },
    { 0x62, 0x6a, 0x3b, 0x9e, 0xad, 0x7b, 0xd7, 0xfa },
    { 0x08, 0x94, 0x80, 0xa2, 0xf5, 0xec, 0x21, 0x53 },
    { 0xc9, 0xe5, 0x83, 0xc3, 0x73, 0xe0, 0xde, 0xd8 },
    { 0x5a, 0x37, 0x23, 0xed, 0x2d, 0x8c, 0x1a, 0x82 },
    { 0x0e, 0x0c, 0x50, 0x61, 0xca, 0x40, 0x4a, 0x92 }
};

void bin2hex(char *s, void *p, int len) {
  int i;
  printf("%s : ", s);
  for (i=0; i<len; i++) {
    printf ("%02x ", ((uint8_t*)p)[i]);
  }
  printf("\n\n");
}

int main(void)
{
  int     i, equ;
  uint8_t buf[8], key[16];
  
  for (i=0; i<6; i++) {
    memcpy(buf, &xtea_test_pt[i][0], 8);
    memcpy(key, &xtea_test_key[i][0], 16);
    
    #ifdef ASM
      xtea_encryptx(key, buf);
    #else
      xtea_encrypt(key, buf);
    #endif
    
    bin2hex("c:", buf, 8);
    
    equ = memcmp(buf, &xtea_test_ct[i][0], 8)==0;
    printf ("XTEA Test #%i %s\n", 
        (i+1), equ ? "OK" : "FAILED");
  }
  return 0;
}
