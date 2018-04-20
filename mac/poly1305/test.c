
// test unit for poly1305
// odzhan


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "cc20.h"
#include "poly1305.h"

void poly1305_macx(void*, const void*, int, const void*); 

// 2.8.2 AEAD test vector

// Plaintext Sunscreen:
const uint8_t ae_plain[]=
{ 0x4c,0x61,0x64,0x69,0x65,0x73,0x20,0x61,
  0x6e,0x64,0x20,0x47,0x65,0x6e,0x74,0x6c,
  0x65,0x6d,0x65,0x6e,0x20,0x6f,0x66,0x20,
  0x74,0x68,0x65,0x20,0x63,0x6c,0x61,0x73,
  0x73,0x20,0x6f,0x66,0x20,0x27,0x39,0x39,
  0x3a,0x20,0x49,0x66,0x20,0x49,0x20,0x63,
  0x6f,0x75,0x6c,0x64,0x20,0x6f,0x66,0x66,
  0x65,0x72,0x20,0x79,0x6f,0x75,0x20,0x6f,
  0x6e,0x6c,0x79,0x20,0x6f,0x6e,0x65,0x20,
  0x74,0x69,0x70,0x20,0x66,0x6f,0x72,0x20,
  0x74,0x68,0x65,0x20,0x66,0x75,0x74,0x75,
  0x72,0x65,0x2c,0x20,0x73,0x75,0x6e,0x73,
  0x63,0x72,0x65,0x65,0x6e,0x20,0x77,0x6f,
  0x75,0x6c,0x64,0x20,0x62,0x65,0x20,0x69,
  0x74,0x2e };
  
const uint8_t ae_aad[]=
{ 0x50,0x51,0x52,0x53,0xc0,0xc1,0xc2,0xc3,
  0xc4,0xc5,0xc6,0xc7 };

const uint8_t ae_key[]=
{ 0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,
  0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
  0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,
  0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f };
  
const uint8_t ae_tv[]=
{ 0x7b,0xac,0x2b,0x25,0x2d,0xb4,0x47,0xaf,
  0x09,0xb6,0x7a,0x55,0xa4,0xe9,0x55,0x84,
  0x0a,0xe1,0xd6,0x73,0x10,0x75,0xd9,0xeb,
  0x2a,0x93,0x75,0x78,0x3e,0xd5,0x53,0xff };
  
const uint8_t ae_iv[]=
{ 0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47 };

const uint8_t ae_ctr[]=
{ 0x07, 0x00, 0x00, 0x00 };

const uint8_t ae_cipher[]=
{ 0xd3,0x1a,0x8d,0x34,0x64,0x8e,0x60,0xdb,
  0x7b,0x86,0xaf,0xbc,0x53,0xef,0x7e,0xc2,
  0xa4,0xad,0xed,0x51,0x29,0x6e,0x08,0xfe,
  0xa9,0xe2,0xb5,0xa7,0x36,0xee,0x62,0xd6,
  0x3d,0xbe,0xa4,0x5e,0x8c,0xa9,0x67,0x12,
  0x82,0xfa,0xfb,0x69,0xda,0x92,0x72,0x8b,
  0x1a,0x71,0xde,0x0a,0x9e,0x06,0x0b,0x29,
  0x05,0xd6,0xa5,0xb6,0x7e,0xcd,0x3b,0x36,
  0x92,0xdd,0xbd,0x7f,0x2d,0x77,0x8b,0x8c,
  0x98,0x03,0xae,0xe3,0x28,0x09,0x1b,0x58,
  0xfa,0xb3,0x24,0xe4,0xfa,0xd6,0x75,0x94,
  0x55,0x85,0x80,0x8b,0x48,0x31,0xd7,0xbc,
  0x3f,0xf4,0xde,0xf0,0x8e,0x4b,0x7a,0x9d,
  0xe5,0x76,0xd2,0x65,0x86,0xce,0xc6,0x4b,
  0x61,0x16 };
  
const uint8_t ae_tag[]=
{ 0x1a,0xe1,0x0b,0x59,0x4f,0x09,0xe2,0x6a,
  0x7e,0x90,0x2e,0xcb,0xd0,0x60,0x06,0x91 };

void aead_test(void)
{
  uint8_t  pkey[32], t[128], mac_data[512];
  uint8_t  ae_nonce[256], tag[16];
  uint64_t len, pos;
  int      i, equ;
  
  // generate 96-bit nonce
  memset (ae_nonce, 0, sizeof(ae_nonce));
  memcpy (ae_nonce, ae_ctr, sizeof(ae_ctr));  
  memcpy (&ae_nonce[4], ae_iv, sizeof(ae_iv));
  
  // generate poly1305 key
  poly1305_key_gen(pkey, ae_key, ae_nonce);
  equ = memcmp(ae_tv, pkey, sizeof(pkey))==0;
  
  printf ("\nAEAD %s test 1", 
      equ ? "PASSED" : "FAILED");
      
  // encrypt plaintext
  memcpy (t, ae_plain, sizeof(ae_plain));
  
  cc20_encrypt(ae_key, 1, 
      ae_nonce, t, sizeof(ae_plain));
      
  equ = memcmp(ae_cipher, t, sizeof(ae_cipher))==0;
  
  printf ("\nAEAD %s test 2", 
      equ ? "PASSED" : "FAILED");
      
  memset(mac_data, 0, sizeof(mac_data));
  memcpy(mac_data, ae_aad, sizeof(ae_aad));
  pos = (sizeof(ae_aad) & -16) + 16;
  
  memcpy(&mac_data[pos], t, sizeof(ae_cipher));
  pos += (sizeof(ae_cipher) & -16) + 16;
  
  len = sizeof(ae_aad);
  memcpy(&mac_data[pos], &len, sizeof(len));
  
  len = sizeof(ae_cipher);
  memcpy(&mac_data[pos+8], &len, sizeof(len));
  
  poly1305_macx(tag, mac_data, pos+16, pkey); 
  equ = memcmp(ae_tag, tag, sizeof(ae_tag))==0;
  
  printf ("\nAEAD %s test 3", 
      equ ? "PASSED" : "FAILED");
      
  /*for (i=0; i<pos+16; i++) {
    if ((i & 15)==0) putchar('\n');
    printf ("%02x ", mac_data[i]);
  }*/
}

// 2.6.2 Poly1305 Key Generation Test Vector
const uint8_t pkg_key[]=
{ 0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,
  0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
  0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,
  0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f };
  
const uint8_t pkg_nonce[]=
{ 0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x03,
  0x04,0x05,0x06,0x07 };

const uint8_t pkg_tv[]=
{ 0x8a,0xd5,0xa0,0x8b,0x90,0x5f,0x81,0xcc,
  0x81,0x50,0x40,0x27,0x4a,0xb2,0x94,0x71,
  0xa8,0x33,0xb6,0x37,0xe3,0xfd,0x0d,0xa5,
  0x08,0xdb,0xb8,0xe2,0xfd,0xd1,0xa6,0x46 };
  
void poly1305_keygen_test(void)
{
  uint8_t key[32];
  int     equ;
  
  poly1305_key_gen (key, pkg_key, pkg_nonce);
  
  equ = memcmp(pkg_tv, key, 32)==0 ? 1 : 0;
  
  printf ("\nRFC7539 Poly1305 Key Generator : %s\n", 
      equ ? "PASSED" : "FAILED");
}

// Message to be Authenticated: 
// "Cryptographic Forum Research Group"
const uint8_t pm_msg[]=
{0x43,0x72,0x79,0x70,0x74,0x6f,0x67,0x72,
 0x61,0x70,0x68,0x69,0x63,0x20,0x46,0x6f,
 0x72,0x75,0x6d,0x20,0x52,0x65,0x73,0x65,
 0x61,0x72,0x63,0x68,0x20,0x47,0x72,0x6f,
 0x75,0x70 };

// r, s key stream
const uint8_t pm_key[]=
{ 0x85,0xd6,0xbe,0x78,0x57,0x55,0x6d,0x33, 
  0x7f,0x44,0x52,0xfe,0x42,0xd5,0x06,0xa8,
  0x01,0x03,0x80,0x8a,0xfb,0x0d,0xb2,0xfd, 
  0x4a,0xbf,0xf6,0xaf,0x41,0x49,0xf5,0x1b };
    
// 128-bit test vector
const uint8_t pm_tv[]=
{ 0xa8,0x06,0x1d,0xc1,0x30,0x51,0x36,0xc6, 
  0xc2,0x2b,0x8b,0xaf,0x0c,0x01,0x27,0xa9 };

void poly1305_mac_test(void)
{
  uint8_t tag[16];
  int     equ;
  
  poly1305_macx (tag, pm_msg, sizeof(pm_msg), pm_key);
  
  equ = memcmp(pm_tv, tag, 16)==0 ? 1 : 0;
  
  printf ("\nRFC7539 Poly1305 MAC test : %s\n", 
      equ ? "PASSED" : "FAILED");
}

// 2.4.2.  Example and Test Vector for the ChaCha20 Cipher
const uint8_t ss_key[]=
{ 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
  0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
  0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
  0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f };
      
const uint8_t ss_nonce[]=
{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4a,
  0x00,0x00,0x00,0x00 };

// Plaintext Sunscreen:
const uint8_t ss_plain[]=
{ 0x4c,0x61,0x64,0x69,0x65,0x73,0x20,0x61,
  0x6e,0x64,0x20,0x47,0x65,0x6e,0x74,0x6c,
  0x65,0x6d,0x65,0x6e,0x20,0x6f,0x66,0x20,
  0x74,0x68,0x65,0x20,0x63,0x6c,0x61,0x73,
  0x73,0x20,0x6f,0x66,0x20,0x27,0x39,0x39,
  0x3a,0x20,0x49,0x66,0x20,0x49,0x20,0x63,
  0x6f,0x75,0x6c,0x64,0x20,0x6f,0x66,0x66,
  0x65,0x72,0x20,0x79,0x6f,0x75,0x20,0x6f,
  0x6e,0x6c,0x79,0x20,0x6f,0x6e,0x65,0x20,
  0x74,0x69,0x70,0x20,0x66,0x6f,0x72,0x20,
  0x74,0x68,0x65,0x20,0x66,0x75,0x74,0x75,
  0x72,0x65,0x2c,0x20,0x73,0x75,0x6e,0x73,
  0x63,0x72,0x65,0x65,0x6e,0x20,0x77,0x6f,
  0x75,0x6c,0x64,0x20,0x62,0x65,0x20,0x69,
  0x74,0x2e };
  
const uint8_t ss_cipher[]=
{ 0x6e,0x2e,0x35,0x9a,0x25,0x68,0xf9,0x80,
  0x41,0xba,0x07,0x28,0xdd,0x0d,0x69,0x81,
  0xe9,0x7e,0x7a,0xec,0x1d,0x43,0x60,0xc2,
  0x0a,0x27,0xaf,0xcc,0xfd,0x9f,0xae,0x0b,
  0xf9,0x1b,0x65,0xc5,0x52,0x47,0x33,0xab,
  0x8f,0x59,0x3d,0xab,0xcd,0x62,0xb3,0x57,
  0x16,0x39,0xd6,0x24,0xe6,0x51,0x52,0xab,
  0x8f,0x53,0x0c,0x35,0x9f,0x08,0x61,0xd8,
  0x07,0xca,0x0d,0xbf,0x50,0x0d,0x6a,0x61,
  0x56,0xa3,0x8e,0x08,0x8a,0x22,0xb6,0x5e,
  0x52,0xbc,0x51,0x4d,0x16,0xcc,0xf8,0x06,
  0x81,0x8c,0xe9,0x1a,0xb7,0x79,0x37,0x36,
  0x5a,0xf9,0x0b,0xbf,0x74,0xa3,0x5b,0xe6,
  0xb4,0x0b,0x8e,0xed,0xf2,0x78,0x5e,0x42,
  0x87,0x4d }; 
  
// ChaCha20 section 2.4.2 of RFC7539
void chacha20_test(void)
{
  uint8_t    r[CC20_STATE_LEN*2];
  uint8_t    equ;
  
  memcpy (r, ss_plain, sizeof(ss_plain));
  
  cc20_encrypt(ss_key, 1, ss_nonce, r, sizeof(ss_plain));
  
  equ = memcmp(r, ss_cipher, sizeof(ss_plain)) == 0;
  
  printf ("\nRFC7539 ChaCha20 test : %s\n", 
      equ ? "PASSED" : "FAILED");
}

int main(int argc, char *argv[])
{  
  chacha20_test();
  poly1305_mac_test();
  poly1305_keygen_test();
  aead_test();
  
  return 0;
}
