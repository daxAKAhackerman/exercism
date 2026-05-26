#ifndef NUCLEOTIDE_COUNT_H
#define NUCLEOTIDE_COUNT_H

#define BUFFER_SIZE 64

typedef struct {
  unsigned int a;
  unsigned int c;
  unsigned int g;
  unsigned int t;
} nucleotide_count_t;

char *count(const char *dna_strand);

#endif
