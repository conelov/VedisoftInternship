//
// Created by dym on 27.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_DBLINK_HPP
#define VEDISOFTINTERNSHIP_DBLINK_HPP
#include "src/deffwd.hpp"
#include <QString>
#include <QPair>

class QSqlDatabase;
class QSqlQuery;

class DBLink {
public:
  static QString const sqlDriveType, dbFileName, connectName;

  static void close();

private:
  QString const dbFilePath;

public:
  ~DBLink();
  DBLink();

  bool storeToDB(ProviderVector const &providers) const;
  ProviderVector loadFromDB() const;

  /// For unit-test
  /// QSqlQuery type return
  auto exec(const QString &query, QSqlDatabase &db) const;
  auto exec(const QString &query) const;

  void exec(QSqlQuery &sql) const;
  void exec(QSqlQuery &sql, const QString &query) const;

  /// QSqlDatabase type return
  auto getDb() const;

  /// val or null
  QPair<bool, uint> getDBHash() const;

private:
  void init() const;

  bool isValid() const;

  void dropAll() const;
};

#endif // VEDISOFTINTERNSHIP_DBLINK_HPP
