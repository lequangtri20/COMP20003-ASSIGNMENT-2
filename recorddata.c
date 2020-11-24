/*							COMP20003 ASSIGNMENT 2 

*	Program written by Quang Tri Le/ Student ID: 1118563.

=================================DATA RECORDING===============================*/

#include "header.h"

/*Function below is used to parse csv file and record data to business record */
int record_business(FILE* fin, list_t* business_record){
	char str[LINE_MAX_LENGTH + 1];
	char field_value[FIELD_MAX_LENGTH + 1]; /* Buffer for each data field */

	int no_input = 0, field_value_index = 0, i = 0, field_order = 0;
    int inside_quotes = 0; /* Check whether in quotes or not */
    
    data_t* data;	/* struct storing data while reading input */
    data = (data_t*)malloc(sizeof(*data));
    assert(data);

	fgets(str, sizeof(str), fin); /*Take the header of input file away*/

	while (fgets(str, sizeof(str), fin) != NULL){
		field_order = 0;
		no_input += 1;
		field_value_index = 0;
		i = 0;

	    while ((str[i] != '\0') ||((str[i] == '\0') && (str[i-1] != '\n'))) {
	    	/*Above condition allows to recognize the end of each line,
	    	including the last line which does not have end of line character */
	    	field_value[field_value_index] = str[i];
	    	field_value_index += 1;	    	

	    	if ((inside_quotes == 0) && (str[i] == ',' || str[i] == '\n' ||
	    		str[i] == '\r')){
	    		/*This condition signals the end of each data field by 
	    		recognizing comma delimiter or end of line */
	            field_value[field_value_index-1] = 0;
	            field_value_index = 0;
	            
	            /*field_value is recorded to data */
	            data = record_to_struct(field_order, field_value, data); 
	            field_order += 1;

	            if (field_order == 11){
	            	/*All data field of each line is recorded, let's insert them
	            	to business record */
	            	insert_at_foot(business_record, data);	
	            	break;
	            }

	            if (str[i] == '\n')
	            	field_order = 0;
	    	}

	    	if (str[i] == '"' && str[i+1] != '"'){
	    		/*Double quotes handling */
	    		field_value_index -= 1;
	    		inside_quotes = !inside_quotes;
	    	}

	        if (str[i] == '"' && str[i + 1] == '"'){
	        	/*Consecutive double quotes handling */
	            i += 1;
	        }
	        i +=1 ;
	    }
	}

	free(data);

	return no_input;	
}


/*Function below is used to assign each data field value (based on order of each
data field) to data (which is later copied to business record)*/
data_t* record_to_struct(int field_order, char* field_value, data_t* data){
	if (field_order == 0){
		data->census_year = (char*)malloc(sizeof(char)*strlen(field_value)+1);
		assert(data->census_year);
		strcpy(data->census_year, field_value);
	}

	if (field_order == 1){
		data->block_id = (char*)malloc(sizeof(char)*strlen(field_value)+1);
		assert(data->block_id);
		strcpy(data->block_id, field_value);
	}

	if (field_order == 2){
		data->prop_id = (char*)malloc(sizeof(char)*strlen(field_value)+1);
		assert(data->prop_id);
		strcpy(data->prop_id, field_value);
	}	

	if (field_order == 3){
		data->base_prop_id = (char*)malloc(sizeof(char)*strlen(field_value)+1);
		assert(data->base_prop_id);
		strcpy(data->base_prop_id, field_value);

	}
	if (field_order == 4){
		data->area_name = (char*)malloc(sizeof(char)*strlen(field_value)+1);
		assert(data->area_name);
		strcpy(data->area_name, field_value);
	}

	if (field_order == 5){
		data->trade_name = (char*)malloc(sizeof(char)*strlen(field_value)+1);
		assert(data->trade_name);
		strcpy(data->trade_name, field_value);
	}

	if (field_order == 6){
		data->industry_code = (char*)malloc(sizeof(char)*strlen(field_value)+1);
		assert(data->industry_code);
		strcpy(data->industry_code, field_value);
	}

	if (field_order == 7){
		data->industry_des = (char*)malloc(sizeof(char)*strlen(field_value)+1);
		assert(data->industry_des);
		strcpy(data->industry_des, field_value);
	}

	if (field_order == 8){
		data->x_coor = (char*)malloc(sizeof(char)*strlen(field_value)+1);
		assert(data->x_coor);
		strcpy(data->x_coor, field_value);

	}
	if (field_order == 9){
		data->y_coor = (char*)malloc(sizeof(char)*strlen(field_value)+1);
		assert(data->y_coor);
		strcpy(data->y_coor, field_value);

	}
	if (field_order == 10){
		data->location = (char*)malloc(sizeof(char)*strlen(field_value)+1);
		assert(data->location);
		strcpy(data->location, field_value);
	}

	return data;
}