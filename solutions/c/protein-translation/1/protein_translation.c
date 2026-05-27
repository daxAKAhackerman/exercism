#include "protein_translation.h"
#include <stdlib.h>
#include <string.h>

char *codon_amino_map[] = {"AUG",     "UUU UUC", "UUA UUG", "UCU UCC UCA UCG",
                           "UAU UAC", "UGU UGC", "UGG",     "UAA UAG UGA"};

protein_t protein(const char *const rna) {
  protein_t protein_result = {.valid = true};

  char *codon = calloc(4, sizeof(char));
  char *ptr_rna = (void *)rna;
  amino_acid_t *ptr_amino = protein_result.amino_acids;

valid_amino:
  while (*ptr_rna != '\0') {
    for (unsigned int i = 0; i < 3; i++) {
      if ((codon[i] = ptr_rna[i]) == '\0') {
        // Return invalid if there we need to handle a truncated amino
        protein_result.valid = false;
        free(codon);
        return protein_result;
      }
    }
    ptr_rna += 3;

    for (unsigned int i = 0; i <= Tryptophan + 1; i++) {
      if (strstr(codon_amino_map[i], codon) != NULL) {
        if (i == 7) {
          // Return result if we encounter STOP amino
          free(codon);
          return protein_result;
        }

        protein_result.count++;
        *ptr_amino++ = i;

        if (protein_result.count >= MAX_AMINO_ACIDS) {
          // Return if we reach max result
          free(codon);
          return protein_result;
        }

        // Goto is used to break out of a nested loop
        goto valid_amino;
      }
    }

    // If we got there, it's because we got an amino we can't parse
    protein_result.valid = false;
    free(codon);
    return protein_result;
  }

  // Happy path
  free(codon);
  return protein_result;
}
