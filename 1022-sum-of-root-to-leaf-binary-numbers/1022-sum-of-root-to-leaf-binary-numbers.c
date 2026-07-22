/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int dfs(struct TreeNode* node, int current)
{
    if(node==NULL)
    {
        return 0;
    }
    current=current*2+node->val;
    if(node->left==NULL&&node->right==NULL)
    {
        return current;
    }
    return dfs(node->left,current)+dfs(node->right,current);
}
int sumRootToLeaf(struct TreeNode* root)
{
    return dfs(root,0);
}