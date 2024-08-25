#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "tests.h"

#include "int-element.h"
#include "float-element.h"


void PrintMenu() {
    printf("\n--------------------------Menu--------------------------\n");
    printf("1. Show all matrices\n");
    printf("2. Show a chosen matrix\n");
    printf("3. Create a matrix\n");
    printf("4. Rename a matrix\n");
    printf("5. Matrix addition\n");
    printf("6. Matrix multiplication\n");
    printf("7. Multiplication of a matrix by a scalar\n");
    printf("8. Add a linear combination of rows to the selected row\n");
    printf("--------------------------------------------------------\n\n");
    printf("Enter 'STOP' to finish\n");
    printf("----------Or----------\n");
    printf("Select an action: ");
}

int main() {

    AllTests();
    printf("\nAll tests completed successfully\n");

    int action;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    while(1) {
        PrintMenu();

        char user_input[20];
        scanf("%19s", user_input);

        if (strcmp(user_input, "STOP") == 0) {

            for (int i = 0; i < collection.size; i++)
            {
                MatrixFree(&collection.matrices[i].matrix);
            }
            free(collection.matrices);

            exit(0);
        }

        action = atoi(user_input);

        switch(action){
            case 1:{
                if(collection.size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                printf("\nNumber of matrices: %zu\n", collection.size);
                for(int i=0; i < collection.size; i++){
                    printf("\n%d. %s\n", i+1, &collection.matrices[i].name);
                    MatrixPrint(&collection.matrices[i].matrix);
                }

                break;
            }


            case 2:{
                if(collection.size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                int response=0;
                char name[20];
                Matrix *m;
                size_t size;

                printf("\nNumber of matrices: %zu\n", collection.size);
                printf("Enter the matrix's name: ");
                scanf("%19s", name);

                MatrixFind(&collection, &m, name, &response, &size);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }

                printf("\nMatrix %s:\n", name);
                MatrixPrint(&m);

                break;
            }


            case 3:{
                Matrix *m;
                char name[20];
                size_t size;

                printf("\nEnter the matrix's name: ");
                scanf("%19s", name);
                if(collection.size > 0){
                    int response=0;
                    MatrixNameFind(&collection, name, &response);
                    if(response > 0){
                        printf("\nError: A matrix with this name already exists\n");
                        break;
                    }
                }


                int option;
                printf("\nWhat type of elements do you want the matrix to have?\n");
                printf("Enter <1> for int or <2> for float: ");
                scanf("%d", &option);


                FieldInfo *m_field_info;
                if(option==1){

                    m_field_info = GetIntFieldInfo();

                    printf("\nEnter the size of the matrix (max size is 29): ");
                    scanf("%zu", &size);
                    if (size > 29){
                        printf("\nError: The max size is 29!\n");
                        break;
                    }
                }
                else if(option==2){
                    m_field_info = GetFloatFieldInfo();

                    printf("\nEnter the size of the matrix (max size is 9): ");
                    scanf("%zu", &size);
                    if (size > 9){
                        printf("\nError: The max size is 9!\n");
                        break;
                    }
                }
                else{
                    printf("\nError: This type doesn't exist. Please try again.\n");
                    break;
                }


                void *max_number = malloc(m_field_info->element_size);
                if(max_number == NULL){
                    printf("\nError: Couldn't allocate memory space for multiplier\n");
                    exit(-1);
                }

                printf("\nDo you want to create the matrix automatically or manually?\n");
                printf("Enter <1> for automatic creation or <2> for manual: ");
                scanf("%d", &option);

                if(option==1){
                    printf("\nEnter the max number for random generation: ");
                    if(strcmp( m_field_info->type_name, "int")==0 ){
                        scanf("%d", max_number);
                    }
                    else if(strcmp( m_field_info->type_name, "float")==0 ){
                        scanf("%f", max_number);
                    }
                    MatrixAutoCreate(&collection, &m, name, size, m_field_info, max_number);
                }
                else if(option==2){
                    MatrixCreate(&collection, &m, name, size, m_field_info);
                }
                else{
                    printf("\nError: This action doesn't exist. Please try again.\n");
                    break;
                }

                printf("%zu. %s\n", collection.size, name);
                MatrixPrint(&m);

                free(max_number);
                break;
            }


            case 4:{
                if(collection.size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                char name_1[20];
                char name_2[20];
                Matrix *m;
                size_t size;

                printf("\nEnter the name of the matrix you want to rename: ");
                scanf("%19s", name_1);

                int response=0;
                MatrixFind(&collection, &m, name_1, &response, &size);
                if(response == 0){
                    printf("\nError: A matrix with this doesn't exist\n");
                    break;
                }
                response = 0;


                printf("\nEnter the new name for the matrix %s: ", name_1);
                scanf("%19s", name_2);

                MatrixNameFind(&collection, name_2, &response);
                if(response > 0){
                    printf("\nError: A matrix with this name already exists\n");
                    break;
                }


                MatrixRename(&collection, name_1, name_2);

                printf("\nMatrix %s:\n", name_2);
                MatrixPrint(&m);

                break;
            }


            case 5:{
                if(collection.size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }
                else if(collection.size < 2){
                    printf("\nError: There are less then 2 matrices! You need at least 2 matrices for addition\n");
                    break;
                }

                int response=0;


                Matrix *m_1;
                char name_1[20];
                size_t size_1;
                printf("\nEnter the first matrix's name: ");
                scanf("%19s", name_1);

                MatrixFind(&collection, &m_1, name_1, &response, &size_1);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                response = 0;


                Matrix *m_2;
                char name_2[20];
                size_t size_2;
                printf("\nEnter the second matrix's name: ");
                scanf("%19s", name_2);

                MatrixFind(&collection, &m_2, name_2, &response, &size_2);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                response = 0;


                if(size_1 != size_2){
                    printf("\nError: For addition you need matrices to be the same size.\n");
                    break;
                }
                MatrixElementTypeCompare(&m_1, &m_2, &response);
                if(response > 0){
                    printf("\nError: Matrices need to have the same type of elements.\n");
                    break;
                }
                response = 0;


                Matrix *m_sum;
                char name_3[20];
                printf("\nEnter the new matrix's name: ");
                scanf("%19s", name_3);

                MatrixNameFind(&collection, name_3, &response);
                if(response > 0){
                    printf("\nError: A matrix with this name already exists\n");
                    break;
                }
                response = 0;

                MatrixAdd(&m_sum, &m_1, &m_2, &collection, name_3);

                printf("\nResult - Matrix %s:\n", name_3);
                MatrixPrint(&m_sum);

                break;
            }


            case 6:{
                if(collection.size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }
                else if(collection.size < 2){
                    printf("\nError: There are less then 2 matrices! You need at least 2 matrices for multiplication\n");
                    break;
                }

                int response=0;

                Matrix *m_1;
                char name_1[20];
                size_t size_1;
                printf("\nEnter the first matrix's name: ");
                scanf("%19s", name_1);

                MatrixFind(&collection, &m_1, name_1, &response, &size_1);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                response = 0;


                Matrix *m_2;
                char name_2[20];
                size_t size_2;
                printf("\nEnter the second matrix's name: ");
                scanf("%19s", name_2);

                MatrixFind(&collection, &m_2, name_2, &response, &size_2);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                response = 0;


                if(size_1 != size_2){
                    printf("\nError: For multiplication you need matrices to be the same size.\n");
                    break;
                }
                MatrixElementTypeCompare(&m_1, &m_2, &response);
                if(response > 0){
                    printf("\nError: Matrices need to have the same type of elements.\n");
                    break;
                }
                response = 0;


                Matrix *m_mult;
                char name_3[20];
                printf("\nEnter the new matrix's name: ");
                scanf("%19s", name_3);

                MatrixNameFind(&collection, name_3, &response);
                if(response > 0){
                    printf("\nError: A matrix with this name already exists\n");
                    break;
                }

                MatrixMultiply(&m_mult, &m_1, &m_2, &collection, name_3);

                printf("\nResult - Matrix %s:\n", name_3);
                MatrixPrint(&m_mult);

                break;
            }


            case 7:{
                if(collection.size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                int response=0;

                Matrix *m_1;
                char name_1[20];
                size_t size;
                printf("\nEnter the matrix's name: ");
                scanf("%19s", name_1);

                MatrixFind(&collection, &m_1, name_1, &response, &size);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                response = 0;


                void *multiplier = malloc(m_1->type_info->element_size);
                if(multiplier == NULL){
                    printf("\nError: Couldn't allocate memory space for multiplier\n");
                    exit(-1);
                }

                printf("\nEnter the a %s scalar: ", m_1->type_info->type_name);
                if (strcmp( m_1->type_info->type_name, "int")==0 ){
                    scanf("%d", multiplier);
                }
                else if (strcmp( m_1->type_info->type_name, "float")==0 ){
                    scanf("%f", multiplier);
                }


                Matrix *m_mult;
                char name_2[20];
                printf("\nEnter the new matrix's name: ");
                scanf("%19s", name_2);

                MatrixNameFind(&collection, name_2, &response);
                if(response > 0){
                    printf("\nError: A matrix with this name already exists\n");
                    break;
                }

                MatrixMultiplyByScalar(&m_mult, &m_1, &collection, name_2, multiplier);

                printf("\nResult - Matrix %s:\n", name_2);
                MatrixPrint(&m_mult);

                free(multiplier);
                break;
            }


            case 8:{
                if(collection.size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                int response=0;

                Matrix *m_1;
                char name_1[20];
                size_t size;
                printf("\nEnter the matrix's name: ");
                scanf("%s", name_1);
                MatrixFind(&collection, &m_1, name_1, &response, &size);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                response = 0;


                int row_number;
                printf("\nEnter the number of the row: ");
                scanf("%d", &row_number);
                if(row_number > size || row_number <= 0){
                    printf("\nError: This row doesn't exist\n");
                    break;
                }


                Matrix *m_res;
                char name_2[20];
                printf("\nEnter the new matrix's name: ");
                scanf("%s", name_2);

                MatrixNameFind(&collection, name_2, &response);
                if(response > 0){
                    printf("\nError: A matrix with this name already exists\n");
                    break;
                }


                void *max_number = malloc(m_1->type_info->element_size);
                if(max_number == NULL){
                    printf("\nError: Couldn't allocate memory space for multiplier\n");
                    exit(-1);
                }

                if(strcmp( m_1->type_info->type_name, "int")==0 ){
                    if(max_number == NULL){
                        printf("\nError: Couldn't allocate memory space for multiplier\n");
                        exit(-1);
                    }

                    *(int*)max_number = 10;
                }
                else if(strcmp( m_1->type_info->type_name, "float")==0 ){
                    if(max_number == NULL){
                        printf("\nError: Couldn't allocate memory space for multiplier\n");
                        exit(-1);
                    }

                    *(float*)max_number = 10.0;
                }


                Matrix *linear_combination;
                LinearCombinationInitialize(&linear_combination, &m_1);


                MatrixAddLinearCombination(&m_res, row_number, &m_1, &collection, name_2, &linear_combination, max_number);

                printf("\nResult - Matrix %s:\n", name_2);
                MatrixPrint(&m_res);

                free(max_number);
                MatrixFree(&linear_combination);
                break;
            }


            default:{
                printf("\nError: This action doesn't exist. Please try again.\n");
                break;
            }
        }
    }

    return 0;
}
