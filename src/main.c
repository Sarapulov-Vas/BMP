#include "main.h"
#include <stdio.h>

int readFile(char *path, struct BMPFileHeader fileHeader,
             struct BMPInfo fileInfo) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "The input file open failed.\n");
        return 1;
    }

    fread(&fileHeader, sizeof(fileHeader), 1, file);
    if (fileHeader.Type[0] != 'B' || fileHeader.Type[1] != 'M') {
        fprintf(stderr, "The file is not a BMP file.\n");
        return 1;
    }

    fread(&fileInfo.Size, sizeof(fileInfo.Size), 1, file);
    fread(&fileInfo.Width, fileInfo.Size - sizeof(fileInfo.Size), 1, file);
    fclose(file);
    return 0;
}

void printHeader(struct BMPFileHeader fileHeader, struct BMPInfo fileInfo) {
    Print_Line();
    printf("| %-25s | %25u |\n", "Size", fileHeader.Size);
    Print_Line();
    printf("| %-25s | %12d x %-11d|\n", "Width/Height", fileInfo.Width,
           fileInfo.Height);
    Print_Line();
    printf("| %-25s | %25hu |\n", "Bit Count", fileInfo.BitCount);
    Print_Line();
    printf("| %-25s | %25u |\n", "Compression", fileInfo.Compression);
    Print_Line();
    printf("| %-25s | %25u |\n", "Size image", fileInfo.SizeImage);
    Print_Line();
    printf("| %-25s | %12d x %-11d|\n", "Pels per meter", fileInfo.XPelsPerMetr,
           fileInfo.YPelsPerMetr);
    Print_Line();
    printf("| %-25s | %25u |\n", "Clr used", fileInfo.ClrUsed);
    Print_Line();
    printf("| %-25s | %25u |\n", "Clr important", fileInfo.ClrImportant);
    Print_Line();
    if (fileInfo.Size == Version_3_Size) {
        return;
    }

    printf("| %-25s | %25x |\n", "Red mask", fileInfo.RedMask);
    Print_Line();
    printf("| %-25s | %25x |\n", "Green mask", fileInfo.GreenMask);
    Print_Line();
    printf("| %-25s | %25x |\n", "Blue mask", fileInfo.BlueMask);
    Print_Line();
    printf("| %-25s | %25x |\n", "Alpha mask", fileInfo.AlphaMask);
    Print_Line();
    printf("| %-25s | %25x |\n", "CSType", fileInfo.CSType);
    Print_Line();
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Red X",
           fileInfo.EndPoints.ciexyzRed.ciexyzX);
    Print_Line();
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Red Y",
           fileInfo.EndPoints.ciexyzRed.ciexyzY);
    Print_Line();
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Red Z",
           fileInfo.EndPoints.ciexyzRed.ciexyzZ);
    Print_Line();
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Green X",
           fileInfo.EndPoints.ciexyzGreen.ciexyzX);
    Print_Line();
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Green Y",
           fileInfo.EndPoints.ciexyzGreen.ciexyzY);
    Print_Line();
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Green Z",
           fileInfo.EndPoints.ciexyzGreen.ciexyzZ);
    Print_Line();
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Blue X",
           fileInfo.EndPoints.ciexyzBlue.ciexyzX);
    Print_Line();
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Blue Y",
           fileInfo.EndPoints.ciexyzBlue.ciexyzY);
    Print_Line();
    printf("| %-25s | %25x |\n", "EndPoints ciexyz Blue Z",
           fileInfo.EndPoints.ciexyzBlue.ciexyzZ);
    Print_Line();
    printf("| %-25s | %25x |\n", "Gamma red", fileInfo.GammaRed);
    Print_Line();
    printf("| %-25s | %25x |\n", "Gamma green", fileInfo.GammaGreen);
    Print_Line();
    printf("| %-25s | %25x |\n", "Gamma blue", fileInfo.GammaBlue);
    Print_Line();
    if (fileInfo.Size == Version_4_Size) {
        return;
    }

    printf("| %-25s | %25u |\n", "Intent", fileInfo.Intent);
    Print_Line();
    printf("| %-25s | %25u |\n", "Profile data", fileInfo.ProfileData);
    Print_Line();
    printf("| %-25s | %25u |\n", "Profile size", fileInfo.ProfileSize);
    Print_Line();
    printf("| %-25s | %25u |\n", "Reserved", fileInfo.Reserved);
    Print_Line();
}

int main(int argc, char *argv[]) {
    struct BMPFileHeader fileHeader;
    struct BMPInfo fileInfo;
    if (argc != 2) {
        printf("Wrong number of the incoming parameters\n");
        return 1;
    }

    if (readFile(argv[1], fileHeader, fileInfo) == 1) {
        return 1;
    }

    printHeader(fileHeader, fileInfo);
    return 0;
}
