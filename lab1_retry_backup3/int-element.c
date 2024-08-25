#include <stdio.h>
#include <stdlib.h>

#include "int-element.h"


void IntAdd(void *sum, void* a, void* b) {
    *(int*)sum = *(int*)a + *(int*)b;
}

void IntMultiply(void *product, void* a, void* b) {
    *(int*)product = (*(int*)a * *(int*)b);
}

void IntPrint(void *element) {
    printf("%3d ", *(int*)element);
}

void IntScan(void *element) {
    scanf("%d", element);
}

void IntRandom(void *element, void *max_int_number) {

    int random_int;

    for (int k=0; k < 5; k++){
        random_int = rand()/(RAND_MAX/(*(int*)max_int_number));
    }
    *(int*)element = random_int;
}

static FieldInfo *int_field_info = NULL;

FieldInfo *GetIntFieldInfo(){
    if(int_field_info == NULL){
        int_field_info = (FieldInfo*)malloc(sizeof(FieldInfo));
        int_field_info->type_name = "int";
        int_field_info->element_size = sizeof(int*);

        int_field_info->m_addition = IntAdd;
        int_field_info->m_multiplication = IntMultiply;
        int_field_info->m_print = IntPrint;
        int_field_info->m_scan = IntScan;
        int_field_info->m_random = IntRandom;
    }
    return int_field_info;
}