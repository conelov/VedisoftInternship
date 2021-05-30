//
// Created by dym on 27.05.2021.
//
#include "DBLink.hpp"
#include "DBLinkExecutor.hpp"
#include "src/PropertyGenerator.hpp"
#include "src/entities/Provider.hpp"
#include "src/utils.hpp"
#include <QCoreApplication>
#include <QFileInfo>
#include <QSqlQuery>

#ifndef NDEBUG
  #include <QDebug>
  #include <QSqlError>
#endif

#if defined(TABLE_PROVIDER) || defined(TABLE_CARD) || defined(TABLE_LOG)
  #error "^^ redefinition"
#endif

#define TABLE_LOG "log"
#define TABLE_PROVIDER "provider"
#define TABLE_CARD "card"

namespace
{
namespace dbs
{
const std::array init{
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
  QStringLiteral("CREATE UNIQUE INDEX " TABLE_LOG "_hash_uindex on " TABLE_LOG
                 " (hash);"),
  QStringLiteral(
      "CREATE TABLE " TABLE_CARD " ( "
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
//      "constraint " TABLE_CARD "_pk unique (id_own, id_" TABLE_PROVIDER ") "
      ");")
};
}
} // namespace

QString const DBLink::sqlDriveType= QStringLiteral("QSQLITE"),
    DBLink::dbFileName  = QStringLiteral("dbCache.sqlite"),
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

DBLink::DBLink()
    : dbFilePath(QCoreApplication::applicationDirPath() + '/' + dbFileName)
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
  assert(isValid());
  /// Validation end
}

bool DBLink::isValid() const
{
  QStringList tables= getDb().tables(),
              tablesDefault{ QStringLiteral(TABLE_PROVIDER),
                             QStringLiteral(TABLE_LOG),
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
  auto db= getDb();
  exec(QStringLiteral("PRAGMA foreign_keys = on; "), db);
  if (!db.transaction())
    assert(false);
  for (auto const &query : dbs::init) {
    exec(query, db);
  }
  if (!db.commit())
    assert(false);
}

auto DBLink::getDBHash() const
{
  using RetType= QPair<bool, uint>;
  QSqlQuery sql= exec(QStringLiteral("SELECT hash from " TABLE_LOG "; "));

#ifndef NDEBUG
  /// Check row count log table
  InvokeOnDestruct callBack{ [&sql] { assert(!sql.next()); } };
#endif

  if (!sql.first())
    return RetType{ false, {} };
  return RetType{ true, sql.value(0).value<uint>() };
}

void DBLink::insertToCache(const ProviderVector &providers) const
{
  auto const [dbHashExist, dbHash]= getDBHash();
  uint currentHash;

  if (dbHashExist && (currentHash= qHash(providers)) == dbHash)
    return;

  dropAll();

  auto db= getDb();
  QSqlQuery sql(db);

  db.transaction();
  if (!sql.prepare(
          QStringLiteral("INSERT INTO " TABLE_LOG "(hash) VALUES (?)"))) {
    assert(false);
  }
  sql.addBindValue(currentHash);
  exec(sql);
  db.commit();

  uint const idLog= sql.lastInsertId().toUInt();
  db.transaction();
  for (auto const &provider : providers) {
    if (!sql.prepare(QStringLiteral("INSERT INTO " TABLE_PROVIDER
                                    " (id_own,title,image_url,id_" TABLE_LOG
                                    ") VALUES (?,?,?,?)"))) {
      assert(false);
    }
    for (PropertyGenerator pg{ provider }; pg; ++pg) {
      if (QLatin1String{ pg.property().name() } == QLatin1String{ "cards" })
        continue;
      sql.addBindValue(pg.read());
    }
    sql.addBindValue(idLog);
    exec(sql);

    uint const idProvider= sql.lastInsertId().toUInt();
    for (auto const &card : provider.cards) {
      if (!sql.prepare(QStringLiteral(
              "INSERT INTO " TABLE_CARD " "
              "(featured_bool,id_own,credit,point,codes_count,title,image_url,"
              "currency,description,redeem_url,id_" TABLE_PROVIDER ") "
              "VALUES (?,?,?,?,?,?,?,?,?,?,?)"))) {
        assert(false);
      }
      for (PropertyGenerator pg{ card }; pg; ++pg) {
        if (QLatin1String{ pg.property().name() }.endsWith(QLatin1String{ "Str" })) {
          continue;
        }
        sql.addBindValue(pg.read());
      }
      sql.addBindValue(idProvider);
      exec(sql);
    }
  }
  db.commit();
}
void DBLink::dropAll() const
{
  auto db= getDb();
  db.transaction();
  for (auto const &query : { QStringLiteral("DELETE FROM " TABLE_CARD "; "),
                             QStringLiteral("DELETE FROM " TABLE_PROVIDER "; "),
                             QStringLiteral("DELETE FROM " TABLE_LOG "; ") }) {
    exec(query, db);
  }
  db.commit();
  exec(QStringLiteral("VACUUM"), db);
}
