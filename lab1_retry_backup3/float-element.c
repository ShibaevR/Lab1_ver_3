#include <stdio.h>
#include <stdlib.h>

#include "float-element.h"


void FloatAdd(void *sum, void* a, void* b){
    *(float*)sum = *(float*)a + *(float*)b;
}

void FloatMultiply(void *product, void* a, void* b){
    *(float*)product = *(float*)a * *(float*)b;
}

void FloatPrint(void *element){
    printf("%11f ", *(float*)element);
}

void FloatScan(void *element){
    scanf("%f ", element);
}

void FloatRandom(void *element, void *max_float_number){
    float random_float;

    for (int k=0; k < 5; k++){
        random_float = (float)rand()/((float)RAND_MAX/(*(float*)max_float_number));
    }
    *(float*)element = random_float;
}


static FieldInfo *float_field_info = NULL;

FieldInfo *GetFloatFieldInfo(){
    if(float_field_info == NULL){
        float_field_info = (FieldInfo*)malloc(sizeof(FieldInfo));
        float_field_info->type_name = "float";
        float_field_info->element_size = sizeof(float*);

        float_field_info->m_addition = FloatAdd;
        float_field_info->m_multiplication = FloatMultiply;
        float_field_info->m_print = FloatPrint;
        float_field_info->m_scan = FloatScan;
        float_field_info->m_random = FloatRandom;
    }
    return float_field_info;
}
