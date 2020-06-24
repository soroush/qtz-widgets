#ifndef EDITTABLEWIDGET_H
#define EDITTABLEWIDGET_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include "data/dialog-insert-item.hpp"
#include "data/dialog-edit-item.hpp"
#include "qtz-widgets.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class EditTableWidget;
}
QT_END_NAMESPACE

class QTZ_WIDGETS_SHARED_EXPORT WidgetEditTable : public QWidget {
    Q_OBJECT

public:
    explicit WidgetEditTable(QWidget *parent = 0);
    ~WidgetEditTable();

    void setModel(QSqlRelationalTableModel *model);

signals:
    void add();
    void remove(QModelIndexList);
    void edit(QModelIndex);
    void refresh();
    void revert();
    void save();

protected:
    void changeEvent(QEvent *e);

protected slots:
    void emitRemove();
    void emitEdit();

private:
    Ui::EditTableWidget *ui;

};

#endif // EDITTABLEWIDGET_H
