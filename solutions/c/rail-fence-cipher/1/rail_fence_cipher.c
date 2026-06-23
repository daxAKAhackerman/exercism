#include "rail_fence_cipher.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *encode(char *text, size_t rails) {
  // Setup result var
  size_t len = strlen(text);
  char *r = calloc(len + 1, sizeof(char));
  char *r_ptr = r;

  // Allocate a matrix
  char **matrix = calloc(rails, sizeof(char *));
  for (unsigned int i = 0; i < rails; i++) {
    matrix[i] = calloc(len + 1, sizeof(char));
  }

  // Place the letters on a zig zag pattern on the matrix
  unsigned int rail = 0;
  direction_t direction = DOWN;
  for (unsigned int j = 0; j < len; j++) {
    matrix[rail][j] = *text++;
    if (rail == rails - 1 && direction == DOWN) {
      // If we get to the bottom, reverse direction
      direction = UP;
    } else if (rail == 0 && direction == UP) {
      // If we get to the top, reverse direction
      direction = DOWN;
    }
    rail += direction;
  }

  // Read each rail to the result ptr to get the cyphertext
  for (rail = 0; rail < rails; rail++) {
    for (unsigned int j = 0; j < len; j++) {
      if (matrix[rail][j] != '\0') {
        // If it's not a blank spot
        *r_ptr++ = matrix[rail][j];
      }
    }
  }

  // Free the matrix
  for (unsigned int i = 0; i < rails; i++) {
    free(matrix[i]);
  }
  free(matrix);

  return r;
}

char *decode(char *text, size_t rails) {
  // Setup result var
  size_t len = strlen(text);
  char *r = calloc(len + 1, sizeof(char));
  char *r_ptr = r;

  // Allocate a matrix
  char **matrix = calloc(rails, sizeof(char *));
  for (unsigned int i = 0; i < rails; i++) {
    matrix[i] = calloc(len + 1, sizeof(char));
  }

  // Get the spacing between the letters
  // Spacing alternates between two sizes (k and k')
  unsigned int k = (rails - 1) * 2;
  unsigned int k_p = 0;
  // k_state allows us to keep track of which k to use
  k_state_t k_state = K;

  // On each rail, spread the letters correctly
  for (unsigned int rail = 0; rail < rails; rail++) {
    // j starts at the current rail number and we skip the increment logic since
    // it is too complex to put here
    for (unsigned int j = rail; j < len;) {
      // If we're on a K count and k value is not zero, put the letter here and
      // increment by k
      if (k_state == K && k != 0) {
        matrix[rail][j] = *text++;
        j += k;
      } else if (k_state == K_P && k_p != 0) {
        // If we're on a K' count and k' value is not zero, put the letter here
        // and increment by k'
        matrix[rail][j] = *text++;
        j += k_p;
      }
      // Flip the state (k will become k' and vice versa)
      k_state ^= 1;
    }

    // After the row, reset the state to K, and adjust the values of k and k'
    // for next row
    k_state = K;
    k -= 2;
    k_p += 2;
  }

  // Read the letters on a zig zag pattern on the matrix
  unsigned int rail = 0;
  direction_t direction = DOWN;
  for (unsigned int j = 0; j < len; j++) {
    *r_ptr++ = matrix[rail][j];
    if (rail == rails - 1 && direction == DOWN) {
      // If we get to the bottom, reverse direction
      direction = UP;
    } else if (rail == 0 && direction == UP) {
      // If we get to the top, reverse direction
      direction = DOWN;
    }
    rail += direction;
  }

  // Free the matrix
  for (unsigned int i = 0; i < rails; i++) {
    free(matrix[i]);
  }
  free(matrix);

  return r;
}
