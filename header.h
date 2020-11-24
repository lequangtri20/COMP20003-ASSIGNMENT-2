/*							COMP20003 ASSIGNMENT 2

*	Program written by Quang Tri Le/ Student ID: 1118563.


=============================GENERAL HEADER FILE==============================*/

#ifndef HEADER_H
#define HEADER_H


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "data.h"
#include "list.h"
#include "kd.h"


#define LINE_MAX_LENGTH 512
#define FIELD_MAX_LENGTH 128
#define MAXDIST 99999999

/*Reading business record*/
int record_business(FILE* fin,list_t* business_record); 
void add_to_dictionary(int field_no, node_t *business_node);
data_t* record_to_struct(int field_no, char* field_value, data_t* data);


#endif //HEADER_H