/*
 *  jvt_rbtree.h 
 *  jvt_rbtree
 *
 *  Created by Jevstein on 2019/01/27 18:49.
 *  Copyright @ 2019year Jevstein. All rights reserved.
 *
 *  红黑树：增、删、改、查
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define JVT_RED     1
#define JVT_BLACK   2

typedef int DATA_TYPE;
typedef int KEY_TYPE;
typedef void* VALUE_TYPE;

#define JVT_RBTREE_ENTRY(NAME, TYPE)    \
    struct NAME {                       \
        unsigned char color;            \
        struct TYPE *parent;            \
        struct TYPE *left;              \
        struct TYPE *right;             \
    }                                   \

#define JVT_RBTREE_DATA(NAME, KEY, VAULE)   \
    struct NAME {                           \
        KEY key;                            \
        VAULE value;                        \
    }

typedef struct _jvt_rbtree_node {
    JVT_RBTREE_DATA(, KEY_TYPE, VALUE_TYPE);
    JVT_RBTREE_ENTRY(, _jvt_rbtree_node);
    // JVT_RBTREE_ENTRY(ready, _jvt_rbtree_node) rbt_ready;
    // JVT_RBTREE_ENTRY(defer, _jvt_rbtree_node) rbt_defer;
    // JVT_RBTREE_ENTRY(sleep, _jvt_rbtree_node) rbt_sleep;
    // JVT_RBTREE_ENTRY(wait, _jvt_rbtree_node) rbt_wait;
} jvt_rbtree_node_t;

typedef struct _jvt_rbtree {
    jvt_rbtree_node_t *root;
    jvt_rbtree_node_t *nil;
} jvt_rbtree_t;


int jvt_rbtree_init(jvt_rbtree_t* T);
int jvt_rbtree_destroy(jvt_rbtree_t* T);
jvt_rbtree_node_t* jvt_rbtree_create_node(const KEY_TYPE key, VALUE_TYPE value, int size);
jvt_rbtree_node_t* jvt_rbtree_create_node_data(const KEY_TYPE key, DATA_TYPE data);
void jvt_rbtree_destroy_node(jvt_rbtree_node_t *node);
int jvt_rbtree_rotate_l(jvt_rbtree_t *T, jvt_rbtree_node_t *node);                   //private
int jvt_rbtree_rotate_r(jvt_rbtree_t *T, jvt_rbtree_node_t *node);                   //private
int jvt_rbtree_insert(jvt_rbtree_t *T, const KEY_TYPE key, const DATA_TYPE data);    //增
int jvt_rbtree_delete(jvt_rbtree_t *T, const KEY_TYPE key);                          //删
int jvt_rbtree_update(jvt_rbtree_t *T, const KEY_TYPE key, const DATA_TYPE data);    //改
jvt_rbtree_node_t* jvt_rbtree_search(jvt_rbtree_t *T, const KEY_TYPE key);           //查
int jvt_rbtree_traversal(jvt_rbtree_node_t *node);


int jvt_rbtree_init(jvt_rbtree_t* T) {
    assert(T);

    T->root = NULL;
    T->nil = NULL;

    return 0;
}

int jvt_rbtree_destroy(jvt_rbtree_t* T) {
    assert(T);

    return 0;
}

jvt_rbtree_node_t* jvt_rbtree_create_node(const KEY_TYPE key, VALUE_TYPE value, int size) {
    jvt_rbtree_node_t *node = (jvt_rbtree_node_t *)calloc(1, sizeof(jvt_rbtree_node_t));
    assert(node);

    node->value = (VALUE_TYPE)(calloc(1, size));
    assert(node->value);

    node->key = key;
    memcpy(node->value, value, size);
    node->color = JVT_RED;
    node->parent = node->left = node->right = NULL;

    return node;
}

jvt_rbtree_node_t* jvt_rbtree_create_node_data(const KEY_TYPE key, DATA_TYPE data) {
    jvt_rbtree_node_t *node = (jvt_rbtree_node_t *)calloc(1, sizeof(jvt_rbtree_node_t));
    assert(node);

    node->value = (VALUE_TYPE)(calloc(1, sizeof(DATA_TYPE)));
    assert(node->value);

    node->key = key;
    *(DATA_TYPE *)node->value = data;
    node->color = JVT_RED;
    node->parent = node->left = node->right = NULL;

    return node;
}

void jvt_rbtree_destroy_node(jvt_rbtree_node_t *node) {
    if (!node)
        return;

    if (node->value) free(node->value);

    node->key = 0;
    node->value = NULL;
    node->color = JVT_RED;
    node->parent = node->left = node->right = NULL;

    free(node);
}

int jvt_rbtree_rotate_l(jvt_rbtree_t *T, jvt_rbtree_node_t *x) {
    assert(T);
    assert(x);

    //无论左旋还是右旋，修改3个节点的方向，共6个指针变量
    //以x为支点左旋:

    jvt_rbtree_node_t *y = x->right;

    // I.y->left
    x->right = y->left;//1.
    if (y->left != T->nil) y->left->parent = x; //2.

    // II.y
    y->parent = x->parent;//3.
    if (x->parent == T->nil)        T->root = y;        //4.
    else if (x == x->parent->left)  x->parent->left = y;
    else                            x->parent->right = y;

    // III.x
    y->left = x;//5.
    x->parent = y;//6.

    return 0;
}

int jvt_rbtree_rotate_r(jvt_rbtree_t *T, jvt_rbtree_node_t *y){
    assert(T);
    assert(y);

    //无论左旋还是右旋，修改3个节点的方向，共6个指针变量
    //以y为支点右旋，与jvt_rbtree_rotate_l对应，调整如下:
    // left --> right
    // right --> left
    // x --> y
    // y --> x

    jvt_rbtree_node_t *x = y->left;

    // I.x->right
    y->left = x->right;//1.
    if (x->right != T->nil) x->right->parent = y;//2.

    // II.x
    x->parent = y->parent;//3.
    if (y->parent == T->nil)        T->root = x;//4. 
    else if (y == y->parent->left)  y->parent->left = x;
    else                            y->parent->right = y;

    // III.y
    x->right = y;//5.
    y->parent = x;//6.

    return 0;
}

int jvt_rbtree_insert(jvt_rbtree_t *T, const KEY_TYPE key, const DATA_TYPE data) {
    assert(T);

    jvt_rbtree_node_t *node = jvt_rbtree_create_node_data(key, data);
    assert(node);

    jvt_rbtree_node_t *p = T->root;
    jvt_rbtree_node_t *parent = T->nil;//当前节点的"父节点"
    jvt_rbtree_node_t *uncle = T->nil;//当前节点的"叔节点"

    // I.将节点挂载到树上
    while (p != T->nil) {
        if (key == p->key)
            return -1;

        parent = p;
        p = (key < p->key) ? p->left : p->right;
    }

    node->parent = parent;

    if (parent == T->nil) {//根节点为空
        T->root = node;
        node->color = JVT_BLACK;
        return 0;
    }

    if (key < parent->key) parent->left = node;
    else                   parent->right = node;

    // II.无需调整
    if (parent->color == JVT_BLACK)
    {//当前节点的“父节点”是黑色: 将当前节点直接挂在“父节点”上即可
        return 0;
    }

    // III.调整红黑树 - 当前节点的“父节点”是红色 
    do {
        parent = node->parent;
        if (parent == T->nil) {
            node->color = JVT_BLACK;
            break;
        }

        uncle = (parent->left == node) ? parent->right : parent->left;
        if (uncle == T->nil || uncle->color == JVT_BLACK)
        {//“叔节点”是黑色
            if (node == parent->right) 
            {//1.当前节点的"父节点"是红色，"叔节点"是黑色，且当前节点是其"父节点"的"右孩子"
                // (01) 将“父节点”设为“黑色”
                // (02) 将“祖父节点”设为“红色”
                // (03) 以“祖父节点”为支点进行左旋
                parent->color = JVT_BLACK;
                parent->parent->color = JVT_RED;
                jvt_rbtree_rotate_l(T, parent->parent);
                break;
            } else {//2.当前节点的"父节点"是红色，"叔节点"是黑色，且当前节点是其"父节点"的"左孩子"
                //(01) 将“父节点”作为“新的当前节点”
                //(02) 以“新的当前节点”为支点进行右旋
                node = parent;
                jvt_rbtree_rotate_r(T, node);
            }
        } else {//3.“叔节点”是红色
            // (01) 将“父节点”设为黑色
            // (02) 将“叔叔节点”设为黑色
            // (03) 将“祖父节点”设为“红色
            // (04) 将“祖父节点”设为“当前节点”(红色节点)；即，之后继续对“当前节点”进行操作

            parent->color = JVT_BLACK;
            uncle->color = JVT_BLACK;
            parent->parent->color = JVT_RED;
            node = parent->parent;
        }
    } while(1);

    return 0;
}

jvt_rbtree_node_t* jvt_rbtree_search(jvt_rbtree_t *T, const KEY_TYPE key) {
    assert(T);

    jvt_rbtree_node_t* node = T->root;

    while (node) {
        if (key == node->key)
            return node;

        node = (key < node->key) ? node->left : node->right;
    }

    return NULL;
}

int jvt_rbtree_traversal(jvt_rbtree_node_t *node) {
    if (!node)
        return -1;

    jvt_rbtree_traversal(node->left);
    // printf("node: [%d][%p][%p][%p][%d][%d]\n", node->color, node->parent, node->left, node->right, node->key, *(DATA_TYPE*)node->value);
    // printf("{[%d][%p][%p][%p][%d][%d]} ", node->color, node->parent, node->left, node->right, node->key, *(DATA_TYPE*)node->value);
    // printf("[%d][%d] ", node->key, *(DATA_TYPE*)node->value);
    printf("%d ", node->key);
    jvt_rbtree_traversal(node->right);

    return 0;
}


#define ARRAY_LENGTH 10

int main () {
    KEY_TYPE data_array[ARRAY_LENGTH] = {23, 45, 56, 32, 41, 90, 21, 43, 87, 76};

    jvt_rbtree_t T = {0};
    int i = 0;
    // DATA_TYPE data = 0;
    KEY_TYPE key = 0;
    DATA_TYPE value = 0;
    jvt_rbtree_node_t *node = NULL;

    // 增
    printf("========= initialize =========\n");
    jvt_rbtree_init(&T);

    // 增
    printf("========= insert =========\n");
    for (i = 0; i < ARRAY_LENGTH; ++i) {
        key = data_array[i];
        value = key * 10;
        printf("insert[%d][%d][%d]: ", i, key, value);
        jvt_rbtree_insert(&T, key, value);
        jvt_rbtree_traversal(T.root);
        printf("\n");
    }
    // jvt_rbtree_traversal(T.root);
    // printf("\n");

    // // 改
    // printf("========= update =========\n");
    // for (i = 0; i < ARRAY_LENGTH; ++i) {
    //     data = (i % 2 == 0) ? data_array[i] + 10 : data_array[i] - 10;
    //     printf("update[%d][%d->%d]: ", i, data_array[i], data);
    //     jvt_bstree_update(&T, data_array[i], data);
    //     jvt_bstree_traversal(T.root);
    //     printf("\n");
    //     data_array[i] = data;
    // }

    // 查
    printf("========= search =========\n");
    key = 20;
    for (i = -1; i < ARRAY_LENGTH; ++i) {
        if ( i != -1)
            key = data_array[i];

        node = jvt_rbtree_search(&T, key);
        if (node)
            printf("find: [%d][%p][%p][%p][%d][%d]\n", node->color, node->parent, node->left, node->right, node->key, *(DATA_TYPE*)node->value);
        else
            printf("failed to find [%d] from bstree!\n", key);
    }

    // // 删
    // printf("========= delete =========\n");
    // for (i = 0; i < ARRAY_LENGTH; ++i) {
    //     printf("delete[%d][%d]: ", i, data_array[i]);
    //     jvt_bstree_delete(&T, data_array[i]);
    //     jvt_bstree_traversal(T.root);
    //     printf("\n");
    // }

    printf("========= the end =========\n");
    printf("T.root: %p\n", T.root);

    return 0;
}