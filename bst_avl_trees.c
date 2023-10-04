#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tree
{
    int height;
    int val;
    struct tree *left,*right;
} node;

node* createnode(int nval)
{
    node *t = malloc(sizeof(node));
    t->left = NULL;
    t->right = NULL;
    t->val = nval;
    t->height = 1;
    return t;
}


void preorder(FILE * output_file, node * root)
{
    if (root == NULL)
        return;
    fprintf(output_file, "%d ", root->val);
    preorder(output_file, root->left);
    preorder(output_file, root->right);
}

void inorder(FILE * output_file, node * root)
{
    if (root == NULL)
        return;
    inorder(output_file, root->left);
    fprintf(output_file, "%d ", root->val);
    inorder(output_file, root->right);
}

void postorder(FILE * output_file, node * root)
{
    if (root == NULL)
        return;
    postorder(output_file, root->left);
    postorder(output_file, root->right);
    fprintf(output_file, "%d ", root->val);
}

node* insert_(node* root, int nval)
{
    if (root == NULL)
        root = createnode(nval);
    else
    {
        if (nval < root -> val)
            root -> left = insert_(root->left, nval);
        else if (nval > root -> val)
            root -> right = insert_(root->right, nval);
    }
    int hl, hr;
    hl = 0, hr = 0;

    if (root -> left != NULL)
        hl = root->left->height;
    if (root -> right != NULL)
        hr = root->right->height;
    if (hl>hr)
    {
        root->height= hl+1;
    }
    else
        root-> height= hr+1;

    return root;
}

node* minimum_r (node* nde, int nval)
{
    if (nde == NULL)
        return NULL;
    if (nde -> left != NULL)
        return minimum_r (nde -> left, nval);
    else return nde;
}


node* delete_ (node* nde, int nval)
{
    if ( nde == NULL)
        return NULL;
    else if (nval < nde -> val)
        nde->left= delete_ (nde->left, nval);
    else if (nval > nde -> val)
        nde->right = delete_ (nde->right, nval);
    else
    {
        if (nde->left != NULL && nde->right != NULL)
        {
            node* temp = minimum_r(nde->right, nval);
            nde -> val = temp-> val;
            nde -> right = delete_ (nde->right, temp->val);
        }
        else
        {
            node* temp = nde;
            if(nde->left == NULL)
                nde = nde->right;
            else if(nde->right == NULL)
                nde = nde->left;
            free(temp);
        }

    }

    int hl, hr;
    hl = 0, hr = 0;

    if (nde -> left != NULL)
        hl = nde->left->height;
    if (nde -> right != NULL)
        hr = nde->right->height;
    if (hl>hr)
    {
        nde->height= hl+1;
    }
    else
        nde-> height = hr+1;

    return nde;
}

node* rotate_right (node* nde)
{
    if ( nde == NULL)
        return NULL;
    if (nde->left == NULL)
        return nde;

    node* temp = nde -> left;
    nde->left= temp->right;
    temp-> right = nde;

    int hl, hr;
    hl = 0, hr = 0;

    if (nde-> left != NULL)
        hl = nde->left->height;
    if (nde -> right != NULL)
        hr = nde->right->height;
    if (hl>hr)
    {
        nde->height= hl+1;
    }
    else
        nde-> height= hr+1;

    hl = 0, hr = 0;

    if (temp-> left != NULL)
        hl = temp->left->height;
    if (temp -> right != NULL)
        hr = temp->right->height;
    if (hl>hr)
    {
        temp->height= hl+1;
    }
    else
        temp-> height=hr+1;

    return temp;
}

node* rotate_left (node* nde)
{
    if ( nde == NULL)
        return NULL;
    if (nde->right == NULL)
        return nde;

    node* temp = nde -> right;
    nde->right= temp->left;
    temp-> left = nde;

    int hl, hr;
    hl = 0, hr = 0;

    if (nde-> left != NULL)
        hl = nde->left->height;
    if (nde -> right != NULL)
        hr = nde->right->height;
    if (hl>hr)
    {
        nde->height= hl+1;
    }
    else
        nde-> height=hr+1;

    hl = 0, hr = 0;

    if (temp-> left != NULL)
        hl = temp->left->height;
    if (temp -> right != NULL)
        hr = temp->right->height;
    if (hl>hr)
    {
        temp->height= hl+1;
    }
    else
        temp-> height=hr+1;

    return temp;
}
node* search_rotate_right (node* nde , int nval)
{
    if (nde == NULL)
        return NULL;
    else if ( nval < nde-> val)
        nde->left = search_rotate_right(nde->left, nval);
    else if ( nval > nde-> val)
        nde->right = search_rotate_right(nde->right, nval);
    else nde = rotate_right(nde);
    return nde;
}

node* search_rotate_left (node* nde , int nval)
{
    if (nde == NULL)
        return NULL;
    else if ( nval < nde-> val)
        nde->left = search_rotate_left (nde->left, nval);
    else if ( nval > nde-> val)
        nde->right = search_rotate_left(nde->right, nval);
    else nde = rotate_left(nde);
    return nde;
}

node* insert_avl(node* root, int nval)
{
    if (root == NULL)
        root = createnode(nval);
    else
    {
        if (nval < root -> val)
            root -> left = insert_avl(root->left, nval);
        else if (nval > root -> val)
            root -> right = insert_avl(root->right, nval);
    }
    int hl, hr;
    hl = 0, hr = 0;

    if (root -> left != NULL)
        hl = root->left->height;
    if (root -> right != NULL)
        hr = root->right->height;
    if (hl>hr)
    {
        root->height= hl+1;
    }
    else
        root-> height=hr+1;

    int x = hl-hr;

    if (x < -1 && nval > root -> right -> val)
        return rotate_left (root);

    if (x >1 && nval < root->left->val)
        return rotate_right (root);

    if (x >1 && nval > root->left->val)
    {
        root->left = rotate_left(root-> left);
        return rotate_right (root);
    }

    if (x < -1 && nval > root -> right -> val)
    {
        root->right = rotate_right(root-> right);
        return rotate_left (root);
    }
    return root;
}

node* delete_avl (node* nde, int nval)
{
    if ( nde == NULL)
        return NULL;
    else if (nval < nde -> val)
        nde->left= delete_avl (nde->left, nval);
    else if (nval > nde -> val)
        nde->right = delete_avl (nde->right, nval);
    else
    {
        if (nde->left != NULL && nde->right != NULL)
        {
            node* temp = minimum_r(nde->right, nval);
            nde -> val = temp-> val;
            nde -> right = delete_avl(nde->right, temp->val);
        }
        else
        {
            node* temp = nde;
            if(nde->left == NULL)
                nde = nde->right;
            else if(nde->right == NULL)
                nde = nde->left;
            free(temp);
        }

    }
    if (nde == NULL)
        return NULL;

    int hl, hr;
    hl = 0, hr = 0;

    if (nde -> left != NULL)
        hl = nde->left->height;
    if (nde -> right != NULL)
        hr = nde->right->height;
    if (hl>hr)
    {
        nde->height= hl+1;
    }
    else
        nde-> height = hr+1;
    int x = hl-hr;

    if (x < -1 && nval > nde -> right -> val)
        return rotate_left (nde);

    if (x >1 && nval < nde->left->val)
        return rotate_right (nde);

    if (x >1 && nval > nde->left->val)
    {
        nde->left = rotate_left(nde-> left);
        return rotate_right (nde);
    }

    if (x < -1 && nval > nde -> right -> val)
    {
        nde->right = rotate_right(nde-> right);
        return rotate_left (nde);
    }
    return nde;
}



void purge (node* root)
{
    if (root == NULL)
        return;
    purge (root->left);
    purge (root -> right);
    free (root);
}


int main(int argc, char** argv)

{
    if (argc<3)
        return 0;
    FILE* input_file = fopen(argv[1], "r");
    FILE* output_file = fopen(argv[2], "w");
    node* root =NULL;
    char command[20];
    while (fscanf(input_file, "%19s", command)!= EOF)
        if (strcmp(command, "preorder")==0)
            {
            preorder(output_file, root );
            fprintf(output_file, "\n");
        }

        else if (strcmp(command, "inorder")==0)
        {
            inorder(output_file, root );
            fprintf(output_file, "\n");
        }

        else if (strcmp(command, "postorder")==0)
         {
            postorder(output_file, root );
            fprintf(output_file, "\n");
        }

        else if (strcmp(command, "rotate_right")==0)
        {
            int x;
            fscanf(input_file, "%d",&x);
            root = search_rotate_right(root, x);
        }
        else if (strcmp(command, "rotate_left")==0)
        {
            int x;
            fscanf(input_file, "%d",&x);
            root=  search_rotate_left(root, x);
        }
        else if (strcmp(command, "insert")==0)
        {
            int x;
            fscanf(input_file, "%d",&x);
            root = insert_(root, x);
        }

        else if (strcmp(command, "delete")==0)
        {
            int x;
            fscanf(input_file, "%d",&x);
            root = delete_(root, x);
        }
        else if (strcmp(command, "insert_avl")==0)
        {
            int x;
            fscanf(input_file, "%d",&x);
            root = insert_avl(root, x);
        }
        else if (strcmp(command, "delete_avl")==0)
        {
            int x;
            fscanf(input_file, "%d",&x);
            root = delete_avl(root, x);
        }
        else if (strcmp(command, "purge")==0)
        {
            purge(root);
            root = NULL;
        }
    purge(root);
    fclose(input_file);
    fclose(output_file);
    return 0;
}
