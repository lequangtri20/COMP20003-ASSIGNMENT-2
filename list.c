/*							COMP20003 ASSIGNMENT 2

*	Program written by Quang Tri Le/ Student ID: 1118563.

=============================LINKED LIST OPERATION============================*/

#include "header.h"

/*
	Three functions: "make_empty_list", "insert_at_foot" and "free_list" were
	originally written by Alistair Moffat, as  examples for the book
    "Programming, Problem Solving, and Abstraction with C", Pearson
    Custom Books, Sydney, Australia, 2002; revised edition 2012,
    ISBN 9781486010974.

	Modified and adapted by Quang Tri Le.
 */

/* The function below initializes business record with a linked list */
list_t *make_empty_list(void) {
	list_t *list;
	list = (list_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	return list;
}

/* insert_at_foot() is capable of inserting (or append) new node at the end of
the list */
list_t *insert_at_foot(list_t *list, data_t *value) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->data = *value;
	new->next = NULL;
	if (list->foot==NULL) {
		/* this is the first insertion into the list */
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}

/* free_list will free the memory of the business record at the end */
void free_list(list_t *list) {
	node_t *current, *previous;
	assert(list!=NULL);
	current = list->head;
	while (current) {
		previous = current;
		current = current->next;
		free_data(previous);
		free(previous);
	}
	free(list);
}


/* Function below will further free the memory in each data field of each
business to avoid memory leak.
Written by Quang Tri Le */
void free_data(node_t *business_node){
	free(business_node->data.census_year);
	free(business_node->data.block_id);
	free(business_node->data.prop_id);
	free(business_node->data.base_prop_id);
	free(business_node->data.area_name);
	free(business_node->data.trade_name);
	free(business_node->data.industry_code);
	free(business_node->data.industry_des);
	free(business_node->data.x_coor);
	free(business_node->data.y_coor);
	free(business_node->data.location);

}