#ifndef SortedList
#define SortedList
#define MAX 100

#include <stdio.h>
#include <stdlib.h>
#include "Aluno.h"

//struct that represent a treeNode
struct branch {
	Student * student;
	//int index;//This variable is for debugging purpose. I'll leave it here to facilitate your debugging as well
	struct branch * right_branch;//The right branch will be an Aluno with the matricula number greater than the atual aluno
	struct branch * left_branch;//The left branch will be an Aluno with the matricula number lower than the atual aluno
};

typedef struct branch TreeBranch;

struct Root{
    struct branch * first;
	int size;
};

typedef struct Root TreeRoot;

//typedef struct binaryTree BinaryTree;

//check if the node has a left branch
int hasLeftBranch(struct branch * branch){
    if(branch->left_branch != NULL) return 1;
	return 0;
}

//check if the node has a right branch
int hasRigthBranch(struct branch * branch){
    if(branch->right_branch != NULL) return 1;
	return 0;
}

//check if the tree is empty
int isEmpty(TreeRoot * list) {
	return (list->first == NULL);
}

//check if the tree is full
int isFull(TreeRoot * list) {
	return (list->size < 30);
}

//Create a new tree
void newTree (TreeRoot * tree_root) {
    tree_root->first = NULL;
	tree_root->size = 0;
}

struct branch* addSort(struct branch * tree_branch, Student * student){
	if(tree_branch == NULL){
		struct branch * new_branch;
		new_branch = (struct branch*) malloc(sizeof(struct branch));
		new_branch->student = student;
		new_branch->left_branch = NULL;
		new_branch->right_branch = NULL;
		return new_branch;
	}else{
		if (tree_branch->student->enroll > student->enroll)
		{
			tree_branch->left_branch = addSort(tree_branch->left_branch, student);
		}else if (tree_branch->student->enroll < student->enroll)
		{
			tree_branch->right_branch = addSort(tree_branch->right_branch, student);
		}else{
			printf("duplicated\n");
		}
	}
}

struct branch* addSortBranchs(struct branch * tree_branch, struct branch * new_branch){
	if(tree_branch == NULL){
		return new_branch;
	}else{
		if (tree_branch->student->enroll > new_branch->student->enroll)
		{
			tree_branch->left_branch = addSortBranchs(tree_branch->left_branch, new_branch);
		}else if (tree_branch->student->enroll < new_branch->student->enroll)
		{
			tree_branch->right_branch = addSortBranchs(tree_branch->right_branch, new_branch);
		}else{
			printf("duplicated\n");
		}
	}
}

void goThroughBranchs(TreeRoot * root, TreeBranch * tree_branch, struct branch* (*f)(struct branch * tree_branch, struct branch * new_branch)){//
	if(tree_branch != NULL){
		goThroughBranchs(root, tree_branch->left_branch, f);
		goThroughBranchs(root, tree_branch->right_branch, f);
		(*f)(tree_branch, root->first);
	}
}

void TreeSize(TreeRoot * root){
	root->size += 1;
}

void printBranch(TreeBranch * tree_branch){
	printStudent(tree_branch->student);
}

//Go to the lowest branch and start to trigger a function call for all branches.
void goThroughTree(TreeBranch * tree_branch, void (*f)(TreeBranch * tree_branch)){//
	if(tree_branch != NULL){
		goThroughTree(tree_branch->left_branch, f);
		(*f)(tree_branch);
		goThroughTree(tree_branch->right_branch, f);
	}
}

struct branch* find(TreeBranch * tree_branch, int enroll){
	if(tree_branch == NULL){
		printf("Can't find this student\n");
		return NULL;
	}else{
		if (tree_branch->student->enroll > enroll)
		{
			find(tree_branch->left_branch, enroll);
		}else if (tree_branch->student->enroll < enroll)
		{
			find(tree_branch->right_branch, enroll);
		}else{
			return tree_branch;
		}
	}
}

int delete(TreeRoot * root, int enroll){
	TreeBranch * tree_branch = find(root->first, enroll);
	if (tree_branch == NULL)
	{
		return 0;
	}

	struct branch * new_branch;
	new_branch = (struct branch*) malloc(sizeof(struct branch));
	new_branch->left_branch = tree_branch->left_branch;
	new_branch->right_branch = tree_branch->right_branch;
	
	// free(tree_branch->student);
	// free(tree_branch);
	tree_branch = NULL;
	
	goThroughBranchs(root, new_branch->left_branch, addSortBranchs);
	goThroughBranchs(root, new_branch->right_branch, addSortBranchs);
	
	free(new_branch);
	return 1;
}

#endif