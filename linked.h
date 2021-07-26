#ifndef linked
#define linked
#define MAX 100

#include <stdio.h>
#include <stdlib.h>
#include "Aluno.h"

struct Item{
    Student * student;//the student struct
    struct Item* next;//pointer to next item
};

typedef struct {
    struct Item * first;//holds the first item in the list
	int size;//keep track of the size of the list
} LinkedList;

//See if the item has a next item. Returns 1 to true and 0 to false
int hasNext(struct Item * item){
    if(item->next != NULL) return 1;
	return 0;
}

//See if the List is empty. Returns 1 to true and 0 to false
int estahVazia(LinkedList * list) {
	return (list->first == NULL);
}

//Create a new list with size 0, and set the first item to NULL
void criarLista (LinkedList *list) {
    list->first = NULL;
    list->size = 0;
}

//Add a new item to the list and keeps the list in ascending order
int addSort(LinkedList *list, Student * student) {
	if(list->size < 30){
		struct Item* new_item;
		new_item = (struct Item*) malloc(sizeof(struct Item));
		new_item->student = student;
		new_item->next = NULL;
		
		if(estahVazia(list)){
			list->first = new_item;
			list->size += 1;
			return -1;
		}
		struct Item* item_back, *item_next;
		item_back = NULL;
		item_next = list->first;
		
		while (item_next != NULL && item_next->student->enroll < new_item->student->enroll){
			item_back = item_next;
			item_next = item_next->next;
		}
		if(item_back == NULL){
			list->first = new_item;
			new_item->next = item_next;
			list->size += 1;
			return 1;
		}

		new_item->next = item_next;
		item_back->next= new_item;
		list->size += 1;
		return 1;
	}
	return -1;
}

//return the "index" of the student that matches the enrollment number given
int indexOf(LinkedList *list, int enroll){
	struct Item* item_next;
    int index = 0;
	if(estahVazia(list)) return -1;
	item_next = list->first;

    while (item_next != NULL && item_next->student->enroll != enroll){
		index++;
        item_next = item_next->next;
    }
	return index;
}

//removes the student that matches the enrollment number given
int removeFromList(LinkedList *list, int enroll){
	struct Item* item_back, *item_next;
    int index = indexOf(list, enroll);
	if(estahVazia(list)) return -1;
	item_next = list->first;
	
    for (int i = 0; i < index; i++)
	{
		item_back = item_next;
        item_next = item_next->next;
	}
	item_back->next = item_next->next;
	freeStudentData(item_next->student);
	free(item_next->student);
	free(item_next);
	list->size -= 1;
	return 1;
}

//return the student that matches the enrollment number given
Student * getStudent(LinkedList *list, int enroll){
	struct Item* item_next;
    
	if(estahVazia(list)) return 0;
	item_next = list->first;
	int size = 1;

    while (hasNext(item_next) && item_next->student->enroll < enroll){
        item_next = item_next->next;
    }
	return item_next->student;
}

//Print all the students in the list.
int printList(LinkedList *list){
	
	if(estahVazia(list)){
		return -1;
	}

    struct Item* item_next;
    item_next = list->first;
	
    for (int i = 0; i < list->size; i++)
	{
		printStudent(item_next->student);
        item_next = item_next->next;
	}
	return 1;
}

////Print all the approved students in the list.
int printApprovedsStudents(LinkedList *list){
	
	if(estahVazia(list)){
		return -1;
	}

    struct Item* item_next;
    item_next = list->first;
	
    for (int i = 0; i < list->size; i++)
	{
		if(studentApproved(item_next->student) >= 7.0){
			printStudent(item_next->student);
		}
        item_next = item_next->next;
	}
	return 1;
}

#endif