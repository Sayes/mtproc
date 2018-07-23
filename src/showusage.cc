// Copyright 2017-2018 SeetaTech

#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <climits>
#include <iostream>
#include "include/config.h"
#include "include/eupulogger.h"
#include "include/eupulogger4system.h"
#include "include/util.h"

void show_usage(int argc, char* argv[]) {
  bool valid_args = false;
  do {
#if defined(WITH_FILECONF)
    if (argc < 2) {
#else
    if (argc < 4) {
#endif
      LOG(_ERROR_, "paramers are less than 5");
      break;
    }
    Config* pcfg = Config::get_instance();

#if defined(WITH_FILECONF)
    LOG(_INFO_, "with config file");
    std::string config_filename = std::string(argv[1]);
    if (config_filename == "") config_filename = "./conf.json";
    if (!pcfg || !pcfg->init(config_filename.c_str())) {
      LOG(_ERROR_, "main() Config init(%s) failed", config_filename.c_str());
      break;
    }
    int param_idx = 2;
#else
    pcfg->init("");
    int param_idx = 1;
#endif

    int thread_cnt = pcfg->get_thread_cnt();
    std::string srcpath = pcfg->get_src_path();
    std::string destpath = pcfg->get_dest_path();
    std::string model_path = pcfg->get_model_path();
    std::string log_path = pcfg->get_log_path();
    std::string pthfn_lst = pcfg->get_pthfn_lst();

    if (argc > param_idx) {
      srcpath = std::string(argv[param_idx]);
      srcpath = relative2absolut(srcpath);
      pcfg->set_src_path(srcpath);
    }
    param_idx++;
    if (argc > param_idx) {
      destpath = std::string(argv[param_idx]);
      destpath = relative2absolut(destpath);
      pcfg->set_dest_path(destpath);
    }
    param_idx++;
    if (argc > param_idx) {
      if (strtol(argv[param_idx], nullptr, 10) == LONG_MIN ||
          strtol(argv[param_idx], nullptr, 10) == LONG_MAX) {
        std::cout << "thread number must be a number" << std::endl;
        break;
      }
      thread_cnt = atoi(argv[param_idx]);
      pcfg->set_thread_cnt(thread_cnt);
    }
    param_idx++;
    if (argc > param_idx) {
      model_path = std::string(argv[param_idx]);
      pcfg->set_model_path(model_path);
    }
    param_idx++;
    if (argc > param_idx) {
      log_path = std::string(argv[param_idx]);
      pcfg->set_log_path(log_path);
    }
    param_idx++;
    if (argc > param_idx) {
      pthfn_lst = std::string(argv[param_idx]);
      pcfg->set_pthfn_lst(pthfn_lst);
    }

    pcfg->output();

    valid_args = true;
  } while (0);

  if (!valid_args) {
    std::cout << "usage:" << std::endl
#if defined(WITH_FILECONF)
              << "./X conf.json src_path dest_path thread_cnt" << std::endl;
#else
              << "./X src_path dest_path thread_cnt" << std::endl;
#endif
    LOG(_ERROR_, "invalid args");
    exit(EXIT_SUCCESS);
  }
}
