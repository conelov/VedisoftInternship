#include "src/DBLink/DBLink.hpp"
#include "src/DBLink/DBLinkExecutor.hpp"
#include "src/PropertyGenerator.hpp"
#include "testValues/values.hpp"
#include <gtest/gtest.h>

namespace
{}

TEST(DB, load)
{
  DBLink link;
  link.storeToDB(tstv::providers);
  auto const &provider= tstv::providers.front();
  auto db             = link.getDb();
  for (PropertyGenerator pg{ provider }; pg; ++pg) {
    auto const propName= QLatin1String{ pg.property().name() };
    if (propName == QLatin1String{ "cards" })
      continue;
    QSqlQuery sql;
    if (propName != QLatin1String{ "id" })
      sql= link.exec(QString("select ") + propName + " from provider", db);
    else
      sql= link.exec("select id_own from provider", db);
    ASSERT_TRUE(sql.first());
    ASSERT_EQ(pg.read(), sql.value(0));
  }
}

TEST(DB, store)
{
  DBLink link;

  link.storeToDB(tstv::providers);
  auto providers= link.loadFromDB();
  ASSERT_TRUE(std::equal(
      providers.cbegin(),
      providers.cend(),
      tstv::providers.cbegin(),
      [](Provider const &lhs, Provider const &rhs)
      {
        for (PropertyGenerator pgl{ lhs }, pgr{ rhs }; pgl && pgr;
             ++pgl, ++pgr) {
          if (QLatin1String{ pgl.property().name() } ==
              QLatin1String{ "cards" })
            continue;
          if (pgl.read() != pgr.read())
            return false;
        }
        return true;
      }));
}