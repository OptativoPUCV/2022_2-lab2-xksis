#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *list=(List*)malloc(sizeof(List));
  list->head=NULL;
  list->current=NULL;
  list->tail=NULL;
  
  return list;
}

void * firstList(List * list) {
  if(list->head!=NULL){
    list->current=list->head;
  }
  else{
    return NULL;
  }
  return (list->head->data);
}

void * nextList(List * list) {
  if(!list->head)return NULL;
  if(list->current!=NULL && list->current->next!=NULL){
    list->current=list->current->next;
  }
  else{
    return NULL;
  }
  return (list->current->data);
}

void * lastList(List * list) {
  if(!list->head)return NULL;
  if(list->tail!=NULL){
    list->current=list->tail;
  }
  else{
    return NULL;
  }
  return (list->tail->data);
}

void * prevList(List * list) {
  if(!list->head)return NULL;
  if(list->current!=NULL && list->current->prev!=NULL){
    list->current=list->current->prev;
  }
  else{
    return NULL;
  }
  return (list->current->data);
}

void pushFront(List * list, void * data) {
  Node* primero=createNode(data);
  primero->next=list->head;
  if(list->head!=NULL){
    list->head->prev=primero;
  }
  list->head=primero;
  list->tail=primero;
  primero->prev=NULL;
}

void pushBack(List * list, void * data) {
  list->current = list->tail;
  pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node* nodo=createNode(data);
  if(list->head!=NULL && list->current!=NULL && list->current!=list->tail){
    nodo->next=list->current->next;
    list->current->next=nodo;
    nodo->prev=list->current;
    nodo->next->prev=nodo;
  }
  else{
    list->tail=nodo;
    nodo->next=NULL;
    nodo->prev=list->current;
    list->current->next=nodo;
  }
}

void * popFront(List * list) {
  list->current = list->head;
  return popCurrent(list);
}

void * popBack(List * list) {
  list->current = list->tail;
  return popCurrent(list);
}

void * popCurrent(List * list) {
  Node* posicion=list->current;
  void* dato=posicion->data;
  if(!posicion->prev)return NULL;
  if(posicion==list->head){
    posicion->next->prev=NULL;
    list->head=posicion->next;
  }
  else{
    if(posicion==list->tail){
      posicion->prev->next=NULL;
      list->tail=posicion->prev;
    }
    else{
      posicion->prev->next=posicion->next->prev;
      posicion->next->prev=posicion->prev->next;
    }
  }
  free(posicion);
  return dato;
}

void cleanList(List * list) {
  while (list->head != NULL) {
    popFront(list);
  }
}