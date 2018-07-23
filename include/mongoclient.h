/*
 * Copyright 2017-2018 SeetaTech
 */

#ifndef INCLUDE_MONGOCLIENT_H_
#define INCLUDE_MONGOCLIENT_H_

#ifdef WITH_MONGODB

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/options/find.hpp>
#include <mongocxx/uri.hpp>
#include <string>
#include <vector>
#include "include/aocsingleton.h"

class MongoClient : public IAocSingleton<MongoClient> {
 public:
  void init(const std::string&, const std::string&);
  mongocxx::database& getdb() { return db_; }

 private:
  MongoClient();
  virtual ~MongoClient();
  MongoClient(const MongoClient&);
  MongoClient& operator=(const MongoClient&);
  friend IAocSingleton<MongoClient>;

 private:
  mongocxx::instance inst_{};
  mongocxx::client client_;
  mongocxx::database db_;
};

#endif  // WITH_MONGODB

#endif  // INCLUDE_MONGOCLIENT_H_
