#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "matrix.h"


void MatrixPrint(Matrix **matrix){

    printf("\n");
    for (int i=0; i < (*matrix)->size; i++){
        printf("   ");
        for (int j=0; j < (*matrix)->size; j++) {
            (*matrix)->type_info->m_print((Matrix*)(*matrix)->data + (i * (*matrix)->size) + j);
        }
        printf("\n");
    }
    printf("\n");
}


void MatrixFind(MatrixCollection *collection, Matrix **matrix, char *name, int *response, size_t *size){

    for(int i=0; i < collection->size; i++){
        if (strcmp (collection->matrices[i].name, name)==0){
            (*response)++;
            *matrix = collection->matrices[i].matrix;
            *size = (*matrix)->size;

            break;
        }
    }
}


void MatrixNameFind(MatrixCollection *collection, char *name, int *response){

    for(int i=0; i < collection->size; i++){
        if (strcmp (collection->matrices[i].name, name)==0){
            (*response)++;
            return;
        }
    }
}


void MatrixCreate(MatrixCollection *collection, Matrix **matrix, char *name, size_t size, FieldInfo *element_type){

    *matrix = (Matrix *) malloc(sizeof(Matrix));
    (*matrix)->data = malloc(size * size * element_type->element_size * 3);

    if(*matrix && (*matrix)->data){
        for (int i=0; i < size; i++){
            for (int j=0; j < size; j++){

                void *temporary_result = malloc( element_type->element_size);
                if(temporary_result == NULL){
                    printf("\nError in MatrixCreate: Couldn't allocate memory space for temporary_result\n");
                    exit(-1);
                }

                printf("\nEnter element in row %d column %d:", i+1, j+1);

                element_type->m_scan(temporary_result);
                memcpy( (Matrix*)(*matrix)->data + i*size + j, temporary_result, element_type->element_size);

                free(temporary_result);
            }
        }
    }
    else{
        printf("\nError in MatrixCreate: Couldn't allocate memory space for matrix\n");
        exit(-1);
    }

    (*matrix)->size = size;
    (*matrix)->type_info = element_type;

    collection->matrices = realloc( collection->matrices, ( collection->size + 1) *  sizeof(NamedMatrix));

    if(collection->matrices==NULL){
        printf("\nError in MatrixCreate: Couldn't allocate memory space for collection\n");
        exit(-1);
    }

    collection->matrices[collection->size].matrix = *matrix;
    strncpy( collection->matrices[collection->size].name, name, sizeof(collection->matrices[collection->size].name));
    collection->size++;
}


void MatrixAutoCreate(MatrixCollection *collection, Matrix **matrix, char *name, size_t size, FieldInfo *element_type, void *max_number){

    srand((unsigned int)time(NULL));

    *matrix = (Matrix *) malloc(sizeof(Matrix));
    (*matrix)->data = malloc((size * size * element_type->element_size * 3));

    if(*matrix && (*matrix)->data){
        for (int i=0; i < size; i++){
            for (int j=0; j < size; j++){

                void *temporary_result = malloc(element_type->element_size);
                if(temporary_result == NULL){
                    printf("\nError in MatrixAutoCreate: Couldn't allocate memory space for temporary_result\n");
                    exit(-1);
                }

                element_type->m_random(temporary_result, max_number);

                memcpy( (Matrix*)(*matrix)->data + i*size + j, temporary_result, element_type->element_size);

                free(temporary_result);
            }
        }
    }
    else{
        printf("\nError in MatrixAutoCreate: Couldn't allocate memory space for matrix\n");
        exit(-1);
    }

    (*matrix)->size = size;
    (*matrix)->type_info = element_type;

    collection->matrices = realloc( collection->matrices, ( collection->size + 1) * sizeof(NamedMatrix));

    if(collection->matrices==NULL){
        printf("\nError in MatrixAutoCreate: Couldn't allocate memory space for collection\n");
        exit(-1);
    }

    collection->matrices[collection->size].matrix = *matrix;
    strncpy( collection->matrices[collection->size].name, name, sizeof(collection->matrices[collection->size].name));
    collection->size++;
}


void MatrixRename(MatrixCollection *collection, char *name_1, char *name_2){

    for(int i=0; i < collection->size; i++){
        if (strcmp( collection->matrices[i].name, name_1)==0){
            strncpy( collection->matrices[i].name, name_2, sizeof(collection->matrices[i].name));
            break;
        }
    }
}


void MatrixAdd(Matrix **m_sum, Matrix **m_1, Matrix **m_2, MatrixCollection *collection, char *name){

    *m_sum = (Matrix *) malloc(sizeof(Matrix));
    (*m_sum)->data = malloc((*m_1)->size * (*m_1)->size * (*m_1)->type_info->element_size * 3);

    if(*m_sum && (*m_sum)->data){

        (*m_sum)->size = (*m_1)->size;
        (*m_sum)->type_info = (*m_1)->type_info;

        for (int i=0; i < (*m_1)->size; i++){
            for (int j=0; j < (*m_1)->size; j++){

                void *temporary_result = malloc( (*m_1)->type_info->element_size);
                if(temporary_result == NULL){
                    printf("\nError in MatrixAdd: Couldn't allocate memory space for temporary_result\n");
                    exit(-1);
                }

                void *element_1 = (Matrix*)(*m_1)->data + i*(*m_1)->size + j;
                void *element_2 = (Matrix*)(*m_2)->data + i*(*m_1)->size + j;

                (*m_sum)->type_info->m_addition(temporary_result, element_1, element_2);
                memcpy( (Matrix*)(*m_sum)->data + i*(*m_sum)->size + j, temporary_result, (*m_sum)->type_info->element_size);

                free(temporary_result);
            }
        }
    }
    else{
        printf("\nError in MatrixAdd: Couldn't allocate memory space for matrix\n");
        exit(-1);
    }

    collection->matrices = realloc( collection->matrices, ( collection->size + 1) * sizeof(NamedMatrix));

    if(collection->matrices==NULL){
        printf("\nError in MatrixAdd: Couldn't allocate memory space for collection\n");
        exit(-1);
    }

    collection->matrices[collection->size].matrix = *m_sum;
    strncpy( collection->matrices[collection->size].name, name, sizeof(collection->matrices[collection->size].name));
    collection->size++;
}


void MatrixMultiply(Matrix **m_product, Matrix **m_1, Matrix **m_2, MatrixCollection *collection, char *name){

    *m_product = (Matrix*)malloc(sizeof(Matrix));
    (*m_product)->data = malloc((*m_1)->size * (*m_1)->size * (*m_1)->type_info->element_size * 3);

    if(*m_product && (*m_product)->data){

        (*m_product)->size = (*m_1)->size;
        (*m_product)->type_info = (*m_1)->type_info;

        for (int i=0; i < (**m_1).size; i++){
            for (int j=0; j < (**m_1).size; j++){

                void *temporary_result = malloc( (*m_1)->type_info->element_size);
                if(temporary_result == NULL){
                    printf("\nError in MatrixAdd: Couldn't allocate memory space for temporary_result\n");
                    exit(-1);
                }

                void *element_1 = (Matrix*)(*m_1)->data + i*(*m_1)->size + j;
                void *element_2 = (Matrix*)(*m_2)->data + i*(*m_1)->size + j;

                (*m_product)->type_info->m_multiplication(temporary_result, element_1, element_2);
                memcpy( (Matrix*)(*m_product)->data + i*(*m_product)->size + j, temporary_result, (*m_product)->type_info->element_size);

                free(temporary_result);
            }
        }
    }
    else{
        printf("\nError in MatrixMultiply: Couldn't allocate memory space for matrix\n");
        exit(-1);
    }

    collection->matrices = realloc( collection->matrices, ( collection->size + 1) * sizeof(NamedMatrix));

    if(collection->matrices==NULL){
        printf("\nError in MatrixMultiply: Couldn't allocate memory space for collection\n");
        exit(-1);
    }

    collection->matrices[collection->size].matrix = *m_product;
    strncpy( collection->matrices[collection->size].name, name, sizeof(collection->matrices[collection->size].name));
    collection->size++;
}


void MatrixMultiplyByScalar(Matrix **m_product, Matrix **m_1, MatrixCollection *collection, char *name, void *multiplier){

    *m_product = (Matrix*)malloc(sizeof(Matrix));
    (*m_product)->data = malloc((*m_1)->size * (*m_1)->size * (*m_1)->type_info->element_size * 3);

    if(*m_product && (*m_product)->data){

        (*m_product)->size = (*m_1)->size;
        (*m_product)->type_info = (*m_1)->type_info;

        for (int i=0; i < (*m_1)->size; i++){
            for (int j=0; j < (*m_1)->size; j++){

                void *temporary_result = malloc( (*m_1)->type_info->element_size);
                if(temporary_result == NULL){
                    printf("\nError in MatrixMultiplyByScalar: Couldn't allocate memory space for temporary_result\n");
                    exit(-1);
                }

                void *element = (Matrix*)(*m_1)->data + i*(*m_1)->size + j;

                (*m_product)->type_info->m_multiplication(temporary_result, element, multiplier);
                memcpy( (Matrix*)(*m_product)->data + i*(*m_product)->size + j, temporary_result, (*m_1)->type_info->element_size);

                free(temporary_result);
            }
        }
    }
    else{
        printf("\nError in MatrixMultiplyByScalar: Couldn't allocate memory space for matrix\n");
        exit(-1);
    }

    collection->matrices = realloc( collection->matrices, ( collection->size + 1) * sizeof(NamedMatrix));

    if(collection->matrices==NULL){
        printf("\nError in MatrixMultiplyByScalar: Couldn't allocate memory space for collection\n");
        exit(-1);
    }

    collection->matrices[collection->size].matrix = *m_product;
    strncpy( collection->matrices[collection->size].name, name, sizeof(collection->matrices[collection->size].name));
    collection->size++;
}


void LinearCombinationInitialize(Matrix **linear_combination, Matrix **matrix){

    *linear_combination = (Matrix*)malloc(sizeof(Matrix));
    (*linear_combination)->data = malloc((*matrix)->size * (*matrix)->size * (*matrix)->type_info->element_size * 3);

    if(*linear_combination && (*linear_combination)->data ){

        (*linear_combination)->size = (*matrix)->size;
        (*linear_combination)->type_info = (*matrix)->type_info;

        for (int i=0; i < (*linear_combination)->size; i++){
            for (int j=0; j < (*linear_combination)->size; j++){
                memset((Matrix*)(*linear_combination)->data + i*(*linear_combination)->size + j, 0, (*linear_combination)->type_info->element_size);
            }
        }
    }
}


void MatrixAddLinearCombination(Matrix **m_result, int row_number, Matrix **m_1, MatrixCollection *collection, char *name, Matrix **linear_combination, void *max_number){

    srand((unsigned int)time(NULL));

    *m_result = (Matrix*)malloc(sizeof(Matrix));
    (*m_result)->data = malloc((*m_1)->size * (*m_1)->size * (*m_1)->type_info->element_size * 3);

    if(*m_result && (*m_result)->data){

        (*m_result)->size = (*m_1)->size;
        (*m_result)->type_info = (*m_1)->type_info;

        for (int i=0; i < (*m_1)->size; i++){

            if(i+1 != row_number){

                void *multiplier = malloc( (*m_1)->type_info->element_size);
                if(multiplier == NULL){
                    printf("\nError in MatrixAddLinearCombination: Couldn't allocate memory space for multiplier\n");
                    exit(-1);
                }

                (*m_1)->type_info->m_random(multiplier, max_number);

                for (int j=0; j < (*m_1)->size; j++){

                    void *temporary_result_1 = malloc(  (*m_1)->type_info->element_size);
                    if(temporary_result_1 == NULL){
                        printf("\nError in MatrixAddLinearCombination: Couldn't allocate memory space for temporary_result\n");
                        exit(-1);
                    }

                    void *temporary_result_2 = malloc(  (*m_1)->type_info->element_size);
                    if(temporary_result_2 == NULL){
                        printf("\nError in MatrixAddLinearCombination: Couldn't allocate memory space for temporary_result\n");
                        exit(-1);
                    }

                    void *element_matrix = (Matrix*)(*m_1)->data + i*(*m_1)->size + j;
                    void *element_lc = (Matrix*)(*linear_combination)->data + j;

                    (*linear_combination)->type_info->m_multiplication(temporary_result_1, element_matrix, multiplier);

                    (*linear_combination)->type_info->m_addition( temporary_result_2, element_lc, temporary_result_1);

                    memcpy( (Matrix*)(*linear_combination)->data + j, temporary_result_2, (*linear_combination)->type_info->element_size);

                    memcpy( (Matrix*)(*m_result)->data + i*(*m_result)->size + j, (Matrix*)(*m_1)->data + i*(*m_result)->size + j, (*m_result)->type_info->element_size);

                    free(temporary_result_1);
                    free(temporary_result_2);
                }
                free(multiplier);
            }
        }
    }
    else{
        printf("\nError in MatrixAddLinearCombination: Couldn't allocate memory space for matrix\n");
        exit(-1);
    }

    for (int i=0; i < (*m_1)->size; i++){
        for (int j=0; j < (*m_1)->size; j++){
            if(i+1 == row_number){

                void *result = malloc( (*m_1)->type_info->element_size);
                if(result == NULL){
                    printf("\nError in MatrixAddLinearCombination: Couldn't allocate memory space for TemporaryResult\n");
                    exit(-1);
                }

                void *element_lc = (Matrix*)(*linear_combination)->data + j;

                void *element = (Matrix*)(*m_1)->data + i*(*m_1)->size + j;
                (*m_result)->type_info->m_addition(result, element, element_lc);

                memcpy( (Matrix*)(*m_result)->data + i*(*m_result)->size + j, result, (*m_result)->type_info->element_size);


                free(result);
            }
        }
    }

    collection->matrices = realloc( collection->matrices, ( collection->size + 1) * sizeof(NamedMatrix));

    if(collection->matrices==NULL){
        printf("\nError in MatrixMultiplyByScalar: Couldn't allocate memory space for collection\n");
        exit(-1);
    }

    collection->matrices[collection->size].matrix = *m_result;
    strncpy( collection->matrices[collection->size].name, name, sizeof(collection->matrices[collection->size].name));
    collection->size++;
}


void MatrixFree(Matrix **m){
    (*m)->size = 0;
    free((*m)->data);
    free(*m);
}


void MatrixElementTypeCompare(Matrix **m_1, Matrix **m_2, int *response){
    if(strcmp( (*m_1)->type_info->type_name, (*m_2)->type_info->type_name) != 0){
        (*response)++;
    }
}