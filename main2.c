/*							COMP20003 ASSIGNMENT 2

*	Program written by Quang Tri Le/ Student ID: 1118563.

*	To run the program:
*		1. Type "make" in Terminal.
*		2. Type "./map2 input_file output_file < key_file" into the terminal
* 		(names of 3 files are flexible depending on command line arguments).

===========================MAIN FUNCTION FOR MAP2=============================*/

#include "header.h"

int main(int argc, char **argv){
	int num_record; /* optional use */

	/*Initialize a business record containing information of all business under
	form of a linked list*/
	node_t * current_node;
	list_t* business_record = make_empty_list();

	/* Initialize kd tree */
	tree_t* kd_tree = make_empty_tree();

	/*Open input file for data recording */
	FILE *fin;
	if ((fin = fopen(argv[1],"r")) == NULL){
		printf("Error opening input file\n");
		exit(0);
	}

	/*Record all business data from input file to linked list business_record */
	num_record = record_business(fin, business_record);

	/*Insert in order from linked list business_record to the tree */
	kd_tree = insert_in_order(kd_tree, business_record);

	/*Open ouput file for saving records */
	FILE *fout;
	if ((fout = fopen(argv[2], "w"))==NULL){
		printf("Error opening output file\n");
		exit(0);
	}

	/* Read query and find the point within given radius of query point */
	read_query_2(fout, kd_tree);

	/*Close all files used*/
	fclose(fin);
	fclose(fout);

	/*Freeing memories for the business record */
	recursive_free_tree(kd_tree->root);
	free(kd_tree);
	kd_tree = NULL;
	free_list(business_record);
	business_record = NULL;

	return 0;

}
