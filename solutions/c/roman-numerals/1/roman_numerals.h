#ifndef ROMAN_NUMERALS_H
#define ROMAN_NUMERALS_H

#define NUM_OF_NUMERALS 13
#define BUFFER_SIZE 64

typedef struct {
  char numeral[3];
  unsigned int value;
} roman_numeral;

char *to_roman_numeral(unsigned int number);

#endif
