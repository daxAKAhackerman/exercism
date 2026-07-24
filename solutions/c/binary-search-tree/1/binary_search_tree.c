#include "binary_search_tree.h"
#include <stdbool.h>
#include <stdlib.h>

node_t *build_tree(int *tree_data, size_t tree_data_len) {
  node_t *base_node = calloc(1, sizeof(node_t));
  base_node->data = tree_data[0];

  node_t *current_node = base_node;

  for (unsigned int i = 1; i < tree_data_len; i++) {
    node_t *new_node = calloc(1, sizeof(node_t));
    new_node->data = tree_data[i];
    while (true) {
      if (new_node->data <= current_node->data) {
        if (current_node->left == NULL) {
          current_node->left = new_node;
          break;
        } else {
          current_node = current_node->left;
          continue;
        }
      } else {
        if (current_node->right == NULL) {
          current_node->right = new_node;
          break;
        } else {
          current_node = current_node->right;
          continue;
        }
      }
    }
    current_node = base_node;
  }

  return base_node;
}

void free_tree(node_t *tree) {
  if (tree->left != NULL)
    free_tree(tree->left);
  if (tree->right != NULL)
    free_tree(tree->right);

  free(tree);
}

static void get_next_sorted_int(node_t *tree, int **r) {
  if (tree->left != NULL)
    get_next_sorted_int(tree->left, r);

  **r = tree->data;
  (*r)++;

  if (tree->right != NULL)
    get_next_sorted_int(tree->right, r);
}

int *sorted_data(node_t *tree) {
  int *r = calloc(64, sizeof(int));
  int *r_ptr = r;
  get_next_sorted_int(tree, &r_ptr);
  return r;
}
