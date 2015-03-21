#include "toolbar.h"
#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    w.show();
    
    //QToolBar window;
   /* Toolbar window;
      window.resize(300, 200);
      window.move(300, 300);
      window.setWindowTitle("QToolBar");
      window.show();
    //return app.exec();
*/
    return a.exec();
}
