/*
 * Copyright Seetatech 2017-2018
 */

#ifdef WITH_MYSQL

#include "include/mysqlclient.h"
#include <memory>
#include <string>
#include "include/eupulogger4system.h"

MysqlClient::MysqlClient() {}
MysqlClient::~MysqlClient() {
  if (conn_) {
    conn_->close();
  }
}

void MysqlClient::init(const std::string& host, const std::string& user,
                       const std::string& passwd) {
  try {
    do {
      driver_ = get_driver_instance();
      if (!driver_) {
        LOG(_ERROR_, "doQueryMySql() get_driver_instance() failed");
        break;
      }
      std::unique_ptr<sql::Connection> conn(
          driver_->connect(host.c_str(), user.c_str(), passwd.c_str()));
      if (!conn) {
        LOG(_ERROR_, "doQueryMySql() driver->connect() failed");
        break;
      }
      conn_.swap(conn);
      std::unique_ptr<sql::Statement> stmt(conn_->createStatement());
      if (!stmt) {
        LOG(_ERROR_, "doQueryMySql() conn->createStatement() failed");
        break;
      }
      stmt_.swap(stmt);
    } while (0);
  } catch (sql::SQLException& e) {
    LOG(_ERROR_, "MysqlClient::init() failed");
  }
}

#endif  // WITH_MYSQL
