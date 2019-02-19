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
#include <sys/time.h>

#include "jvt_algorithm.h"
#include "sort/jvt_sort.h"

#define MAX_LEVEL 3
enum ELEVEL {
    L1 = 0,
    L2,
    L3,
};

char space__[MAX_LEVEL][32] = {
      ""
    , "  "
    , "      "};

int data__[] = { 99, 62, 85, 62, 40, 36, 89, 72, 23, 19, 64, 80, 26, 84, 47, 83, 79, 94, 86, 99,
                 43, 54, 20, 10, 34, 20, 65, 91, 55, 38, 42,  5, 51, 27, 18, 90, 14, 58, 15, 89,
                 77, 77, 68, 54, 12, 66, 88, 91, 59, 83,  9, 21, 98, 45, 06,  3, 88, 39, 95, 96,
               };

typedef struct _jvt_sort {
    jvt_datas_t datas;
    int levels[MAX_LEVEL];
} jvt_sort_t;


void jvt_sort_init(jvt_sort_t *obj);
void jvt_sort_reset(jvt_sort_t *obj);
void jvt_sort_print(jvt_sort_t *obj);
void jvt_sort_title(jvt_sort_t *obj, const char *title);


void jvt_sort_init(jvt_sort_t *obj) {
    assert(obj);
    obj->datas.size = sizeof(data__) / sizeof(data__[0]);
    obj->datas.data = (int *)calloc(1, obj->datas.size * sizeof(int));
    memset(obj->levels, 0, sizeof(obj->levels));
}

void jvt_sort_reset(jvt_sort_t *obj) {
    assert(obj);
    memcpy(obj->datas.data, data__, sizeof(data__));
}

void jvt_sort_print(jvt_sort_t *obj) {
    assert(obj);
    int l=L3;
    printf("\n%s", space__[l]);

    int i;
    for (i = 0; i < obj->datas.size; i++) {
        printf("%d %s%s", obj->datas.data[i]
        , (i > 0 && i % 30 == 0) ? "\n" : ""
        , (i > 0 && i % 30 == 0) ? space__[l] : "");
    }

    printf("\n");
}

void jvt_sort_title(jvt_sort_t *obj, const char *title) {
    int l = L1;
    printf("%s⭐️%d.%s\n", space__[l], ++obj->levels[l], title);
    obj->levels[l+1] = 0;
}
  
#define _JVT_TITLE_(s, o) {                         \
    jvt_sort_title(o, s);                           \
}

#define _JVT_CALL_(s, func, o) {                    \
    int l = L2;                                     \
    printf("%s>%d.%d.%s:\n%s{", space__[l], (o)->levels[l-1], ++(o)->levels[l], s, space__[l]);\
    jvt_sort_reset(o);                              \
    /*jvt_sort_print(o);*/                          \
	struct timeval tv1;                             \
	struct timeval tv2;                             \
	gettimeofday(&tv1, NULL);                       \
    func(&(o)->datas);                              \
	gettimeofday(&tv2, NULL);                       \
	int cost = (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec);\
    jvt_sort_print(o);                              \
    printf("%s} cost: %d(us)\n\n", space__[l], cost); \
}



int main()
{
    jvt_sort_t obj;
    jvt_sort_init(&obj);

    printf("========= sort =========\n");

    _JVT_TITLE_("插入排序", &obj);
    {
        _JVT_TITLE_("直接插入排序", &obj);
        {
            _JVT_CALL_("简单", jvt_easy_insertion_sort, &obj);
            _JVT_CALL_("高级", jvt_enhanced_insertion_sort, &obj);
        }

        _JVT_TITLE_("折半插入排序(二分插入)", &obj);
        {
            _JVT_CALL_("简单", jvt_easy_insertion_sort, &obj);
            _JVT_CALL_("高级", jvt_enhanced_insertion_sort, &obj);
        }
    }

    _JVT_TITLE_("直接插入排序", &obj);
    _JVT_CALL_("简单", jvt_easy_insertion_sort, &obj);
    _JVT_CALL_("高级", jvt_enhanced_insertion_sort, &obj);

    printf("========= the end =========\n");

    return 0;
}