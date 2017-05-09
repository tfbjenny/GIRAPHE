
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

minHeap* initList(int32_t type) {
  minHeap *heap = malloc(sizeof(heap));
  if (heap != NULL) {
    //heap->size = 0;
    // edge type
    heap->type = type;
    heap->array = createList(EDGE);
  }
  return heap;
}

void swap(struct List* list, int index1, int index2){
    struct Edge* data1 = (struct Edge*) getList(list, index1);
    struct Edge* data2 = (struct Edge*) getList(list, index2);
    
    //struct Edge temp;
    //temp = *data2;
    //*data2 = *data1;
    //*data1 = temp;
	
    setList(list, index1, data2);
    setList(list, index2, data1);
}

//void buildHeap(struct List* list, int n){
//    int i = n /2;
//    while( i > 0) heapify(list, n, --i);
//}

int eCompare(struct minHeap* hp, struct Edge* lchild, struct Edge* rchild) {
    switch(hp->type) {
        case INT:
          return lchild->a > rchild->a ? 1 : 0;
          break;
        case FLOAT:
          return lchild->b > rchild->b ? 1 : 0;
          break;
        case BOOL:
          return lchild->c > rchild->c ? 1 : 0;
          break;
        default:
          printf("[Error] Unsupported type for edge compare !\n");
          exit(1);
          break;
    }
}

void heapify(minHeap* hp, int size){
    int i = (size - 1) /2;
    struct Edge* lchild = NULL;
    struct Edge* rchild = NULL;
    struct Edge* cur = NULL;
    int largest = i;
    while (i >= 0) {
        cur = (struct Edge*) getList(hp->array, i);
        if (2 * i + 1 < size) {
            lchild = (struct Edge*) getList(hp->array, 2 * i + 1);
        }
        if (2 * i + 2 < size) {
            rchild = (struct Edge*) getList(hp->array, 2 * i + 2);
        }
        if (rchild != NULL && lchild != NULL) {
            if (eCompare(hp, lchild, rchild) > 0) {
                if (eCompare(hp, cur, rchild) > 0) {
                    swap(hp->array, i, 2 * i + 2);
                }
            } else {
                if (eCompare(hp, cur, lchild) > 0) {
                    swap(hp->array, i, 2 * i + 1);
                }
            }
        } else if (rchild == NULL && lchild != NULL){
            if (eCompare(hp, cur, lchild) > 0) {
                swap(hp->array, i, 2 * i + 1);
            }
        }
        i--;
    }
	
	// printf("heapify start!");
    
    // if(getList(hp->array, (2*i+1)) != -1) childLeft = 2*i+1;
    // if(getList(hp->array, (2*i+2)) != -1) childRight =2*i+2;
	
	// printf("Child Intialized sucesss!");
    
    // if(childLeft < 0 && childRight < 0) return;
    // if(childLeft < 0) childLeft = childRight;
    // if(childRight < 0) childRight = childLeft;
    
    // if(getList(hp->array, childLeft) > getList(hp->array, i)) largest = childLeft;
    // if(getList(hp->array, childRight) > getList(hp->array,largest)) largest = childRight;
    
    // if(largest != i){
    //   swap(hp->array, i, largest);
    //   heapify(hp, largest);
    // }
    
}

void insertData(minHeap* hp, struct Edge* data){
    if(getListSize(hp->array) > 0){
      addList(hp->array, data);
      int size = getListSize(hp->array);
      heapify(hp, size);
    } else {
      addList(hp->array, data);
    }
}


struct Edge* getMinValue(minHeap* hp){
    if(getListSize(hp->array) > 0){
      struct Edge* data = (struct Edge*) getList(hp->array,0);
      int size = getListSize(hp->array);
      swap(hp->array, 0, size - 1);
      popList(hp->array);
      heapify(hp,size - 1);
      return data;
    } else {
      printf("Cannot get value from empty minHeap");
      return NULL;
    }
}

int32_t printHeap(minHeap* hp){
    printList(hp->array);
    //printf("printHeap finished");
    return 0;
}



int main(){
	/*
	struct List* a = createList(EDGE);
	struct Node* sour = createNode(1, 0, 12, 0, 0, NULL);
	struct Node* dest = createNode(2, 1, 0, 1.2, 0, NULL);
	struct Edge ed = createEdge(sour, dest, EDGE, 0, 0, 0, NULL);
	struct Node* s = createNode(3, 0, 3, 0, 0, NULL);
	//printNode(s);
	struct Node* d = createNode(4, 1, 0, 1.5, 0, NULL);
	//printNode(d);
	struct Edge edg = createEdge(s, d, EDGE, 0, 0, 0, NULL);
	struct Edge* e_ptr = &(ed);
	struct Edge* e_ptr2 = &(edg);
	//printEdge(e_ptr);
	//printEdge(e_ptr2);
	
 	addList(a, e_ptr);
	addList(a, e_ptr2);
	
	printList(a);
	swap(a,0,1);
	printList(a);
	
	struct Edge* data = getList(a,0);
	printEdge(data);
	
	*/
	
	
   	 minHeap* mp = initList(INT);
    	struct Node* sour = createNode(1, 0, 12);
    	struct Node* dest = createNode(2, 0, 3);
    //printNode(sour);
    //printNode(dest);
    	struct Node* s = createNode(3, 0, 6);
    	struct Node* d = createNode(4, 0, 4);
    	struct Edge e = createEdge(sour, dest, 0, 6, 0.0, 0, NULL);
    	struct Edge edg = createEdge(s, d, 0, 3, 0.0, 0, NULL);
        struct Edge e2 = createEdge(s, dest, 0, 2, 0.0, 0, NULL);
        struct Edge e3 = createEdge(sour, d, 0, 1, 0.0, 0, NULL);
    	struct Edge* e_ptr = &(e);
    	struct Edge* e_ptr2 = &(edg);
        //printEdge(e_ptr);
	//printEdge(e_ptr2);
    	insertData(mp, e_ptr);
    	int size = getListSize(mp->array);
    	printf("size: %d \n",size);
    	printHeap(mp);
	printf("------ \n");
    	insertData(mp, e_ptr2);
    	int size2 = getListSize(mp->array);
    	printf("size: %d \n",size2);
	printHeap(mp);
    printf("------ \n");
    	insertData(mp, &e2);
    	int size3 = getListSize(mp->array);
    	printf("size: %d \n",size3);
	printHeap(mp);
    printf("------ \n");
    	insertData(mp, &e3);
    	int size4 = getListSize(mp->array);
    	printf("size: %d \n",size4);
	printHeap(mp);
	
	printf("------ \n");
	struct Edge* data = getMinValue(mp);
	printEdge(data);
	
}







