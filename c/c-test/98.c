




bool checkIsBst(struct TreeNode* node, bool leftBoundInf, int leftBound, bool rightBoundInf, int rightBound){
    return 
        (node == NULL)
        || (leftBoundInf || node->val > leftBound)
        && (rightBoundInf || node->val < rightBound)
        && checkIsBst(node->left, leftBoundInf, leftBound, false, node->val)
        && checkIsBst(node->right, false, node->val, rightBoundInf, rightBound);
}

bool isValidBST(struct TreeNode* root){
    return checkIsBst(root, true, INT_MIN, true, INT_MAX);
}
