## Архитектура

### Сущности:

#### qml:

Состоит из qml файлов в папке qml:

* **Card**. Представление карты. *Tooltip* при наведении
* **Main**. Основной элемент окна. Состоит из вертикального listView, вложенного в него горизонтального listView,
  содержащего Card. *Вертикальный, горизонтальный скролл*
* Entities папка
    * **ErrDialog**. Окно уведомления об ошибках

*Анимированный элемент `BusyIndicator` при ожидании данных*

#### cpp:

Папка impl:

* **LogMsg** Класс handler над сторонним библиотечным логером. Настраивается из config файла
* **MarshalJson** Класс, с набором статических функций, реализующих десериализацию json
* **DBLink** Класс, с набором статических функций, реализующих общение с базой данных
* **ConfigLoader** Класс, инкапсулирующий `QSettings`. Читает конфигурацию из файла `.ini`
* **NetManager** `Q_Object` класс, живет в отдельном потоке, общается с сервером. Отвечает основному
  потоку `QJsonDocument`
* **AppEngine** `Q_Object` класс, обеспечивающий логику работы cpp части приложения. Живет в main потоке
* Вспомогательные `Q_GADGET` струткуры для обмена данными. Entities папка
    * **Card** Описывает карту. *Поля `cahs`,`point`,`image`, `id` служебный*
    * **Provider** Описывает провайдера. *Поля `title`,`linkCards`, `id` служебный*
    * **ProvidersContain** Агрегат. Связывает `Card`,`Provider` в одну сущность для общения с qml
      
**Config** файл содержит url подключения к сети, уровень логирования

Схема взаимодействия:

1. Создается `QQmlApplicationEngine`, **AppEngine**.
1. **AppEngine** читает конфиг файл, принимает состояние. По необходимости инициализирует **LogMsg**. 
1. **AppEngine** создает экземпляр `QThread`, **NetManager**. Подписывается на сигнал **NetManager** о получении данных,
   связывает его слот о запросе. Перемещает его в `QThread`.
1. **AppEngine** сигналит **NetManager** о запросе данных. Ждет данных.
1. **AppEngine** парсит json, обновляет кэш в бд, составляет **ProvidersContain**, отправляет его на сторону qml.