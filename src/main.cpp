// Copyright 2022 NNTU-CS
#include "train.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace std::chrono;

void runExperiment(const string& label,
                   const vector<bool>& config,
                   ofstream& outCount,
                   ofstream& outTime) {
  Train train;
  for (bool state : config) {
    train.addCar(state);
  }

  auto start = steady_clock::now();
  int length = train.getLength();
  auto end = steady_clock::now();
  int ops = train.getOpCount();

  auto duration = duration_cast<milliseconds>(end - start).count();

  outCount << config.size() << "," << ops << "," << label << "\n";
  outTime << config.size() << "," << duration << "," << label << "\n";

  cout << "Length = " << length << ", Steps = " << ops
       << ", Time = " << duration << "ms (" << label << ")\n";
}

int main() {
  const int MIN_SIZE = 2;
  const int MAX_SIZE = 100;

  ofstream outCount("result/ops.csv");
  ofstream outTime("result/time.csv");

  outCount << "n,ops,type\n";
  outTime << "n,time,type\n";

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, 1);

  for (int n = MIN_SIZE; n <= MAX_SIZE; ++n) {
    vector<bool> allOff(n, false);
    runExperiment("off", allOff, outCount, outTime);

    vector<bool> allOn(n, true);
    runExperiment("on", allOn, outCount, outTime);

    vector<bool> randomConfig;
    for (int i = 0; i < n; ++i) {
      randomConfig.push_back(dis(gen));
    }
    runExperiment("random", randomConfig, outCount, outTime);
  }

  outCount.close();
  outTime.close();

  return 0;
}
