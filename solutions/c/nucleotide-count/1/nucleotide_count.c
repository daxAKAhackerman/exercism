#include "nucleotide_count.h"
#include <stdio.h>
#include <stdlib.h>

char *count(const char *dna_strand) {
  nucleotide_count_t counter = {0};
  char c = '\0';
  char *buffer = calloc(BUFFER_SIZE, sizeof(char));

  while ((c = *dna_strand++) != '\0') {
    switch (c) {
    case 'A':
      counter.a++;
      break;
    case 'C':
      counter.c++;
      break;
    case 'G':
      counter.g++;
      break;
    case 'T':
      counter.t++;
      break;
    default:
      return buffer;
    }
  }

  snprintf(buffer, BUFFER_SIZE, "A:%d C:%d G:%d T:%d", counter.a, counter.c,
           counter.g, counter.t);
  return buffer;
}
