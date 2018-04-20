/**
  Copyright © 2015 Odzhan. All Rights Reserved.
  
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  3. The name of the author may not be used to endorse or promote products
  derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY AUTHORS "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

#include "des.h"

uint8_t sbox[256] = {
  // S-box 1
  0xE4, 0xD1, 0x2F, 0xB8, 0x3A, 0x6C, 0x59, 0x07,
  0x0F, 0x74, 0xE2, 0xD1, 0xA6, 0xCB, 0x95, 0x38,
  0x41, 0xE8, 0xD6, 0x2B, 0xFC, 0x97, 0x3A, 0x50,
  0xFC, 0x82, 0x49, 0x17, 0x5B, 0x3E, 0xA0, 0x6D,
  // S-box 2
  0xF1, 0x8E, 0x6B, 0x34, 0x97, 0x2D, 0xC0, 0x5A,
  0x3D, 0x47, 0xF2, 0x8E, 0xC0, 0x1A, 0x69, 0xB5,
  0x0E, 0x7B, 0xA4, 0xD1, 0x58, 0xC6, 0x93, 0x2F,
  0xD8, 0xA1, 0x3F, 0x42, 0xB6, 0x7C, 0x05, 0xE9,
  // S-box 3
  0xA0, 0x9E, 0x63, 0xF5, 0x1D, 0xC7, 0xB4, 0x28,
  0xD7, 0x09, 0x34, 0x6A, 0x28, 0x5E, 0xCB, 0xF1,
  0xD6, 0x49, 0x8F, 0x30, 0xB1, 0x2C, 0x5A, 0xE7,
  0x1A, 0xD0, 0x69, 0x87, 0x4F, 0xE3, 0xB5, 0x2C,
  // S-box 4
  0x7D, 0xE3, 0x06, 0x9A, 0x12, 0x85, 0xBC, 0x4F,
  0xD8, 0xB5, 0x6F, 0x03, 0x47, 0x2C, 0x1A, 0xE9,
  0xA6, 0x90, 0xCB, 0x7D, 0xF1, 0x3E, 0x52, 0x84,
  0x3F, 0x06, 0xA1, 0xD8, 0x94, 0x5B, 0xC7, 0x2E,
  // S-box 5
  0x2C, 0x41, 0x7A, 0xB6, 0x85, 0x3F, 0xD0, 0xE9,
  0xEB, 0x2C, 0x47, 0xD1, 0x50, 0xFA, 0x39, 0x86,
  0x42, 0x1B, 0xAD, 0x78, 0xF9, 0xC5, 0x63, 0x0E,
  0xB8, 0xC7, 0x1E, 0x2D, 0x6F, 0x09, 0xA4, 0x53,
  // S-box 6
  0xC1, 0xAF, 0x92, 0x68, 0x0D, 0x34, 0xE7, 0x5B,
  0xAF, 0x42, 0x7C, 0x95, 0x61, 0xDE, 0x0B, 0x38,
  0x9E, 0xF5, 0x28, 0xC3, 0x70, 0x4A, 0x1D, 0xB6,
  0x43, 0x2C, 0x95, 0xFA, 0xBE, 0x17, 0x60, 0x8D,
  // S-box 7
  0x4B, 0x2E, 0xF0, 0x8D, 0x3C, 0x97, 0x5A, 0x61,
  0xD0, 0xB7, 0x49, 0x1A, 0xE3, 0x5C, 0x2F, 0x86,
  0x14, 0xBD, 0xC3, 0x7E, 0xAF, 0x68, 0x05, 0x92,
  0x6B, 0xD8, 0x14, 0xA7, 0x95, 0x0F, 0xE2, 0x3C,
  // S-box 8
  0xD2, 0x84, 0x6F, 0xB1, 0xA9, 0x3E, 0x50, 0xC7,
  0x1F, 0xD8, 0xA3, 0x74, 0xC5, 0x6B, 0x0E, 0x92,
  0x7B, 0x41, 0x9C, 0xE2, 0x06, 0xAD, 0xF3, 0x58,
  0x21, 0xE7, 0x4A, 0x8D, 0xFC, 0x90, 0x35, 0x6B };

uint8_t e_permtab[]={0x06,
  0x1f, 0x00, 0x01, 0x02, 0x03, 0x04, 0x03, 0x04,
  0x05, 0x06, 0x07, 0x08, 0x07, 0x08, 0x09, 0x0a,
  0x0b, 0x0c, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
  0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x13, 0x14,
  0x15, 0x16, 0x17, 0x18, 0x17, 0x18, 0x19, 0x1a,
  0x1b, 0x1c, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x00 };

uint8_t p_permtab[]={0x04,
  0x0f, 0x06, 0x13, 0x14, 0x1c, 0x0b, 0x1b, 0x10,
  0x00, 0x0e, 0x16, 0x19, 0x04, 0x11, 0x1e, 0x09,
  0x01, 0x07, 0x17, 0x0d, 0x1f, 0x1a, 0x02, 0x08,
  0x12, 0x0c, 0x1d, 0x05, 0x15, 0x0a, 0x03, 0x18 };

uint8_t ip_permtab[]={0x08,
  0x39, 0x31, 0x29, 0x21, 0x19, 0x11, 0x09, 0x01,
  0x3b, 0x33, 0x2b, 0x23, 0x1b, 0x13, 0x0b, 0x03,
  0x3d, 0x35, 0x2d, 0x25, 0x1d, 0x15, 0x0d, 0x05,
  0x3f, 0x37, 0x2f, 0x27, 0x1f, 0x17, 0x0f, 0x07,
  0x38, 0x30, 0x28, 0x20, 0x18, 0x10, 0x08, 0x00,
  0x3a, 0x32, 0x2a, 0x22, 0x1a, 0x12, 0x0a, 0x02,
  0x3c, 0x34, 0x2c, 0x24, 0x1c, 0x14, 0x0c, 0x04,
  0x3e, 0x36, 0x2e, 0x26, 0x1e, 0x16, 0x0e, 0x06 };

uint8_t inv_ip_permtab[]={0x08,
  0x27, 0x07, 0x2f, 0x0f, 0x37, 0x17, 0x3f, 0x1f,
  0x26, 0x06, 0x2e, 0x0e, 0x36, 0x16, 0x3e, 0x1e,
  0x25, 0x05, 0x2d, 0x0d, 0x35, 0x15, 0x3d, 0x1d,
  0x24, 0x04, 0x2c, 0x0c, 0x34, 0x14, 0x3c, 0x1c,
  0x23, 0x03, 0x2b, 0x0b, 0x33, 0x13, 0x3b, 0x1b,
  0x22, 0x02, 0x2a, 0x0a, 0x32, 0x12, 0x3a, 0x1a,
  0x21, 0x01, 0x29, 0x09, 0x31, 0x11, 0x39, 0x19,
  0x20, 0x00, 0x28, 0x08, 0x30, 0x10, 0x38, 0x18 };

uint8_t pc1_permtab[]={0x07,
  0x38, 0x30, 0x28, 0x20, 0x18, 0x10, 0x08, 0x00,
  0x39, 0x31, 0x29, 0x21, 0x19, 0x11, 0x09, 0x01,
  0x3a, 0x32, 0x2a, 0x22, 0x1a, 0x12, 0x0a, 0x02,
  0x3b, 0x33, 0x2b, 0x23, 0x3e, 0x36, 0x2e, 0x26,
  0x1e, 0x16, 0x0e, 0x06, 0x3d, 0x35, 0x2d, 0x25,
  0x1d, 0x15, 0x0d, 0x05, 0x3c, 0x34, 0x2c, 0x24,
  0x1c, 0x14, 0x0c, 0x04, 0x1b, 0x13, 0x0b, 0x03 };

uint8_t pc2_permtab[]={0x06,
  0x0d, 0x10, 0x0a, 0x17, 0x00, 0x04, 0x02, 0x1b,
  0x0e, 0x05, 0x14, 0x09, 0x16, 0x12, 0x0b, 0x03,
  0x19, 0x07, 0x0f, 0x06, 0x1a, 0x13, 0x0c, 0x01,
  0x28, 0x33, 0x1e, 0x24, 0x2e, 0x36, 0x1d, 0x27,
  0x32, 0x2c, 0x20, 0x2f, 0x2b, 0x30, 0x26, 0x37,
  0x21, 0x34, 0x2d, 0x29, 0x31, 0x23, 0x1c, 0x1f };

uint8_t splitin6bitword_permtab[]={0x08,
  0x3f, 0x3f, 0x00, 0x05, 0x01, 0x02, 0x03, 0x04,
  0x3f, 0x3f, 0x06, 0x0b, 0x07, 0x08, 0x09, 0x0a,
  0x3f, 0x3f, 0x0c, 0x11, 0x0d, 0x0e, 0x0f, 0x10,
  0x3f, 0x3f, 0x12, 0x17, 0x13, 0x14, 0x15, 0x16,
  0x3f, 0x3f, 0x18, 0x1d, 0x19, 0x1a, 0x1b, 0x1c,
  0x3f, 0x3f, 0x1e, 0x23, 0x1f, 0x20, 0x21, 0x22,
  0x3f, 0x3f, 0x24, 0x29, 0x25, 0x26, 0x27, 0x28,
  0x3f, 0x3f, 0x2a, 0x2f, 0x2b, 0x2c, 0x2d, 0x2e };

uint8_t shiftkey_permtab[]={0x07,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
  0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
  0x19, 0x1a, 0x1b, 0x00, 0x1d, 0x1e, 0x1f, 0x20,
  0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
  0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30,
  0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x1c };

// derived from work by Svend Olaf Mikkelsen
// http://www.partitionsupport.com/
//
void des_str2key (void *str, w64_t* key) {
    uint32_t x1, r1, *p1;
    w64_t  *s=(w64_t*)str;
    int      i, j;

    for (i=0; i<2; i++) {
      p1=(uint32_t*)&s->b[i*3];
      x1=SWAP32(*p1);
      if (i==1) {
        x1=ROTL32 (x1, 4);
      }
      r1=0;
      for (j=0; j<4; j++) {
        r1 = ROTL32((r1 | (x1 & 0xFE000000)), 8);
        x1 <<= 7;
      }
      key->w[i] = SWAP32(r1);
    }
}

/*********************************************************/
void permute (uint8_t ptbl[], void *input, w64_t *out) 
{
    uint8_t i, j, x, t, ob;
    w64_t *in=(w64_t*)input;
    uint8_t *p=(uint8_t*)ptbl;
    
    // we always expect out to absorb 8 bytes
    memset (out->b, 0, 8);
    
    // load destination buffer in bytes
    ob = *p++;
    
    // for i=0 to output bytes
    for (i=0; i<ob; i++) 
    {
      t=0; 
      // permute 8-bits
      for (j=0; j<8; j++) 
      {
        x = *p++;
        t <<= 1;
        if ((in->b[x / 8]) & (0x80 >> (x & 7)) ){
          t |= 0x01;
        }
      }
      out->b[i]=t;
    }
}

/*****************************************************/

uint32_t des_f (uint32_t *x, w64_t *key) {
    uint8_t  i, x0, x1;
    uint32_t t=0;
    uint8_t  *sbp;
    w64_t  t0, t1;
    
    // permute 1 half of data
    permute (e_permtab, x, &t0);
    
    // mix key with data
    for (i=0; i<7; i++) {
      t0.b[i] ^= key->b[i];
    }

    permute (splitin6bitword_permtab, &t0, &t1);
    sbp=sbox;
    
    for (i=0; i<8; ++i) 
    {
      x0   = t1.b[i];
      x1   = sbp[x0 >> 1];
      x1   = (x0 & 1) ? x1 & 0x0F : x1 >> 4;
      t  <<= 4;
      t   |= x1;
      sbp += 32;
    }
    t = SWAP32(t);

    permute (p_permtab, &t, &t0);
    return t0.w[0];
}

// create 16 subkeys for encryption/decryption
void des_setkey (des_ctx *ctx, void *input)
{
    uint32_t rnd;
    w64_t *k, *ks;
    w64_t k1, k2;
    
    ks=&ctx->keys[0];
    
    permute (pc1_permtab, input, &k1);
    
    for (rnd=0; rnd<16; rnd++)
    {
      permute (shiftkey_permtab, &k1, &k2);
      k=&k2;
      if (ROTTABLE & (1 << rnd)) {
        permute (shiftkey_permtab, &k2, &k1);
        k=&k1;
      }
      permute (pc2_permtab, k, ks++);
      memcpy (k1.b, k->b, w64_t_LEN);
    }
}

// encrypt/decrypt 64-bits of input
void des_enc (des_ctx *ctx, void *in, 
  void *out, int enc)
{
    int      rnd, ofs=1;
    w64_t    p;
    uint32_t L, R, t;
    
    w64_t *key=&ctx->keys[0];
    
    if (enc==DES_DECRYPT) {
      ofs  = -1;
      key += 15;
    }
    // apply initial permutation to input
    permute (ip_permtab, in, &p);
    
    L = p.w[0]; R = p.w[1];
    
    for (rnd=0; rnd<DES_ROUNDS; rnd++)
    {
      L ^= des_f (&R, key);
      // swap
      XCHG(L, R);
      key += ofs;
    }
    p.w[0] = R; p.w[1] = L;
    
    // apply inverse permutation
    permute (inv_ip_permtab, &p, out);
}

/* perform Triple-DES encryption
void des3_enc (void *out, void *in, 
  void *key1, void *key2, void *key3)
{
  w64_t c1, c2;
  des_ctx ctx1, ctx2, ctx3;
  
  // encrypt in to c1
  des_setkey (&ctx, key1);
  des_enc (&ctx, c1, in, DES_ENCRYPT);
  
  // decrypt c1 to c2
  des_setkey (&ctx, key2);
  des_enc (&ctx, c2, c1, DES_DECRYPT);
  
  // encrypt c2 to out
  des_setkey (&ctx, key3);
  des_enc (&ctx, out, c2, DES_ENCRYPT);
}

// perform Triple-DES decryption
void des3_dec (void *out, void *in, 
  void *key1, void *key2, void *key3)
{
  w64_t c1, c2;
  des_ctx ctx;
  
  // encrypt in to c1
  des_setkey (&ctx, key1);
  des_enc (&ctx, c1, in, DES_ENCRYPT);
  
  // decrypt c1 to c2
  des_setkey (&ctx, key2);
  des_enc (&ctx, c2, c1, DES_DECRYPT);
  
  // encrypt c2 to out
  des_setkey (&ctx, key3);
  des_enc (&ctx, out, c2, DES_ENCRYPT);
}*/
/**********************************************/

