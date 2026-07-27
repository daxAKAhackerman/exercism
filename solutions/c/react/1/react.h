#ifndef REACT_H
#define REACT_H

typedef enum { INPUT, COMPUTE1, COMPUTE2 } cell_type_t;

struct reactor;
struct cell;
struct callback_t;

typedef int (*compute1)(int);
typedef int (*compute2)(int, int);

struct cell {
  struct reactor *r;
  int value;
  cell_type_t cell_type;
  compute1 c_fn1;
  compute2 c_fn2;
  struct cell *c1;
  struct cell *c2;
  struct callback_t *callbacks;
  int callback_next_id;
};

struct reactor {
  struct cell **cells;
  unsigned int num_cells;
};

struct reactor *create_reactor(void);
// destroy_reactor should free all cells created under that reactor.
void destroy_reactor(struct reactor *);

struct cell *create_input_cell(struct reactor *, int initial_value);
struct cell *create_compute1_cell(struct reactor *, struct cell *, compute1);
struct cell *create_compute2_cell(struct reactor *, struct cell *,
                                  struct cell *, compute2);

int get_cell_value(struct cell *);
void set_cell_value(struct cell *, int new_value);

typedef void (*callback)(void *, int);
typedef int callback_id;

struct callback_t {
  int id;
  callback c_fn;
  void *params;
  struct callback_t *next;
};

// The callback should be called with the same void * given in add_callback.
callback_id add_callback(struct cell *, void *, callback);
void remove_callback(struct cell *, callback_id);

#endif
