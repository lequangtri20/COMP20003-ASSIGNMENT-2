/*							COMP20003 ASSIGNMENT 2 

*	Program written by Quang Tri Le/ Student ID: 1118563.

==============================K-D TREE OPERATIONS=============================*/
#include "header.h"

tree_t *make_empty_tree(void) {
	tree_t* kd_tree;
	kd_tree = (tree_t*)malloc(sizeof(*kd_tree));
	assert(kd_tree!=NULL);
	kd_tree->root = NULL;
	return kd_tree;
}

/* Loop through linked list to perform inserting points to the tree */
tree_t* insert_in_order(tree_t *tree, list_t* business_record){
	int loop_count = 0;
	node_t* current_list_node = business_record->head;
	node_tree_t* new_node = (node_tree_t*)malloc(sizeof(node_tree_t));
	assert(new_node);

	while (current_list_node){
 		new_node->key.x = atof(current_list_node->data.x_coor);
 		new_node->key.y = atof(current_list_node->data.y_coor);
 		
 		/* Nodes in tree have data pointer pointing straight to data of node in
 		linked list */
 		new_node->data = &(current_list_node->data);
 		new_node->right = NULL;
 		new_node->left = NULL;
 		new_node->next_duplicate = NULL;

		tree->root = insert_to_tree(tree->root, new_node);
		current_list_node = current_list_node->next;
	}
	free(new_node);
	return tree;
}

/* Find and insert point to correct position of the tree */
node_tree_t* insert_to_tree(node_tree_t *root, node_tree_t *new){
	node_tree_t** insert_location = &root; /* used to find suitable position
	for new node */
	int depth = 0;

	while (*insert_location){
		/* Check if the two keys are the same (compare both x and y). If it is
		insert it to the linked list */
		
		if (!compare_two_doubles((*insert_location)->key.x, new->key.x)
		 && !compare_two_doubles((*insert_location)->key.y, new->key.y)){

			while (*insert_location){
				insert_location = &((*insert_location)->next_duplicate);
			}

			*insert_location = (node_tree_t*)malloc(sizeof(node_tree_t));
			assert(*insert_location);
			(*insert_location)->right = NULL;
    		(*insert_location)->left = NULL;
    		(*insert_location)->next_duplicate = NULL;
    		(*insert_location)->data = new->data;
    		(*insert_location)->depth = depth;
    		(*insert_location)->key.x = new->key.x;
    		(*insert_location)->key.y = new->key.y;
			return root;
		}

		/* Comparing x only based on depth */
		if ((depth % 2) == 0){

			if (compare_two_doubles((*insert_location)->key.x,
			 new->key.x) < 0){
			
				insert_location = &((*insert_location)->left);
			}

			else if (compare_two_doubles((*insert_location)->key.x,
			 new->key.x) >= 0){

				insert_location = &((*insert_location)->right);
			}
					
		}

		/* Comparing y only based on depth */
		else if ((depth % 2) == 1){

			if (compare_two_doubles((*insert_location)->key.y,
			 new->key.y) < 0){
			
				insert_location = &((*insert_location)->left);
			}

			else if (compare_two_doubles((*insert_location)->key.y,
			 new->key.y) >= 0){

				insert_location = &((*insert_location)->right);
			}
			
		}
		depth += 1;
		
	}

    *insert_location = (node_tree_t*)malloc(sizeof(node_tree_t));
    assert(*insert_location);
    (*insert_location)->right = NULL;
    (*insert_location)->left = NULL;
    (*insert_location)->next_duplicate = NULL;
    (*insert_location)->data = new->data;
    (*insert_location)->depth = depth;
    (*insert_location)->key.x = new->key.x;
    (*insert_location)->key.y = new->key.y;
	return root;
}

/* Printing information to output file for nearest.c*/
void print_to_output(node_tree_t* node_to_print,FILE* fout, char* key_to_print){

	while (node_to_print){
		fprintf(fout,"%s --> Census year: %s || Block ID: %s || "
		"Property ID: %s || Base property ID: %s || CLUE small area: %s || "
		"Trading Name: %s ||Industry (ANZSIC4) code: %s || Industry "
		"(ANZSIC4) description: %s || x coordinate: %s || y coordinate: %s ||"
		" Location: %s ||\n", key_to_print, node_to_print->data->census_year,
		 		node_to_print->data->block_id, node_to_print->data->prop_id,
		 		node_to_print->data->base_prop_id,node_to_print->data->area_name
		 		, node_to_print->data->trade_name,
		 		node_to_print->data->industry_code,
		 		 node_to_print->data->industry_des,
		 		node_to_print->data->x_coor,
		 		 node_to_print->data->y_coor,
		 		node_to_print->data->location);

		node_to_print = node_to_print->next_duplicate;
	}
}


/* Function below calculated Euclidean distance */
double distance (keyc_t key_query, keyc_t node_tree){
	return sqrt(pow((key_query.x -node_tree.x),2) + pow((key_query.y -
	 node_tree.y),2));
}

int compare_two_doubles(double current_node_coor, double new_node_coor){
	double epsilon = 0.0000001; //1e-7

	if (new_node_coor < current_node_coor){
		return -1;
	}
	else if (new_node_coor > current_node_coor){
		return 1;
	}
	else if (fabs(new_node_coor - current_node_coor) <= epsilon){
		return 0;
	}
	return 2; /* Not gonna happen but it's there for completion */
}


void recursive_free_tree(node_tree_t *root) {
	if(!root){
		return;
	}

	recursive_free_tree(root->left);
	recursive_free_tree(root->right);
    if (root->next_duplicate)
        free_dup(root);
    if (root)
        free(root);
}


/* Free linked list of same coordinates point */
void free_dup(node_tree_t *root) {
	node_tree_t *curr, *prev;
	curr = root->next_duplicate;
	while (curr) {
		prev = curr;
		curr = curr->next_duplicate;
		free(prev);
	}
}