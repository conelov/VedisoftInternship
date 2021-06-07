//
// Created by dym on 27.05.2021.
//
#include "DBLink.hpp"
#include "DBLinkExecutor.hpp"
#include "src/Logger/Logger.hpp"
#include "src/PropertyGenerator.hpp"
#include "src/entities/Provider.hpp"
#include "src/utils.hpp"
#include <QCoreApplication>
#include <QFileInfo>
#include <QSqlQuery>

#if defined(TABLE_PROVIDER) || defined(TABLE_CARD) || defined(TABLE_LOG)
#    error "^^ redefinition"
#endif

#define TABLE_LOG "log"
#define TABLE_PROVIDER "provider"
#define TABLE_CARD "card"

namespace {
namespace dbs {
const std::array init {
    QStringLiteral("CREATE TABLE " TABLE_LOG " ( "
                   " id   integer not null         constraint " TABLE_LOG
                   "_pk primary key autoincrement, "
                   " hash integer not null "
                   ");"),
    QStringLiteral("CREATE TABLE " TABLE_PROVIDER " ("
                   " id integer PRIMARY KEY AUTOINCREMENT,"
                   " id_own integer NOT NULL,"
                   " title text NOT NULL,"
                   " image_url text NOT NULL,"
                   " id_" TABLE_LOG " integer NOT NULL REFERENCES "
                   "" TABLE_LOG " (id) ON DELETE CASCADE ON UPDATE CASCADE);"),
    QStringLiteral("CREATE UNIQUE INDEX " TABLE_LOG "_hash_uindex on " TABLE_LOG " (hash);"),
    QStringLiteral("CREATE TABLE " TABLE_CARD " ( "
                   " id             integer   primary key autoincrement, "
                   " featured_bool  integer   not null, "
                   " id_own         integer   not null, "
                   " credit         integer   not null, "
                   " point          integer   not null, "
                   " codes_count    integer   not null, "
                   " title          text      not null, "
                   " image_url      text      not null, "
                   " currency       text      not null, "
                   " description    text      not null, "
                   " redeem_url     text      not null, "
                   " id_" TABLE_PROVIDER " int not null "
                   " references " TABLE_PROVIDER " on update cascade on delete cascade"
                   //      ",     "
                   //      "constraint " TABLE_CARD "_pk unique (id_own, id_"
                   //      TABLE_PROVIDER ") "
                   ");")
};
}
} // namespace

QString const DBLink::sqlDriveType = QStringLiteral("QSQLITE"),
              DBLink::dbFileName = QStringLiteral("dbCache.sqlite"),
              DBLink::connectName = DBLink::sqlDriveType + '_' + DBLink::dbFileName;

void DBLink::close()
{
    if (QSqlDatabase::contains(connectName))
        QSqlDatabase::removeDatabase(connectName);
}

DBLink::~DBLink()
{
    close();
}

DBLink::DBLink() : dbFilePath(QCoreApplication::applicationDirPath() + '/' + dbFileName)
{
    /// Validation or prepare
    if (!QFileInfo::exists(dbFilePath)) {
        init();
    }
    if (!isValid()) {
        close();
        QFile::remove(dbFilePath);
        init();
    }
#ifndef NDEBUG
    if (!isValid()) {
        LOG_Error_DBINVALID
    }
#endif
    /// Validation end
}

bool DBLink::isValid() const
{
    QStringList tables = getDb().tables(),
                tablesDefault { QStringLiteral(TABLE_PROVIDER), QStringLiteral(TABLE_LOG),
                                QStringLiteral(TABLE_CARD) };
    tables.removeOne(QStringLiteral("sqlite_sequence"));
    if (tables.size() != tablesDefault.size())
        return false;

    tables.sort();
    tablesDefault.sort();
    return std::equal(tables.cbegin(), tables.cend(), tablesDefault.cbegin());
}

void DBLink::init() const
{
    auto db = getDb();
    exec(QStringLiteral("PRAGMA foreign_keys = on; "), db);
    if (!db.transaction())
        LOG_Error << QStringLiteral("unable to create request transaction");
    for (auto const &query : dbs::init) {
        exec(query, db);
    }
    if (!db.commit())
        LOG_Error << QStringLiteral("unable to commit the request transaction");
}

QPair<bool, uint> DBLink::getDBHash() const
{
    using RetType = QPair<bool, uint>;
    QSqlQuery sql = exec(QStringLiteral("SELECT hash from " TABLE_LOG "; "));

#ifndef NDEBUG
    /// Check row count log table
    InvokeOnDestruct callBack { [&sql] {
        if (sql.next()) {
            LOG_Error << QStringLiteral("database structure error: the number of "
                                        "rows in the hash table is not equal to "
                                        "1");
        }
    } };
#endif
    if (!sql.first())
        return RetType { false, {} };
    return RetType { true, sql.value(0).value<uint>() };
}

bool DBLink::storeToDB(const ProviderVector &providers) const
{
    auto const [dbHashExist, dbHash] = getDBHash();
    uint currentHash {};

    if (dbHashExist && (currentHash = qHash(providers)) == dbHash)
        return false;

    dropAll();

    auto db = getDb();
    QSqlQuery sql(db);

    db.transaction();
    if (!sql.prepare(QStringLiteral("INSERT INTO " TABLE_LOG "(hash) VALUES (?)"))) {
        LOG_Error_PREPAPRESQL
    }
    sql.addBindValue(currentHash);
    exec(sql);
    db.commit();

    uint const idLog = sql.lastInsertId().toUInt();
    db.transaction();
    for (auto const &provider : providers) {
        if (!sql.prepare(QStringLiteral("INSERT INTO " TABLE_PROVIDER
                                        " (id_own,title,image_url,id_" TABLE_LOG
                                        ") VALUES (?,?,?,?)"))) {
            LOG_Error_PREPAPRESQL
        }
        for (PropertyGenerator pg { provider }; pg; ++pg) {
            if (QLatin1String { pg.property().name() } == QLatin1String { "cards" })
                continue;
            sql.addBindValue(pg.read());
        }
        sql.addBindValue(idLog);
        exec(sql);

        uint const idProvider = sql.lastInsertId().toUInt();
        for (auto const &card : provider.cards) {
            if (!sql.prepare(QStringLiteral(
                        "INSERT INTO " TABLE_CARD " "
                        "(featured_bool,id_own,codes_count,credit,point,title,image_url,"
                        "currency,description,redeem_url,id_" TABLE_PROVIDER ") "
                        "VALUES (?,?,?,?,?,?,?,?,?,?,?)"))) {
                LOG_Error_PREPAPRESQL
            }
            for (PropertyGenerator pg { card }; pg; ++pg) {
                if (QLatin1String { pg.property().name() }.endsWith(QLatin1String { "Str" })) {
                    continue;
                }
                sql.addBindValue(pg.read());
            }
            sql.addBindValue(idProvider);
            exec(sql);
        }
    }
    db.commit();
    return true;
}

void DBLink::dropAll() const
{
    auto db = getDb();
    db.transaction();
    for (auto const &query : { QStringLiteral("DELETE FROM " TABLE_CARD "; "),
                               QStringLiteral("DELETE FROM " TABLE_PROVIDER "; "),
                               QStringLiteral("DELETE FROM " TABLE_LOG "; ") }) {
        exec(query, db);
    }
    db.commit();
    exec(QStringLiteral("VACUUM"), db);
}

ProviderVector DBLink::loadFromDB() const
{
#ifndef NDEBUG
    if (!isValid()) {
        LOG_Error_DBINVALID
    }
#endif

    auto sql =
            exec(QStringLiteral("SELECT "
                                " " TABLE_PROVIDER ".id AS '" TABLE_PROVIDER "_id', "
                                " " TABLE_PROVIDER ".id_own AS '" TABLE_PROVIDER "_id_own', "
                                " " TABLE_PROVIDER ".title AS '" TABLE_PROVIDER "_title', "
                                " " TABLE_PROVIDER ".image_url AS '" TABLE_PROVIDER "_image_url', "
                                " " TABLE_CARD ".featured_bool,"
                                " " TABLE_CARD ".id_own,"
                                " " TABLE_CARD ".codes_count,"
                                " " TABLE_CARD ".credit,"
                                " " TABLE_CARD ".point,"
                                " " TABLE_CARD ".title,"
                                " " TABLE_CARD ".image_url,"
                                " " TABLE_CARD ".currency,"
                                " " TABLE_CARD ".description,"
                                " " TABLE_CARD ".redeem_url"
                                " from " TABLE_PROVIDER " LEFT JOIN " TABLE_CARD
                                " ON " TABLE_PROVIDER ".id = " TABLE_CARD ".id_" TABLE_PROVIDER ""
                                " ORDER BY " TABLE_PROVIDER ".id"));

    if (!sql.first())
        return {};

    uint lastProviderId = std::numeric_limits<uint>::max();
    ProviderVector dataRet;
    do {
        auto const currProviderId = sql.value(0).toUInt();
        if (lastProviderId != currProviderId) {
            lastProviderId = currProviderId;
            /// New Provider
            dataRet.push_back({});
            int count = 1;
            for (PropertyGenerator pg(dataRet.back()); count < 4 && pg; ++pg, ++count) {
                pg.write(sql.value(count));
            }
        }

        int count = 4;
        dataRet.back().cards.push_back({});
        auto &card = dataRet.back().cards.back();
        for (PropertyGenerator pg { card }; count < 14 && pg; ++pg, ++count) {
            pg.write(sql.value(count));
        }
    } while (sql.next());

    return dataRet;
}
