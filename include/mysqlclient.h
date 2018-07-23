/*
 * Copyright 2017-2018 SeetaTech
 */

#ifndef INCLUDE_MYSQLCLIENT_H_
#define INCLUDE_MYSQLCLIENT_H_

#ifdef WITH_MYSQL

#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <memory>
#include <string>
#include <vector>
#include "include/aocsingleton.h"

class MysqlClient : public IAocSingleton<MysqlClient> {
 public:
  void init(const std::string&, const std::string&, const std::string&);
  sql::Statement* getstmt() { return stmt_.get(); }
  int64_t getcntinc() { return cnt_++; };

 private:
  MysqlClient();
  virtual ~MysqlClient();
  MysqlClient(const MysqlClient&);
  MysqlClient& operator=(const MysqlClient&);
  friend IAocSingleton<MysqlClient>;

 private:
  sql::Driver* driver_{nullptr};
  std::unique_ptr<sql::Connection> conn_{nullptr};
  std::unique_ptr<sql::Statement> stmt_{nullptr};
  int64_t cnt_;
};
#endif  // WITH_MYSQL

#endif  // INCLUDE_MYSQLCLIENT_H_
