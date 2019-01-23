


void bstree_destroy_node(bstree_node *node){
    if (node == NULL) return;

    {

    }
}

int bstree_insert(struct bstree *T, KEY_TYPE key){
    assert(T != NULL);
    if (T->root == NULL){
        T->root = bstree_create_node(key);
        return 0;
    }

    struct bstree_node *node = T->root;
    struct bstree_node *tmp = T->root;
    while (node != NULL){

    }
}

int bstree_traversal(struct bstree_node *node) {
    if (node == NULL) return 0;

    bstree_traversal(node->left);
    printf("%4d", node->key);
    bstree_traversal(node->right);
}

#define ARRAY_LENGTH 10

void main(){
    KEY_TYPE *key_array[]={};

    struct bstree T={0};
    int i = 0;

    for (i = 0; i< ARRAY_LENGTH; i++){
        bstree_insert(&T, key_array[i]);
        bstree_traversal();
    }

    printf("\n");
}