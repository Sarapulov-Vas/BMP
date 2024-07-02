#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#pragma pack(push, 1)
struct BMPFileHeader
{
    uint8_t Type[2];
    uint32_t Size;
    uint16_t Reserved1;
    uint16_t Reserved2;
    uint32_t OffBits;
};

struct CIEXYZ
{
    uint32_t ciexyzX;
    uint32_t ciexyzY;
    uint32_t ciexyzZ;
};

struct CIEXYZTRIPLE
{
    struct CIEXYZ ciexyzRed;
    struct CIEXYZ ciexyzGreen;
    struct CIEXYZ ciexyzBlue;
};

struct BMPInfo
{
    uint32_t Size;
    int32_t Width;
    int32_t Height;
    uint16_t Planes;
    uint16_t BitCount;
    uint32_t Compression;
    uint32_t SizeImage;
    int32_t XPelsPerMetr;
    int32_t YPelsPerMetr;
    uint32_t ClrUsed;
    uint32_t ClrImportant;

    uint32_t RedMask;
    uint32_t GreenMask;
    uint32_t BlueMask;
    uint32_t AlphaMask;
    uint32_t CSType;
    struct CIEXYZTRIPLE EndPoints;
    uint32_t GammaRed;
    uint32_t GammaGreen;
    uint32_t GammaBlue;

    uint32_t Intent;
    uint16_t ProfileData;
    uint32_t ProfileSize;
    uint32_t Reserved;
};

#pragma pack(pop)
int main (int argc, char* argv[])
{
    struct BMPFileHeader fileHeader;
    struct BMPInfo fileInfo;
    FILE *file;
    file = fopen("/home/sarapulov-vasilii/work/BMP/files/logo.bmp", "r");
    // if (argc != 2)
	// {
	// 	printf("Wrong number of the incoming parameters\nPlease, try again or use \"help\"\n");
	// 	return 1;
	// }

    // if (argv[1] == '--help' || argv[1] == "-h")
    // {
    //     printf("Enter the path to the BMP file.\n");
	// 	return 0;
    // }

    // file = argv[1];
    if (file == NULL)
    {
        fprintf(stderr, "The input file open failed.\n");
        return 1;
    }

    fread(&fileHeader, sizeof(fileHeader), 1, file);
    if (fileHeader.Type[0] != 'B' || fileHeader.Type[1] != 'M')
    {
        fprintf(stderr, "The file is not a BMP file.\n");
        return 1;
    }

    fread(&fileInfo, sizeof(fileInfo), 1, file);

    fclose(file);
    return 0;
}