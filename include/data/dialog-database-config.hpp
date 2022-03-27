#ifndef DIALOGDATABASECONFIG_H
#define DIALOGDATABASECONFIG_H

#include <QDialog>
#include <QFutureWatcher>
#include <QFuture>
#include <QSqlDatabase>
#include <qtz/data/data-provider.hpp>
#include <qtz/security/key-ring.hpp>
#include "../qtz-widgets.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class DialogDatabaseConfig;
}
QT_END_NAMESPACE

class QTZ_WIDGETS_SHARED_EXPORT DialogDatabaseConfig : public QDialog {
    Q_OBJECT
    friend class GuiTest;
public:
    explicit DialogDatabaseConfig(bool doEncrypt = false, KeyRing* keyRing = nullptr, QWidget* parent = nullptr);
    ~DialogDatabaseConfig();

protected:
    void changeEvent(QEvent* e);

private:
    void initializeDatabaseSystems();
    void createConnections();
    bool testConnection();
    void readConnectionInfo();
    void writeConnectionInfo();
    void clearConnectionInfo();
    bool testDBOpen();

public slots:
    void accept();

private slots:
    void updateDatabaseType(int);
    void test();
    void handleTestResult();
    void handleActualConnection();
    void updateLocalHostStatus(bool);
    void updateDefaultPortStatus(bool);
    void updateSecurityOption(int);
    void lockGUI();
    void releaseGUI();

private:

    Ui::DialogDatabaseConfig* ui;
    DataProvider::Type currentType;
    bool tested;
    bool connected;
    QString lastCustomHost;
    quint32 lastCustomPort;
    QString lastSSLCA;
    QString lastSSLCert;
    QString lastSSLKey;
    // TODO: Move data operations into another thread
    QFutureWatcher<bool> FW_testDBOpen;
    QFutureWatcher<bool> FW_mainDBOpen;
    QFuture<bool> F_testDBOpen;
    QFuture<bool> F_mainDBOpen;

    QSqlDatabase testDB;
    KeyRing* m_keyRing;
    bool m_doEncrypt;
};

#endif // DIALOGDATABASECONFIG_H
