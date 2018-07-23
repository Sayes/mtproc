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
#include "include/util.h"
#include "include/workbasethread.h"

class XThread : public WorkBaseThread {
 public:
  explicit XThread(int id);
  virtual ~XThread();

  int process_task();

  void set_filenames(std::vector<pthinf> ifns) { filenames_ = ifns; }

 private:
  int do_X_proc();
  void doX4one(const std::string& strregtime);

 private:
  std::vector<pthinf> filenames_;
  int id_;
  Config* pcfg_;
};

#endif  // INCLUDE_CUTTHREAD_H_
