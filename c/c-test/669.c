





struct TreeNode* trimBST(struct TreeNode* root, int low, int high){
    if (root == NULL){
        return NULL;
    }
    
    if (root->val > high){
        return trimBST(root->left, low, high);
    }

    if (root->val < low){
        return trimBST(root->right, low, high);
    }
    
    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);
    return root;
}
