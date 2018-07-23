/*
 * Copyright 2017-2018 SeetaTech
 */

#ifndef INCLUDE_JSONREADERINST_H_
#define INCLUDE_JSONREADERINST_H_

#if defined(WITH_FILECONF)

#include <json/json.h>
#include <memory>
#include <string>
#include <vector>
#include "include/aocsingleton.h"

class JsonReaderInst : public IAocSingleton<JsonReaderInst> {
 public:
  void init();
  Json::CharReader* getpcr() { return pcr_.get(); }

 private:
  JsonReaderInst();
  virtual ~JsonReaderInst();
  JsonReaderInst(const JsonReaderInst&);
  JsonReaderInst& operator=(const JsonReaderInst&);
  friend IAocSingleton<JsonReaderInst>;

 private:
  Json::CharReaderBuilder crb_;
  std::unique_ptr<Json::CharReader> pcr_{nullptr};
};

#endif

#endif  // INCLUDE_JSONREADERINST_H_
