#include <stdio.h>

// bjc2975
// Brian Coombs

typedef struct node{
    int value;
    node *next;
}node;

void Quiz() {

}

int Length(node *ptr){
    int size = 0;
    while(ptr->next != NULL){
        ptr = ptr->next;
        size++;
    }
    return size;
}

node* findNode(node* ptr, int index){
    node* temp = ptr;
    for(int i=0; i <= index; i++){
        temp = temp->next;
    }
    return temp;
}

node* insert(node* ptr,int index, int value){
    node* ptr1 = findNode(ptr, index);
    node* newPtr = (node*) malloc(sizeof(node));
    newPtr->value = value;
    newPtr->next = ptr1->next;
    ptr1->next = newPtr;
    if(ptr1->value == ptr->value){
        return newPtr;
    }
    else{
        return ptr;
    }

}

node* Remove(node* ptr, int index){
    if(index == 0){
        return ptr->next;
    }
    else{
        node* ptr1 = findNode(ptr, index);
        ptr1->next = ptr1->next->next;
        return ptr;
    }

}

node* Switch(node*ptr, int index1, int index2) {
    node *ptr1 = findNode(ptr, index1);
    node *ptr2 = findNode(ptr, index2);
    node *temp1Next = findNode(ptr, index1)->next;
    node *temp2Next = findNode(ptr, index2)->next;
    if (index1 == 0) {
        findNode(ptr, index2 - 1)->next = ptr1;
        ptr1->next = temp2Next;
        ptr2->next = temp1Next;
        return ptr2;
    }
    if(index2 == 0) {
        findNode(ptr, index1 - 1)->next = ptr2;
        ptr1->next = temp2Next;
        ptr2->next = temp1Next;
        return ptr1;
    }
    findNode(ptr, index1 - 1)->next = ptr2;
    findNode(ptr, index2 - 1)->next = ptr1;
    ptr1->next = temp2Next;
    ptr2->next = temp1Next;
    return ptr;
}

node* CopyList(node* ptr){
    int len = Length(ptr);
    node *temp = malloc(len * sizeof(node));
    int i = 0;
    for (node* start2 = ptr; start2 != NULL; start2 = start2->next) {
        temp[i].value = start2->value;
        temp[i].next = &temp[i+1];
    }
    temp[len-1].next = NULL;
    return temp;
}