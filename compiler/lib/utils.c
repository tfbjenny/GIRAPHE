#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include "utils.h"
#include "hashmap.c"
#include "list.c"
#include "cast.c"

int32_t printBool(bool a) {
	printf("%s\n", a ? "true" : "false");
	return 0;
}

/************************************
	Queue Methods
************************************/
struct Queue* createQueue(int32_t type) {
	struct Queue* new = (struct Queue*) malloc(sizeof(struct Queue));
	new->lst = createList(type);
	return new;
}

struct Queue* pushBack(struct Queue* q, ...) {
	va_list ap;
	va_start(ap, 1);
	void* data;
	switch (q->lst->type) {
		case INT:
			addList(q->lst, va_arg(ap, int));
			break;

		case FLOAT:
			addList(q->lst, va_arg(ap, double));
			break;

		case BOOL:
			addList(q->lst, va_arg(ap, bool));
			break;

		case STRING:
			addList(q->lst, va_arg(ap, char*));
			break;

		case NODE:
			addList(q->lst, va_arg(ap, struct Node*));
			break;

		case GRAPH:
			addList(q->lst, va_arg(ap, struct Graph*));
			break;

		default:
			break;
	}
  va_end(ap);
  return q;
}

void* popFront(struct Queue* q) {
	if (q == NULL) {
		printf("[Error] popFront() - queue doesn't exist. \n");
		exit(1);
	} else if (q->lst->curPos -1 < 0) {
		printf("Error! Nothing Can be poped T.T\n");
		exit(1);
	}
	void* data = getList(q->lst, 0);
	removeList(q->lst, 0);
	return data;
}

int getQueueSize(struct Queue* q) {
	return getListSize(q->lst);
}

int32_t printQueue(struct Queue* q) {
	return printList(q->lst);
}

/************************************
	Node Methods
************************************/

struct Node* createNode(int32_t id, int32_t type, ...) {
	struct Node* new = (struct Node*) malloc(sizeof(struct Node));
	new->id = id;
	new->type = type;
	new->visited = false;
	va_list ap;
	va_start(ap, 1);
	switch (type) {
		case INT:
			new->a = va_arg(ap, int);	break;
		case FLOAT:
			new->b = va_arg(ap, double);	break;
		case BOOL:
			new->c = va_arg(ap, bool);	break;
		case STRING:
			new->d = va_arg(ap, char*);	break;
		default:
			break;
	}
  va_end(ap);
  return new;
}

bool setVisited(struct Node* node) {
	node->visited = true;
	return 1;
}

bool isVisited(struct Node* node) {
	return node->visited;
}

void* nodeGetValue(struct Node* node, int32_t type) {
		if (node == NULL) {
			printf("[Error] Node doesn't exist!\n");
			exit(1);
		}
		void* res;
		switch (type) {
			case INT:
				if (node->type == INT)
					res = InttoVoid(node->a);
				else if (node->type == FLOAT)
					res = InttoVoid((int)node->b);
				else if (node->type == BOOL)
					res = InttoVoid( node->c ? 1 : 0 );
				else {
					res = InttoVoid(0);
				}
				break;
			case FLOAT:
				if (node->type == INT)
					res = FloattoVoid((double)node->a);
				else if (node->type == FLOAT)
					res = FloattoVoid(node->b);
				else if (node->type == BOOL)
					res = FloattoVoid( node->c ? 1 : 0 );
				else {
					res = FloattoVoid(0);
				}
				break;
			case BOOL:
				if (node->type == INT)
					res = BooltoVoid(node->a != 0);
				else if (node->type == FLOAT)
					res = BooltoVoid(node->b != 0);
				else if (node->type == BOOL)
					res = BooltoVoid(node->c);
				else {
					res = BooltoVoid(false);
				}
				break;
			case STRING:
				if (node->type == STRING)
					res = StringtoVoid(node->d);
				else{
					res = StringtoVoid("");
				}
				break;
			default:
				printf("[Error] Edge Value Type Error!\n");
				exit(1);
				break;
		}
		return res;
}

int32_t printNode(struct Node * node) {
	if (node == NULL) {
		printf("(null)\n");
		return 0;
	}
	switch (node->type) {
		case 0:
			printf("node %d\n", node->a);
			break;
		case 1:
			printf("node %f\n", node->b);
			break;
		case 2:
			printf("node %s\n", node->c ? "true" : "false");
			break;
		case 3:
			printf("node %s\n", node->d);
			break;
		default:
			printf("node%3d\n", node->id);
			break;
	}
	return 0;
}

/************************************
	Edge Methods
************************************/

struct Edge createEdge(
	struct Node* sour,
	struct Node* dest,
	int32_t type,
	int32_t a,
	double b,
	bool c,
	char* d
) {
	struct Edge e = {sour, dest, type, a, b, c, d};
	return e;
}

void* edgeGetValue(struct Edge* edge, int32_t type) {
	if (edge == NULL) {
		printf("[Error] Edge doesn't exist!\n");
		exit(1);
	}
	void* res;
	switch (type) {
		case INT:
			if (edge->type == INT)
				res = InttoVoid(edge->a);
			else if (edge->type == FLOAT)
				res = InttoVoid((int)edge->b);
			else if (edge->type == BOOL)
				res = InttoVoid( edge->c ? 1 : 0 );
			else {
				res = InttoVoid(0);
			}
			break;
		case FLOAT:
			if (edge->type == INT)
				res = FloattoVoid((double)edge->a);
			else if (edge->type == FLOAT)
				res = FloattoVoid(edge->b);
			else if (edge->type == BOOL)
				res = FloattoVoid( edge->c ? 1 : 0 );
			else {
				res = FloattoVoid(0);
			}
			break;
		case BOOL:
			if (edge->type == INT)
				res = BooltoVoid(edge->a != 0);
			else if (edge->type == FLOAT)
				res = BooltoVoid(edge->b != 0);
			else if (edge->type == BOOL)
				res = BooltoVoid(edge->c);
			else {
				res = BooltoVoid(false);
			}
			break;
		case STRING:
			if (edge->type == STRING)
				res = StringtoVoid(edge->d);
			else {
				res = StringtoVoid("");
			}
			break;
		default:
			printf("[Error] Edge Value Type Error!\n");
			exit(1);
			break;
	}
	return res;
}

int32_t printEdge(struct Edge * edge) {
	if (edge == NULL) {
		printf("(null)\n");
		return 0;
	}
	switch (edge->type) {
		// case 0:
		// 	printf("edge %3d->%d\n$%3d", edge->sour->id, edge->a, edge->dest->id);
		// 	break;
		// case 1:
		// 	printf("edge %3d->%f\n$%3d", edge->sour->id, edge->b, edge->dest->id);
		// 	break;
		// case 2:
		// 	printf("edge %3d->%s\n$%3d", edge->sour->id, edge->c ? "true" : "false", edge->dest->id);
		// 	break;
		// case 3:
		// 	printf("edge %3d->%s\n$%3d", edge->sour->id, edge->d, edge->dest->id);
		// 	break;
		// default:
		// 	printf("edge %3d->node%3d\n", edge->sour->id, edge->dest->id);
		// 	break;
		case 0:
			printf("edge%d ->%d: %d\n", edge->sour->a, edge->dest->a, edge->a);
			break;
		case 1:
			printf("edge%f ->%f: %d\n", edge->sour->b, edge->dest->b, edge->a);
			break;
		case 2:
			printf("edge%s ->%s: %d\n", edge->sour->c, edge->dest->c, edge->a);
			break;
		case 3:
			printf("edge%s ->%s: %d\n", edge->sour->d, edge->dest->d, edge->a);
			break;
		default:
			printf("edge%3d ->%3d: 0\n", edge->sour->id, edge->dest->id);
			break;
	}
	return 0;
}

int32_t printEdgeValue(struct Edge * edge) {
	if (edge == NULL) {
		printf("(null)\n");
		return 0;
	}
	switch (edge->type) {
		case 0:
			printf("%d\n", edge->a);
			break;
		case 1:
			printf("%f\n", edge->b);
			break;
		case 2:
			printf("%s\n", edge->c ? "true" : "false");
			break;
		case 3:
			printf("%s\n", edge->d);
			break;
		default:
			printf("[Error] Unknown Edge Value Type!\n");
			exit(1);
			break;
	}
	return 0;
}

/************************************
	Graph Methods
************************************/

int32_t graphAddEdgeHelper(struct Graph* g, struct Edge e) {
	if (g == NULL) exit(1);
	int i;
	for (i=0; i < g->en; i++) {
		if (g->edges[i].sour == e.sour && g->edges[i].dest == e.dest) {
			g->edges[i] = e;
			return 0;
		}
	}
	g->edges[i] = e;
	g->en ++;
	return 0;
}

int32_t graphAddEdgeP( struct Graph* g, struct Node* sour, struct Node* dest, int32_t type, ...) {
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	if (sour == dest) return 0;
	if (g->en + 1 >= g->en_len) {
		printf("[Error] # Graph Edges reach the limit!\n");
		exit(1);
	}
	if (graphAddNode(g, sour) > 0) exit(1);
	if (graphAddNode(g, dest) > 0) exit(1);

	// Assign the Edge Value
	struct Edge e = createEdge(sour, dest, type, 0, 0, 0, NULL);
	va_list ap;
	va_start(ap, 1);
	void* tmp = va_arg(ap, void*);
	switch (type) {
		case INT:
			e.a = *((int*)tmp);	break;
		case FLOAT:
			e.b = *((double*)tmp);	break;
		case BOOL:
			e.c = *((bool*)tmp);	break;
		case STRING:
			e.d = ((char*)tmp);	break;
		default:
			break;
	}
  va_end(ap);

	int i;
	// Edges already exist in the graph
	for (i=0; i<g->en; i++) {
		if (g->edges[i].sour == sour && g->edges[i].dest == dest) {
			g->edges[i] = e;
			return 0;
		}
	}
	g->edges[i] = e;
	g->en++;
	return 0;
}

int32_t graphAddEdge(
	struct Graph* g,
	struct Node* sour,
	struct Node* dest,
	int32_t type,
	int32_t a,
	double b,
	bool c,
	char* d
) {
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	if (sour == dest) return 0;
	if (g->en + 1 >= g->en_len) {
		printf("[Error] # Graph Edges reach the limit!\n");
		exit(1);
	}
	if (graphAddNode(g, sour) > 0) exit(1);
	if (graphAddNode(g, dest) > 0) exit(1);
	int i;
	// Edges already exist in the graph
	for (i=0; i<g->en; i++) {
		if (g->edges[i].sour == sour && g->edges[i].dest == dest) {
			g->edges[i].type = type;
			g->edges[i].a = a;
			g->edges[i].b = b;
			g->edges[i].c = c;
			g->edges[i].d = d;
			return 0;
		}
	}
	struct Edge e = createEdge(sour, dest, type, a, b, c, d);
	g->edges[i] = e;
	g->en++;
	return 0;
}

bool graphEdgeExist(struct Graph* g, struct Node* sour, struct Node* dest) {
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	int i;
	for (i=0; i<g->en; i++) {
		if (g->edges[i].sour == sour && g->edges[i].dest == dest) {
			return true;
		}
	}
	return false;
}
struct Edge* graphGetEdge(struct Graph* g, struct Node* sour, struct Node* dest) {
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	int i;
	for (i=0; i<g->en; i++) {
		if (g->edges[i].sour == sour && g->edges[i].dest == dest) {
			return &g->edges[i];
		}
	}
	return NULL;
}

/*
	Split the graph into a list of graphs, in which all graphs are connected.
 */
struct List* splitGraph(struct Graph * gh) {
	struct List* l = createList(GRAPH);
	if (gh == NULL) return l;

	gh = copyGraph(gh);
	struct Node* root = gh->root;
	struct Graph* gh_tmp = NULL;
	int vn = gh->vn, en = gh->en, max_vn = gh->vn, max_en = gh->en;
	int i, j, k;
	struct List* queue = createList(NODE);
	struct Node* node = NULL, *node_tmp = NULL;

	while (vn > 0) {
		gh_tmp = createGraph();
		for (i=0; i<max_vn; i++) {
			if (gh->nodes[i] != NULL) break;
		}
		addList(queue, gh->nodes[i]);
		while (getListSize(queue) > 0) {
			node = (struct Node*) getList(queue, 0);
			removeList(queue, 0);
			graphAddNode(gh_tmp, node);
			for (k=0; k<max_vn; k++) {
				if (gh->nodes[k] == node) {
					gh->nodes[k] = NULL;
					vn--;
					break;
				}
			}
			if (k == max_vn) continue;
			for (j=0; j<max_en; j++) {
				if (gh->edges[j].type != -9 && gh->edges[j].sour == node) {
					node_tmp = gh->edges[j].dest;
				} else if (gh->edges[j].type != -9 && gh->edges[j].dest == node) {
					node_tmp = gh->edges[j].sour;
				} else {
					node_tmp = NULL;
				}
				if (node_tmp == NULL ) continue;
				addList(queue, node_tmp);
				graphAddEdgeHelper(gh_tmp, gh->edges[j]);
				gh->edges[j].type = -9;
			}
		}
		// Adjust the root to the original one
		bool hasRoot = false;
		for (i=0; i<gh_tmp->vn; i++) {
			if (gh_tmp->nodes[i] == root) {
				gh_tmp -> root = root;
				hasRoot = true;
				break;
			}
		}
		// Make sure the subgrpah with original root is the first in the list
		if (hasRoot && getListSize(l) > 0) {
			addList(l, (struct Graph*)getList(l, 0));
			setList(l, 0, gh_tmp);
		} else {
			addList(l, gh_tmp);
		}
	}
	free(gh);
	return l;
}

struct Graph* createGraph() {
	struct Graph* g = (struct Graph*) malloc( sizeof(struct Graph) );
	g->vn = 0;
	g->en = 0;
	g->vn_len = 32;
	g->en_len = 128;
	g->root = NULL;
	g->nodes = (struct Node**) malloc( sizeof(struct Node*) * 16 );
	g->edges = (struct Edge*) malloc( sizeof(struct Edge) * 64 );
	return g;
}
struct Graph* copyGraph(struct Graph* a) {
	if (a == NULL) return NULL;
	struct Graph* g = (struct Graph*) malloc( sizeof(struct Graph) );
	memcpy(g, a, sizeof(struct Graph));
	g->nodes = (struct Node**) malloc( sizeof(struct Node*) * a->vn_len );
	g->edges = (struct Edge*) malloc( sizeof(struct Edge) * a->en_len );
	int i;
	for (i=0; i<a->vn; i++) {
		g->nodes[i] = a->nodes[i];
	}
	struct Edge* tmp;
	for (i=0; i<a->en; i++) {
		tmp = (struct Edge*) malloc( sizeof(struct Edge) );
		memcpy(tmp, &a->edges[i], sizeof(struct Edge));
		g->edges[i] = *tmp;
	}
	return g;
}

struct Graph* mergeGraph(struct Graph* a, struct Graph* b) {
	if (b == NULL) return copyGraph(a);
	if (a == NULL) return copyGraph(b);

	struct Graph* gh = copyGraph(a);
	// Check whether two graph have shared nodes
	int i; int j;
	bool hasShared = false;
	for (i=0; i < a->vn; i++) {
		for (j=0; j < b->vn; j++) {
			if (a->nodes[i] == b->nodes[j]) {
				hasShared = true;
				break;
			}
		}
		if (hasShared) break;
	}
	if (!hasShared) return gh; // Return the copy of graph a

	for (i=0; i< b->vn; i++) {
		graphAddNode(gh, b->nodes[i]);
	}
	for (i=0; i< b->en; i++) {
		graphAddEdgeHelper(gh, b->edges[i]);
	}
	return gh;
}
struct Node* graphGetRoot(struct Graph* g) {
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	return g->root;
}
int32_t graphSetRoot(struct Graph* g, struct Node * root) {
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	if (root == NULL) {
		printf("[Error] Root node doesn't exist!\n");
		exit(1);
	}
	int i;
	for (i=0; i<g->vn; i++) {
		if (g->nodes[i] == root) {
			g->root = root;
			return 0;
		}
	}
	printf("[Error] Root doesn't exist in the graph!\n");
	exit(1);
}

struct List* subGraph(struct Graph* a, struct Graph* b) {
	if (a == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	struct Graph* gh = copyGraph(a);
	if (b == NULL || b->en <= 0) {
		struct List* l = createList(GRAPH);
		addList(l, gh);
		return l;
	}
	int i, j, k;
	for (i = 0; i < b->en; i++) {
		struct Edge e = b->edges[i];
		for (j = 0; j < gh->en; j++) {
			if (gh->edges[j].sour == e.sour && gh->edges[j].dest == e.dest) {
				gh->edges[j] = gh->edges[gh->en-1];
				gh->en --;
				break;
			}
		}
	}
	return splitGraph(gh);
}

int32_t graphAddList(struct Graph* g, int direction, struct List * l, struct List * edges) {
	if (g == NULL || g->root == NULL || l == NULL) {
		printf("[Error] Graph or List doesn't exist!\n");
		exit(1);
	}
	int i, j, lsize = l->curPos, rsize = edges == NULL ? 0 : edges->curPos;
	if (lsize != rsize && rsize > 1) {
		printf("[Error] Edge List Not Compatible with Node/Graph List!\n");
		exit(1);
	}
	for (i=0; i<lsize; i++) {
		struct Node * node = NULL;
		if (l->type == GRAPH) {
			// Merge the graph
			struct Graph * gh_tmp = (struct Graph*)l->arr[i];
			node = gh_tmp->root;
			for (j=0; j< gh_tmp->vn; j++) {
				graphAddNode(g, gh_tmp->nodes[j]);
			}
			for (j=0; j< gh_tmp->en; j++) {
				graphAddEdgeHelper(g, gh_tmp->edges[j]);
			}
		} else if (l->type == NODE) {
			node = (struct Node*)l->arr[i];
		} else {
			printf("[Error] GraphAddList List Type doesn't supported!!\n");
			exit(1);
		}

		if (node == NULL) continue;
		if (edges != NULL && edges->curPos > 0) {
			int edgePos = edges->curPos == 1 ? 0 : i;
			switch (direction) {
				case RIGHT_LINK:
					graphAddEdgeP(g, g->root, node, edges->type, edges->arr[edgePos]); break;
				case LEFT_LINK:
					graphAddEdgeP(g, node, g->root, edges->type, edges->arr[edgePos]); break;
				case DOUBLE_LINK:
					graphAddEdgeP(g, g->root, node, edges->type, edges->arr[edgePos]);
					graphAddEdgeP(g, node, g->root, edges->type, edges->arr[edgePos]);
					break;
				default:
					break;
			}
		} else {
			switch (direction) {
				case RIGHT_LINK:
					graphAddEdgeP(g, g->root, node, -1, NULL); break;
				case LEFT_LINK:
					graphAddEdgeP(g, node, g->root, -1, NULL); break;
				case DOUBLE_LINK:
					graphAddEdgeP(g, g->root, node, -1, NULL);
					graphAddEdgeP(g, node, g->root, -1, NULL);
					break;
				default:
					break;
			}
		}
	}
	return 0;
}

int32_t graphAddNode(struct Graph* g, struct Node * node) {
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	if (g->vn + 1 >= g->vn_len) {
		printf("[Warning] # Graph Nodes reach the limit!\n");
		exit(1);
	}
	int i;
	// Nodes already exist in the graph
	for (i=0; i<g->vn; i++) {
		if (g->nodes[i] == node) return 0;
	}
	// Update the root if the graph is empty
	if (g->root == NULL) {
		g->root = node;
	}
	g->nodes[i] = node;
	g->vn++;
	return 0;
}

struct List* graphRemoveNode(struct Graph* gh, struct Node * node) {
	if (gh == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	gh = copyGraph(gh);
	int i, j;
	// Remove Node
	for (i=0; i<gh->vn; i++) {
		if (gh->nodes[i] == node) {
			for (j=i; j<gh->vn-1; j++) {
				gh->nodes[j] = gh->nodes[j+1];
			}
			gh->nodes[j] = NULL;
			gh->vn--;
		}
	}
	if (gh->root == node) {
		gh->root = gh->vn == 0 ? NULL : gh->nodes[0];
	}
	// Remove Edges
	for (i=0, j=gh->en-1; i<=j;) {
		if (gh->edges[i].sour == node || gh->edges[i].dest == node) {
			gh->edges[i] = gh->edges[j];
			gh->en--;
			j--;
		} else {
			i++;
		}
	}
	return splitGraph(gh);
}

struct List* graphGetAllNodes(struct Graph* g) {
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	struct List* ret = createList(NODE);
	int i;
	for (i=0; i < g->vn; i++) {
		addList(ret, g->nodes[i]);
	}
	return ret;
}

int32_t graphNumOfNodes(struct Graph* g) {
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	return g->vn;
}

int32_t graphNumOfEdges(struct Graph* g) {
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	return g->en;
}

struct List* graphGetChildNodes(struct Graph* g, struct Node* rt) {
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	struct List* children = createList(NODE);
	if (rt == NULL) return children;
	int i;
	for (i=0; i< g->en; i++) {
		if (g->edges[i].sour == rt) {
			addList(children, g->edges[i].dest);
		}
	}
	return children;
}

bool containsNode(struct Graph* g, struct Node* n) {
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	int i;
	for (i = 0; i < g->vn; i++) {
		if (g->nodes[i] == n) {
			return true;
		}
	}
	return false;
}

int32_t printGraph(struct Graph* g) {
	if (g == NULL) {
		printf("(null)\n");
		return 0;
	}
	printf("--------------------------------------\n");
	// printf("#Nodes: %d  ", g->vn);
	// if (g->root != NULL) {
	// 	printf("Root Node: %d\n", g->root->id);
	// } else {
	// 	printf("\n");
	// }
	printf("Nodes:\n");
	int i;
	for (i=0; i<g->vn; i++) {
		printNode(g->nodes[i]);
	}
	// printf("#Edges: %d\n", g->en);
	printf("\n");
	printf("Edges:\n");
	for (i=0; i<g->en; i++) {
		printEdge(&g->edges[i]);
	}
	printf("--------------------------------------\n");
	return 0;
}

bool setAllUnvisited(struct Graph* g) {
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		exit(1);
	}
	int i;
	for (i = 0; i < g->vn; i++) {
		g->nodes[i]->visited = false;
	}
	return true;
}


bool dfs(struct Graph* g, struct Node* n) {
	bool flag = true;
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		return false;
	} else if (!containsNode(g, n)) {
		printf("[Error] Graph doesn't contain source node!\n");
		return false;
	} else {
		printf("-------------------------- DFS BEGIN -------------------------\n");
		setAllUnvisited(g);
		struct List* lst = createList(NODE);
		addList(lst, n);
		while (getListSize(lst) != 0) {
			struct Node* tmp = (struct Node*) popList(lst);
			if (tmp->visited == true) {
				flag = false;
				continue;
			} else {
				tmp->visited = true;
				printNode(tmp);
				struct List* childs = graphGetChildNodes(g, tmp);
				lst = concatList(lst, childs);
			}
		}
		printf("-------------------------- DFS END -------------------------\n");
	}
	if (!flag) {
		printf("graph has cycle in it\n");
	}
	return flag;
}

bool bfs(struct Graph* g, struct Node* n) {
	bool flag = true;
	if (g == NULL) {
		printf("[Error] Graph doesn't exist!\n");
		return false;
	} else if (!containsNode(g, n)) {
		printf("[Error] Graph doesn't contain source node!\n");
		return false;
	} else {
		printf("-------------------------- BFS BEGIN -------------------------\n");
		setAllUnvisited(g);
		struct Queue* q = createQueue(NODE);
		pushBack(q, n);
		while (getQueueSize(q) != 0) {
			struct Node* tmp = (struct Node*) popFront(q);
			if (tmp->visited) {
				flag = false;
				continue;
			} else {
				tmp->visited = true;
				printNode(tmp);
				struct List* childs = graphGetChildNodes(g, tmp);
				concatList(q->lst, childs);
			}
		}
		printf("-------------------------- BFS END -------------------------\n");
	}
	if (!flag) {
		printf("graph has cycle in it\n");
	}
	return flag;
}

// int main() {
// 	struct Queue* q = createQueue(INT);
// 	pushBack(q, 1);
// 	pushBack(q, 2);
// 	pushBack(q, 3);
// 	printQueue(q);
// 	popFront(q);
// 	printQueue(q);
// 	popFront(q);
// 	printQueue(q);
// 	pushBack(q, 4);
// 	printQueue(q);
// }

//test list
// int main() {
	// test list
	// struct List* list = createList(1);
	// printf("list type:%d\n", list->type);
	// struct List* newList = addList(addList(addList(addList(list, 52), 53), 54), 55);
	// printList(list);

	// struct Node* a = createNode(1, 0, 12, 0, 0, NULL);
	// struct Node* b = createNode(2, 1, 0, 1.2, 0, NULL);
	// struct Node* c = createNode(3, 2, 0, 0, 0, NULL);
	// struct Node* d = createNode(4, 3, 0, 0, 1, "Hello World!");
	// struct Graph* g = createGraph();
	// graphAddNode(g, a);
	// graphAddNode(g, b);
	// graphAddNode(g, c);
	// graphAddNode(g, d);
	// graphAddEdge(g, a, b, 3,0,0,0,"Edge1");
	// graphAddEdge(g, b, c, 2,0,0,1,NULL);

	// struct Graph* g2 = copyGraph(g);
	// g->edges[0].d = "ffff";
	// d->d = "????";
	// graphAddEdge(g2, c, d, 1,0,3.3,0,NULL);

	// printGraph(g);
	// printf("****************************\n");
	// printGraph(g2);

	// void * ptr = "xxx";
	// printf("%s\n", get_str_from_void_ptr(ptr));
	// exit(1);
// }



// below is the test for dict

// #include <stdlib.h>
// #include <stdio.h>
// #include <assert.h>

// #include "hashmap.h"

// #define KEY_MAX_LENGTH (256)
// #define KEY_PREFIX ("somekey")
// #define KEY_COUNT (1024*1024)

// typedef struct data_struct_s
// {
//     char key_string[KEY_MAX_LENGTH];
//     int number;
// } data_struct_t;


// int main()
// {
//     int index;
//     int error;
//     map_t mymap;
//     char key_string[KEY_MAX_LENGTH];
//     data_struct_t* value;

//     mymap = hashmap_new();

//     /* First, populate the hash map with ascending values */
//     /* Store the key string along side the numerical value so we can free it later */
//     value = malloc(sizeof(data_struct_t));
//     value->number = 1;
//     strcpy(value->key_string, "Warrior");
//     printf("%s\n", value->key_string);
//     hashmap_put(mymap, value->key_string, value);
//     data_struct_t* tmp = malloc(sizeof(data_struct_t));
//     int a = hashmap_get(mymap, value->key_string, (void**)(&tmp));
//     printf("%s:%d", tmp->key_string, tmp->number);
//     // error = hashmap_remove(mymap, key_string);
//     /* Now, destroy the map */
//     hashmap_free(mymap);

//     exit(1);
// }


// 	struct List* list = createList(1);
// 	printf("list type:%d\n", list->type);
// 	struct List* newList = addList(addList(addList(addList(list, 52), 53), 54), 55);
// 	printList(list);
// }

// test graph
// int main() {
// 	struct Node* a = createNode(1, 3, "a");
// 	struct Node* b = createNode(2, 3, "b");
// 	struct Node* c = createNode(3, 3, "c");
// 	struct Node* d = createNode(4, 3, "d");
//
// 	struct Graph* g = createGraph();
// 	graphAddNode(g, a);
// 	graphAddNode(g, b);
// 	graphAddNode(g, c);
// 	graphAddNode(g, d);
// 	graphAddEdgeP(g, a, b, STRING, "a->b");
// 	graphAddEdgeP(g, a, c, STRING, "a->c");
// 	graphAddEdgeP(g, a, d, STRING, "a->d");
// 	graphAddEdgeP(g, c, d, STRING, "c->d");
//
//
// 	struct Graph* g1 = createGraph();
// 	graphAddNode(g1, a);
// 	graphAddNode(g1, b);
// 	graphAddNode(g1, c);
// 	graphAddNode(g1, d);
// 	// graphAddEdgeP(g1, a, b, STRING, "a->b");
// 	graphAddEdgeP(g1, a, c, STRING, "a->c");
// 	// graphAddEdgeP(g1, a, d, STRING, "a->d");
// 	graphAddEdgeP(g1, c, d, STRING, "c->d");
//
//  	struct List* l = subGraph(g, g1);
//
//
// 	printf("The list size is: %d\n", getListSize(l));
// 	int i;
// 	for (i=getListSize(l)-1; i>=0; i-- ) {
// 		printf("===============================\n");
// 		printGraph( getList(l, i) );
// 		printf("===============================\n");
// 	}
// }


// int main() {
// 	printf("%f", (float)1 );
// }
