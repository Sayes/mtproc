/*
 * Copyright 2017-2018 SeetaTech
 */

#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_

#include <list>
#include <string>
#include <vector>
#include "include/aocsingleton.h"

typedef struct {
  uint32_t thread_cnt;
  std::string src_path;
  std::string dest_path;
  std::string model_path;
  std::string log_path;
  std::string pthfn_lst;
} FdConf;

class Config : public IAocSingleton<Config> {
 public:
  bool init(const std::string &cfg_path);

  uint32_t get_thread_cnt() const { return cfg_.thread_cnt; }
  const std::string get_src_path() const { return cfg_.src_path; }
  const std::string get_dest_path() const { return cfg_.dest_path; }
  const std::string get_model_path() const { return cfg_.model_path; }
  const std::string get_log_path() const { return cfg_.log_path; }
  const std::string get_pthfn_lst() const { return cfg_.pthfn_lst; }

  void output();

  void set_thread_cnt(int thread_cnt) { cfg_.thread_cnt = thread_cnt; }
  void set_src_path(const std::string &src_path) { cfg_.src_path = src_path; }
  void set_dest_path(const std::string &dest_path) {
    cfg_.dest_path = dest_path;
  }
  void set_model_path(const std::string &model_path) {
    cfg_.model_path = model_path;
  }
  void set_log_path(const std::string &log_path) { cfg_.log_path = log_path; }
  void set_pthfn_lst(const std::string &lst) { cfg_.pthfn_lst = lst; }

 private:
  Config();
  virtual ~Config();
  Config(const Config &);
  Config &operator=(const Config &);
  friend IAocSingleton<Config>;

 private:
  FdConf cfg_;
  std::string selfpath_;
};

#endif  // INCLUDE_CONFIG_H_
