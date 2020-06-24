#ifndef DIALOGINSERTITEM_H
#define DIALOGINSERTITEM_H

#include <QDialog>
#include "../qtz-widgets.hpp"

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
QT_END_NAMESPACE

class QTZ_WIDGETS_SHARED_EXPORT DialogInsertItem : public QDialog {
    Q_OBJECT
public:
    explicit DialogInsertItem(QSqlRelationalTableModel *model = 0,
                              QWidget *parent = 0);
    virtual void setModel(QSqlRelationalTableModel *model_);
    virtual bool insert();
private:
    QSqlRelationalTableModel *m_model;
public slots:
    void accept();
};

#endif // DIALOGINSERTITEM_H
