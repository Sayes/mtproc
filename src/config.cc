// Copyright 2017-2018 SeetaTech

#include "include/config.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <memory>
#ifdef WITH_FILECONF
#include <json/json.h>
#endif
#include "include/eupulogger4system.h"
#include "include/jsonreaderinst.h"

static const char *THREAD_CNT = "thread_cnt";
static const char *SRC_PATH = "src_path";
static const char *DEST_PATH = "dest_path";
static const char *MODEL_PATH = "model_path";
static const char *LOG_PATH = "log_path";
static const char *PTHFN_LST = "pthfn_lst";

Config::Config() {}

Config::~Config() {}

bool Config::init(const std::string &cfg_path) {
  bool ret = false;
  std::ifstream f;
  do {
#ifdef WITH_FILECONF
    f.open(cfg_path.c_str());
    if (!f.is_open()) {
      LOG(_ERROR_, "Config::init() open config file %s failed", cfg_path.c_str());
      break;
    }
    f.seekg(0, std::ios::end);
    int64_t flen = f.tellg();
    f.seekg(0, std::ios::beg);
    std::unique_ptr<char> tmpbuf(new char[flen]);
    if (!tmpbuf) {
      LOG(_ERROR_, "Config::init() new char[%lu] failed", flen);
      break;
    }
    f.read(tmpbuf.get(), flen);

    JsonReaderInst *pjsonreaderinst = JsonReaderInst::get_instance();
    if (pjsonreaderinst == nullptr) {
      LOG(_ERROR_, "JsonReaderInst::get_instance() failed");
      break;
    }
    pjsonreaderinst->init();
    Json::Value v;
    JSONCPP_STRING err;

    if (pjsonreaderinst->getpcr() == nullptr) {
      LOG(_ERROR_, "JsonReaderInst::get_instance()->getpcr() == nullptr");
      break;
    }
    if (!pjsonreaderinst->getpcr()->parse(tmpbuf.get(), tmpbuf.get() + flen, &v, &err)) {
      LOG(_ERROR_, "Config::init() parse config %s failed", cfg_path.c_str());
      break;
    }
    selfpath_ = cfg_path;

    cfg_.thread_cnt = v[THREAD_CNT].asInt();
    cfg_.src_path = v[SRC_PATH].asString();
    cfg_.dest_path = v[DEST_PATH].asString();
    cfg_.model_path = v[MODEL_PATH].asString();
    cfg_.log_path = v[LOG_PATH].asString();
    cfg_.pthfn_lst = v[PTHFN_LST].asString();
#else
    cfg_.thread_cnt = 2;
    cfg_.src_path = "";
    cfg_.dest_path = "/tmp/";
    cfg_.model_path = "";
    cfg_.log_path = "";
    cfg_.pthfn_lst = "";
#endif
    ret = true;
  } while (0);
  f.close();
  return ret;
}

void Config::output() {
  printf("%s %d\n", THREAD_CNT, cfg_.thread_cnt);
  printf("%s %s\n", SRC_PATH, cfg_.src_path.c_str());
  printf("%s %s\n", DEST_PATH, cfg_.dest_path.c_str());
  printf("%s %s\n", MODEL_PATH, cfg_.model_path.c_str());
  printf("%s %s\n", LOG_PATH, cfg_.log_path.c_str());
  printf("%s %s\n", PTHFN_LST, cfg_.pthfn_lst.c_str());
}
