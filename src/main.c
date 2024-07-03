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
    uint32_t ProfileData;
    uint32_t ProfileSize;
    uint32_t Reserved;
};

#pragma pack(pop)
int main (int argc, char* argv[])
{
    struct BMPFileHeader fileHeader;
    struct BMPInfo fileInfo;
    FILE *file;
    if (argc != 2)
	{
		printf("Wrong number of the incoming parameters\nPlease, try again or use \"--help\" or \"-h\"\n");
		return 1;
	}

    if (argv[1] == "--help" || argv[1] == "-h")
    {
        printf("Enter the path to the BMP file.\n");
		return 0;
    }

    file = fopen(argv[1], "r");
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

    fread(&fileInfo, sizeof(fileInfo.Size), 1, file);
    fread(&fileInfo.Width, fileInfo.Size - sizeof(fileInfo.Size), 1, file);
    fclose(file);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25u |\n", "Size", fileHeader.Size);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %12d x %-11d|\n", "Width/Height", fileInfo.Width, fileInfo.Height);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25u |\n", "Bit Count", fileInfo.BitCount);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25u |\n", "Compression", fileInfo.Compression);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25u |\n", "Size image", fileInfo.SizeImage);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %12d x %-11d|\n", "Pels per meter", fileInfo.XPelsPerMetr, fileInfo.YPelsPerMetr);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25u |\n", "Clr used", fileInfo.ClrUsed);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25u |\n", "Clr important", fileInfo.ClrImportant);
    printf("+---------------------------+---------------------------+\n");
    if (fileInfo.Size == 40)
    {
        return 0;
    }

    printf("| %-25s | %25x |\n", "Red mask", fileInfo.RedMask);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "Green mask", fileInfo.GreenMask);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "Blue mask", fileInfo.BlueMask);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "Alpha mask", fileInfo.AlphaMask);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "CSType", fileInfo.CSType);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Red X", fileInfo.EndPoints.ciexyzRed.ciexyzX);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Red Y", fileInfo.EndPoints.ciexyzRed.ciexyzY);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Red Z", fileInfo.EndPoints.ciexyzRed.ciexyzZ);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Green X", fileInfo.EndPoints.ciexyzGreen.ciexyzX);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Green Y", fileInfo.EndPoints.ciexyzGreen.ciexyzY);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Green Z", fileInfo.EndPoints.ciexyzGreen.ciexyzZ);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Blue X", fileInfo.EndPoints.ciexyzBlue.ciexyzX);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Blue Y", fileInfo.EndPoints.ciexyzBlue.ciexyzY);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Blue Z", fileInfo.EndPoints.ciexyzBlue.ciexyzZ);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "Gamma red", fileInfo.GammaRed);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "Gamma green", fileInfo.GammaGreen);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25x |\n", "Gamma blue", fileInfo.GammaBlue);
    printf("+---------------------------+---------------------------+\n");
    if (fileInfo.Size == 108)
    {
        return 0;
    }

    printf("| %-25s | %25u |\n", "Intent", fileInfo.Intent);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25u |\n", "Profile data", fileInfo.ProfileData);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25u |\n", "Profile size", fileInfo.ProfileSize);
    printf("+---------------------------+---------------------------+\n");
    printf("| %-25s | %25u |\n", "Reserved", fileInfo.Reserved);
    printf("+---------------------------+---------------------------+\n");
    return 0;
}
