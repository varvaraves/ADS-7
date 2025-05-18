// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

#include <cstdint>

class Train {
 private:
    struct Car {
        bool light;
        Car* next;
        Car* prev;
        explicit Car(bool l = false) : light(l), next(this), prev(this) {}
    };
    Car* first;
    int countOp;
 public:
    Train();
    ~Train();
    void addCar(bool light);
    int getLength();
    int getOpCount() const { return countOp; }
};
#endif  // INCLUDE_TRAIN_H_
