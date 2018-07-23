#include "include/util.h"
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <vector>
#include "include/config.h"

void traversal_dir(const std::string& src_path, std::vector<pthinf>& pths) {
  DIR* d;
  struct dirent* file{nullptr};
  if (!(d = opendir(src_path.c_str()))) {
    struct stat sb;
    lstat(src_path.c_str(), &sb);
    if (S_ISREG(sb.st_mode)) {
      pthinf pi;
      pi.pthfn = src_path;
      pths.push_back(pi);
      std::string tmp1 = src_path;
      size_t pos = std::string::npos;
      while ((pos = tmp1.find("//")) != std::string::npos) tmp1.replace(pos, 2, "/");
      std::string tmp2 = tmp1.substr(0, tmp1.rfind("/"));
      Config::get_instance()->set_src_path(tmp2);
    }
    return;
  }

  std::string nxtpth;
  while ((file = readdir(d)) != nullptr) {
    if (strncmp(file->d_name, ".", 1) == 0) continue;

    nxtpth = src_path + "/" + file->d_name;
    struct stat sb;
    lstat(nxtpth.c_str(), &sb);

    if (S_ISDIR(sb.st_mode)) {
      traversal_dir(nxtpth, pths);
    } else {
      pthinf pi;
      pi.pthfn = nxtpth;
      pths.push_back(pi);
    }
  }  // while
  closedir(d);
}

void traversal_lst(const std::string& src_path, std::vector<pthinf>& pathfilenames) {
  FILE* fp;
  char* line = nullptr;
  size_t len = 0;
  ssize_t read;
  fp = fopen(src_path.c_str(), "r");
  if (fp == nullptr) return;

  pthinf fn;
  while ((read = getline(&line, &len, fp)) != -1) {
    line[read - 1] = '\0';
    fn.pthfn = std::string(line);
    pathfilenames.push_back(fn);
  }
  free(line);
  fclose(fp);
}

std::string relative2absolut(const std::string& const_relpth) {
  char dir[PATH_MAX]{0};
  char* ch = getcwd(dir, PATH_MAX);
  if (ch == nullptr) return "";

  std::string strcwd(dir);
  std::string relpth{const_relpth};
  relpth.erase(0, relpth.find_first_not_of(" "));
  relpth.erase(relpth.find_last_not_of(" ") + 1);
  if (relpth[0] == '/') return relpth;
  if (relpth[0] == '~') {
    snprintf(dir, sizeof(dir), "%s%s", getenv("HOME"), relpth.substr(1).c_str());
    return std::string(dir);
  }
  if (relpth[0] != '.') {
    strcwd += "/";
    strcwd += relpth;
    return strcwd;
  }

  std::vector<std::string> dirs;
  boost::split(dirs, strcwd, boost::is_any_of("/"), boost::token_compress_on);
  std::vector<std::string> relpths;
  boost::split(relpths, relpth, boost::is_any_of("/"), boost::token_compress_on);

  for (auto it : relpths) {
    if (it == ".") continue;
    if (it == ".." && dirs.size() > 0) {
      dirs.pop_back();
      continue;
    }
    dirs.push_back(it);
  }

  std::string abspth;
  for (auto it : dirs) {
    if (it != "") {
      abspth += "/";
      abspth += it;
    }
  }
  return abspth;
}

void mk_dest_dir(const std::vector<pthinf>& filenames) {
  std::vector<std::string> paths{};
  std::string src_path = Config::get_instance()->get_src_path();
  std::string dest_path = Config::get_instance()->get_dest_path();
  if (dest_path.empty()) {
    return;
  }
  size_t pos = std::string::npos;
  while ((pos = src_path.find("//")) != std::string::npos) src_path.replace(pos, 2, "/");
  while ((pos = dest_path.find("//")) != std::string::npos) dest_path.replace(pos, 2, "/");

  for (auto it : filenames) {
    std::string tmp = it.pthfn.substr(0, it.pthfn.rfind("/"));
    if (std::find(paths.begin(), paths.end(), tmp) == paths.end()) {
      tmp.replace(tmp.find(src_path), src_path.length(), dest_path);
      paths.push_back(tmp);
    }
  }

  // begin mkdir
  for (auto it : paths) {
    int i = 0;
    int iLen = 0;
    char* pszDir = nullptr;

    pszDir = strdup(it.c_str());
    iLen = strlen(pszDir);

    for (i = 0; i < iLen; ++i) {
      if (pszDir[i] == '/') {
        pszDir[i] = '\0';
        if (access(pszDir, 0) != 0) {
          mkdir(pszDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        pszDir[i] = '/';
      }
    }
    mkdir(pszDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    free(pszDir);
  }  // for
}
