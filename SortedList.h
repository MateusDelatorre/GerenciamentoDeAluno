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
			return NULL;
		}
	}
}

//Go to the lowest branch and start to trigger a function call for all branches.
void goThroughTree(TreeBranch * tree_branch, void (*f)(TreeBranch * tree_branch)){//
	if(tree_branch != NULL){
		goThroughTree(tree_branch->left_branch, f);
		(*f)(tree_branch);
		goThroughTree(tree_branch->right_branch, f);
	}
}

void printBranch(TreeBranch * tree_branch){
	printStudent(tree_branch->student);
}

void printList(TreeRoot * root){
	goThroughTree(root->first, printBranch);
}

void printApprovedStudent(TreeBranch * tree_branch){
	if(studentApproved(tree_branch->student) >= 7.0){
		printStudent(tree_branch->student);
	}
}

void printApprovedsStudents(TreeRoot * root){
	goThroughTree(root->first, printApprovedStudent);
}

struct branch* getStudent(TreeBranch * tree_branch, int enroll){
	if(tree_branch == NULL){
		return NULL;
	}else{
		if (tree_branch->student->enroll > enroll)
		{
			return getStudent(tree_branch->left_branch, enroll);
		}else if (tree_branch->student->enroll < enroll)
		{
			return getStudent(tree_branch->right_branch, enroll);
		}else{
			return tree_branch;
		}
	}
}

struct branch* getLowerBranch(TreeBranch * tree_branch, int enroll){
	if(tree_branch == NULL){
		return NULL;
	}else{
		if (tree_branch->student->enroll > enroll)
		{
			return getLowerBranch(tree_branch->left_branch, enroll);
		}else if (tree_branch->student->enroll < enroll)
		{
			return getLowerBranch(tree_branch->right_branch, enroll);
		}else{
			return tree_branch;
		}
	}
}


int removeFromList(TreeRoot * root, int enroll){
	/*
	So i find this on the internet:
	Deleting a node that has two subtrees is very complicated....
	Here is the summary of the procedure:
        First, we find the deletion node p (= the node that we want to delete)
        Find the successor node of p(lower value from the right branch of the deletion node)
        Replace the content of node p with the content of the successor node
        Delete the successor node
	source: http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/9-BinTree/BST-delete2.html
	Acessed on: 26/07/2021
	*/

	TreeBranch * deletion_branch = getStudent(root->first, enroll);//Deletion node found!
	
	if (deletion_branch == NULL)//just to be sure
	{
		return 0;
	}

	TreeBranch * successor_branch = getLowerBranch(deletion_branch, deletion_branch->student->enroll);

	if (successor_branch == NULL)//there is no successor branch
	{
		free(deletion_branch);
		return 1;
	}

	deletion_branch = successor_branch;
	free(successor_branch);
}

#endif