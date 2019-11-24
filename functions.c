//HEADER FILES

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// DEFINITIONS

#define string_to_float     atof
#define string_to_integer   atoi

// FUNCTION PROTOTYPES
void erase_specific_character(char*, char);
int retrieve_column_no(char*);
char *retrieve_token_column(char *, int);

//REQUIRED FUNCTIONS

//GETMAX()
double getMax(char *csvfile, char *column) 
{
    FILE *filePointer = fopen(csvfile, "r");
    if (filePointer == NULL) {
        printf("\n Specifed file does not exist or is unreadable:  %s\n", csvfile);
        exit(1);
    }

    int col_number = retrieve_column_no(column);
    if (col_number < 0)
        return col_number;  
    col_number += 2;  

    double maximum_value = 0;

    char input_file_line[3000];
    fgets(input_file_line, 3000, filePointer);  // Skip first input_file_line
    while (fgets(input_file_line, 3000, filePointer))
     {
        char *retrieved_val = retrieve_token_column(input_file_line, col_number);
        if ( strcmp(retrieved_val, "N/A") != 0 && strcmp(retrieved_val, "") != 0) 
        {
            int input_value = string_to_float(retrieved_val);
            if (input_value > maximum_value)
                maximum_value = input_value;
        }
    }
    return maximum_value;
}

// GETMIN()
double getMin(char *csvfile, char *column)
 {
    FILE *filePointer = fopen(csvfile, "r");
    if (filePointer == NULL) {
        printf("\n Specifed file does not exist or is unreadable:  %s\n", csvfile);
        exit(1);
    }

    int col_number = retrieve_column_no(column);
    if (col_number < 0.0)
        return col_number;

    col_number += 2;  // retrieve_column_no returns 1 for P5.1, but in actual file p5.1 is column3

    double minimum_value = 0;

    char input_file_line[3000];
    fgets(input_file_line, 3000, filePointer);  // Skip first input_file_line
    while (fgets(input_file_line, 3000, filePointer)) 
    {
        char *retrieved_val = retrieve_token_column(input_file_line, col_number);
        if (strcmp(retrieved_val, "N/A") != 0 && strcmp(retrieved_val, "") != 0)
         {
            int input_value = string_to_float(retrieved_val);
            if (input_value < minimum_value)
                minimum_value = input_value;
        }
    }
    return minimum_value;
}

// UTILITY FUNCTION
void erase_specific_character(char* input_str, char toBeErased) 
{
    char *previous_ptr = input_str, *next_ptr = input_str;
    while (*previous_ptr)
    {
        *next_ptr = *previous_ptr++;
        next_ptr += (*next_ptr != toBeErased);
    }
    *next_ptr = '\0';
}

// GET AVG
double getAvg(char *csvfile, char *column) 
{
    FILE *filePointer = fopen(csvfile, "r");
    if (filePointer == NULL) 
    {
        printf("\n Specifed file does not exist or is unreadable:  %s\n", csvfile);
        exit(1);
    }

    int col_number = retrieve_column_no(column);
    if (col_number < 0)
        return col_number;    

    col_number += 2; 

    double column_sum = 0;
    int counter_var = 0;

    char input_file_line[3000];
    fgets(input_file_line, 3000, filePointer);  // Skip first input_file_line
    while (fgets(input_file_line, 3000, filePointer)) 
    {
        char *retrieved_val = retrieve_token_column(input_file_line, col_number);
        if ( strcmp(retrieved_val, "N/A") != 0 && strcmp(retrieved_val, "") != 0) {
            int input_value = string_to_float(retrieved_val);
            column_sum += input_value;
            counter_var++;
        }
    }
    return (double) column_sum / counter_var;
}

//UTILITY FUNCTION
int retrieve_weight_column(char* input_title) 
{
    char* csv_header = strdup(input_title);
    char* temp = strsep(&csv_header," "); // Discard section
    temp = strsep(&csv_header," ");       // Discard hyphen
    temp = strsep(&csv_header," ");      //discard title text
    erase_specific_character(csv_header,'(');
    erase_specific_character(csv_header,')');

    int column_weight = string_to_integer(csv_header);
    return column_weight;
}

//GETCOUNT()
int getCount(char *csvfile, char *column, double threshold) 
{
    
    int col_number = retrieve_column_no(column);
    if (col_number < 0)
        return col_number;    
    col_number += 2;
    int counter_var = 0;
    FILE *filePointer = fopen(csvfile, "r");
    if (filePointer == NULL) 
    {
        printf("\n Specifed file does not exist or is unreadable:  %s\n", csvfile);
        exit(1);
    }
    char input_file_line[3000];
    fgets(input_file_line, 3000, filePointer);  
    while (fgets(input_file_line, 3000, filePointer)) 
    {
        char *retrieved_val = retrieve_token_column(input_file_line, col_number);
        if ( strcmp(retrieved_val, "N/A") != 0 && strcmp(retrieved_val, "") != 0) {
            double input_value = string_to_float(retrieved_val);
            if (input_value >= threshold)
                counter_var++;
        }
    }
    return counter_var;
}

//GETGRADE()
double getGrade(char *csvfile, char first[], char last[]) {
    FILE *filePointer = fopen(csvfile, "r");
    if (filePointer == NULL) 
    {
        printf("\n Specifed file does not exist or is unreadable:  %s\n", csvfile);
        exit(1);
    }

    char input_file_line[3000];
    char** csv_column_titles = (char**)malloc(60 * sizeof(char*));
    fgets(input_file_line, 3000, filePointer); // get csv_column_titles input_file_line
    char* temporary_var = strdup(input_file_line);
    char* tokenized_str = strsep(&temporary_var, ",");
    int csv_headers_no=0;
    while(tokenized_str) 
    {
        csv_column_titles[csv_headers_no++] = tokenized_str;
        tokenized_str = strsep(&temporary_var, ",");
    }

    //For windows line endings
    erase_specific_character(csv_column_titles[csv_headers_no-1],'\r');
    erase_specific_character(csv_column_titles[csv_headers_no-1],'\n');

    /* For unix line endings

    erase_specific_character(csv_column_titles[csv_headers_no-1],'\n');

     */
    char* last_name,*first_name;
    while (fgets(input_file_line, 3000, filePointer)) 
    {
        char* temporary_var = strdup(input_file_line);
        last_name = strsep(&temporary_var,",");
        first_name = strsep(&temporary_var,",");
        if(strcasecmp(last_name,last)==0 && strcasecmp(first_name,first)==0) {
            temporary_var = strdup(input_file_line);
            char** grades_student = (char**)malloc(60 * sizeof(char*));
            char* tokenized_str = strsep(&temporary_var, ",");
            int subject_types_no=0;
            while(tokenized_str) {
                grades_student[subject_types_no++] = tokenized_str;
                tokenized_str = strsep(&temporary_var, ",");
            }
            double cumulative_marks=0, cumulative_weight=0;
            for(int i=2; i<subject_types_no; ++i) {
                cumulative_marks += (string_to_float(grades_student[i]) * retrieve_weight_column(csv_column_titles[i]));
                cumulative_weight += retrieve_weight_column(csv_column_titles[i]);
            }
            double average_weighted = (double) cumulative_marks / cumulative_weight;
            return average_weighted;
        }
    }
    return -99;
}

char *retrieve_token_column(char *input_file_line, int measure) {
    char *temporary_var = strdup(input_file_line);
    char *token_str = strsep(&temporary_var, ",");
    while (token_str) {
        if (!--measure)
            return token_str;
        token_str = strsep(&temporary_var, ",");
    }
    return NULL;
}

int retrieve_column_no(char *column) {
    if (strcmp(column, "P5.1") == 0) return 1;
    else if (strcmp(column, "C5.1") == 0) return -1;
    else if (strcmp(column, "C5.2") == 0) return 17;
    else if (strcmp(column, "C5.3") == 0) return -1;
    else if (strcmp(column, "C5.4") == 0) return 19;
    else if (strcmp(column, "C5.5") == 0) return 20;
    else if (strcmp(column, "C5.6") == 0) return -1;
    else if (strcmp(column, "C5.7") == 0) return 22;
    else if (strcmp(column, "C5.8") == 0) return -1;
    else if (strcmp(column, "C5.9") == 0) return 24;
    else if (strcmp(column, "C5.10") == 0) return -1;
    else if (strcmp(column, "C5.11") == 0) return -1;
    else if (strcmp(column, "C5.12") == 0) return -1;
    else if (strcmp(column, "C5.13") == 0) return -2;
    else if (strcmp(column, "C5.14") == 0) return -1;
    else if (strcmp(column, "C5.15") == 0) return -1;
    else if (strcmp(column, "P5.2") == 0) return 2;
    else if (strcmp(column, "P5.3") == 0) return 3;
    else if (strcmp(column, "P5.4") == 0) return 4;
    else if (strcmp(column, "P5.5") == 0) return 5;
    else if (strcmp(column, "P5.6") == 0) return 6;
    else if (strcmp(column, "P5.7") == 0) return 7;
    else if (strcmp(column, "P5.8") == 0) return 8;
    else if (strcmp(column, "P5.9") == 0) return 9;
    else if (strcmp(column, "P5.10") == 0) return 10;
    else if (strcmp(column, "P5.11") == 0) return 11;
    else if (strcmp(column, "P5.12") == 0) return 12;
    else if (strcmp(column, "P5.13") == 0) return 13;
    else if (strcmp(column, "P5.14") == 0) return -1;
    else if (strcmp(column, "P5.15") == 0) return -1;
    else if (strcmp(column, "L5.21") == 0) return 31;
    else if (strcmp(column, "L5.23") == 0) return 32;
    else if (strcmp(column, "L5.25") == 0) return 33;
    else if (strcmp(column, "L5.26") == 0) return 34;
    else if (strcmp(column, "L5.27") == 0) return 35;
    else return -2;
}

