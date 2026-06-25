#include <iostream>
#include <pthread.h>

#include "LinkedList.h"


void* threadRoutine(void* arg){
  LinkedList *l = static_cast<LinkedList*>(arg);
  for(int i=0; i<1e3; i++){
    l->insert(i);
  }

  return nullptr;
}

int main(){

  LinkedList l1{};
  l1.init();
  // l1.insert(5);
  // l1.insert(4);
  // l1.insert(3);
  // l1.insert(2);
  // l1.insert(1);

  // std::cout << std::boolalpha << l1.contains(4) << "\n";

  pthread_t t1, t2;

  pthread_create(&t1, NULL, threadRoutine, &l1);
  pthread_create(&t2, NULL, threadRoutine, &l1);

  pthread_join(t1, NULL);
  // pthread_join(t2, NULL);

  std::cout << l1 << "\n";


  return 0;
}