/*
 *  jvt_b-tree.h 
 *  jvt_b-tree
 *
 *  Created by Jevstein on 2019/01/30 6:59.
 *  Copyright @ 2019year Jevstein. All rights reserved.
 *
 *  [B 树]: B树的原英文名称为B-tree，事实上B-tree就是指的B树,不存在B-树。
 *  [操作]：增、删、改、查
 *  [性质]一颗M阶B树T，满足以下条件:
 *      1.每个结点至多拥有M棵子树
 *      2.根结点至少拥有两棵子树(M>=2)
 *      3.除了根结点以外，其余每个分支结点至少拥有M/2棵子树
 *      4.所有的叶结点都在同一层上
 *      5.有k棵子树的分支结点则存在k-1个关键字，关键字按照递增顺序进行排序
 *      6.关键字数量满足ceil(M/2)-1 <= n <= M-1
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define JVT_DEGREE 3        //度
#define JVT_M (2 * DEGREE)  //阶
typedef int KEY_VALUE;

typedef struct _jvt_btree_node {
    KEY_VALUE *keys;
    struct _jvt_btree_node** children;
    int num;//当前关键字的个数
    int leaf;//当前子节点的个数
} jvt_btree_node_t;

typedef struct _jvt_btree {
    jvt_btree_node_t *root;
    int t;//每个节点所包含的关键字个数有上界和下届, 用t表示B树的最小度数（即内节点中节点最小孩子数目）,t>=2
} jvt_btree_t;


int jvt_btree_init(jvt_btree_t *T, int t);
void jvt_btree_destroy(jvt_btree_t *T);
jvt_btree_node_t* jvt_btree_create_node(int t, int leaf);                       //private
void jvt_btree_destroy_node(jvt_btree_node_t *node);                            //private
void jvt_btree_split_child(jvt_btree_t *T, jvt_btree_node_t *x, int idx);       //private
void jvt_btree_merge_child(jvt_btree_t *T, jvt_btree_node_t *x, int idx);       //private
void jvt_btree_insert_nonfull(jvt_btree_t *T, jvt_btree_node_t *x, KEY_VALUE k);//private
int jvt_btree_insert(jvt_btree_t *T, KEY_VALUE key);
int jvt_btree_delete(jvt_btree_t *T, KEY_VALUE key);
int jvt_btree_modify(jvt_btree_t *T, KEY_VALUE src, KEY_VALUE dest);
int jvt_btree_search(jvt_btree_t *T, KEY_VALUE key);

int jvt_btree_init(jvt_btree_t *T, int t) {
    assert(T);

    T->t = t;
	T->root = jvt_btree_create_node(t, 1);
    assert(T->root);

    return 0;
}

void jvt_btree_destroy(jvt_btree_t *T) {

}

jvt_btree_node_t* jvt_btree_create_node(int t, int leaf) {
    jvt_btree_node_t *node = (jvt_btree_node_t *)calloc(1, sizeof(jvt_btree_node_t));
    assert(node);

	node->leaf = leaf;
	node->keys = (KEY_VALUE *)calloc(1, (2 * t - 1) * sizeof(KEY_VALUE));
	node->children = (jvt_btree_node_t **)calloc(1, (2 * t) * sizeof(jvt_btree_node_t));
	node->num = 0;

    return node;
}

void jvt_btree_destroy_node(jvt_btree_node_t *node){
    if (!node)
        return;

    if (node->keys) free(node->keys);
    if (node->children) free(node->children);

    node->leaf = 0;
    node->keys = NULL;
    node->children = NULL;
    node->num = 0;

    free(node);
}

void jvt_btree_split_child(jvt_btree_t *T, jvt_btree_node_t *x, int idx) {
    int t = T->t;

    jvt_btree_node_t *y = x->children[idx];
    jvt_btree_node_t *z = jvt_btree_create_node(t, y->leaf);

	z->num = t - 1;
}


// int jvt_btree_insert(jvt_btree_t *T, KEY_VALUE key) {
//     assert(T);
    
//     jvt_btree_node_t *p = T->root;
//     if (p->num == (2 * T->t - 1)) {
//         jvt_btree_node_t *node = jvt_btree_create_node(T->t, 0);
//         T->root = node;

//         node->children[0] = p;
        
// 		jvt_btree_split_child(T, node, 0);

// 		int i = 0;
// 		if (node->keys[0] < key)
//             i++;
// 		jvt_btree_insert_nonfull(T, node->children[i], key);
//     } else {
//         jvt_btree_insert_nonfull(T, p, key);
//     }

//     return 0;
// }


#define KEY_SIZE 26

int main () {
    jvt_btree_t T;
    char keys[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	srand(48);

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