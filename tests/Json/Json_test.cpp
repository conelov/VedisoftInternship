#include "src/MarshalJson.hpp"
#include "src/entities/Provider.hpp"
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
    QFile file("../fileInput/jsonSrcNet.json");
    assert(file.open(QIODevice::ReadOnly | QIODevice::Text));
    data= file.readAll();
  }
  QJsonParseError errorPtr{};
  jsonDocument= QJsonDocument::fromJson(data, &errorPtr);
  assert(errorPtr.error == QJsonParseError::NoError);
  return jsonDocument;
}();
}

TEST(MarshalJson, _1)
{
  auto const deserial= MarshalJson::deserialize(jsonDocumentSource);
  ASSERT_EQ(deserial.front().id, 1);
  ASSERT_EQ(deserial.front().title, QStringLiteral("Amazon.com"));
  ASSERT_EQ(
      deserial.front().image_url,
      QStringLiteral("http://g-ec2.images-amazon.com/images/G/01/social/"
                     "api-share/amazon_logo_500500.png"));
}
