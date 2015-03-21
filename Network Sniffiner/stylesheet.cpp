#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stylesheet.h"


void StylesAplly()
{
    QFile File("style.cdb");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    qApp->setStyleSheet(StyleSheet);
}

