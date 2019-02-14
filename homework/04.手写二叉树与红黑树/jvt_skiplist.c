/*
 *  jvt_skiplist.h 
 *  jvt_skiplist
 *
 *  Created by Jevstein on 2019/02/14 10:58.
 *  Copyright @ 2019year Jevstein. All rights reserved.
 *
 *  跳跃表：
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// #define JVT_MAX_SKLEVLE 6

typedef int KEY_TYPE;

/*
#define JVT_SKNODE_ENTRY(name, type)\
struct name {                       \
    struct type* next;              \
    struct type* down;              \
}                                   \

typedef struct _jvt_sknode
{
    KEY_TYPE key;
    JVT_SKNODE_ENTRY(, _jvt_sknode);
} jvt_sknode_t;

typedef struct _jvt_skiplist
{
    jvt_sknode_t **heads;
    int max_level;
    int level;
} jvt_skiplist_t;
*/

#define JVT_SKNODE_ENTRY(name, type)\
struct name {                       \
    struct type** forwards;         \
}                                   \

typedef struct _jvt_sknode
{
    KEY_TYPE key;
    JVT_SKNODE_ENTRY(, _jvt_sknode);
} jvt_sknode_t;

typedef struct _jvt_skiplist
{
    jvt_sknode_t *nil;  //此处表示+∞
    jvt_sknode_t *head;
    // jvt_sknode_t *tail;
    // int count;          //节点个数
    int level;          //当前最大维度, 从1开始
    // int max_level;      //最大维度: log(n)/log(2)
}jvt_skiplist_t;


int jvt_skiplist_init(jvt_skiplist_t *L, int max_level);
void jvt_skiplist_destroy(jvt_skiplist_t *L);
int jvt_skiplist_insert(jvt_skiplist_t *L, KEY_TYPE key);                   //增
int jvt_skiplist_delete(jvt_skiplist_t *L, KEY_TYPE key);                   //删
int jvt_skiplist_update(jvt_skiplist_t *L, KEY_TYPE src, KEY_TYPE dest);    //改
jvt_sknode_t* jvt_skiplist_search(jvt_skiplist_t *L, KEY_TYPE key);         //查
int jvt_skiplist_random_level();                                            //private
void jvt_skiplist_print(jvt_skiplist_t *L);
int jvt_skiplist_traversal(jvt_skiplist_t *L);


int jvt_skiplist_init(jvt_skiplist_t *L, int max_level)
{
    assert(L);
    assert(max_level > 0);

    // L->head = (jvt_sknode_t*)calloc(1, sizeof(jvt_skiplist_t));
    // assert(L->head);

    L->head = NULL;
    // L->tail = NULL;
    L->nil = NULL;
    L->level = 0;

    return 0;
}

void jvt_skiplist_destroy(jvt_skiplist_t *L)
{
    if (!L)
        return;
}

jvt_sknode_t* jvt_skiplist_search(jvt_skiplist_t *L, KEY_TYPE key)
{
    assert(L);

    jvt_sknode_t *p = L->head;
    if (!p)
        return NULL;
        
    int i;
    for (i=L->level; i>=0; i--) {//从高到低，遍历每个维度
        if (p->key == key)
            return p;

        while (p->forwards[i] && (p->forwards[i]->key < key)) {//同维度往后，找到第一个大于key的节点的前一个节点p
            p = p->forwards[i];
        }
    }

    return NULL;
}

int jvt_skiplist_insert(jvt_skiplist_t *L, KEY_TYPE key)
{
    assert(L);

    int level = jvt_skiplist_random_level(L->level);

    // 新建一个节点
    jvt_sknode_t *node = (jvt_sknode_t *)calloc(1, sizeof(jvt_sknode_t));
    assert(node);
    node->forwards = (jvt_sknode_t**)calloc(1, (level + 1) * sizeof(jvt_sknode_t));
    assert(node->forwards);
    node->forwards[level] = L->nil;
    node->key = key;
    
    jvt_sknode_t **update_nodes;//记录搜索过程中在各层走过的最大的结点位置
    jvt_sknode_t *p = L->head;
    if (!p) {
        L->level = level;
        L->head = node;
    } else {
        if (L->level < level) {
            L->level = level;
            L->head->forwards = (jvt_sknode_t **)realloc(L->head->forwards, L->level * sizeof(jvt_sknode_t));
            assert(L->head->forwards);
            L->head->forwards[level] = L->nil;
        }

        update_nodes = (jvt_sknode_t**)calloc(1, L->level * sizeof(jvt_sknode_t));
        assert(update_nodes);

        // 查找待插入的合适位置
        int i = 0;
        for (i=L->level; i>=0; i--) {//从高到低，遍历每个维度
            while (p->forwards[i] && (p->forwards[i]->key < key)) {//同维度往后，找到第一个大于key的节点的前一个节点p
                p = p->forwards[i];
            }

            update_nodes[i]=p;//update_nodes[i]记录了搜索过程中在各层中走过的最大的结点位置
        }

        // 在合适位置插入
        for (i=0; i<L->level; i++) {
            p->forwards[i] = update_nodes[i]->forwards[i];
            update_nodes[i]->forwards[i] = p;
        }

        free(update_nodes);
    }

    return 0;
}

int jvt_skiplist_random_level(int level)
{
    // "投硬币"：每次投到正面，都向上跃一个维度
    int k = 1;
    while (k <= level && (rand() % 2 == 0)) {
        k++;
    }

    return k;
}


int main () {
    KEY_TYPE data_array[] = {23, 45, 56, 32, 41, 90, 21, 43, 87, 76};
    int data_size = sizeof(data_array) / sizeof(KEY_TYPE);

    int i;

    // 初始化
    printf("========= 1.init =========\n");
    printf("data{%d}: ", data_size);
    for(i = 0; i < data_size; i++)
    {
        printf("%d ", data_array[i]);
    }
    printf("\n");

    // printf("text: '%s'\n", text);
    // for( k = 0; k < sizeof(patterns) / 20; k++)
    // {
    //     printf("pattern[%d]: '%s'\n", k, patterns[k]);
    // }
    
    // 增
    printf("\n========= 2.insert =========\n");
    

    printf("\n========= 4.the end =========\n");
    printf("perfect!\n");


    return 0;
}