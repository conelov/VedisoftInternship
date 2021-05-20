#include <QAbstractListModel>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

namespace
{
class Card {
  Q_GADGET
  Q_PROPERTY(QString credit MEMBER credit)
  Q_PROPERTY(QString point MEMBER point)

public:
  QString credit, point;
  bool operator==(const Card &rhs) const
  {
    return credit == rhs.credit && point == rhs.point;
  }
  bool operator!=(const Card &rhs) const
  {
    return !(rhs == *this);
  }
};
} // namespace
Q_DECLARE_METATYPE(Card)

namespace
{
class Provider {
  Q_GADGET
  Q_PROPERTY(QString title MEMBER title)
  Q_PROPERTY(QVariantList cards MEMBER cards)

public:
  QString title;
  QVariantList cards;

  bool operator==(const Provider &rhs) const
  {
    return title == rhs.title && cards == rhs.cards;
  }
  bool operator!=(const Provider &rhs) const
  {
    return !(rhs == *this);
  }
};
} // namespace
Q_DECLARE_METATYPE(Provider)

namespace
{
QVector<Provider> const providers{
  {
      "Amazon.com",
      { QVariant::fromValue(Card{ "$1,000,000.00", "20,000" }),
        QVariant::fromValue(Card{ "$0.00", "0" }) },

  },
  {
      "iTunes",
      { QVariant::fromValue(Card{ "$123.00", "990,000" }),
        QVariant::fromValue(Card{ "$0.99", "1" }),
        QVariant::fromValue(Card{ "$999,000.09", "25,000" }) },

  }
};

class ModelProviderCard: public QAbstractListModel {
  Q_OBJECT

public:
  explicit ModelProviderCard(QObject *parent= nullptr)
      : QAbstractListModel(parent)
  {}
  // Basic functionality:
  int rowCount(const QModelIndex &parent= QModelIndex()) const override
  {
    // For list models only the root node (an invalid parent) should return the
    // list's size. For all other (valid) parents, rowCount() should return 0 so
    // that it does not become a tree model.
    if (parent.isValid())
      return 0;

    return providers.count();
  }

  QVariant
  data(const QModelIndex &index, int role= Qt::DisplayRole) const override
  {
    if (!index.isValid() || role != Qt::DisplayRole)
      return QVariant();

    return QVariant::fromValue(providers[index.row()]);
  }
};

class AppEngine final : public QObject{
  Q_OBJECT
  Q_PROPERTY(ModelProviderCard _pcModel READ pcModel)    /// Provider Card Model

  ModelProviderCard _pcModel;
public:
  Q_INVOKABLE ModelProviderCard const & pcModel() const{
    return _pcModel;
  }



};
} // namespace

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine,
      &QQmlApplicationEngine::objectCreated,
      &app,
      [url](QObject *obj, const QUrl &objUrl)
      {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  ModelProviderCard model;
  engine.rootContext()->setContextProperty("md", &model);

  return QGuiApplication::exec();
}

#include "main.moc"
