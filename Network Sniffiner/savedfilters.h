#ifndef SAVEDFILTERS_H
#define SAVEDFILTERS_H

#include <QDialog>

namespace Ui {
class SavedFilters;
}

class SavedFilters : public QDialog
{
    Q_OBJECT
    
public:
    explicit SavedFilters(QWidget *parent = 0);
    ~SavedFilters();
    
private:
    Ui::SavedFilters *ui;
};

#endif // SAVEDFILTERS_H
