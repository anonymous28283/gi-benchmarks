


struct ListItem {
    struct TreeNode* node;
    struct ListItem* next;
};

bool findTargetPath(struct TreeNode* node, struct TreeNode* target, struct ListItem* path){
    if (node == NULL){
        return false;
    }
    
    struct ListItem* pathItem = malloc(sizeof(struct ListItem));
    pathItem->node = node;
    pathItem->next = NULL;
    path->next = pathItem;
    
    if (node->val == target->val){
        return true;
    }

    if (findTargetPath(node->left, target, pathItem)){
        return true;
    }
    
    if (findTargetPath(node->right, target, pathItem)){
        return true;
    }
    
    path->next = NULL;
    free(pathItem);
    return false;
}

void freeList(struct ListItem* target){
    if (target->next != NULL){
        freeList(target->next);
    }
    
    free(target);
}







struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    struct ListItem* pPath = malloc(sizeof(struct ListItem));
    struct ListItem* qPath = malloc(sizeof(struct ListItem));
    
    findTargetPath(root, p, pPath);
    findTargetPath(root, q, qPath);
    
    struct TreeNode* lowestTreeNode = NULL;
    struct ListItem* pPathCursor = pPath->next;
    struct ListItem* qPathCursor = qPath->next;
    while(pPathCursor != NULL && qPathCursor != NULL) {
        if (pPathCursor->node->val == qPathCursor->node->val){
            lowestTreeNode = pPathCursor->node;
            pPathCursor = pPathCursor->next;
            qPathCursor = qPathCursor->next;
            continue;
        }

        break;
    }
    
    freeList(pPath);
    freeList(qPath);
    
    return lowestTreeNode;
}
