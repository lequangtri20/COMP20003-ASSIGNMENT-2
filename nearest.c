/*							COMP20003 ASSIGNMENT 2

*	Program written by Quang Tri Le/ Student ID: 1118563.

=========================FIND NEAREST POINT TO QUERY==========================*/

#include "header.h"

/*Function below is used to read keys from query file and find for its nearest
point */
int read_query(FILE* fout, tree_t* tree){
	char key[FIELD_MAX_LENGTH + 1]; /* Store key to categorize data field */
	char key_to_print[FIELD_MAX_LENGTH + 1]; /* Store key to print to output */
	char c;
	char deli[2] = " ";
	char *token; 
	int i = 0;
	int *count = (int*)malloc(sizeof(int)); /* store number of comparison */
	assert(count);

	double *min_dist = (double*)malloc(sizeof(double)); /* store min distance */
	assert(min_dist);

	keyc_t key_query; /* store coordinates of query */
	node_tree_t** node_traverse = &(tree->root);
	node_tree_t* nearest;
	
	while(1){
		if (scanf("%c",&c) == EOF){
			/*Last line of queryfile */
			nearest = (node_tree_t*)malloc(sizeof(node_tree_t));
			assert(nearest);
			*count = 0;
			*min_dist = MAXDIST;
			node_traverse = &(tree->root);
				
			key[i] = '\0';
			key_to_print[i] = '\0';


			if (key[0] == '\0'){
				free(nearest);
				break;
			}
			
			token = strtok(key, deli);
			key_query.x = atof(token);
			token = strtok(NULL, deli);
			key_query.y = atof(token);
			

			/* Find the closest location */
			nearest_location(node_traverse, nearest, min_dist, key_query,count);
			/* Print result to output file and stdout */
			printf("%s --> %d\n", key_to_print,*count);
			print_to_output(nearest, fout, key_to_print);

			free(nearest);
			break;
		}

		else if (c == '\n'){
			/*End of each line in queryfile */
			nearest = (node_tree_t*)malloc(sizeof(node_tree_t));
			assert(nearest);
			*count = 0;
			*min_dist = MAXDIST;
			node_traverse = &(tree->root);
			
			key[i] = '\0';
			key_to_print[i] = '\0';
			i = 0;

			token = strtok(key, deli);
			key_query.x = atof(token);
			token = strtok(NULL, deli);
			key_query.y = atof(token);

			/* Find the closest location */
			nearest_location(node_traverse, nearest, min_dist, key_query,count);
			/* Print result to output file and stdout */
			printf("%s --> %d\n", key_to_print,*count);
			print_to_output(nearest, fout, key_to_print);
			fprintf(fout,"\n");

			free(nearest);
			
			continue;
		}
		else if (c == '\r'){
			continue;
		}

		key[i] = c;
		key_to_print[i] = c;
		i += 1;

	}
	free(min_dist);
	free(count);
	return 0;
}

/* Recursive function to find for nearest point to query */
void nearest_location(node_tree_t** node_traverse, node_tree_t* nearest_yet,
 double* min_dist, keyc_t key_query, int*count){

	/* Base case */
	if (!(*node_traverse)){
		return;
	}

	*count += 1;
	/* Current found distance <= tracking min distance */
	if (compare_two_doubles((*min_dist), distance(key_query,
	 (*node_traverse)->key)) <= 0) {

		*min_dist = distance(key_query, (*node_traverse)->key);
		*nearest_yet = **node_traverse;
	}

	/* Compare x dimension */
	if ((*node_traverse)->depth % 2 == 0){
		/* Proceed to more likely branch of having closer point first */
		if (compare_two_doubles((*node_traverse)->key.x,key_query.x) < 0) {
			nearest_location(&((*node_traverse)->left), nearest_yet,
			 min_dist, key_query, count);
			if (compare_two_doubles(*min_dist,fabs((*node_traverse)->key.x - 
				key_query.x)) < 0)
				nearest_location(&((*node_traverse)->right), nearest_yet,
				 min_dist, key_query, count);		
		}
		

		else{
			nearest_location(&((*node_traverse)->right), nearest_yet,
			 min_dist, key_query, count);
			if (compare_two_doubles(*min_dist,fabs((*node_traverse)->key.x - 
				key_query.x)) < 0)
				nearest_location(&((*node_traverse)->left), nearest_yet,
			 	min_dist, key_query, count);
		}
	}

	/* Compare y dimension */
	else{
		/* Proceed to more likely branch of having closer point first */ 
		if (compare_two_doubles((*node_traverse)->key.y,key_query.y) < 0) {
			nearest_location(&((*node_traverse)->left), nearest_yet,
			 min_dist, key_query, count);
			if (compare_two_doubles(*min_dist,fabs((*node_traverse)->key.y -
			key_query.y)) < 0)
				nearest_location(&((*node_traverse)->right), nearest_yet,
			 	min_dist, key_query, count);
		}
		else{
			nearest_location(&((*node_traverse)->right), nearest_yet,
			 min_dist, key_query, count);
			if (compare_two_doubles(*min_dist,fabs((*node_traverse)->key.y - 
				key_query.y)) < 0)
				nearest_location(&((*node_traverse)->left), nearest_yet,
			 	min_dist, key_query, count);
		}		
	}

	return;
}

