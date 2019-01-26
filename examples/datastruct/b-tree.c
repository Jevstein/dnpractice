#define DEGREE 3
#define M (2 * DEGREE)


typedef int KEY_TYPE;

typedef struct _btree_node {
    KEY_TYPE *keys;
    struct _btree_node **childrens;

    short num;
    short leaf;//是不是叶子节点
} btree_node;

typedef struct _btree {
    btree_node *root;
    int degree;
} btree;

btree_node* btree_create_node(int degree, int leaf) {
    btree_node* node = calloc(1, sizeof(btree_node));
    accert(node != NULL);

    node->leaf = leaf;
    node->keys = (KEY_TYPE *)calloc(1, (M -1) * sizeof(KEY_TYPE));
    accert(node != NULL);

    node->childrens = (btree_node**)calloc(M, sizeof(btree_node *));
    accert(node->childrens != NULL);
    node->num = 0;
}

void btree_destroy_node(btree_node *node) {
    accert(node);

    free(node->childrens);
    free(node->keys);
    free(node);
}

void btree_create(btree *T, int degree) {
    accert(T);

    T->degree = degree;
    T->root = btree_create_node(degree, 1);
}

void btree_split_child(btree *T, btree_node *x, int idx) {
    int degree = T->degree;
    btree_node *y = x->childrens[idx];
    btree_node *z = btree_create_node(degree, y->leaf);

    z->num = degree - 1;

    int j = 0;
    for (j = 0; j< degree; j++) {
        z->keys[j] = y->keys[j+degree];
    }

    if (y->leaf == 0) {
        for (j = 0; j< degree; j++) {
            z->childrens[j] = y->childrens[j+degree];
        }
    }

    y->num = degree - 1;

    for (j = x->num; j >= idx + 1; j--) {
        x->childrens[j+1] = x->childrens[j];
    }

    x->childrens[idx+1] = z;

    for (j = x->num-1; j >= idx; j--) {
        x->keys[j+1] = x->childrens[j];
    }

    x->keys[idx] = y->keys[degree-1];
    x->num += 1;
}

//insert --> split
// childres --> 2*degree
// keys--> 2*degree -1
void btree_insert(btree *T, KEY_TYPE key) {
    btree_node *root = T->root;

    if (root->num == M - 1) {//根节点满了
        btree_node *node = btree_create_node(T->root, 0);

        T->root = node;
        node->childrens[0] = root;

    }
}

//delete --> merge