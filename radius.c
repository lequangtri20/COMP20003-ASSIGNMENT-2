/*							COMP20003 ASSIGNMENT 2

*	Program written by Quang Tri Le/ Student ID: 1118563.

===================FIND ALL POINTS WITHIN RADIUS OF QUERY=====================*/

#include "header.h"

/*Function below is used to read keys from query file and find all points within
radius of query */
int read_query_2(FILE* fout, tree_t* tree){
	char key[FIELD_MAX_LENGTH + 1];	/* Store key to categorize data field */
	char key_to_print[FIELD_MAX_LENGTH + 1]; /* Store key to print to output */
	char c;
	char deli[2] = " ";
	char *token;
	int i = 0;
	int *count = (int*)malloc(sizeof(int));
	assert(count);

	int *found = (int*)malloc(sizeof(int));	/* toggle tells if point found in
	radius */
	assert(found);

	double radius;
	keyc_t key_query;

	node_tree_t** node_traverse = &(tree->root);
	while(1){
		if (scanf("%c",&c) == EOF){
			/*Last line of keyfile */
			*count = 0;
			*found = 0;
			node_traverse = &(tree->root);
				
			key[i] = '\0';
			key_to_print[i] = '\0';


			if (key[0] == '\0'){
				break;
			}
		
			/* Record coordinates and radius */
			token = strtok(key, deli);
			key_query.x = atof(token);
			token = strtok(NULL, deli);
			key_query.y = atof(token);
			token = strtok(NULL, deli);
			radius = atof(token);

			/* Find all point within radius of query */
			within_radius(node_traverse,radius ,key_query, count, found, fout,
				key_to_print);

			/* Print NOTFOUND result to output file */
			if (*found ==0)
				fprintf(fout, "%s --> NOTFOUND\n", key_to_print);

			/* Print count to stdout */
			printf("%s --> %d\n", key_to_print,*count);

			break;
		}

		else if (c == '\n'){
			/*End of each line in keyfile */
			*count = 0;
			*found = 0;

			node_traverse = &(tree->root);
			key[i] = '\0';
			key_to_print[i] = '\0';
			i = 0;

			/* Record coordinates */
			token = strtok(key, deli);
			key_query.x = atof(token);
			token = strtok(NULL, deli);
			key_query.y = atof(token);
			token = strtok(NULL, deli);
			radius = atof(token);
			

			/* Find all point within radius of query */
			within_radius(node_traverse, radius , key_query,count, found, fout,
				key_to_print); 

			/* Print NOTFOUND result to output file */
			if (*found ==0)
				fprintf(fout, "%s --> NOTFOUND\n", key_to_print);

			fprintf(fout,"\n");

			/* Print count to stdout */
			printf("%s --> %d\n", key_to_print, *count);

			continue;
		}

		else if (c == '\r'){
			continue;
		}

		key[i] = c;
		key_to_print[i] = c;
		i += 1;

	}
	free(count);
	free(found);
	return 0;
}


/* Recursive function to find all points within radius of query */
void within_radius(node_tree_t** node_traverse, double radius,
 keyc_t key_query, int* count, int* found, FILE* fout, char* key_to_print){
 	
	node_tree_t* node_print;

	if (!(*node_traverse)){
		return;
	}

	*count += 1;

	/* Print the found node to out put if it's within radius of query point */
	if (compare_two_doubles(radius, distance(key_query,
	 (*node_traverse)->key)) <= 0) {
		*found = 1;
		node_print = malloc(sizeof(node_tree_t));
		*node_print = **node_traverse;
		print_to_output(node_print, fout, key_to_print);
		free(node_print);
	}

	/* Compare x dimension */
	if ((*node_traverse)->depth % 2 == 0){
		/* Proceed to more likely branch of having point within radius first */
		if (compare_two_doubles((*node_traverse)->key.x,key_query.x) < 0){
			within_radius(&((*node_traverse)->left), radius, key_query,
			 count, found,fout, key_to_print);
			if (compare_two_doubles(radius,fabs((*node_traverse)->key.x - 
			key_query.x)) < 0)
				within_radius(&((*node_traverse)->right), radius, key_query,
			 	count, found, fout, key_to_print);
		}

		else{
			within_radius(&((*node_traverse)->right), radius, key_query,
			 count, found,fout, key_to_print);
			if (compare_two_doubles(radius,fabs((*node_traverse)->key.x - 
			key_query.x)) < 0)
				within_radius(&((*node_traverse)->left), radius, key_query,
			 	count, found, fout, key_to_print);
		}

	}

	/* Compare y dimension */
	else{
		/* Proceed to more likely branch of having point within radius first */
		if (compare_two_doubles((*node_traverse)->key.y,key_query.y) < 0){
			within_radius(&((*node_traverse)->left), radius, key_query,
			 count,found,fout, key_to_print);
			if (compare_two_doubles(radius,fabs((*node_traverse)->key.y - 
			key_query.y)) < 0)
				within_radius(&((*node_traverse)->right), radius, key_query,
			 	count, found, fout, key_to_print);
		}

		else{
			within_radius(&((*node_traverse)->right), radius, key_query,
			 count, found, fout, key_to_print);
			if (compare_two_doubles(radius,fabs((*node_traverse)->key.y - 
			key_query.y)) < 0)
				within_radius(&((*node_traverse)->left), radius, key_query,
			 	count, found, fout, key_to_print);
		}	
	}
	return;
}



