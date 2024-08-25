#ifndef LAB1_RETRY_MATRIX_H
#define LAB1_RETRY_MATRIX_H

#include "fieldinfo.h"


typedef struct{
    void *data;              //Указатель на элементы матрицы
    size_t size;              //Размер матрицы
    FieldInfo *type_info;      //Тип элементов матрицы
} Matrix;

typedef struct{
    char name[20];
    Matrix *matrix;
} NamedMatrix;

typedef struct{
    NamedMatrix *matrices;
    size_t size;
} MatrixCollection;  //Массив указателей на матрицы


void MatrixPrint(Matrix **m);   //1 и 2

void MatrixFind(MatrixCollection *collection, Matrix **matrix, char *name, int *response, size_t *size); //1 и 2

void MatrixNameFind(MatrixCollection *collection, char *name, int *response);

void MatrixCreate(MatrixCollection *collection, Matrix **matrix, char *name, size_t size, FieldInfo *element_type);      //3

void MatrixAutoCreate(MatrixCollection *collection, Matrix **matrix, char *name, size_t size, FieldInfo *element_type, void *max_number);  //3

void MatrixRename(MatrixCollection *collection, char *name_1, char *name_2); //4

void MatrixAdd(Matrix **m_sum, Matrix **m_1, Matrix **m_2, MatrixCollection *collection, char *name);  //5

void MatrixMultiply(Matrix **m_product, Matrix **m_1, Matrix **m_2, MatrixCollection *collection, char *name);  //6

void MatrixMultiplyByScalar(Matrix **m_product, Matrix **m_1, MatrixCollection *collection, char *name, void *multiplier);  //7

void LinearCombinationInitialize(Matrix **linear_combination, Matrix **matrix);

void MatrixAddLinearCombination(Matrix **m_result, int row_number, Matrix **m_1, MatrixCollection *collection, char *name, Matrix **linear_combination, void *max_number);  //8

void MatrixFree(Matrix **m);

void MatrixElementTypeCompare(Matrix **m_1, Matrix **m_2, int *response);


#endif //LAB1_RETRY_MATRIX_H

