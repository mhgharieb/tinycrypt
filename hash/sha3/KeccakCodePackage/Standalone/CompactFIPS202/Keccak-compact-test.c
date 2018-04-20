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

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#ifdef VERBOSE
#include <stdio.h>
#endif

void Keccak(int rate, int capacity, const unsigned char *input, unsigned long long int inputByteLen, unsigned char delimitedSuffix, unsigned char *output, unsigned long long int outputByteLen);

#ifdef TestAtBitLevel

void performTestBitLevel(unsigned int rate, unsigned int capacity, unsigned char *checksum)
{
    #define inputByteSize 512
    #define outputByteSize 512
    unsigned char input[inputByteSize];
    unsigned char output[outputByteSize];
    unsigned char acc[outputByteSize];
    unsigned int inputBitLength;

    /* Acumulated test vector */
    memset(acc, 0x00, sizeof(acc));

    for(inputBitLength = 0; inputBitLength <= (inputByteSize*8); inputBitLength += (inputBitLength < 1600) ? 1 : 8) {
        unsigned int i;
        unsigned int inputByteLengthCeiling = (inputBitLength + 7) / 8;

        /* Preparing some input value */
        for(i=0; i<inputByteLengthCeiling; i++)
            input[i] = inputBitLength - i;
        if ((inputBitLength % 8) != 0)
            input[inputByteLengthCeiling-1] &= (1 << (inputBitLength % 8)) - 1;

        if ((inputBitLength % 8) == 0) {
            Keccak(rate, capacity, input, inputBitLength/8, 0x01, output, outputByteSize);
        }
        else {
            unsigned char delimitedSuffix = input[inputByteLengthCeiling-1] | (1 << (inputBitLength % 8));
            Keccak(rate, capacity, input, inputBitLength/8, delimitedSuffix, output, outputByteSize);
        }

#ifdef VERBOSE
        printf("Keccak[r=%d, c=%d]\n", rate, capacity);
        printf("Input of %d bits:", inputBitLength);
        for(i=0; i<inputByteLengthCeiling; i++)
            printf(" %02x", (int)input[i]);
        printf("\n");
        printf("Output of %d bits:", outputByteSize*8);
        for(i=0; i<outputByteSize; i++)
            printf(" %02x", (int)output[i]);
        printf("\n\n");
#endif

        for (i = 0; i < outputByteSize; i++)
            acc[i] ^= output[i];
        Keccak(1344, 256, acc, outputByteSize, 0x1F, acc, outputByteSize);
    }
    memcpy(checksum, acc, outputByteSize);

#ifdef VERBOSE
    {
        unsigned int i;
        printf("Keccak[r=%d, c=%d]\n", rate, capacity);
        printf("Checksum: ", outputByteSize);
        for(i=0; i<outputByteSize; i++)
            printf("\\x%02x", (int)checksum[i]);
        printf("\n\n");
    }
#endif
}

void testKeccakInstanceBitLevel(unsigned int rate, unsigned int capacity, const unsigned char *expected)
{
    unsigned char checksum[outputByteSize];

    performTestBitLevel(rate, capacity, checksum);
    assert(memcmp(expected, checksum, outputByteSize) == 0);
    #undef inputByteSize
    #undef outputByteSize
}

#endif

void performTestByteLevel(unsigned int rate, unsigned int capacity, unsigned char delimitedSuffix, unsigned int outputByteLength, unsigned char *checksum)
{
    #define inputByteSize 1024
    #define outputByteSize 512
    unsigned char input[inputByteSize];
    unsigned char output[outputByteSize];
    unsigned char acc[outputByteSize];
    unsigned int inputByteLength;

    assert(outputByteLength <= outputByteSize);

    /* Acumulated test vector */
    memset(acc, 0x00, sizeof(acc));

    for(inputByteLength = 0; inputByteLength <= inputByteSize; inputByteLength++) {
        unsigned int i;

        /* Preparing some input value */
        for(i=0; i<inputByteLength; i++)
            input[i] = inputByteLength - i;

        Keccak(rate, capacity, input, inputByteLength, delimitedSuffix, output, outputByteLength);

#ifdef VERBOSE
        printf("Keccak[r=%d, c=%d] with suffix=%02x\n", rate, capacity, delimitedSuffix);
        printf("Input of %d bytes:", inputByteLength);
        for(i=0; i<inputByteLength; i++)
            printf(" %02x", (int)input[i]);
        printf("\n");
        printf("Output of %d bytes:", outputByteLength);
        for(i=0; i<outputByteLength; i++)
            printf(" %02x", (int)output[i]);
        printf("\n\n");
#endif

        for (i = 0; i < outputByteLength; i++)
            acc[i] ^= output[i];
        Keccak(1344, 256, acc, outputByteLength, 0x1F, acc, outputByteLength);
    }
    memcpy(checksum, acc, outputByteLength);

#ifdef VERBOSE
    {
        unsigned int i;
        printf("Keccak[r=%d, c=%d] with suffix=%02x and %d bytes of output\n", rate, capacity, delimitedSuffix, outputByteLength);
        printf("Checksum: ", outputByteLength);
        for(i=0; i<outputByteLength; i++)
            printf("\\x%02x", (int)checksum[i]);
        printf("\n\n");
    }
#endif
}

void testKeccakInstanceByteLevel(unsigned int rate, unsigned int capacity, unsigned char delimitedSuffix, unsigned int outputByteLength, const unsigned char *expected)
{
    unsigned char checksum[outputByteSize];

    performTestByteLevel(rate, capacity, delimitedSuffix, outputByteLength, checksum);
    assert(memcmp(expected, checksum, outputByteLength) == 0);
    #undef inputByteSize
    #undef outputByteSize
}

int genKAT_main();

int main()
{
    testKeccakInstanceByteLevel(1344,  256, 0x1F, 168, "\xc0\x96\x67\xb2\x04\xfe\x18\xea\x1b\x10\x93\x15\xd6\xd8\x80\x9a\xe6\xd4\x1f\xc2\x13\x07\x55\x1d\x65\x2d\xfa\x8e\x12\x93\xb8\x09\xa7\x3e\x14\x3a\x6f\xb9\x52\x61\x79\xbd\x34\xe9\x8b\x16\xd1\x60\x94\x83\xc2\x89\x3e\x71\x44\x0f\xa0\x7a\x54\x9c\xeb\x6d\x7f\xbe\xd8\x76\x39\x01\x9c\x4a\x2e\x25\x07\xaa\x36\x0d\x54\xf2\x78\x68\xc0\xd3\x49\x5c\x9f\xaa\x56\x65\xba\x8c\xb2\x59\x30\x46\x2a\x5a\x14\x29\xb1\x6f\xc7\xd4\x1e\xe2\xbd\xb6\xe4\x62\x39\x30\x6e\xb3\xd5\xc8\xd8\x73\xfe\x6c\x71\xc9\x3e\x40\x4e\x60\x61\x64\xa5\x6e\x59\x30\xe5\xe3\xbb\x11\x16\x0e\x2d\xb0\xab\x95\xce\xfd\x09\xa8\x08\xf9\xfd\xf1\x31\x47\x4b\x3b\xb5\x79\xcf\x6b\x98\xe7\xeb\x44\xaa\xd2\x3a\x31\x83\x15\x39\xb7"); /* SHAKE128 */
    testKeccakInstanceByteLevel(1088,  512, 0x1F, 136, "\x37\xf9\xa2\x05\xb9\x2e\xdf\x89\xb8\x18\xa6\x89\xd2\xa9\x2d\x93\xb8\x63\x8e\x21\x61\x24\x38\x2a\x9f\xe6\x08\xfe\xf0\x0c\x6a\x54\xbe\x60\xa7\x09\x36\xfa\x49\xa6\x11\xf8\xc8\x10\x96\xdf\x18\x51\x01\x29\x34\xfe\xb4\xd4\xf3\x2c\x95\x03\xb6\xa1\x97\xa4\x7f\xf5\xe1\xa5\xc8\x18\x6f\x1e\xc6\xef\xe9\x90\x07\x89\x2b\xb1\xde\x0a\xe0\x42\xf0\x31\x35\xd0\x51\x30\x19\x2e\x04\xc3\xf9\x92\x4d\x94\x40\x63\xe1\x07\x12\xf5\xf5\x7e\xb4\xba\xcf\x40\x78\xff\x35\xda\x99\x3e\x94\x97\xfc\x46\xdb\x2c\x4c\xa1\x76\x0b\x06\x15\xf4\xd6\xf5\x4b\x32\x66\x27\xb5\xf1\x48"); /* SHAKE256 */
    testKeccakInstanceByteLevel(1152,  448, 0x06,  28, "\xf3\x61\xcb\xd5\x9b\x84\x1d\x8e\x0c\xdb\xd4\x06\x1e\xb5\x7a\xea\x75\x1d\x34\x36\x01\x23\x6e\xef\x0c\x5d\x81\x7b"); /* SHA3-224 */
    testKeccakInstanceByteLevel(1088,  512, 0x06,  32, "\x99\xa3\xc2\x65\xcf\xdd\x51\x68\x40\xd1\x78\x46\xd7\x53\xf6\x3e\x5f\xbf\x2e\xce\x47\x51\xa3\xf0\x59\x35\x29\x0b\x56\x19\x0f\xcb"); /* SHA3-256 */
    testKeccakInstanceByteLevel( 832,  768, 0x06,  48, "\x06\xdf\x16\xce\x63\xd3\xcc\x5f\xf6\xae\xc8\x8e\x2f\x49\xa6\xe9\x53\x88\x12\xfc\xdd\x04\xfe\x88\x09\x5a\x41\x93\x76\xd3\x74\xf5\x5f\x09\x45\xa1\x5f\xaa\x20\x5c\x8f\x12\x8e\xcb\xbe\xe2\xb0\x10"); /* SHA3-384 */
    testKeccakInstanceByteLevel( 576, 1024, 0x06,  64, "\x9a\xdb\x76\x33\xcc\xb6\x44\xe7\x16\x19\x93\x6a\xa5\xac\x2e\xd1\x01\x51\xa5\x2c\xcf\xc6\xf7\x0d\x6d\xd7\x50\x9f\x57\x35\x9e\x27\xd4\xa2\x62\x24\xab\xc7\x87\xfc\xcd\x62\x74\x9d\x20\x61\x7f\x87\x29\xb3\x3e\x9b\x89\x51\x0c\xba\x20\x8a\x55\x98\xeb\x3b\xf5\x61"); /* SHA3-512 */

#ifdef TestAtBitLevel
    testKeccakInstanceBitLevel(576, 1024, "\x18\x6b\x69\x2f\xaa\x41\x4a\x9d\x8a\xf1\x0e\x9c\x2a\xfc\x99\x2d\x38\x16\xac\xfe\xed\x37\xc9\x42\x89\x9c\xd9\x0d\x75\xce\x64\x0c\x7d\xb3\xfb\xe5\xde\x15\x7e\x26\x72\x35\xd1\x1e\xfc\x00\x26\xfd\x9b\x57\x3c\x21\xeb\xdd\xad\x42\x26\x72\x22\xbf\x39\x4e\x2a\xdc\x00\x26\x36\x72\xbc\xf7\xb0\xef\x54\x0e\x33\xdf\xfa\x56\xdb\xa4\xe0\xc4\x22\xa1\xfa\xe0\xcd\x5a\x8b\x15\x7f\x34\x27\x53\x8f\x2f\x2a\x0c\xfe\xf7\x06\x7f\x8f\x42\x4a\xea\x31\x20\x2c\x63\x11\x8d\x72\x14\x14\xd9\xfb\x1a\x32\xb4\xbd\x6a\xbe\xf5\x2c\xa0\xfd\x1e\x85\xc2\xcc\x6f\x09\x86\xca\x70\x0a\x35\xe8\x2e\xfe\xb3\xa3\x9e\x25\xec\x4f\x2c\xd4\x87\x34\x03\x4d\xc8\x3f\x39\x2f\xa1\xfd\x6d\xe1\xd8\xab\x73\x97\x01\xb1\x60\xd7\x74\x03\x19\x75\x24\x71\xe4\x5a\x80\x8e\xb5\x15\x40\x24\xd2\x28\x5f\xc7\x42\xc9\xbf\xeb\x49\x9b\x7f\x1d\x73\x8c\xa0\x7f\x6b\xf8\x40\xc5\x78\x11\x11\xcc\x88\xf5\x9f\x31\xe7\xe5\x7d\xff\xb1\x31\x5f\x58\x31\xb4\xf3\x8c\xaa\xeb\x1e\xd6\x19\xc2\xb0\x65\x02\xb5\x74\xfe\xa2\x6c\xa2\x69\xb2\x20\xdb\x8e\x69\x1f\x8e\x67\xdf\x4b\x38\x28\xa7\x49\xa2\x57\x97\x8a\x69\x3c\x3f\x72\x23\xcb\xf1\x7d\x11\x7e\x6a\xd7\xc4\x12\xfd\xd7\x22\x07\xd7\xaf\x22\x42\xa4\xd8\x75\x79\x89\x1b\x4a\x48\x1a\xec\x81\x61\x83\x06\xbc\x9f\x15\x1e\xa3\x44\xfb\xd6\x4d\xb0\x2a\xa2\x57\x4c\x85\x45\x29\xd4\x43\xd0\xe4\x4a\x7a\x21\xbf\x2f\x9c\xe3\x41\x9e\x61\x7a\x0f\x00\xd8\x76\x3e\x69\x30\x6c\x20\x3b\x5a\x80\x1b\x59\x08\x26\x0a\x69\x86\xb4\x07\x69\xc1\x56\xad\x79\x7d\x3f\xe0\xed\x0c\xad\xa1\x21\x10\x30\x43\x11\x39\xad\xc0\xde\x25\x52\x4c\x9b\xcd\xf1\xaa\x2d\x21\x75\xf2\xfc\xc0\xab\xdf\x70\xac\xbc\x8e\x11\x48\x0c\x30\xf5\xc4\xe8\x7e\xe3\x08\x16\x55\x23\x0f\x3a\xc5\x06\xe4\xc2\x4b\xcb\xd7\xb8\x90\x83\x9e\x9f\x8e\xf8\x9a\x4a\xd0\x7a\xfd\x31\x10\xf0\x2c\x99\x2e\xdf\xf8\x99\x56\x0c\x08\x37\x1c\x7c\x78\x07\xd8\x0c\x97\x76\x75\xd1\x7b\x17\x41\xcb\xcf\xb3\x39\x51\x3b\x4c\xeb\x3f\x05\x79\x67\xf2\x0c\x59\x7d\xba\x4e\xb4\x07\x2d\xfa\xc9\x27\x42\xc4\x40\x91\xae\xed\xd7\xc7\x5e\x58\xd4\xa6\x27\x68\x0d\x67\xc6\xcc\x79\x2d\xa9\x95\x17\x34\x3a\xb7\xeb\x05\x4b\x60\x37\x56\xab\x0d\x31\x18\xb2\x05\x40\xa0\x62\x13"); /* Keccak[r=576, c=1024] */
    testKeccakInstanceBitLevel(832, 768, "\xf7\x65\xbd\xf7\xa9\x55\xff\xe0\xf1\x75\xc8\x7b\x0e\xdc\xf2\xa0\x49\x57\xc8\x76\xd6\x40\x1f\xbd\x0f\x7a\xbd\x7a\x82\xef\x44\xc7\x13\x69\x09\x29\xc3\x30\x6f\x0f\x10\xe9\x41\xd3\x04\x59\x93\x45\x53\x28\x6c\xf6\xd4\x7b\x97\x38\xf7\x18\xce\x07\xee\x40\x66\xcb\x4f\x10\xcf\x0f\xeb\xc1\x41\xca\x70\x49\xc6\xa7\xa7\xec\xd1\x2d\xe8\xad\xcf\x78\xe6\x1a\x73\xbf\xec\x0e\x56\x0c\x79\x61\xa3\xbd\xc0\x10\x19\x64\x9f\x78\x89\x94\xb1\xff\x71\xcb\x0a\x07\xaa\x9a\xb5\x16\xce\x2c\xa8\x3b\xf5\x59\xa2\xbe\x52\x09\xd4\x26\xaf\x13\x9a\x0f\x41\x53\x35\xa4\xdd\xed\x0c\x8a\x9c\x3a\x9b\x64\xef\x72\xa9\xa6\x98\x05\xd1\xb8\xb0\xe4\xe1\x21\x01\xc0\xea\xe1\x6c\x15\x2d\x49\x5e\xea\xd3\xc5\x76\xc0\xd5\x54\x9d\xa7\x6d\xc1\x00\x30\x80\x83\xf9\x0c\xb5\x75\x66\xba\xb4\x65\xf2\xc5\xd4\x76\x1e\x0f\xeb\x21\x72\xb0\x8d\xd3\x81\x10\x00\x18\x39\x6f\x47\x9e\x80\xdc\xc1\x04\x94\x97\xbc\x4d\xaa\xe9\x4d\x6e\x92\x2a\xcc\xb8\x55\xf2\x8c\x5b\xed\xea\xe8\x09\x0d\x64\xcc\xfe\xd1\xfb\x5e\x24\x3c\xdf\x19\x56\xf3\xd4\x24\x3a\x9b\x5f\x02\x90\x3d\x33\xdb\xea\xb7\xbb\xe2\xf1\xf7\xec\x72\xe9\x67\xad\x94\x38\x28\xeb\x26\x66\x46\x3b\x00\x07\xa1\x88\xd7\x0e\x04\x3c\x8f\x5c\xa1\x1e\xf7\x1b\xcf\x28\x10\x1a\x46\x98\x26\xbe\xcd\x3a\x66\x81\x81\x65\xae\xa4\x4b\x00\xae\xf0\xb9\x4d\x4b\x29\x86\xff\x3c\x1c\x01\xbe\x74\x65\x09\xed\x96\x17\xd7\xb7\x30\x39\x05\x4f\x78\xe5\x15\x33\x44\xa5\x78\x9d\xe6\x1f\x4f\x1f\xa3\x32\xa1\xcf\xc4\x2e\xf2\x05\x3e\xa4\x16\x88\x62\x6d\xe5\xd6\x24\x2d\x21\xa1\x6e\xd8\x79\x90\x58\xc7\x7d\x63\xd6\x18\x58\xf4\xd7\xb1\x36\x3f\x69\x12\x85\xa4\xbb\xe3\xda\x32\x3c\xd8\x70\xf8\xda\x30\xaa\x53\xae\x2b\xa6\xde\xe8\x51\xfb\x11\x17\xfd\x41\x52\x27\x7f\xab\x07\x8c\x69\x90\x60\x88\x4e\xab\xae\x5c\x32\x19\x3a\xb6\x46\xda\x38\xf1\x81\xef\xfa\x47\x46\x86\xce\x71\x38\x51\xf2\x38\x20\x3d\x81\x64\x23\xad\xbc\x14\x23\x50\xdd\x6f\x56\x00\x50\xa8\x48\xd5\xc8\x5f\xb5\x65\x5a\xa7\x0f\xa3\xed\xc2\xdf\xb6\x12\x51\x4e\xae\xe5\x4c\xf7\xb3\x54\xc0\x93\xe1\x6a\x03\x06\xb5\x9f\xce\x73\xea\x89\x43\x40\x1b\x41\x9e\xae\x87\xdb\xeb\x35\x1f\x7b\x90\x70\xd0\x03\x9d\x74\x27\xd5\xf4\x06\xbd\x7c"); /* Keccak[r=832, c=768] */
    testKeccakInstanceBitLevel(1024, 576, "\x6e\x20\xc9\xfd\xb0\x18\x81\x89\xcc\x0e\xac\x60\x18\x9d\x70\x75\x59\xe6\xc9\xa7\x05\xce\x20\xce\x96\xda\x5a\xf8\x05\x56\x1c\xdd\xd1\xdf\xe7\xfc\x17\xef\xd9\xdf\x0b\x34\xe6\x51\xdf\xd7\x65\xdd\xeb\x7d\x4b\x54\x33\x6a\xda\xde\x55\x73\x92\x51\xfb\x4a\xe7\x95\x86\x02\xb2\x75\xee\x39\xb2\x4a\x34\xaa\x32\x5c\x63\xc6\x7e\x8b\xef\x9c\x18\x9d\xe6\x83\x8d\x0a\xf7\x5b\x80\x58\x62\x8e\xf0\xfa\x0a\xee\xe0\x18\xb2\xb8\x67\x83\x31\x47\xe5\x07\x97\x79\x97\xb9\x76\x8b\xd8\x31\x13\x9d\x23\xd0\x9c\x1b\x98\xbe\xfb\x07\x57\x8b\x4d\x52\xc8\x3c\xc1\xc4\x77\xfb\x48\x2c\x05\xd5\x1b\x3f\x2e\xf2\x1d\xe5\x23\xf2\xe0\x07\x56\xda\xdc\x46\xc6\x0f\xa9\x88\xa7\xb2\xd2\x73\x8a\x73\xea\x2f\xec\x24\x5f\xdf\xb9\x91\x37\x4f\xfa\x17\xf3\x24\x75\x7e\x76\xa1\xce\x69\x47\x7b\x81\xb6\x2b\x3d\x3b\x8d\xa2\xfc\x25\x4b\x4d\x58\xd8\x56\x8e\x15\x7b\x32\xe7\x20\xb6\x15\x1c\x9b\x4f\xf8\x61\x87\x95\xc6\x39\x2f\x7c\x72\x74\xc8\x5d\xfd\x41\x3b\x11\x32\x24\x47\x88\xa4\x23\x88\x60\x3c\xf6\xc4\x00\x57\xe6\xb6\x23\xf3\x7b\x64\x64\xb6\xd7\xef\x58\xc3\x3e\x4c\x32\x86\x5b\x84\x60\x31\x36\x47\x8b\x0d\x6b\x1b\xb0\xc1\x47\x78\x16\xe9\x35\xee\x0e\x82\xc1\xaf\x7f\xa2\xfc\x2c\xf8\x37\xac\x06\x18\x59\x65\x16\xc2\xd2\x5f\x5f\x31\x25\xc7\xeb\xf8\x2b\x57\x05\xcb\xdd\x8c\x25\xef\xfc\xe1\xf6\xaf\xb3\x62\x40\x1a\xa3\xde\x86\x54\x3b\x6f\x2d\xae\x4d\x67\x03\xf7\x30\x93\x26\x04\xc0\x83\x4f\x44\x19\xd2\x82\x2d\x72\x3d\x07\xe9\xae\x14\x07\xe3\x82\x23\xa0\x7f\xc1\x54\x6b\x7b\xbe\x60\xa4\x4e\x85\x4a\xca\x94\x99\xfc\x87\x3e\xd6\x71\x95\xad\x86\xb7\xe2\x33\x47\x99\xbe\x74\x05\xf8\xd1\xb3\xaf\xa1\x4f\x6b\x05\x7b\x2b\x81\x2f\x00\x54\x79\xc8\xb0\x53\x92\x03\x3a\x19\xc0\xb2\x54\xac\xdc\x38\x15\x4e\x49\xff\x53\xbc\xac\x75\x5d\xc1\x96\xea\x5e\x9d\x35\xc8\x80\x8b\x02\x7d\x0a\xac\xa3\x85\xf2\xef\x13\x08\xbf\x0d\x89\x28\xc1\xba\xcf\x71\xfa\xca\xa6\xe9\xfe\x2b\xf0\x62\x33\x11\x5a\x63\xbf\x9b\xd4\x7b\x0c\x43\x08\x0e\xa6\x62\xaf\xb7\x20\x57\x31\x32\xd2\xb8\xe1\x56\xf8\x7f\x6c\xa6\xee\x9e\x69\x88\xb0\x9e\x00\x47\x07\xff\xf6\x58\x57\x79\x04\x34\x50\x13\x5f\xd9\x2b\x08\xae\x52\x1d\x2b\x2c\x43\x14\x86\xaa\xea"); /* Keccak[r=1024, c=576] */
    testKeccakInstanceBitLevel(1088, 512, "\x49\x39\x13\x5e\xcf\x8d\x28\x1f\x3b\xfa\x00\xac\x6a\x3d\xb5\x09\x0a\xaa\x75\x5c\xb3\x16\x44\xc4\x87\xa3\xac\xf5\xa1\xfe\x29\x23\x1c\xce\x0c\x4c\x5a\xdb\x21\x8b\xc4\xc8\x8a\x1a\x6a\x53\xc1\xdd\x66\x90\x0a\xe1\x80\xc7\xb3\x45\x5b\xdc\x00\xa8\x3a\xf3\x37\xb7\xb0\xc5\x22\xac\x6f\xd1\x70\x85\xb5\x03\x65\x96\xcf\xe0\x2a\x97\x40\x64\xf9\xf4\xca\xb3\x72\x93\x6b\xfc\x9c\x91\x82\x00\x68\x58\x45\x27\xeb\xe4\x5c\x52\xf0\x5b\xe1\x88\xfd\x9c\x96\x44\xcb\xde\xe6\xb3\x50\xb9\xdc\x74\xcf\x80\x42\x12\xca\xfd\xa4\x51\x44\xe2\xc0\x3f\x29\x4e\xb2\xca\x61\x8c\xab\x10\x19\xf7\x69\x04\x16\x6d\xb6\x0f\xc3\xc0\x52\xb3\x2c\xb0\xa4\xaa\xbc\x51\x3e\xa1\x13\x4b\xc8\xe6\x37\x9c\x12\xb4\x39\xf1\x5d\x9e\x22\xb3\x1c\x71\xa7\x56\xa0\xf5\x12\xa2\xb0\x8a\xa8\xa3\xd6\x96\xce\xd2\x78\x05\x34\xa8\x31\x6c\x34\xea\x05\x1b\xda\x9f\xf3\x0b\x4b\x7e\x0d\x54\xe9\xf9\x13\x06\x5c\x05\x32\x14\xf0\x79\xc4\xf4\xc7\xec\x6c\x5d\x45\x38\x07\x52\xf1\x40\x4e\xc0\xec\xe5\x78\x6e\x8d\x54\x81\x24\x80\x29\x30\x4c\x0d\x33\x11\x83\x51\xd9\x1f\xb0\xfe\xa4\x83\x40\x11\xa5\xb1\x13\x1d\x70\x2c\xdc\x5b\x17\xae\x26\x3e\xb6\xf6\x2b\xa0\x23\x55\x5b\xda\xea\x3e\xb5\x68\xf9\x7f\x93\xed\x70\x76\xfd\xf5\xf8\x47\x1a\x67\x99\x81\x21\xec\x34\x0e\x2b\xb0\x2b\x0f\x31\xbd\x5a\x8f\xdf\x3e\x03\x89\xfc\xfe\xea\xf3\xa2\xf5\x2e\xb4\x11\xa1\xde\x7d\x20\xe7\xd3\x0a\xde\x70\x3c\xf3\x8d\xca\x6f\x4e\x28\xfd\x7d\x03\x13\x60\x43\x43\xd2\x24\x46\x80\x18\x0b\x56\x74\x98\x4e\x1f\x48\x78\xdf\x0a\x02\x5a\x26\x2c\x50\x86\x27\x71\x62\x58\x0e\x41\xb8\x75\xb5\xd8\xb9\x7e\xd7\x2a\xce\x63\xc7\xf4\x91\x69\x0f\xb8\x7e\x36\x7d\xc1\x40\x12\xb2\xca\xfd\x2c\xc5\x9b\xbb\x02\x89\x55\x50\x24\x40\xcd\xc0\x10\x10\x4c\xf2\x7d\xf2\x45\xf4\x75\x0f\xcf\x34\x02\x8a\x6d\x42\x9c\x90\x67\xc5\xe1\x48\x41\x32\x86\xbc\x82\x65\x66\x0b\xe3\x54\x6d\x09\x9e\xee\xfb\xfb\x0d\x17\x51\xec\x8d\xdc\x7d\x4c\x80\x29\xae\xab\xba\x08\x23\x28\xeb\xc5\xc5\xec\x68\x12\x99\xfe\x18\x4b\xd7\x79\xd3\xd6\x3f\x03\x27\xa4\x2e\x5e\xe9\x7a\x66\x5c\x6a\x02\xd5\xf2\x46\xa1\x3c\xc0\x9a\xd2\x5c\x2e\xb3\xba\xbe\x70\xca\x21\x31\x18\x75\x5d\xb6\x2e\x6d\x4a\xb5\x0d\xf5"); /* Keccak[r=1088, c=512] */
    testKeccakInstanceBitLevel(1152, 448, "\x9c\xe4\x91\x56\xac\xbc\x4f\x28\x38\xd8\x7e\x39\x2c\xab\x5e\x20\x2e\x68\x07\x2d\x8d\xb0\x1d\x8a\x23\x8e\x59\xee\x38\xaf\x65\x72\xd5\x28\xee\xed\xf2\xa7\x08\x36\x60\xc2\xee\x52\xc1\x76\x13\x99\x82\xa8\x96\x94\xab\x50\x52\x5f\x65\xeb\x97\xa1\x6a\x18\xd9\x14\x1a\x41\x5f\x73\x23\x34\x45\xc9\xf1\x84\x9f\xea\xdd\xcf\x93\xbe\xdd\x45\x02\x79\xc2\x24\x3f\xd4\xb9\xf0\x86\xbf\x13\x26\x7e\xb8\xcd\x9f\x26\xa6\x3a\x5d\x31\xd5\x67\xce\x55\x8a\xe4\xd0\xf0\x8c\x6f\x2e\xd3\xb4\x16\xec\x75\x42\x0f\x13\x6e\x2b\x74\x60\xba\xc2\xf3\xea\x71\xb2\x26\xd5\x11\x25\xf2\x47\xb2\x95\xcd\x1c\xb3\xbe\xa1\x90\x5e\x77\x2a\xa0\x78\x39\x7a\xf3\x46\x05\xf9\xbf\xf7\x1b\x60\x52\x42\x47\x5f\x90\x50\x8a\xc3\xa8\x23\x96\x0f\x47\x22\x8d\xc6\x59\x19\xc7\xa8\xf2\xee\x5a\x1b\xdd\xda\x56\xe2\xbd\x0d\xc1\x60\x7d\x77\x7d\x4b\x9f\x29\xb3\x3e\x99\x8a\x97\x51\xf9\x47\x2e\x2f\x18\x2f\x7c\x82\xaa\x54\x16\x09\xd5\xfd\x63\xd6\x94\x90\x88\x83\x2e\xc6\x90\xdb\x03\x79\x5b\x20\x6c\x2d\x2f\xc1\xa5\x66\x20\x19\x5c\x93\x34\xa5\x08\xb6\xd4\xc6\x4e\xc3\xd6\xa0\x0d\xac\x27\xef\x57\x06\xb5\xbc\x45\x46\x79\xe3\xda\x8c\x46\xd9\x1b\x77\xe0\x64\xc0\x49\x97\xca\xe9\x24\x76\x47\xf5\x39\x5c\x49\xc9\x5c\xb0\x7e\x09\x83\x1c\x72\x46\xd1\xcf\x88\xe3\xe2\x23\x50\xf1\x5f\x91\xcb\x6e\x3d\x52\xcb\x8b\x9c\x30\xd9\x83\xcd\x77\x3e\x54\x87\x7e\x4d\x3b\x56\xbf\x38\x13\xa1\xb7\xfb\xa8\xf7\xed\xb9\x60\x58\x8d\xa9\x0f\x56\x3d\x75\xaa\xeb\x7f\x7f\xc4\x32\x75\xbc\x1d\x83\xe7\xca\xd0\x07\x21\x56\x4b\xc7\x03\x11\xde\x95\xb9\x66\x50\xd9\x50\x37\x79\x16\x2b\xc1\x23\xc7\xd4\xa9\xe7\x2b\xb0\xe2\x96\x81\xb9\x68\x29\x77\xd9\xcd\x59\x91\x6c\xfb\xde\xa3\x8d\x74\xf8\x01\xbe\xa0\xa4\x66\x91\x69\x7d\x77\x90\x0a\x4d\xa7\x7f\xa6\x9f\x0c\xf5\xf4\x07\xeb\x94\x59\xc4\x52\x03\x6a\x34\x83\xfd\xbd\x60\xb2\xae\x79\xb3\x6a\x09\xba\x53\x56\xd8\x7d\xc0\xcb\x43\x40\x39\xb5\x48\x40\xce\x48\xc5\xfe\xc8\x8f\xe3\x72\xe2\x07\x2f\xd7\xfc\xc9\x9e\xa4\x21\x55\x59\x87\x09\xfe\x81\x4f\x02\x8c\x9d\x9f\xae\x25\x9c\xfc\xaf\x9c\xb7\x45\x6b\x87\xa5\xca\xbe\x87\xf3\x00\x3b\x42\x3e\xff\x25\x53\x76\x0a\xfe\x35\x50\x9c\xcd\x62\x0f\xfa\xd4\x80\xca"); /* Keccak[r=1152, c=448] */
    testKeccakInstanceBitLevel(1344, 256, "\xff\x73\xac\xa3\x1e\x3e\x53\x2c\x0e\x64\x1b\x77\xf5\xec\x39\x7c\x20\x20\xb8\x93\x20\x73\x14\xed\xb3\x90\xcd\xf9\x80\xac\x55\xd6\x9d\xd2\xf5\x41\xc4\xf6\xd9\x1a\xff\x0c\x2c\x6b\x69\x11\x96\xa3\xd9\x7a\x9d\x40\x30\x64\xf7\xde\xbc\x75\x40\xa2\xd3\xfd\x0b\xdf\xb1\x02\x90\x89\xa4\xff\x6d\x36\xca\x68\xe1\xb4\xae\xf0\x42\x35\xa8\x75\x19\xc6\x93\x7e\xc1\x3c\xce\xec\xea\x71\x17\x9d\xae\x21\x4e\xd9\xd6\xd7\xc4\x67\xc6\x59\xfa\x20\xeb\x99\xbd\xc3\xd7\x40\x55\x3c\x71\xdf\xa7\xe2\x16\x75\xd0\xa7\x81\x24\x6a\xc3\x10\x0e\xb9\x22\xb2\x04\x15\x0f\x04\x90\xa8\xb7\x68\xce\xcf\x73\x44\x80\x09\x2d\x9e\xf0\x5d\xf9\xe1\x6c\xf5\xa4\x82\x5c\x41\x07\xcd\x57\xef\xe5\xed\x1a\xd2\x47\xdc\xd8\xdd\x32\xb1\x36\xea\x31\xc6\xf9\x0a\xde\x7b\x8d\x18\x5e\xcf\x1b\xf6\x1b\x5f\xa8\xdd\xb2\x5a\xef\xed\xb8\xa3\x3b\x30\x14\xd9\x78\x40\xed\x18\x9a\xdc\xe5\x39\x80\x56\x01\xaf\xea\x2a\x3d\x31\x2f\x3c\x41\x00\x94\x22\x41\x55\xd4\x98\x12\x53\xac\x07\x35\x51\x0b\x49\x67\x7d\xc3\x13\x54\xc6\xc9\x11\x1c\xae\x92\x4b\x2a\xa1\xa4\x3d\xeb\x35\x50\x72\xe8\x48\xa1\x70\x25\xf2\xdb\x90\x95\x8b\x6a\xdf\x31\xa2\xdf\xaa\xcd\x78\x0f\x43\xa1\x44\x7d\xd7\xb3\x8f\xa1\xcb\x6e\x30\xeb\x62\x1b\xb7\x54\xf4\x4f\xb0\x34\xe6\x99\x69\x5c\xdc\x12\x13\x5a\x18\xbc\xa6\xe6\x59\xb8\x4f\x6e\x07\xac\x7b\xf5\xf3\x0f\x0d\x7c\xb1\xa8\xd1\x45\x71\x61\x5d\x0c\xc3\x50\xe8\xb1\x9b\x0f\x58\x85\x9c\xec\xfb\x74\xb2\x17\x14\xe7\xe1\xc7\x42\xd5\x61\x5b\x7b\xd4\xae\x58\x84\xf8\x94\x2e\xa8\x3e\xf4\x8b\x5f\x88\xe0\xd2\x51\x64\xff\xe6\xff\x80\x16\x06\xab\xa1\xbf\xa0\xfa\x2c\xf2\x87\x0c\x95\x60\x38\xf7\xf2\x3e\xa1\x01\x3c\x1c\xcd\xee\x45\xc6\xaa\xb5\x68\x19\xc9\x15\x44\x47\x46\x7f\x0b\xc9\x1f\xc9\x82\xd6\xac\xd2\x4d\x77\x4e\x8d\x06\x32\xd9\x61\x51\x90\x23\x99\x32\x4c\xe7\x3e\xce\x3b\x35\x5b\xc1\x14\xec\x15\xb0\x71\x95\x90\x32\x87\x36\xae\xca\xd7\xbb\xdb\xd2\x0f\xae\xb7\xc0\xc4\xa4\xdc\xeb\x78\xdd\x76\xb7\xbf\x80\x37\xc5\xdb\x63\xd2\xdf\x90\xe9\xde\xba\x94\x8f\xca\x28\x4d\x05\x7a\x9b\x86\x2e\x76\x99\x64\x74\xd5\xd5\x4e\xa5\xfc\xd8\x0d\x74\x50\x0d\x2d\x2d\xcb\x00\x69\x19\x0c\x59\xc1\xcb\xb6\xfa\x6f\xe4\xb1\x52"); /* Keccak[r=1344, c=256] */
#endif

    return genKAT_main();
}
