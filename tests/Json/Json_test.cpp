#include "src/MarshalJson/MarshalJson.hpp"
#include "src/entities/Provider.hpp"
#include <gtest/gtest.h>

TEST(MarshalJson, _1)
{
    /// TODO: file input
    auto const deserial= MarshalJson::deserialize(jsonDocumentSource);
  ASSERT_EQ(deserial.front().id, 1);
  ASSERT_EQ(deserial.front().title, QStringLiteral("Amazon.com"));
  ASSERT_EQ(
      deserial.front().image_url,
      QStringLiteral("http://g-ec2.images-amazon.com/images/G/01/social/"
                     "api-share/amazon_logo_500500.png"));
}
