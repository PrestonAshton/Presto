#include <stdio.h>
#include <stdlib.h>

char* readEntireFile(char* filename)
{
  char* result = 0;
  FILE* file = fopen(filename, "r");
  if (file)
  {
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    //result = malloc...
    fread();

    fclose(file);
  }
}

int main(int argc, char** argv)
{

}
