/*
 * Copyright 2017-2018 Seetatech
 */

#ifndef INCLUDE_UTIL_H_
#define INCLUDE_UTIL_H_

#include <string>
#include <vector>
#include "pthinf.h"

void traversal_dir(const std::string& rootpth, std::vector<pthinf>& pths);
void traversal_lst(const std::string& path, std::vector<pthinf>&);
std::string relative2absolut(const std::string& relpth);
void mk_dest_dir(const std::vector<pthinf>& dstpth);

#endif  // INCLUDE_UTIL_H_
