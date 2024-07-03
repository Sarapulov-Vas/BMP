#include "main.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
   struct BMPFileHeader fileHeader;
   struct BMPInfo fileInfo;
   FILE *file;
   if (argc != 2) {
      printf(
          "Wrong number of the incoming parameters\nPlease, try again or use "
          "\"--help\" or \"-h\"\n");
      return 1;
   }

   if (argv[1] == "--help" || argv[1] == "-h") {
      printf("Enter the path to the BMP file.\n");
      return 0;
   }

   file = fopen(argv[1], "r");
   if (file == NULL) {
      fprintf(stderr, "The input file open failed.\n");
      return 1;
   }

   fread(&fileHeader, sizeof(fileHeader), 1, file);
   if (fileHeader.Type[0] != 'B' || fileHeader.Type[1] != 'M') {
      fprintf(stderr, "The file is not a BMP file.\n");
      return 1;
   }

   fread(&fileInfo, sizeof(fileInfo.Size), 1, file);
   fread(&fileInfo.Width, fileInfo.Size - sizeof(fileInfo.Size), 1, file);
   fclose(file);
   PrintLine();
   printf("| %-25s | %25u |\n", "Size", fileHeader.Size);
   PrintLine();
   printf("| %-25s | %12d x %-11d|\n", "Width/Height", fileInfo.Width,
          fileInfo.Height);
   PrintLine();
   printf("| %-25s | %25u |\n", "Bit Count", fileInfo.BitCount);
   PrintLine();
   printf("| %-25s | %25u |\n", "Compression", fileInfo.Compression);
   PrintLine();
   printf("| %-25s | %25u |\n", "Size image", fileInfo.SizeImage);
   PrintLine();
   printf("| %-25s | %12d x %-11d|\n", "Pels per meter", fileInfo.XPelsPerMetr,
          fileInfo.YPelsPerMetr);
   PrintLine();
   printf("| %-25s | %25u |\n", "Clr used", fileInfo.ClrUsed);
   PrintLine();
   printf("| %-25s | %25u |\n", "Clr important", fileInfo.ClrImportant);
   PrintLine();
   if (fileInfo.Size == Version3Size) {
      return 0;
   }

   printf("| %-25s | %25x |\n", "Red mask", fileInfo.RedMask);
   PrintLine();
   printf("| %-25s | %25x |\n", "Green mask", fileInfo.GreenMask);
   PrintLine();
   printf("| %-25s | %25x |\n", "Blue mask", fileInfo.BlueMask);
   PrintLine();
   printf("| %-25s | %25x |\n", "Alpha mask", fileInfo.AlphaMask);
   PrintLine();
   printf("| %-25s | %25x |\n", "CSType", fileInfo.CSType);
   PrintLine();
   printf("| %-25s | %25x |\n", "EndPoints ciexyz Red X",
          fileInfo.EndPoints.ciexyzRed.ciexyzX);
   PrintLine();
   printf("| %-25s | %25x |\n", "EndPoints ciexyz Red Y",
          fileInfo.EndPoints.ciexyzRed.ciexyzY);
   PrintLine();
   printf("| %-25s | %25x |\n", "EndPoints ciexyz Red Z",
          fileInfo.EndPoints.ciexyzRed.ciexyzZ);
   PrintLine();
   printf("| %-25s | %25x |\n", "EndPoints ciexyz Green X",
          fileInfo.EndPoints.ciexyzGreen.ciexyzX);
   PrintLine();
   printf("| %-25s | %25x |\n", "EndPoints ciexyz Green Y",
          fileInfo.EndPoints.ciexyzGreen.ciexyzY);
   PrintLine();
   printf("| %-25s | %25x |\n", "EndPoints ciexyz Green Z",
          fileInfo.EndPoints.ciexyzGreen.ciexyzZ);
   PrintLine();
   printf("| %-25s | %25x |\n", "EndPoints ciexyz Blue X",
          fileInfo.EndPoints.ciexyzBlue.ciexyzX);
   PrintLine();
   printf("| %-25s | %25x |\n", "EndPoints ciexyz Blue Y",
          fileInfo.EndPoints.ciexyzBlue.ciexyzY);
   PrintLine();
   printf("| %-25s | %25x |\n", "EndPoints ciexyz Blue Z",
          fileInfo.EndPoints.ciexyzBlue.ciexyzZ);
   PrintLine();
   printf("| %-25s | %25x |\n", "Gamma red", fileInfo.GammaRed);
   PrintLine();
   printf("| %-25s | %25x |\n", "Gamma green", fileInfo.GammaGreen);
   PrintLine();
   printf("| %-25s | %25x |\n", "Gamma blue", fileInfo.GammaBlue);
   PrintLine();
   if (fileInfo.Size == Version4Size) {
      return 0;
   }

   printf("| %-25s | %25u |\n", "Intent", fileInfo.Intent);
   PrintLine();
   printf("| %-25s | %25u |\n", "Profile data", fileInfo.ProfileData);
   PrintLine();
   printf("| %-25s | %25u |\n", "Profile size", fileInfo.ProfileSize);
   PrintLine();
   printf("| %-25s | %25u |\n", "Reserved", fileInfo.Reserved);
   PrintLine();
   return 0;
}
