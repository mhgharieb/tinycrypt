/*
Implementation by the Keccak, Keyak and Ketje Teams, namely, Guido Bertoni,
Joan Daemen, Michaël Peeters, Gilles Van Assche and Ronny Van Keer, hereby
denoted as "the implementer".

For more information, feedback or questions, please refer to our websites:
http://keccak.noekeon.org/
http://keyak.noekeon.org/
http://ketje.noekeon.org/

To the extent possible under law, the implementer has waived all copyright
and related or neighboring rights to the source code in this file.
http://creativecommons.org/publicdomain/zero/1.0/
*/

#include <string.h>
#include "test_crypto_hash.h"

int main()
{
    const unsigned char *message = (const unsigned char *)
        "\x11\x97\x13\xCC\x83\xEE\xEF";
    const unsigned char *hash = (const unsigned char *)
        "\xc0\x25\x61\xc1\x2c\xcd\xd1\x67\xca\x95\x9d\x97\x56\xcc\x70\x94\x6f\x7f\xed\x8b\xa7\x05\xe3\xed\xc4\x33\xd3\xc4\x5d\x92\x99\xd0\xae\xfe\x9e\x8e\x25\xd6\x02\xc4\xdb\x0d\x14\xec\xae\xfd\xfd\xfe\xd2\xde\x13\x4a\xc5\xd0\xc4\xdf\xc0\x2a\xbe\xff\xfd\xd7\x66\x7a\x43\x49\x36\x15\x1d\x52\x9a\x93\xcb\x26\x61\x00\xb9\x4a\xd0\x44\x95\x97\xb1\x59\x03\x98\xa1\xa6\x3c\x42\x64\x93\x85\xb4\xcf\xaa\x82\x8c\x89\x03\x7e\x0f\x97\xbe\xda\x84\x50\xa6\x85\x20\x14\x38\x89\xa9\x2c\x25\x86\x45\x66\x4e\xb5\x7c\xba\x01\xc3\xb1\x13\x43\x18\xe1\x1a\x18\x48\xd9\x12\xd0";
    return test_crypto_hash(message, 7, hash, 136);
}
