// Copyright 2017-2018 SeetaTech

#include "include/Xthread.h"
#include <sys/time.h>
#include <unistd.h>
#include <uuid/uuid.h>
#include <fstream>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
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
  LOG(_INFO_, "XThread::do_X_proc() filenames_ cnt %d, id = %d", filenames_.size(), id_);

  for (auto& it_fn : filenames_) {
    doX4one(it_fn.pthfn);
  }
  return 0;
}

void XThread::doX4one(const std::string& param) { std::cout << param << std::endl; }
