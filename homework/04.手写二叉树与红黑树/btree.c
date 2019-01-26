
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
int bstree_delete(struct bstree *T, KEY_TYPE data);                 //删
int bstree_update(struct bstree *T, KEY_TYPE src, KEY_TYPE dest);   //改
struct bstree_node* bstree_find(struct bstree *T, KEY_TYPE data);   //查

struct bstree_node* bstree_create_node(KEY_TYPE data) {
    struct bstree_node* node = (struct bstree_node*)calloc(1, sizeof(struct bstree_node));
    assert(node);//若连分配内存不成功，其它一定也可能出现异常，此时最适合用断言

    node->data = data;
    node->left = node->right = NULL;
    return node;
}

void bstree_destroy_node(struct bstree_node* node){
    if (!node)
        return;

    node->left = node->right = NULL;
    free(node);
}

int bstree_traversal(struct bstree_node *node) {
    if (!node)
        return 0;

	// printf("%4d", node->data);//置此：前序遍历
    bstree_traversal(node->left);
	printf("%4d", node->data);//置此：中序遍历
	bstree_traversal(node->right);
	// printf("%4d", node->data);//置此：后序遍历

    return 0;
}

int bstree_insert(struct bstree *T, KEY_TYPE data){
    assert(T);

    if (!T->root) {
        T->root = bstree_create_node(data);
        return 0;
    }

    struct bstree_node* parrent = T->root;
    struct bstree_node* p = T->root;

    while (p) {
        parrent = p;

        if (data < p->data)
            p = p->left;
        else 
            p = p->right;
    }

    if (data < parrent->data)
        parrent->left = bstree_create_node(data);
    else 
        parrent->right = bstree_create_node(data);

    return 0;
}

int bstree_delete(struct bstree *T, KEY_TYPE data) {
    assert(T);

    struct bstree_node* p = T->root;
    struct bstree_node* temp = NULL;
    struct bstree_node* parent = NULL;
    struct bstree_node* node = NULL;

    // 找出待删节点, 和它的父节点
    while(p) {
        if (data == p->data) {
            node = p;
            break;
        }

        parent = p;
        if (data < p->data)
            p = p->left;
        else 
            p = p->right;
    }

    if (!node)
        return -1;

    if (!node->left && !node->right) {//叶子节点
        if (!parent)
            T->root = NULL;
        else {
            if (parent->left == node)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
    } else if (!node->left) {//左子树为空，重接右子树
        if (!parent)
            T->root = node->right;
        else {
            if (parent->left == node)
                parent->left = node->right;
            else
                parent->right = node->right;
        }
    } else if (!node->right) {//右子树为空，重接左子树
        if (!parent)
            T->root = node->left;
        else {
            if (parent->left == node)
                parent->left = node->left;
            else
                parent->right = node->left;
        }
    } else {//左右子树都不为空
        // 此时分为3步：
        // 1.找出右子树中最小节点p（即：右子树最左的子节点）
        // 2.将找出的节点“覆盖”到待删节点位置
        // 3.删除待删节点
        p = node->right;
        while (p) {
            if (!p->left) 
                break;

            temp = p;
            p = p->left;
        }

        p->left = node->left;
        if (temp) {//p的父节点
            temp->left = p->right;
            p->right = node->right;
        }

        if (!parent) {
            T->root = p;
        } else {
            if (parent->left == node)
                parent->left = p;
            else
                parent->right = p;
        }
    }
    
    bstree_destroy_node(node);

    return 0;
}

int bstree_update(struct bstree *T, KEY_TYPE src, KEY_TYPE dest) {
    // struct bstree_node* node = bstree_find(T, src);
    // if (!node)
    //  return -1;

    // node->data = dest;

    


    return 0;
}

struct bstree_node* bstree_find(struct bstree *T, KEY_TYPE data){
    assert(T);

    struct bstree_node* node = T->root;
    
    while (node) {
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
    bstree_delete(&T, 23);
    bstree_traversal(T.root);
    printf("\n");

    // 查

}