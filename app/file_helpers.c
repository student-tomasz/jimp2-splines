#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file_helpers.h"

char *file_helpers_change_extension(const char *filename, const char *extension)
{
  char *new_filename = malloc(sizeof(*new_filename) * (strlen(filename)+strlen(extension)+2));
  strcpy(new_filename, filename);

  if (strlen(extension) == 0) {
    return new_filename;
  }

  char *dot = strrchr(new_filename, '.');
  if (dot)
    strcpy(dot, extension);
  else
    strcat(new_filename, extension);
  return new_filename;
}

