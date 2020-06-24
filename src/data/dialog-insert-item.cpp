#include "data/dialog-insert-item.hpp"

DialogInsertItem::DialogInsertItem(QSqlRelationalTableModel *model,
                                   QWidget *parent) :
    QDialog(parent), m_model(model)
{
}

void DialogInsertItem::setModel(QSqlRelationalTableModel *model_)
{
    this->m_model = model_;
}

bool DialogInsertItem::insert()
{
    return false;
}

void DialogInsertItem::accept()
{
    if(this->insert()) {
        QDialog::accept();
    }
    else {
        // TODO show error
    }
}
