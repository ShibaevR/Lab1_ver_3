#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tests.h"
#include "matrix.h"
#include "int-element.h"


void TestMatrixCreation(){

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    Matrix *m_1;
    FieldInfo *m_field_info;
    m_field_info = GetIntFieldInfo();

    char name_1[20] = "a";
    size_t size_1 = 2;

    void *max_number = malloc(m_field_info->element_size);
    *(int*)max_number = 5;

    MatrixAutoCreate(&collection, &m_1, name_1, size_1, m_field_info, max_number);

    if(collection.size != 1){
        assert(0 && "Error in MatrixAutomaticCreate: couldn't add a matrix to the collection");
    }

    MatrixFree(&m_1);
    collection.size = 0;
    free(collection.matrices);
    free(max_number);
}


void TestExistingMatrixFind(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    Matrix *m_1;
    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    char name_1[20] = "a";
    size_t size_1 = 2;

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, max_number);
    MatrixNameFind(&collection, name_1, &response);

    assert(response && "Error in MatrixFind: couldn't find the matrix to the collection");

    MatrixFree(&m_1);
    collection.size = 0;
    free(collection.matrices);
    free(max_number);
}


void TestNotExistingMatrixFind(){
    int response = -1;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    Matrix *m_1;
    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    char name_1[20] = "a";
    char non_existing_name[20] = "c";
    size_t size_1 = 2;

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, max_number);
    MatrixNameFind(&collection, non_existing_name, &response);

    assert(response && "Error in MatrixFind: found a matrix that doesn't exist");

    MatrixFree(&m_1);
    collection.size = 0;
    free(collection.matrices);
    free(max_number);
}


void TestRenamedMatrixFind(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    Matrix *m_1;
    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    char name_1[20] = "a";
    char new_name[20] = "d";
    size_t size_1 = 2;

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, max_number);
    MatrixRename(&collection, name_1, new_name);

    MatrixNameFind(&collection, new_name, &response);

    assert(response && "Error in MatrixRename: couldn't rename a matrix");

    MatrixFree(&m_1);
    collection.size = 0;
    free(collection.matrices);
    free(max_number);
}


void TestReplacedNameMatrixFind(){
    int response = -1;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    Matrix *m_1;
    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    char name_1[20] = "a";
    char new_name[20] = "d";
    size_t size_1 = 2;

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, max_number);
    MatrixRename(&collection, name_1, new_name);
    MatrixNameFind(&collection, name_1, &response);

    assert(response && "Error in MatrixRename: found a name that's no longer in use");

    MatrixFree(&m_1);
    collection.size = 0;
    free(collection.matrices);
    free(max_number);
}


void TestMatrixAdd(){

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix *m_1;
    char name_1[20] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, max_number);

    Matrix *m_2;
    char name_2[20] = "b";
    size_t size_2 = 2;
    MatrixAutoCreate(&collection, &m_2, name_2, size_2, &m_field_info, max_number);

    Matrix *m_sum;
    char name_3[20] = "sum";
    MatrixAdd(&m_sum, &m_1, &m_2, &collection, name_3);

    for(int i=0; i < 2; i++){
        for(int j=0; j < 2; j++){
            if(m_sum->data + i*m_sum->size + j == NULL){
                assert(0 && "Error in MatrixAdd: incorrect sum of elements");
            }
        }
    }

    MatrixFree(&m_1);
    MatrixFree(&m_2);
    MatrixFree(&m_sum);
    collection.size = 0;
    free(collection.matrices);
    free(max_number);
}


void TestMatrixSumFind(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix *m_1;
    char name_1[20] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, max_number);

    Matrix *m_2;
    char name_2[20] = "b";
    size_t size_2 = 2;
    MatrixAutoCreate(&collection, &m_2, name_2, size_2, &m_field_info, max_number);

    Matrix *m_sum;
    char name_3[20] = "sum";
    MatrixAdd(&m_sum, &m_1, &m_2, &collection, name_3);

    MatrixNameFind(&collection, name_3, &response);

    assert(response && "Error in MatrixAdd: couldn't add the matrix sum to the collection");

    MatrixFree(&m_1);
    MatrixFree(&m_2);
    MatrixFree(&m_sum);
    collection.size = 0;
    free(collection.matrices);
    free(max_number);
}


void TestMatrixMultiply(){

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix* m_1;
    char name_1[20] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, max_number);

    Matrix *m_2;
    char name_2[20] = "b";
    size_t size_2 = 2;
    MatrixAutoCreate(&collection, &m_2, name_2, size_2, &m_field_info, max_number);

    Matrix *m_product;
    char name_3[20] = "product";
    MatrixMultiply(&m_product, &m_1, &m_2, &collection, name_3);

    for(int i=0; i < 2; i++){
        for(int j=0; j < 2; j++){
            if(m_product->data + i*m_product->size + j == NULL){
                assert(0 && "Error in MatrixMultiply: incorrect product of elements");
            }
        }
    }

    MatrixFree(&m_1);
    MatrixFree(&m_2);
    MatrixFree(&m_product);
    collection.size = 0;
    free(collection.matrices);
    free(max_number);
}


void TestMatrixProductFind(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix *m_1;
    char name_1[20] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, max_number);

    Matrix *m_2;
    char name_2[20] = "b";
    size_t size_2 = 2;
    MatrixAutoCreate(&collection, &m_2, name_2, size_2, &m_field_info, max_number);

    Matrix *m_product;
    char name_3[20] = "product";
    MatrixMultiply(&m_product, &m_1, &m_2, &collection, name_3);

    MatrixNameFind(&collection, name_3, &response);

    assert(response && "Error in MatrixMultiply: couldn't add the matrix to the collection");

    MatrixFree(&m_1);
    MatrixFree(&m_2);
    MatrixFree(&m_product);
    collection.size = 0;
    free(collection.matrices);
    free(max_number);
}


void TestMatrixMultiplyByScalar(){

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix *m_1;
    char name_1[20] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, max_number);

    Matrix *m_result;
    char name_2[20] = "result";

    void *multiplier = malloc(m_field_info.element_size);
    *(int*)multiplier = 5;

    MatrixMultiplyByScalar(&m_result, &m_1, &collection, name_2, multiplier);

    for(int i=0; i < 2; i++){
        for(int j=0; j < 2; j++){
            if(m_result->data + i*m_result->size + j == NULL){
                assert(0 && "Error in MatrixMultiplyByScalar: incorrect product of elements");
            }
        }
    }

    MatrixFree(&m_1);
    MatrixFree(&m_result);
    collection.size = 0;
    free(collection.matrices);
    free(max_number);
    free(multiplier);
}


void TestMatrixMultiplyByScalarFind(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix *m_1;
    char name_1[20] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, max_number);

    Matrix *m_result;
    char name_2[20] = "result";

    void *multiplier = malloc(m_field_info.element_size);
    *(int*)multiplier = 5;

    MatrixMultiplyByScalar(&m_result, &m_1, &collection, name_2, multiplier);

    MatrixNameFind(&collection, name_2, &response);

    assert(response && "Error in MatrixMultiplyByScalar: couldn't add the matrix to the collection");

    MatrixFree(&m_1);
    MatrixFree(&m_result);
    collection.size = 0;
    free(collection.matrices);
    free(max_number);
    free(multiplier);
}


void TestMatrixAddLinearCombination(){

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix *m_1;
    char name_1[20] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, max_number);

    Matrix *m_result;
    char name_2[20] = "result";
    int row_number = 2;

    Matrix *linear_combination;

    LinearCombinationInitialize(&linear_combination, &m_1);

    MatrixAddLinearCombination(&m_result, row_number, &m_1, &collection, name_2, &linear_combination, max_number);

    for(int i=0; i < 2; i++){
        for(int j=0; j < 2; j++){
            if(m_result->data + i*m_result->size + j == NULL){
                assert(0 && "Error in MatrixAddLinearCombination: incorrect sum of elements");
            }
        }
    }

    MatrixFree(&m_1);
    MatrixFree(&m_result);
    MatrixFree(&linear_combination);
    collection.size = 0;
    free(collection.matrices);
    free(max_number);
}


void TestMatrixMatrixAddLinearCombinationFind(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix *m_1;
    char name_1[20] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, max_number);

    Matrix *m_result;
    char name_2[20] = "result";
    int row_number = 2;

    Matrix *linear_combination;

    LinearCombinationInitialize(&linear_combination, &m_1);

    MatrixAddLinearCombination(&m_result, row_number, &m_1, &collection, name_2, &linear_combination, max_number);

    MatrixNameFind(&collection, name_2, &response);

    assert(response && "Error in MatrixAddOfLinearCombination: couldn't add the matrix to the collection");

    MatrixFree(&m_1);
    MatrixFree(&m_result);
    MatrixFree(&linear_combination);
    collection.size = 0;
    free(collection.matrices);
    free(max_number);
}


void AllTests(){


    TestMatrixCreation();                       //Проверка добавления 1 матрицы в коллекцию
    //printf("\nCompleted 1 test\n");

    TestExistingMatrixFind();                   //Проверка нахождения существующей матрицы в коллекции
    //printf("\nCompleted 2 tests\n");

    TestNotExistingMatrixFind();                //Проверка нахождения несуществующей матрицы в коллекции
    //printf("\nCompleted 3 tests\n");

    TestRenamedMatrixFind();                    //Проверка переименовывания матрицы
    //printf("\nCompleted 4 tests\n");

    TestReplacedNameMatrixFind();               //Проверка нахождения уже заменённого имени
    //printf("\nCompleted 5 tests\n");

    TestMatrixAdd();                            //Проверка сложения матриц
    //printf("\nCompleted 6 tests\n");

    TestMatrixSumFind();                        //Проверка добавления суммы матриц в коллекцию
    //printf("\nCompleted 7 tests\n");

    TestMatrixMultiply();                       //Проверка умножения матриц
    //printf("\nCompleted 8 tests\n");

    TestMatrixProductFind();                    //Проверка добавления произведения матриц в коллекцию
    //printf("\nCompleted 9 tests\n");

    TestMatrixMultiplyByScalar();               //Проверка умножения матрицы на число
    //printf("\nCompleted 10 tests\n");

    TestMatrixMultiplyByScalarFind();           //Проверка добавления новой мтарицы в коллекцию
    //printf("\nCompleted 11 tests\n");

    TestMatrixAddLinearCombination();           //Проверка добавления к строке матрицы линейной комбинации других строк
    //printf("\nCompleted 12 tests\n");

    TestMatrixMatrixAddLinearCombinationFind(); //Проверка добавления новой матрицы в коллекцию

}