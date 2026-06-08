#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>

typedef struct {
  int *buffer;
  unsigned int buffer_size;
  unsigned int oldest_entry_pos;
  unsigned int newest_entry_pos;
  unsigned int num_of_entries;
} circular_buffer_t;

typedef int buffer_value_t;

circular_buffer_t *new_circular_buffer(unsigned int capacity);

int16_t read(circular_buffer_t *buffer, buffer_value_t *read_value);

int16_t write(circular_buffer_t *buffer, int value);

int16_t overwrite(circular_buffer_t *buffer, int value);

void delete_buffer(circular_buffer_t *buffer);

void clear_buffer(circular_buffer_t *buffer);

#endif
