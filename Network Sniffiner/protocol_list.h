#ifndef PROTOCOL_LIST_H
#define PROTOCOL_LIST_H

#include <QDialog>


namespace Ui {
class Protocol_List;
}

class Protocol_List : public QDialog
{
    Q_OBJECT
    
public:
    explicit Protocol_List(QWidget *parent = 0);
    ~Protocol_List();
    
private:
    Ui::Protocol_List *ui;
};

#endif // PROTOCOL_LIST_H
