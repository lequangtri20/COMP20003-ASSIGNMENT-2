/*							COMP20003 ASSIGNMENT 2

*	Program written by Quang Tri Le/ Student ID: 1118563.


=================================LINKED LIST==================================*/
#ifndef LIST_H
#define LIST_H
#include "data.h"

typedef struct node node_t;

struct node {
	data_t data;
	node_t *next;
};

/*Define linked list*/
typedef struct {
	node_t *head;
	node_t *foot;
} list_t;


list_t *make_empty_list(void);
void free_list(list_t *list);
list_t *insert_at_foot(list_t *list, data_t* value);
void free_data(node_t *business_node);

#endif //LIST_H