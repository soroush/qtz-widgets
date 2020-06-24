﻿#ifndef QTZ_TEXTEDITORWINDOW_HPP
#define QTZ_TEXTEDITORWINDOW_HPP

#include <QMainWindow>
#include "../qtz-widgets.hpp"

QT_BEGIN_NAMESPACE
class QFontComboBox;
class QTextCharFormat;

namespace Ui {
class textEditorWindow;
}
QT_END_NAMESPACE

class QTZ_WIDGETS_SHARED_EXPORT TextEditorWindow : public QMainWindow {
    Q_OBJECT
    Q_PROPERTY(QString text READ toHtml WRITE setText NOTIFY textChanged USER true)

public:
    explicit TextEditorWindow(QWidget* parent = 0);
    ~TextEditorWindow();

    QString toPlainText() const;
    QString toHtml() const;

public slots:
    void setText(QString);

signals:
    void textChanged(QString);

protected:
    void changeEvent(QEvent* e);

private:
    Ui::textEditorWindow* ui;
    void setupToolbars();
    QFontComboBox* fontCombo;

private slots:
    //    void delete_();
    //    void find();
    //    void replace();
    void mergeFormatOnWordOrSelection(const QTextCharFormat& format);
    void bold(bool);
    void italic(bool);
    void underline(bool);
    void strickout(bool);
    void changeFont(QFont);
    void updateStatus();
};

#endif // QTZ_TEXTEDITORWINDOW_HPP
