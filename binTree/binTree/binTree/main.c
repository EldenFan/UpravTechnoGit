#include <stdio.h>
#include <stdlib.h>
#define MY 11

typedef struct sTree Tree;

struct sTree
{
	int value;
	unsigned int height;
	Tree* left;
	Tree* right;
};

Tree* createTree(int x)
{
	Tree* nowTree = (Tree*)malloc(sizeof(Tree));
	nowTree->height = 1;
	nowTree->value = x;
	nowTree->left = NULL;
	nowTree->right = NULL;
	return nowTree;
}

void correctHeight(Tree* myTree)
{
	unsigned int heightLeft = 0;
	unsigned int heightRight = 0;
	if (myTree->left != NULL)
	{
		heightLeft = myTree->left->height;
	}
	if (myTree->right != NULL)
	{
		heightRight = myTree->right->height;
	}
	if (heightLeft > heightRight)
	{
		myTree->height = heightLeft + 1;
	}
	else
	{
		myTree->height = heightRight + 1;
	}
}

Tree* rotateRight(Tree* myTree)
{
	Tree* temp = myTree->left;
	myTree->left = temp->right;
	temp->right = myTree;
	correctHeight(myTree);
	correctHeight(temp);
	return temp;
}

Tree* rotateLeft(Tree* myTree)
{
	Tree* temp = myTree->right;
	myTree->right = temp->left;
	temp->left = myTree;
	correctHeight(myTree);
	correctHeight(temp);
	return temp;
}

int deltaHeight(Tree* myTree)
{
	unsigned int heightLeft = 0;
	unsigned int heightRight = 0;
	if (myTree->left != NULL)
	{
		heightLeft = myTree->left->height;
	}
	if (myTree->right != NULL)
	{
		heightRight = myTree->right->height;
	}
	return heightRight - heightLeft;
}

Tree* balance(Tree* myTree)
{
	correctHeight(myTree);

	if (deltaHeight(myTree) == 2)
	{
		if (deltaHeight(myTree->right) < 0)
		{
			myTree->right = rotateRight(myTree->right);
		}
		return rotateLeft(myTree);
	}
	else if (deltaHeight(myTree) == -2)
	{
		if (deltaHeight(myTree->left) > 0)
		{
			myTree->left = rotateLeft(myTree->left);
		}
		return rotateRight(myTree);
	}
	
	return myTree;
}

Tree* insert(Tree* myTree, int x)
{
	if (myTree == NULL)
	{
		return createTree(x);
	}
	if (x < myTree->value)
	{
		myTree->left = insert(myTree->left, x);
	}
	else
	{
		myTree->right = insert(myTree->right, x);
	}
	return balance(myTree);
}

//Он был нагло украден	с сайта https://studassistent.ru/c/vyvod-binarnogo-dereva-c-si
void showLine(char* c, int p, int s) {
	int t = s, i; for (i = 0; i < p; i++) { printf(t & 1 ? "|  " : "   "); t /= 2; } printf(c);
} 

void showTree(Tree* myTree, int p, int s) {
	if (myTree == NULL) return;
	printf("%d", myTree->value); printf("\n");

	if (myTree ->left != NULL) {
		showLine("|\n", p, s); showLine("L: ", p, s);
		showTree(myTree->left, p + 1, s + ((myTree->right == NULL ? 0 : 1) << p));
	}
	if (myTree ->right != NULL) {
		showLine("|\n", p, s); showLine("R: ", p, s);
		showTree(myTree->right, p + 1, s);
	}
} 


Tree* myTree = NULL;
int arr[] = { 5, 6, 8, 10, 12, 3, 13, 7, 19, 1, 20 }; // Когда еще добавишь меняй MY

int main()
{

	for (int i = 0; i < MY; i++)
	{
		myTree = insert(myTree, arr[i]);
	}

	showTree(myTree, 0, 0);

	return 0;
}