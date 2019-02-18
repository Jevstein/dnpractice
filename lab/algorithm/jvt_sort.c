/*
 *  jvt_sort.c 
 *  jvt_sort
 *
 *  Created by Jevstein on 2019/01/27 11:36.
 *  Copyright @ 2019year Jevstein. All rights reserved.
 *
 *  排序
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "jvt_algorithm.h"
#include "sort/jvt_sort.h"

int data__[] = { 99, 62, 85, 62, 40, 36, 89, 72, 23, 19, 64, 80, 26, 84, 47, 83, 79, 94, 86, 99,
                 43, 54, 20, 10, 34, 20, 65, 91, 55, 38, 42,  5, 51, 27, 18, 90, 14, 58, 15, 89,
                 77, 77, 68, 54, 12, 66, 88, 91, 59, 83,  9, 21, 98, 45, 06,  3, 88, 39, 95, 96,
               };

void init_datas(jvt_datas_t *datas);
void reset_datas(jvt_datas_t *datas);
void print_datas(jvt_datas_t *datas);


void init_datas(jvt_datas_t *datas) {
    datas->size = sizeof(data__) / sizeof(int);
    datas->data = (int *)calloc(1, datas->size * sizeof(int));
}

void reset_datas(jvt_datas_t *datas) {
    memcpy(datas->data, data__, sizeof(data__));
    print_datas(datas);
}

void print_datas(jvt_datas_t *datas) {
    printf("\n");

    int i;
    for (i = 0; i < datas->size; i++) {

        printf(" %d %s", datas->data[i], (i > 0 && i % 20 == 0) ? "\n" : "");
    }

    printf("\n");
}

#define _JVT_CALL_(s, func, d) {    \
    printf("\n{title: %s", s);      \
    reset_datas(d);                 \
    func(d);                        \
    print_datas(d);                 \
    printf("}time: %dms\n", 123);   \
}

int main()
{
    jvt_datas_t D;
    init_datas(&D);

    printf("========= sort =========\n");
    // reset_datas(&D);
    // jvt_easy_insertion_sort(&D);     
    // print_datas(&D);

    printf("简单直接插入排序\n");
    _JVT_CALL_("简单直接插入排序", jvt_easy_insertion_sort, &D);
    _JVT_CALL_("高级直接插入排序", jvt_enhanced_insertion_sort, &D);

    printf("========= the end =========\n");

    return 0;
}