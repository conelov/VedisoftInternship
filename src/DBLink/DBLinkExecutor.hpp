//
// Created by dym on 29.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_DBLINKEXECUTOR_HPP
#define VEDISOFTINTERNSHIP_DBLINKEXECUTOR_HPP
#include "DBLink.hpp"
#include "src/Logger/Logger.hpp"
#include <QSqlError>
#include <QSqlQuery>

#if defined(LOG_Error_PREPAPRESQL) || defined(LOG_Error_DBINVALID)
#    error "^^ redefinition"
#endif

#define LOG_Error_PREPAPRESQL LOG_Error << QStringLiteral("sql request preparation error");

#define LOG_Error_DBINVALID                                                                        \
    LOG_Error << QStringLiteral("invalid database state")                                          \
              << QStringLiteral("the database failed the check for the number of tables");

inline auto DBLink::getDb() const
{
    QSqlDatabase db;
    if (QSqlDatabase::contains(connectName))
        db = QSqlDatabase::database(connectName);
    else {
        db = QSqlDatabase::addDatabase(sqlDriveType, connectName);
        db.setDatabaseName(dbFilePath);
    }
    if (!db.open() || !db.isValid()) {
        LOG_Error << QStringLiteral("it is impossible to open a connection to the "
                                    "base or the state of the base is not valid");
    }
    return db;
}

inline auto DBLink::exec(const QString &query, QSqlDatabase &db) const
{
    QSqlQuery sql(db);
    sql.setForwardOnly(true);
    exec(sql, query);
    if (!sql.isActive() || sql.isValid()) {
        LOG_Error << QStringLiteral("pos request error, errc: ") << sql.lastError().text();
    }
    return sql;
}

inline auto DBLink::exec(const QString &query) const
{
    auto db = getDb();
    return exec(query, db);
}

inline void DBLink::exec(QSqlQuery &sql, const QString &query) const
{
    if (!sql.prepare(query)) {
        LOG_Error_PREPAPRESQL
    }
    exec(sql);
}

inline void DBLink::exec(QSqlQuery &sql) const
{
    if (!sql.exec()) {
        LOG_Error << QStringLiteral("request execution error, errc: ") << sql.lastError().text();
    }
}

#endif // VEDISOFTINTERNSHIP_DBLINKEXECUTOR_HPP
