#include "rna_transcription.h"
#include <stdlib.h>
#include <string.h>

char *to_rna(const char *dna) {
  size_t len = strlen(dna);

  char *rna = malloc(len + 1);
  char *ptr_rna = rna;

  while (*dna != '\0') {
    switch (*dna) {
    case 'G':
      *ptr_rna++ = 'C';
      break;
    case 'C':
      *ptr_rna++ = 'G';
      break;
    case 'T':
      *ptr_rna++ = 'A';
      break;
    case 'A':
      *ptr_rna++ = 'U';
      break;
    default:
      *ptr_rna = '\0';
      return rna;
    }
    dna++;
  }

  *ptr_rna = '\0';
  return rna;
}
