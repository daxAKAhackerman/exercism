#include "grade_school.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int comp_student(const void *a, const void *b) {
  char *str1 = calloc(MAX_NAME_LENGTH * 2 + 1, sizeof(char));
  char *str2 = calloc(MAX_NAME_LENGTH * 2 + 1, sizeof(char));

  student_t *student1 = (student_t *)a;
  student_t *student2 = (student_t *)b;

  snprintf(str1, MAX_NAME_LENGTH * 2, "%d%s", student1->grade, student1->name);
  snprintf(str2, MAX_NAME_LENGTH * 2, "%d%s", student2->grade, student2->name);

  int result = strncmp(str1, str2, MAX_NAME_LENGTH + 1);

  free(str1);
  free(str2);

  return result;
}

void init_roster(roster_t *roster) {
  memset(roster->students, 0, sizeof(student_t) * roster->count);
  roster->count = 0;
}

bool add_student(roster_t *roster, char *name, uint8_t grade) {
  for (unsigned int i = 0; i < roster->count; i++) {
    if (strncmp(name, roster->students[i].name, MAX_NAME_LENGTH) == 0) {
      return false;
    }
  }

  roster->students[roster->count] = (student_t){.grade = grade, .name = {'\0'}};
  strncpy(roster->students[roster->count].name, name, MAX_NAME_LENGTH);

  roster->count++;

  qsort(roster->students, roster->count, sizeof(student_t), comp_student);

  return true;
}

roster_t get_grade(roster_t *roster, uint8_t grade) {
  roster_t new_roster = {0};
  for (unsigned int i = 0; i < roster->count; i++) {
    if (roster->students[i].grade == grade) {
      new_roster.students[new_roster.count] = roster->students[i];
      new_roster.count++;
    }
  }
  return new_roster;
}
