/*
 *  jvt_b-tree.h 
 *  jvt_b-tree
 *
 *  Created by Jevstein on 2019/01/30 6:59.
 *  Copyright @ 2019year Jevstein. All rights reserved.
 *
 *  B-树：增、删、改、查
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define JVT_DEGREE 3
typedef int KEY_VALUE;

typedef struct _jvt_btree_node {
    KEY_VALUE *keys;
    struct _jvt_btree_node* children;
    int num;
    int leaf;
} jvt_btree_node_t;

typedef struct _jvt_btree {
    jvt_btree_node_t *root;
    int t;
} jvt_btree_t;


int jvt_btree_init(jvt_btree_t *T, int t);
int jvt_btree_destroy(jvt_btree_t *T);
jvt_btree_node_t* jvt_btree_create_node(int leaf);                          //private
int jvt_btree_destroy_node(jvt_btree_node_t *node);                         //private
int jvt_btree_split_child(jvt_btree_t *T, jvt_btree_node_t *node, int idx); //private
int jvt_btree_merge_child(jvt_btree_t *T, jvt_btree_node_t *node, int idx); //private
int jvt_btree_insert(jvt_btree_t *T, KEY_VALUE key);
int jvt_btree_delete(jvt_btree_t *T, KEY_VALUE key);
int jvt_btree_modify(jvt_btree_t *T, KEY_VALUE src, KEY_VALUE dest);
int jvt_btree_search(jvt_btree_t *T, KEY_VALUE key);

int jvt_btree_init(jvt_btree_t *T, int t) {
    assert(T);

    T->root = NULL;
    T->t = t;

    return 0;
}

int jvt_btree_destroy(jvt_btree_t *T){
    return -1;
}

jvt_btree_node_t* jvt_btree_create_node(int leaf) {
    jvt_btree_node_t *node = (jvt_btree_node_t *)calloc(1, sizeof(jvt_btree_node_t));
    assert(node);

    return node;
}


#define KEY_SIZE 26

int main () {
    jvt_btree_t T;
    char keys[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // 初始化
    printf("========= 1.init =========\n");
    jvt_btree_init(&T, 3);
    printf("keys: %s\n", keys);

    printf("\n========= 2.insert =========\n");
    int i;
    for (i = 0; i < KEY_SIZE; i++) {
        printf("insert [%d]%c \n", i, keys[i]);
    }
    printf("sorry, please wait a moment for me ...\n");
    

    // printf("\n========= 6.the end =========\n");
    // printf("T.root: %p\n", T.root);

    return 0;
}