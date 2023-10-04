#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tree
{
	char val;
    struct tree *left,*right;
} node;

	node* createnode(char c)
{
	node *t = malloc(sizeof(node));
	t->left = NULL;
    t->right = NULL;
    t->val = c;
	return t;
}

    node* createtree(FILE* input_file)
{
	char c;
	fscanf(input_file, "%c", &c);
	if (c == '*')
		return NULL;
    node *t = createnode(c);
	t->left = createtree(input_file);
	t->right = createtree(input_file);
	return t;
}
	int height(node * root)
	{
		if (root == NULL)
			return 0;
		int hl = height(root->left);
		int hr = height(root->right);
        if (hl>hr){
            return hl+1;
        }
            return hr+1;

	}

	void inorder(FILE * output_file, node * root)
	{
		if (root == NULL)
			return;
		inorder(output_file, root->left);
		fprintf(output_file, "%c", root->val);
		inorder(output_file, root->right);
	}

	void preorder(FILE * output_file, node * root)
	{
		if (root == NULL)
			return;
		fprintf(output_file, "%c", root->val);
		preorder(output_file, root->left);
		preorder(output_file, root->right);
	}

    void postorder(FILE * output_file, node * root)
    {
			if (root == NULL)
				return;
			postorder(output_file, root->left);
			postorder(output_file, root->right);
			fprintf(output_file, "%c", root->val);
    }

    int leaves (node* root )
    {
		if (root == NULL)
			return 0;
		if (root->left == NULL && root->right == NULL)
			return 1;
		return leaves(root->left) + leaves(root -> right);
	}

    node* reach_node (node* root ,char c )
    {
        if (root == NULL)
				return NULL;
        if (root->val ==c)
            return root;
        node*right= reach_node (root->right ,c);
        if(right != NULL)
            return right;
        else return reach_node (root->left,c);
    }

	void swap(FILE* input_file, FILE* output_file , node * root)
	{
	    char c;
	    fscanf(input_file, "%c", &c);
	    fscanf(input_file, "%c", &c);
        node* found = reach_node (root, c);
        if(found == NULL)
            return;
        node* temp =  found->right;
        found->right = found -> left;
        found->left = temp;
        inorder (output_file ,root);

	}
    void burn_tree (node* root){
      if (root == NULL)
				return;
    burn_tree (root->left);
    burn_tree (root -> right);
    free (root);
    }
	int main(int argc, char** argv)

	{
	    if (argc<4)
            return 0;
      FILE* input_file = fopen(argv[1] , "r");
      FILE* output_file = fopen(argv[2] , "w");
      node* root = createtree(input_file);
        if (strcmp(argv[3], "height")==0)
            fprintf(output_file, "%d", height(root));
        else if (strcmp(argv[3], "preorder")==0)
            preorder(output_file, root );
        else if (strcmp(argv[3], "inorder")==0)
            inorder(output_file, root );
        else if (strcmp(argv[3], "postorder")==0)
            postorder(output_file, root );
        else if (strcmp(argv[3], "leaves")==0)
            fprintf(output_file, "%d", leaves(root));
        else if (strcmp(argv[3], "swap")==0)
            swap(input_file, output_file, root );
		burn_tree(root);
		return 0;

	}
