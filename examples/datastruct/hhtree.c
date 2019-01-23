
#define RED
#define BLACK

typedef int KEY_TYPE;

#if 1

typedef struct _rbtree_node {
    unsigned char color;

    struct _rbtree_node *right;
    struct _rbtree_node *left;
    struct _rbtree_node *parent;

    KEY_TYPE key;
    void *value;
} _rbtree_node;

typedef struct _rbtree {
    _rbtree_node *root;
    _rbtree_node *nil;
}

#else

#define RBTREE_ENTRY(name, type)\
struct name {                   \
    unsigned char color;        \
    struct _rbtree_node *right; \
    struct _rbtree_node *left;  \
    struct _rbtree_node *parent;\
}

#endif;

void _rbtree_left_rotate() {
    _rbtree_node *y = x->right;

    x->right = y->left;//1
    if (y->left != T->nil){
        y->left->parent = x;//2
    }

    y->parent = x->parent;//3
    if (x->parent == T->nil) {//4
        T->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;//5
    x->parent = y;//6
}