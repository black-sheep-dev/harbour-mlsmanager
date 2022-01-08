#include <QtQuick>
#include <QCoreApplication>
#include <QStandardPaths>

#include <sailfishapp.h>

#include "enums.h"
#include "mlsmanager.h"


#ifdef QT_DEBUG

//some constants to parameterize.
const qint64 LOG_FILE_LIMIT = 3000000;
const QString LOG_PATH = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
const QString LOG_FILENAME = "/mlsmanager.log";

void redirectDebugMessages(QtMsgType type, const QMessageLogContext & context, const QString & str)
{
    Q_UNUSED(context)

    //thread safety
    QMutex mutex;
    mutex.lock();
    QString txt;

    //prepend timestamp to every message
    QString datetime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    //prepend a log level label to every message
    switch (type) {
    case QtDebugMsg:
        txt = QString("[Debug*] ");
        break;
    case QtWarningMsg:
        txt = QString("[Warning] ");
    break;
    case QtInfoMsg:
        txt = QString("[Info] ");
    break;
    case QtCriticalMsg:
        txt = QString("[Critical] ");
    break;
    case QtFatalMsg:
        txt = QString("[Fatal] ");
    }

    QString filePath = LOG_PATH + LOG_FILENAME;
    QFile outFile(filePath);

    //if file reached the limit, rotate to filename.1
    if(outFile.size() > LOG_FILE_LIMIT){
        //roll the log file.
        QFile::remove(filePath + ".1");
        QFile::rename(filePath, filePath + ".1");
        QFile::resize(filePath, 0);
    }

    //write message
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << datetime << txt << str << endl;

    //close fd
    outFile.close();
    mutex.unlock();
}

#endif

int main(int argc, char *argv[])
{
#ifndef QT_DEBUG
    auto uri = "org.nubecula.harbour.mlsmanager";
#else
#define uri "org.nubecula.harbour.mlsmanager"
#endif

#ifdef QT_DEBUG
    qInstallMessageHandler(redirectDebugMessages);
#endif

    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    app->setApplicationVersion(APP_VERSION);
    app->setApplicationName("mlsmanager");
    app->setOrganizationDomain("org.nubecula");
    app->setOrganizationName("org.nubecula");

    QScopedPointer<QQuickView> v(SailfishApp::createView());

    qmlRegisterUncreatableType<PackageType>(uri, 1, 0, "PackageType", "enumeration");

    qmlRegisterType<PackagesModel>(uri, 1, 0, "PackagesModel");
    qmlRegisterType<PackagesSortFilterModel>(uri, 1, 0, "PackagesSortFilterModel");

    qmlRegisterSingletonType<MlsManager>(uri,
                                         1,
                                         0,
                                         "MlsManager",
                                         [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {

        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        auto manager = new MlsManager();

        return manager;
    });


    v->setSource(SailfishApp::pathTo("qml/harbour-mlsmanager.qml"));
    v->show();

    return app->exec();
}
