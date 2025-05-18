// Copyright 2021 NNTU-CS
#include "train.h"
#include <cstdlib>
#include <ctime>

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
  Car* curr = first;
  countOp = 0;

  if (!curr->light) {
    curr->light = true;
    countOp++;
    curr = curr->next;
  } else {
    curr->light = false;
    countOp++;
    curr = curr->next;
  }

  int steps = 1;
  while (true) {
    countOp++;
    if (curr->light) {
      curr->light = false;
      return steps;
    }
    steps++;
    curr = curr->next;
  }
}
