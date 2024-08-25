#ifndef LAB1_RETRY_FIELDINFO_H
#define LAB1_RETRY_FIELDINFO_H

typedef void (*ElementAddition)(void *sum, void *a, void *b), (*ElementMultiplication)(void *product, void *a, void *b);
typedef void (*ElementPrint)(void *element), (*ElementScan)(void *element), (*ElementRandom)(void *element, void *max_number);


typedef struct{
    char *type_name;                             //Название типа элемента
    size_t element_size;                         //Размер 1 элемента

    ElementAddition m_addition;                  //Сумма элементов матрицы
    ElementMultiplication m_multiplication;      //Произведение элементов матрицы
    ElementPrint m_print;                        //Вывод элементов матрицы
    ElementScan m_scan;                          //Ввод элементов матрицы
    ElementRandom m_random;                      //Присваивание случайного значения элементу матрицы
}FieldInfo;


#endif //LAB1_RETRY_FIELDINFO_H
