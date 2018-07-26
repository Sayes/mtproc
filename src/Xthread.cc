// Copyright 2017-2018 SeetaTech

#include "include/Xthread.h"
#include <sys/time.h>
#include <unistd.h>
#if defined(WITH_UUID)
#include <uuid/uuid.h>
#endif
#include <fstream>
#include <iostream>
#if defined(WITH_OPENCV)
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif
#include "include/eupulogger4system.h"
#include "include/workbasethread.h"

XThread::XThread(int id) : WorkBaseThread(), id_(id), pcfg_(nullptr) {
  LOG(_INFO_, "XThread::XThread(%d)", id_);
  pcfg_ = Config::get_instance();
}

XThread::~XThread() { LOG(_INFO_, "XThread::~XThread() id = %d", id_); }

int XThread::process_task() {
  LOG(_INFO_, "XThread::process_task() id = %d", id_);
  int nret = do_X_proc();
  is_operate_ = false;
  return nret;
}

int XThread::do_X_proc() {
  for (auto& it_fn = range_begin_; it_fn != range_end_; ++it_fn) {
    doX4one(*it_fn);
  }
  return 0;
}

void XThread::doX4one(pthinf& inf) { printf("%s\n", inf.pthfn.c_str()); }
