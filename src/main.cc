#include <memory>
#include <vector>
#include "include/doX.h"
#include "include/showusage.h"

#if defined(SHARED_LIB)
#else
int main(int argc, char* argv[]) {
  const char* pth = argv[1];
  show_usage(argc, argv);
  std::vector<pthinf> tasks;
  tasks_collection(pth, tasks);
  do_X(tasks, 8);
  exit(EXIT_SUCCESS);
}
#endif
