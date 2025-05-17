// Copyright 2021 NNTU-CS
#include "train.h"

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
  first = nullptr;
}

void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};

  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
}

int Train::getLength() {
  if (!first || !first->next) {
    return 0;
  }

  Car* current = first;
  countOp = 0;

  if (!current->light) {
    current->light = true;
  }

  int steps = 1;
  current = current->next;
  ++countOp;

  while (!current->light) {
    ++steps;
    current = current->next;
    ++countOp;
  }

  current->light = false;

  for (int i = 0; i < steps; ++i) {
    current = current->prev;
    ++countOp;
  }

  while (!current->light) {
    current->light = true;
    steps = 1;
    current = current->next;
    ++countOp;

    while (!current->light) {
      ++steps;
      current = current->next;
      ++countOp;
    }

    current->light = false;

    for (int i = 0; i < steps; ++i) {
      current = current->prev;
      ++countOp;
    }
  }

  return steps;
}

int Train::getOpCount() {
  return countOp;
}
