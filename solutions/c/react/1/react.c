#include "react.h"
#include <stdbool.h>
#include <stdlib.h>

struct reactor *create_reactor(void) {
  struct reactor *r = calloc(1, sizeof(struct reactor));
  return r;
}

static void add_cell(struct reactor *r, struct cell *c) {
  r->num_cells++;
  r->cells = realloc(r->cells, sizeof(struct cell *) * r->num_cells);
  r->cells[r->num_cells - 1] = c;
}

struct cell *create_input_cell(struct reactor *r, int initial_value) {
  struct cell *c = calloc(1, sizeof(struct cell));
  c->value = initial_value;
  c->r = r;
  add_cell(r, c);
  return c;
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *c1,
                                  compute1 c_fn) {

  struct cell *c = calloc(1, sizeof(struct cell));
  c->cell_type = COMPUTE1;
  c->value = c_fn(c1->value);
  c->r = r;
  c->c_fn1 = c_fn;
  c->c1 = c1;
  add_cell(r, c);
  return c;
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *c1,
                                  struct cell *c2, compute2 c_fn) {
  struct cell *c = calloc(1, sizeof(struct cell));
  c->cell_type = COMPUTE2;
  c->value = c_fn(c1->value, c2->value);
  c->r = r;
  c->c_fn2 = c_fn;
  c->c1 = c1;
  c->c2 = c2;
  add_cell(r, c);
  return c;
}

callback_id add_callback(struct cell *c, void *p, callback c_fn) {
  if (c->callbacks == NULL) {
    c->callbacks = calloc(1, sizeof(struct callback_t));
    c->callbacks->params = p;
    c->callbacks->c_fn = c_fn;
    c->callbacks->id = c->callback_next_id++;
    return c->callbacks->id;
  } else {
    struct callback_t *c_ptr = c->callbacks;
    while (c_ptr->next != NULL)
      c_ptr = c_ptr->next;
    c_ptr->next = calloc(1, sizeof(struct callback_t));
    c_ptr->next->params = p;
    c_ptr->next->c_fn = c_fn;
    c_ptr->next->id = c->callback_next_id++;
    return c_ptr->next->id;
  }
}

void remove_callback(struct cell *c, callback_id cb_id) {
  struct callback_t *cb_buf = NULL;
  if (c->callbacks != NULL && c->callbacks->id == cb_id) {
    cb_buf = c->callbacks->next;
    free(c->callbacks);
    c->callbacks = cb_buf;
  } else {
    struct callback_t *c_ptr = c->callbacks;
    while (c_ptr->next != NULL) {
      if (c_ptr->next->id == cb_id) {
        cb_buf = c_ptr->next->next;
        free(c_ptr->next);
        c_ptr->next = cb_buf;
      }
    }
  }
}

static void fire_callbacks(struct cell *c) {
  struct callback_t *cb = c->callbacks;
  while (cb != NULL) {
    cb->c_fn(cb->params, c->value);
    cb = cb->next;
  }
}

static bool stabilize(struct reactor *r) {
  bool changed = false;
  struct cell *c = NULL;
  int prev_value = 0;

  for (unsigned int i = 0; i < r->num_cells; i++) {
    c = r->cells[i];
    if (c->cell_type == COMPUTE1) {
      prev_value = c->value;
      c->value = c->c_fn1(c->c1->value);
      if (c->value != prev_value) {
        fire_callbacks(c);
        changed = true;
      }
    } else if (c->cell_type == COMPUTE2) {
      prev_value = c->value;
      c->value = c->c_fn2(c->c1->value, c->c2->value);
      if (c->value != prev_value) {
        fire_callbacks(c);
        changed = true;
      }
    }
  }

  if (changed)
    return stabilize(r);

  return changed;
}

int get_cell_value(struct cell *c) { return c->value; }

void set_cell_value(struct cell *c, int new_value) {
  c->value = new_value;
  stabilize(c->r);
}

static void free_callbacks(struct callback_t *cb) {
  if (cb != NULL) {
    if (cb->next != NULL)
      free_callbacks(cb->next);
    free(cb);
  }
}

void destroy_reactor(struct reactor *r) {
  for (unsigned int i = 0; i < r->num_cells; i++) {
    free_callbacks(r->cells[i]->callbacks);
    free(r->cells[i]);
  }

  free(r->cells);
  free(r);
}
