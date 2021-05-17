#include "../src/MarshalJson.hpp"
#include "src/entities/aggregates.hpp"
#include <gtest/gtest.h>

#ifndef NDEBUG
  #include <QDebug>
#endif

namespace
{
static QJsonDocument const jsonDocumentSource= []
{
  QJsonDocument jsonDocument;
  QByteArray data;
  {
    QFile file("../fileInput/jsonSrc.json");
    assert(file.open(QIODevice::ReadOnly | QIODevice::Text));
    data= file.readAll();
  }
  QJsonParseError errorPtr{};
  jsonDocument= QJsonDocument::fromJson(data, &errorPtr);
  assert(errorPtr.error == QJsonParseError::NoError);
  return jsonDocument;
}();
}

TEST(MarhalJson, _1)
{
  auto const deserial= MarshalJson::deserialize(jsonDocumentSource);
  for (auto const &provider : deserial) {
    ASSERT_EQ(provider.id, 2);
    ASSERT_EQ(provider.title, QStringLiteral("Amazon.com"));
    ASSERT_EQ(
        provider.imageUrl,
        QStringLiteral("http://g-ec2.images-amazon.com/images/G/01/social/"
                       "api-share/amazon_logo_500500.png"));
  }
}
