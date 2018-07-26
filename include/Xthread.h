// Copyright (c) 2017, SeetaTech Inc.
// All rights reserved.

#ifndef INCLUDE_CUTTHREAD_H_
#define INCLUDE_CUTTHREAD_H_

#if defined(WITH_OPENCV)
#include <opencv2/imgproc/imgproc.hpp>
#endif
#include <string>
#include <vector>
#include "include/config.h"
#include "include/pthinf.h"
#include "include/util.h"
#include "include/workbasethread.h"

class XThread : public WorkBaseThread {
 public:
  explicit XThread(int id);
  virtual ~XThread();

  int process_task();
  void set_range(std::vector<pthinf>::iterator range_begin,
                 std::vector<pthinf>::iterator range_end) {
    range_begin_ = range_begin;
    range_end_ = range_end;
  }
  int get_id() { return id_; }

 private:
  int do_X_proc();
  void doX4one(pthinf& inf);

 private:
  int id_;
  std::vector<pthinf>::iterator range_begin_;
  std::vector<pthinf>::iterator range_end_;
  Config* pcfg_;
};

#endif  // INCLUDE_CUTTHREAD_H_
