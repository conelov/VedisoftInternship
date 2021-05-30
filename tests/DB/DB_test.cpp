#include "src/DBLink/DBLink.hpp"
#include "src/DBLink/DBLinkExecutor.hpp"
#include "src/PropertyGenerator.hpp"
#include "testValues/values.hpp"
#include <gtest/gtest.h>

namespace
{}

TEST(DB, _1)
{
  DBLink link;
  link.insertToCache(tstv::providers);
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