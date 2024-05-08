#include <QApplication>
#include <QSurfaceFormat>
#include <QOpenGLDebugLogger>
#include "glwidget.h"

void handleLoggedMessage(const QOpenGLDebugMessage &debugMessage)
{
    if (debugMessage.id() == 131185)  //for nvidia buffer create message
        return;
    qDebug() << debugMessage;
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format = QSurfaceFormat::defaultFormat();    
    format.setProfile(QSurfaceFormat::CoreProfile);
    //format.setVersion(4,5);
    format.setVersion(3,3);
    format.setOptions(QSurfaceFormat::DebugContext);
    QSurfaceFormat::setDefaultFormat(format);
    qDebug() << "GL version: " << format.version();

    GLWidget w;
    w.show();

    QOpenGLDebugLogger *logger = new QOpenGLDebugLogger();
    logger->initialize();
    QObject::connect(logger, &QOpenGLDebugLogger::messageLogged, handleLoggedMessage);
    logger->startLogging();

    return app.exec();
}
