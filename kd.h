/*							COMP20003 ASSIGNMENT 2

*	Program written by Quang Tri Le/ Student ID: 1118563.


==================================KD TREE=====================================*/

#ifndef KD_H
#define KD_H

#include "data.h"
#include "list.h"

/* Make type key for easier comparison */
typedef struct {
	double x;
	double y;
} keyc_t;


/* Node in kd tree */
typedef struct node_tree node_tree_t;

struct node_tree {
	keyc_t key;
	int depth;

	data_t* data; /* Pointing to the data of the node in linked list */
	node_tree_t* right;
	node_tree_t* left;
	node_tree_t* next_duplicate;
};

/* Kd tree */
typedef struct {
	node_tree_t* root;
} tree_t;


/* Function prototypes */

tree_t* make_empty_tree(void);
tree_t* insert_in_order(tree_t *tree, list_t* business_record);
node_tree_t* insert_to_tree(node_tree_t *root, node_tree_t *new);

/* Stage 1 functions */
int read_query(FILE* fout, tree_t* tree);
void nearest_location(node_tree_t** node_traverse, node_tree_t* nearest_yet,
double *min_dist, keyc_t key_query, int* count);


/* Stage 2 functions */
int read_query_2(FILE* fout, tree_t* tree);
void within_radius(node_tree_t** node_traverse, double radius, keyc_t key_query,
int* count, int* found, FILE* fout, char* key_to_print);

void print_to_output(node_tree_t* node_to_print,FILE* fout ,char* key_to_print);
void recursive_free_tree(node_tree_t *root);
double distance (keyc_t key_query, keyc_t node_tree);
void free_dup(node_tree_t *root); /*freeing linked list of duplicates */
int compare_two_doubles(double new_node_coor, double current_node_coor);

#endif //KD_H