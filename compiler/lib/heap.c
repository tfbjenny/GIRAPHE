
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include "list.h"
#include "utils.h"


typedef struct minHeap {
    //int size;
    int32_t type;
    struct List* array;
} minHeap ;

minHeap* initList() {
  minHeap *heap = malloc(sizeof(heap));
  if (heap != NULL) {
    //heap->size = 0;
    heap->type = EDGE;
    heap->array = createList(EDGE);
  }
  return heap;
}

void swap(struct List* list, int index1, int index2){
    struct Edge* data1 = getList(list, index1);
    struct Edge* data2 = getList(list, index2);
    setList(list, index1, data2);
    setList(list, index2, data1);
}

//void buildHeap(struct List* list, int n){
//    int i = n /2;
//    while( i > 0) heapify(list, n, --i);
//}

void heapify(minHeap* hp, int i){
    i = i/2;
    int childLeft = -1;
    int childRight = -1;
    int largest = i;
    
    if(getList(hp->array, (2*i+1))) childLeft = 2*i+1;
    if(getList(hp->array, (2*i+2))) childRight =2*i+2;
    
    if(childLeft < 0 && childRight < 0) return;
    if(childLeft < 0) childLeft = childRight;
    if(childRight < 0) childRight = childLeft;
    
    if(getList(hp->array, childLeft) > getList(hp->array, i)) largest = childLeft;
    if(getList(hp->array, childRight) > getList(hp->array,largest)) largest = childRight;
    
    if(largest != i){
      swap(hp->array, i, largest);
      heapify(hp, largest);
    }
    
}

void insertData(minHeap* hp, struct Edge* data){
    if(getListSize(hp->array)){
      addList(hp->array, data);
      int size = getListSize(hp->array);
      heapify(hp, size);
     
    
    }else {
      addList(hp->array, data);
    }
    
    //hp->size ++;
    //printf("insertData finished");
    
}


struct Edge* getMinValue(minHeap* hp){
    if(getListSize(hp->array)){
      struct Edge* data = getList(hp->array,0);
      removeList(hp->array,0);
      int size = getListSize(hp->array);
      heapify(hp,size);
      return data;
    
    } else {
      return NULL;
    
    }
}

int32_t printHeap(minHeap* hp){
    printList(hp->array);
    printf("printHeap finished");
}



int main(){
    minHeap* mp = initList();
    struct Node* sour = createNode(1, 0, 12, 0, 0, NULL);
    struct Node* dest = createNode(2, 1, 0, 1.2, 0, NULL);
    //printNode(sour);
    //printNode(dest);
    struct Node* sour2 = createNode(3, 2, 0, 0, 0, NULL);
	struct Node* dest2 = createNode(4, 3, 0, 0, 1, NULL);
    struct Edge e = createEdge(sour, dest, EDGE, 0, 0, 0, NULL);
    struct Edge ed = createEdge(sour2, dest2, EDGE, 1, 0, 0, NULL);
    struct Edge* e_ptr = &(e);
    struct Edge* e_ptr2 = &(ed);
    //printEdge(e_ptr);
    insertData(mp, e_ptr);
    int size = getListSize(mp->array);
    printf("size: %d",size);
    //printHeap(mp);
    insertData(mp, e_ptr2);
    int size2 = getListSize(mp->array);
    printf("size: %d",size2);
}







