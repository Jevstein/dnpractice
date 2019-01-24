
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef int KEY_TYPE;

// key与左右子树分离
#define BSTREE_ENTRY(name, type)\
struct name {                   \
    struct type* left;          \
    struct type* right;         \
}

// 节点
struct bstree_node {
    KEY_TYPE data;

    BSTREE_ENTRY(, bstree_node);
    // BSTREE_ENTRY(Next, bstree_node) next;
};

// 树
struct bstree {
    struct bstree_node *root;
};

struct bstree_node* bstree_create_node(KEY_TYPE data);
void bstree_destroy_node(struct bstree_node* node);
int bstree_traversal(struct bstree_node *node);
int bstree_insert(struct bstree *T, KEY_TYPE data);                 //增
int bstree_delete(struct bstree *T, KEY_TYPE data);                 //删: 会删除整棵子树
void bstree_delete(struct bstree_node *node);                       //删: 递归删除整棵子树
int bstree_update(struct bstree *T, KEY_TYPE src, KEY_TYPE dest);   //改: 将不再有序了
struct bstree_node* bstree_find(struct bstree *T, KEY_TYPE data);   //查

struct bstree_node* bstree_create_node(KEY_TYPE data) {
    struct bstree_node* node = (struct bstree_node*)calloc(1, sizeof(struct bstree_node));
    assert(node != 0);//若连分配内存不成功，其它一定也可能出现异常，此时最适合用断言

    node->data = data;
    node->left = node->right = NULL;
    return node;
}

void bstree_destroy_node(struct bstree_node* node){
    if (node == NULL) return;

    node->left = node->right = NULL;
    free(node);
}

int bstree_traversal(struct bstree_node *node) {
    if (node == NULL) return 0;

	// printf("%4d", node->data);//置此：前序遍历
    bstree_traversal(node->left);
	printf("%4d", node->data);//置此：中序遍历
	bstree_traversal(node->right);
	// printf("%4d", node->data);//置此：后序遍历

    return 0;
}

int bstree_insert(struct bstree *T, KEY_TYPE data){
    assert(T != NULL);

    if (T->root == NULL) {
        T->root = bstree_create_node(data);
        return 0;
    }

    struct bstree_node* node = T->root;
    struct bstree_node* p = T->root;

    while (p != NULL) {
        node = p;

        if (data < p->data)
            p = p->left;
        else 
            p = p->right;
    }

    if (data < node->data)
        node->left = bstree_create_node(data);
    else 
        node->right = bstree_create_node(data);

    
    return 0;
}

void bstree_delete(struct bstree_node *node) {
    if (node == NULL) return;

    struct bstree_node** temp = &node;

    if (node->left == NULL && node->right == NULL) {//叶子节点
        bstree_destroy_node(node);
    } else if (node->left == NULL) {//左子树为空，重接右子树
        *temp = node->right;
        bstree_destroy_node(node);
    } else if (node->right == NULL) {//右子树为空，重接左子树
        *temp = node->left;
        bstree_destroy_node(node);
    } else {//左右子树都不为空
        printf("| not null{");
        bstree_traversal(node);
        printf("}");
    }
}

int bstree_delete(struct bstree *T, KEY_TYPE data) {
    assert(T != NULL);

    struct bstree_node* node = bstree_find(T, data);
    if (node == NULL) return -1;

    bstree_delete(node);

    return 0;
}

int bstree_update(struct bstree *T, KEY_TYPE src, KEY_TYPE dest) {
    struct bstree_node* node = bstree_find(T, src);
    if (node == NULL) return -1;

    node->data = dest;

    return 0;
}

struct bstree_node* bstree_find(struct bstree *T, KEY_TYPE data){
    assert(T != NULL);

    struct bstree_node* node = T->root;
    
    while (node != NULL) {
        if (node->data == data)
            return node;

        if (data < node->data)
            node = node->left;
        else
            node = node->right;    
    }

    return NULL;
}

#define ARRAY_LENGTH 10

int main () {
    KEY_TYPE data_array[ARRAY_LENGTH] = {23, 45, 56, 32, 41, 90, 21, 43, 87, 76};

    struct bstree T = {0};
    int i = 0;

    // 增
    for (i = 0; i < ARRAY_LENGTH; ++i) {
        bstree_insert(&T, data_array[i]);
    }
    bstree_traversal(T.root);
    printf("\n");

    // // 改
    // bstree_update(&T, 41, 51);
    // bstree_traversal(T.root);
    // printf("\n");

    // 删
    bstree_delete(&T, 43);
    bstree_traversal(T.root);
    printf("\n");

    // 查

}