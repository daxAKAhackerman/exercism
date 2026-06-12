#include "matching_brackets.h"

bool is_paired(const char *input) {
  char bracket_stack[BRACKET_STACK_SIZE] = {0};
  char *stack_ptr = bracket_stack;
  char c = '\0';

  while ((c = *input++) != '\0') {
    if (c == '{' || c == '[' || c == '(') {
      // Add any opening brace to the stack
      *stack_ptr++ = c;
    } else if (c == '}' || c == ']' || c == ')') {
      // If closing bracket
      if (stack_ptr == bracket_stack) {
        // If stack is empty, then unmatched for sure
        return false;
      } else if (*(stack_ptr - 1) != (c == ')' ? '(' : c - 2)) {
        // If last bracket on the stack doesn't match, error
        return false;
      } else {
        // Else it matches, just pop the stack
        stack_ptr--;
      }
    }
  }

  // If anything is left on the stack at the end, error
  if (stack_ptr != bracket_stack) {
    return false;
  }

  return true;
}
