/*
 * Copyright Seetatech 2017-2018
 */

#if defined(WITH_FILECONF)

#include "include/jsonreaderinst.h"
#include <memory>
#include <string>

JsonReaderInst::JsonReaderInst() {}
JsonReaderInst::~JsonReaderInst() {}

void JsonReaderInst::init() {
  std::unique_ptr<Json::CharReader> pcr(crb_.newCharReader());
  pcr_.swap(pcr);
}

#endif
