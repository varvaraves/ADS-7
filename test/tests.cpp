// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
  if (!first) return;
  Car* curr = first->next;
  while (curr != first) {
    Car* temp = curr;
    curr = curr->next;
    delete temp;
  }
  delete first;
}

void Train::addCar(bool light) {
  Car* newCar = new Car(light);
  if (!first) {
    first = newCar;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
}

int Train::getLength() {
  countOp = 0;
  Car* curr = first;

  if (!curr->light) {
    curr->light = true;
    countOp++;
  } else {
    curr->light = false;
    countOp++;
    curr->light = true;
    countOp++;
  }

  int len = 0;
  curr = curr->next;
  countOp++;
  while (!curr->light) {
    curr = curr->next;
    countOp++;
    len++;
  }

  curr->light = false;
  countOp++;

  return len + 1;
}
