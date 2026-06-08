#include "circular_buffer.h"
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

circular_buffer_t *new_circular_buffer(unsigned int capacity) {
  int *internal_buffer = calloc(capacity, sizeof(int));
  circular_buffer_t *buffer = calloc(1, sizeof(circular_buffer_t));
  buffer->buffer = internal_buffer;
  buffer->buffer_size = capacity;

  return buffer;
}

void delete_buffer(circular_buffer_t *buffer) {
  free(buffer->buffer);
  free(buffer);
}

void clear_buffer(circular_buffer_t *buffer) {
  memset(buffer->buffer, 0, buffer->buffer_size);
  buffer->newest_entry_pos = 0;
  buffer->newest_entry_pos = 0;
  buffer->num_of_entries = 0;
}

int16_t read(circular_buffer_t *buffer, buffer_value_t *read_value) {
  if (buffer->num_of_entries == 0) {
    errno = ENODATA;
    return EXIT_FAILURE;
  } else {
    *read_value = buffer->buffer[buffer->oldest_entry_pos];
    buffer->num_of_entries--;
    buffer->oldest_entry_pos =
        buffer->oldest_entry_pos == buffer->buffer_size - 1
            ? 0
            : buffer->oldest_entry_pos + 1;
    return EXIT_SUCCESS;
  }
}

int16_t write(circular_buffer_t *buffer, int value) {
  if (buffer->buffer_size == buffer->num_of_entries) {
    errno = ENOBUFS;
    return EXIT_FAILURE;
  }

  buffer->buffer[buffer->newest_entry_pos] = value;

  buffer->num_of_entries++;
  buffer->newest_entry_pos = buffer->newest_entry_pos == buffer->buffer_size - 1
                                 ? 0
                                 : buffer->newest_entry_pos + 1;

  return EXIT_SUCCESS;
}

int16_t overwrite(circular_buffer_t *buffer, int value) {
  int read_value = 0;
  int16_t status = 0;

  if (buffer->num_of_entries == buffer->buffer_size) {
    if ((status = read(buffer, &read_value)) != EXIT_SUCCESS) {
      return status;
    }
  }
  return write(buffer, value);
}
