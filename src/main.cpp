// Copyright 2022 NNTU-CS
#include "train.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace std::chrono;

void RunExperiment(const string& label,
                   const vector<bool>& config,
                   ofstream& out_count,
                   ofstream& out_time) {
  Train train;
  for (bool state : config) {
    train.addCar(state);
  }

  auto start = steady_clock::now();
  int length = train.getLength();
  auto end = steady_clock::now();
  int ops = train.getOpCount();

  auto duration = duration_cast<milliseconds>(end - start).count();

  out_count << config.size() << "," << ops << "," << label << "\n";
  out_time << config.size() << "," << duration << "," << label << "\n";

  cout << "Length = " << length << ", Steps = " << ops
       << ", Time = " << duration << "ms (" << label << ")\n";
}

int main() {
  const int kMinSize = 2;
  const int kMaxSize = 100;

  ofstream out_count("result/ops.csv");
  ofstream out_time("result/time.csv");

  out_count << "n,ops,type\n";
  out_time << "n,time,type\n";

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, 1);

  for (int n = kMinSize; n <= kMaxSize; ++n) {
    vector<bool> all_off(n, false);
    RunExperiment("off", all_off, out_count, out_time);

    vector<bool> all_on(n, true);
    RunExperiment("on", all_on, out_count, out_time);

    vector<bool> random_config;
    for (int i = 0; i < n; ++i) {
      random_config.push_back(dis(gen));
    }
    RunExperiment("random", random_config, out_count, out_time);
  }

  out_count.close();
  out_time.close();

  return 0;
}
