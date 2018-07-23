#include <time.h>
#include <cstdio>
#if defined(WITH_OPENCV)
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif
#include "include/Xthread.h"
#include "include/config.h"
#include "include/eupulogger.h"
#include "include/eupulogger4system.h"
#include "include/jsonreaderinst.h"
#include "include/showusage.h"
#include "include/util.h"

void tasks_collection(const char*, std::vector<pthinf>&);
void do_X(std::vector<pthinf>& tasks, int thread_cnt);

void init_system(int worker_cnt);
void stop_system(int sig);
void exit_system();
void tasks_distribution(const std::vector<pthinf>&);

std::vector<XThread*> g_workers;

void do_X_impl(std::vector<pthinf>& tasks, int thread_cnt) {
  init_system(thread_cnt);
  tasks_distribution(tasks);
  for (auto it : g_workers) it->start();
  for (auto it : g_workers) pthread_join(it->get_pid(), nullptr);

  exit_system();
#if defined(WITH_FILECONF)
  JsonReaderInst::release();
#endif
  Config::release();
  CEupuLogger4System::Release();
}

void init_system(int worker_cnt) {
  LOG(_INFO_, "init_system()");

  for (int i = 0; i < worker_cnt; ++i) {
    XThread* pthrd = new XThread(i);
    if (pthrd) {
      g_workers.push_back(pthrd);
    }
  }
}

void stop_system(int sig) {
  LOG(_INFO_, "stop_system(%d)", sig);
  for (auto it : g_workers) it->stop();
}

void exit_system() {
  LOG(_INFO_, "exit_system()");
  for (auto it : g_workers) delete it;
  g_workers.clear();
}

void tasks_distribution(const std::vector<pthinf>& pathfilenames) {
  std::vector<std::vector<pthinf>> tasks;
  std::vector<pthinf> emptyitem;
  emptyitem.reserve(125000);
  for (size_t i = 0; i < g_workers.size(); ++i) tasks.push_back(emptyitem);

  int idx = 0;
  for (auto it : pathfilenames) {
    tasks[idx % g_workers.size()].push_back(it);
    idx++;
  }

  idx = 0;
  for (auto it : tasks) {
    g_workers[idx]->set_filenames(it);
    idx++;
  }
}

void tasks_collection(const char* srcpath, std::vector<pthinf>& pathfilenames) {
  std::string pthfn_lst = Config::get_instance()->get_pthfn_lst();
  if (pthfn_lst == "") {
    traversal_dir(srcpath, pathfilenames);
    LOG(_INFO_, "tasks_collection() traversal_dir()");
  } else {
    traversal_lst(pthfn_lst, pathfilenames);
    LOG(_INFO_, "tasks_collection() traversal_lst()");
  }
  uint32_t img_cnt = pathfilenames.size();
  LOG(_INFO_, "tasks_collection() get %d image files", img_cnt);
}

void do_X(std::vector<pthinf>& tasks, int thread_cnt) { do_X_impl(tasks, thread_cnt); }
