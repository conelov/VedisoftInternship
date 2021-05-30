//
// Created by dym on 29.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_DBLINKEXECUTOR_HPP
#define VEDISOFTINTERNSHIP_DBLINKEXECUTOR_HPP
#include "DBLink.hpp"
#include <QSqlQuery>

#ifndef NDEBUG
#include <QDebug>
#include <QSqlError>
#endif

inline auto DBLink::getDb() const
{
  QSqlDatabase db;
  if (QSqlDatabase::contains(connectName))
    db= QSqlDatabase::database(connectName);
  else {
    db= QSqlDatabase::addDatabase(sqlDriveType, connectName);
    db.setDatabaseName(dbFilePath);
  }
  if (!db.open() && db.isValid()) {
    qDebug() << "connectName:" << connectName << "filepath:" << dbFilePath;
    assert(false);
  }
  return db;
}

inline auto DBLink::exec(const QString &query, QSqlDatabase &db) const
{
  QSqlQuery sql(db);
  sql.setForwardOnly(true);
  exec(sql, query);
  assert(sql.isActive());
  return sql;
}

inline auto DBLink::exec(const QString &query) const
{
  auto db= getDb();
  return exec(query, db);
}

inline void DBLink::exec(QSqlQuery &sql, const QString &query) const
{
  sql.prepare(query);
  exec(sql);
}

inline void DBLink::exec(QSqlQuery &sql) const
{
  if (!sql.exec()) {
    qDebug() << "err exec:" << sql.lastQuery() << '\n' << sql.lastError();
    assert(false);
  }
}

#endif // VEDISOFTINTERNSHIP_DBLINKEXECUTOR_HPP
