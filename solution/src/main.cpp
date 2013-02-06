#include <QtGui>
#include "mainwindow.h"
/**
 * Method for running / showing main window
 * Based on Qt official documentation
 *
 * @author Lukas Raska (RAS0053)
 * @author Nokia corporation (Qt official documentation) under BSD licence
 * @version 1.0
 *
 * @param argc number of arguments
 * @param argv arguments
 *
 * @return status code of app
 */
int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    MainWindow mw;
    mw.show();
    return app.exec();
}
