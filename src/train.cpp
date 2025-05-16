// Copyright 2021 NNTU-CS
#include "train.h"
#include <cstddef>

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
  if (!first) return;

  Car* current = first->next;
  while (current != first) {
    Car* temp = current;
    current = current->next;
    delete temp;
  }
  delete first;
}

void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};

  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* last = first->prev;
    newCar->next = first;
    newCar->prev = last;
    last->next = newCar;
    first->prev = newCar;
  }
}

int Train::getLength() {
  if (!first) return 0;

  Car* current = first;
  countOp = 0;

  if (!current->light) {
    current->light = true;
  }

  int k = 1;
  while (true) {
    Car* temp = current;
    for (int i = 0; i < k; ++i) {
      temp = temp->next;
      countOp++;
    }

    if (temp->light) {
      return k;
    }

    temp->light = true;
    ++k;
  }
}

int Train::getOpCount() {
  return countOp;
}
