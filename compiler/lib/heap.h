#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "utils.h"


#ifndef _HEAP_H_
#define _HEAP_H_

typedef struct minHeap {
    int size;
    int32_t type;
    struct List* array;
} minHeap ;


struct minHeap* initList(int size);
void swap(struct List* list, int index1, int index2);
void heapify(minHeap* hp, int i);
void insertData(minHeap* hp, int data);
Edge getMinValue(minHeap* hp);


#endif