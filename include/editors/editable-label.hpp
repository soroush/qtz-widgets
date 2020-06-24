#ifndef QTZ_EDITABLELABEL_HPP
#define QTZ_EDITABLELABEL_HPP

#include <QWidget>
#include <QLabel>
#include <qtz/core/qtz-core.hpp>
#include "../qtz-widgets.hpp"

QT_BEGIN_NAMESPACE
class QVBoxLayout;

namespace Ui {
class EditableLabel;
}
QT_END_NAMESPACE

class TextEditorWindow;

class QTZ_WIDGETS_SHARED_EXPORT EditableLabel : public QWidget {
    Q_OBJECT

public:
    explicit EditableLabel(QWidget* parent = 0);
    ~EditableLabel();

signals:

public slots:
    void startEditig();
    void finishEditig();

protected:
    void changeEvent(QEvent* e);

private:
    Ui::EditableLabel* ui;
    enum Status_t {Normal = 0, Editing = 1};
    Status_t currentStatus;
    QVBoxLayout* mainLayout;
    QLabel m_label;
    TextEditorWindow* editor;
};

#endif // QTZ_EDITABLELABEL_HPP
