/*
 * Copyright Seetatech 2017-2018
 */

#ifdef WITH_MONGODB

#include "include/mongoclient.h"
#include <memory>
#include <mongocxx/cursor.hpp>
#include <mongocxx/exception/query_exception.hpp>
#include <string>
#include "include/eupulogger4system.h"

MongoClient::MongoClient() {}
MongoClient::~MongoClient() {}

void MongoClient::init(const std::string& strUri, const std::string& strDb) {
  try {
    mongocxx::uri uri(strUri);
    client_ = mongocxx::client(uri);
    db_ = client_[strDb.c_str()];
  } catch (mongocxx::query_exception e) {
    LOG(_ERROR_, "init mongocxx::client(%s)[%s] failed", strUri.c_str(), strDb.c_str());
  }
}

#endif  // WITH_MONGODB
