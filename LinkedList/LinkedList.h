#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct Node{
  int data{};
  Node *next{nullptr}; // since we using malloc these default values wont be initialized
};

struct LinkedList{
  Node *head{nullptr};
  pthread_mutex_t gLock{};

  void init(){
    this->head = nullptr;
    // pthread_mutex_init(&(this->gLock), NULL);
  }

  void insert(int data){
    Node* temp = static_cast<Node*>(malloc(sizeof(Node)));
    if(temp == nullptr){
      perror("malloc");
      std::exit(1);
    }
    temp->data = data;

    // pthread_mutex_lock(&(this->gLock));
    temp->next = this->head;
    this->head = temp;
    // pthread_mutex_unlock(&(this->gLock));
  }

  bool contains(int target){
    bool rv {false};

    // pthread_mutex_lock(&(this->gLock));
    Node* temp {this->head};
    while(temp){
      if(temp->data == target){
        rv = true;
        break;
      }
      temp = temp->next;
    }
    // pthread_mutex_unlock(&(this->gLock));

    return rv;
  }

};

inline std::ostream& operator << (std::ostream &out, LinkedList& l){
    // pthread_mutex_lock(&(l.gLock));
    Node *temp{l.head};
    while(temp){
      out << temp->data << " ";
      temp = temp->next;
    }
    // pthread_mutex_unlock(&(l.gLock));

    return out;
  }



#endif