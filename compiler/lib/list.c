#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include "utils.h"
#include "cast.h"
#include "list.h"

struct List* createList(
	int32_t type
) {
	struct List* new = (struct List*) malloc(sizeof(struct List));
	// default initialize size is 1
	new->size = 1;
	new->type = type;
	// means that the next element would be added at curPos
	new->curPos = 0;
	new->arr = (void**)malloc(new->size * sizeof(void*));
	return new;
}

int rangeHelper(int size, int index){
	if(size <= -index || size <= index || size == 0){
		printf("Error! Index out of Range!\n");
		return -1;
		exit(1);
	}
	if (index < 0){
		index += size;
	}
	return index;
}

struct List* addListHelper(
	struct List * list,
	void* addData
){
	if (list->curPos >= list->size){
		list->size = list->size * 2;
		// double size
		list->arr = (void**) realloc(list->arr, list->size * sizeof (void*));
	}
	*(list->arr + list->curPos) = addData;
	list->curPos++;
	return list;
}

struct List* concatList(struct List* list1, struct List* list2){
	int curPos = list2->curPos;
	for(int i =0; i < curPos; i++){
		list1 = addListHelper(list1, *(list2->arr+i));
	}
	return list1;
}

struct List* addList(struct List* list, ...) {
	if (list == NULL) {
		printf("[Error] addList() - List doesn't exist. \n");
		exit(1);
	}
	va_list ap;
	va_start(ap, 1);
	void * data;
	int* tmp0;
	double* tmp1;
	bool* tmp2;
	switch (list->type) {
		case INT:
			data = InttoVoid(va_arg(ap, int));
			break;

		case FLOAT:
			data = FloattoVoid(va_arg(ap, double));
			break;

		case BOOL:
			data = BooltoVoid(va_arg(ap, bool));
			break;

		case STRING:
			data = StringtoVoid(va_arg(ap, char*));
			break;

		case NODE:
			data = NodetoVoid(va_arg(ap, struct Node*));
			break;
		case EDGE:
			data =EdgetoVoid(va_arg(ap, struct Edge*));
			break;

		case GRAPH:
			data = GraphtoVoid(va_arg(ap, struct Graph*));
			break;

		default:
			break;
	}
  va_end(ap);
  return addListHelper(list, data);
}

void* getList(struct List* list, int index){
	if (list == NULL) {
		printf("[Error] getList() - List doesn't exist. \n");
		exit(1);
	}
	index = rangeHelper(list->curPos, index);
	return *(list->arr + index);
}

void* popList(struct List* list){
	if (list == NULL) {
		printf("[Error] popList() - List doesn't exist. \n");
		exit(1);
	}
	if(list->curPos-1 < 0){
		printf("Error! Nothing Can be poped T.T\n");
		exit(1);
	}
	void* add = *(list->arr + list->curPos-1);
	list->curPos--;
	return add;
}

int32_t setList(struct List* list, int index, ...){
	if (list == NULL) {
		printf("[Error] setList() - List doesn't exist. \n");
		exit(1);
	}
	index = rangeHelper(list->curPos, index);
	va_list ap;
	va_start(ap, 1);
	void * data;
	int* tmp0;
	double* tmp1;
	bool* tmp2;
	switch (list->type) {
		case INT:
			data = InttoVoid(va_arg(ap, int));
			break;

		case FLOAT:
			data = FloattoVoid(va_arg(ap, double));
			break;

		case BOOL:
			data = BooltoVoid(va_arg(ap, bool));
			break;

		case STRING:
			data = StringtoVoid(va_arg(ap, char*));
			break;

		case NODE:
			data = NodetoVoid(va_arg(ap, struct Node*));
			break;
		case EDGE:
			data = EdgetoVoid(va_arg(ap, struct Edge*));
			break;

		case GRAPH:
			data = GraphtoVoid(va_arg(ap, struct Graph*));
			break;

		default:
			break;
	}
	*(list->arr + index) = data;
	return 0;
}

int getListSize(struct List* list){
	if (list == NULL) {
		printf("[Error] getListSize() - List doesn't exist. \n");
		exit(1);
	}
	return list->curPos;
}

int32_t removeList(struct List* list, int index){
	if (list == NULL) {
		printf("[Error] removelist() - List doesn't exist. \n");
		exit(1);
	}
	index =rangeHelper(list->curPos, index);
	if (list->curPos == 1 && index == 0) {
	} else {
		for(int i=index; i < list->curPos; i++){
			*(list->arr + i) = *(list->arr + i+1);
		}
	}
	list->curPos--;
	return 0;
}

bool intCompare(int target, int cur) {
	return target == cur;
}

bool floatCompare(double target, double cur) {
	return target == cur;
}

bool boolCompare(bool target, bool cur) {
	return target == cur;
}

bool stringCompare(char* target, char* cur) {
	return strcmp(target, cur) == 0;
}

bool nodeCompare(struct Node* target, struct Node* cur) {
	return target->id == cur->id;
}

bool edgeCompare(struct Edge* target, struct Edge* cur){
	return (target->sour == cur->sour) && (target->dest == cur->dest);
}

struct List* removeData(struct List* list, ...) {
	if (list == NULL) {
		return list;
	} else if (list->curPos == 0) {
		return list;
	} else {
		int p = 0;
		int curPos = list->curPos;
		//printf("%d\n", curPos);
		va_list ap;
		va_start(ap, 1);
		switch (list->type) {
    case INT:
      ;
      int tmp = va_arg(ap, int);
      while (p < curPos) {
        if (intCompare(tmp, *((int *)(*(list->arr + p))))) {
			//printf("Hello\n");
			removeList(list, p);
			p--;
			curPos--;
		}
		//printf("Hey\n");
        p++;
      }
      break;

    case FLOAT:
      ;
      double tmpF = va_arg(ap, double);
      while (p < curPos) {
        if (floatCompare(tmpF, *((double *)(*(list->arr + p))))) {
			removeList(list, p);
			p--;
			curPos--;
		}
        p++;
      }
      break;

    case BOOL:
      ;
      bool tmpB = va_arg(ap, bool);
      while (p < curPos) {
        if (boolCompare(tmpB, *((bool *)(*(list->arr + p))))) {
			removeList(list, p);
			p--;
			curPos--;
		}
        p++;
      }
      break;

    case STRING:
	;
      char * tmpC = va_arg(ap, char*);
      while (p < curPos) {
        if (stringCompare(tmpC, ((char *)(*(list->arr + p))))) {
			removeList(list, p);
			p--;
			curPos--;
		}
        p++;
      }
      break;

    case NODE:
	;
      struct Node * tmpN = va_arg(ap, struct Node *);
      while (p < curPos) {
        if (nodeCompare(tmpN, ((struct Node *)(*(list->arr + p))))) {
			removeList(list, p);
			p--;
			curPos--;
		}
        p++;
      }
      break;
    
    case EDGE:
	;
      struct Edge * tmpE = va_arg(ap, struct Edge *);
      while (p < curPos) {
        if (edgeCompare(tmpE, ((struct Edge *)(*(list->arr + p))))) {
			removeList(list, p);
			p--;
			curPos--;
		}
        p++;
      }
      break;

    // case GRAPH:
    //   while (p < curPos) {
    //     if (graphCompare(va_arg(ap, struct Graph *), ((struct Graph *)(*(list->arr + p))))) {
	// 		result = true;
	// 		break;
	// 	}
    //     p++;
    //   }
    //   break;

    default:
      printf("Unsupported List Type!\n");
	  exit(1);
    }
	va_end(ap);
	return list;
	}
}

bool listContains(struct List *list, ...) {
  if (list == NULL) {
    return false;
  } else if (list->curPos == 0) {
    return false;
  } else {
    int p = 0;
	void *data;
    int curPos = list->curPos;
    va_list ap;
    va_start(ap, 1);
    bool result = false;
    switch (list->type) {
    case INT:
      ;
      int tmp = va_arg(ap, int);
      while (p < curPos) {
        if (intCompare(tmp, *((int *)(*(list->arr + p))))) {
			result = true;
			break;
		}
        p++;
      }
      break;

    case FLOAT:
      ;
      double tmpF = va_arg(ap, double);
      while (p < curPos) {
        if (floatCompare(tmpF, *((double *)(*(list->arr + p))))) {
			result = true;
			break;
		}
        p++;
      }
      break;

    case BOOL:
      ;
      bool tmpB = va_arg(ap, bool);
      while (p < curPos) {
        if (boolCompare(tmpB, *((bool *)(*(list->arr + p))))) {
			result = true;
			break;
		}
        p++;
      }
      break;

    case STRING:
	;
      char * tmpC = va_arg(ap, char*);
      while (p < curPos) {
        if (stringCompare(tmpC, ((char *)(*(list->arr + p))))) {
			result = 1;
			break;
		}
        p++;
      }
      break;

    case NODE:
	;
      struct Node * tmpN = va_arg(ap, struct Node *);
      while (p < curPos) {
        if (nodeCompare(tmpN, ((struct Node *)(*(list->arr + p))))) {
			result = 1;
			break;
		}
        p++;
      }
      break;
     
    case EDGE:
	;
      struct Node * tmpE = va_arg(ap, struct Edge *);
      while (p < curPos) {
        if (edgeCompare(tmpE, ((struct Edge *)(*(list->arr + p))))) {
			result = 1;
			break;
		}
        p++;
      }
      break;

    // case GRAPH:
    //   while (p < curPos) {
    //     if (graphCompare(va_arg(ap, struct Graph *), ((struct Graph *)(*(list->arr + p))))) {
	// 		result = true;
	// 		break;
	// 	}
    //     p++;
    //   }
    //   break;

    default:
      printf("Unsupported List Type!\n");
	  exit(1);
    }
    va_end(ap);
	return result;
  }
}

int32_t printList(struct List * list){
	if (list == NULL) {
		printf("(null)\n");
		return 0;
	}
	int curPos = list->curPos - 1;
	if (curPos < 0) {
		printf("list:[]\n");
		return 0;
	}
	int p = 0;
	printf("list:[");
	switch (list->type) {
		case INT:
			while(p < curPos){
				printf("%d, ", *((int*)(*(list->arr + p))));
				p++;
			}
			printf("%d", *((int*)(*(list->arr + p))));
			break;

		case FLOAT:
			while(p < curPos){
				printf("%f, ", *((double*)(*(list->arr + p))));
				p++;
			}
			printf("%f", *((double*)(*(list->arr + p))));
			break;

		case BOOL:
			while(p < curPos){
				printf("%s, ", *((bool*)(*(list->arr + p))) ? "true" : "false");
				p++;
			}
			printf("%s", *((bool*)(*(list->arr + p))) ? "true" : "false");
			break;

		case STRING:
			while(p < curPos){
				printf("%s, ", ((char*)(*(list->arr + p))));
				p++;
			}
			printf("%s", ((char*)(*(list->arr + p))));
			break;

		case NODE:
			while(p < curPos){
				printNode((struct Node*)(*(list->arr + p)));
				p++;
			}
			printNode((struct Node*)(*(list->arr + p)));
			break;
			
		case EDGE:
			while(p < curPos){
				printEdge((struct Edge*)(*(list->arr + p)));
				p++;
			}
			printEdge((struct Edge*)(*(list->arr + p)));
			break;

		case GRAPH:
			while(p < curPos){
				printGraph((struct Graph*)(*(list->arr + p)));
				p++;
			}
			printGraph((struct Graph*)(*(list->arr + p)));
			break;

		default:
			printf("Unsupported List Type!\n");
			return 1;
	}
	printf("]\n");
	return 0;
	// int p = 0;
	// printf("list:[");
	// while(p < curPos){
	// 	printf(fmt, *(list->arr + p));
	// 	printf(", ");
	// 	p++;
	// }
	// printf(fmt, *(list->arr + curPos));
	// printf("]\n");
	// return 1;
}



// int main() {
//  	struct List* a = createList(INT);
//  	addList(a, 10);
// 	addList(a, 5);
// 	addList(a, 15);
// 	printList(a);
// 	removeData(a, 5);
// 	printList(a);
// 	removeData(a, 10);
// 	printList(a);
// 	// if (listContains(a, 10)) {
// 	//   printf("list contains 10");
// 	// }
// 	// if (!listContains(a, 3)) {
// 	//   printf("list not contains 3");
// 	// }
// }
