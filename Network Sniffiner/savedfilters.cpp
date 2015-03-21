#include "savedfilters.h"
#include "ui_savedfilters.h"

SavedFilters::SavedFilters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SavedFilters)
{
    ui->setupUi(this);
}

SavedFilters::~SavedFilters()
{
    delete ui;
}
