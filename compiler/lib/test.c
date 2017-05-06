#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

int main() {
  struct List *l = createList(sizeof(int));
  addList(l, 3, 4);
  if (contains(l, 3)) {
    printf("contains 3");
  }
  if (contains(l, 5)) {
    printf("contains 5");
  } else {
    printf("not contains 5");
  }
}