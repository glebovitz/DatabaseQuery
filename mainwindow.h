#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMetaObject>
#include <QAction>
#include <QDebug>
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QFile>
#include <QList>
#include <QStack>
#include "datastore.h"
#include "database.h"
#include "databasequery.h"

class QSqlQueryModel;
class DataStoreModel;

typedef QStack<QMetaObject::Connection> ConnectionList;
typedef QList<QAction *> ActionList;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum RunType { Join, Query, Insert, None };

//    RunType getRuntype() { return m_runtype; }

public slots:
    // Reports Menu
//    void on_actionTrials_triggered();
    void on_actionAllLicenses_triggered();
    void on_actionIDELicenses_triggered();
    void on_actionFreeLicenses_triggered();
    void on_actionAppLicenses_triggered();
    void on_actionUsers_triggered();
//    void on_actionCharges_triggered();

//    void on_actionProjectCount_triggered();
//    void on_actionPurchase_triggered();
//    void on_actionPurchased_License_triggered();
//    void on_actionProject_triggered();
//    void on_actionSubscriptions_triggered();
//    void on_actionUser_Query_triggered();
    void on_actionCleanup_triggered();

//    // File Menu
    void contextMenu_triggered(const QPoint & pos);
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionClose_triggered();
    void actionCopy_triggered();
    void importConnectionStrings();

    // Edit Menu
    void on_actionFilter_triggered();

    // Filter Dialog Slots
    void setUsername(QString str) { m_username = str; }
    void setEmail(QString str){ m_email = str; qDebug() << "email" << str;}
    void setUid(QString str){ m_uid = str; }

    // Internal Slots
    void append(const QString &string);
    void statusMessage(const QString &string);
    void enableActions(const bool flag);

//    void finishQuery();
//    void runQuery();
//    void runJoin();
    void displayResults(DataStore base);
    void errorMessageBox(const QString &title, const QString &text);

//    void addConnection(QMetaObject::Connection);
//    void removeConnection();

//    void setRunType(RunType type) { if (type <= None) m_runtype = type; }

signals:
    void queryComplete();

private: // Properties
    Ui::MainWindow *ui;
    DataStoreModel *m_model;
    QList<Database *> m_databases;
    ConnectionList m_connections;

    QFile m_file;
    QString m_savedFileName;
    ActionList m_actionList;
    DataStore m_connectionStrings;

    // Filter variables
    QString m_username;
    QString m_email;
    QString m_uid;
    DatabaseQuery m_dbq;

private: // Methods

    const QString selectFilter(QString);
    const QString userSelectFilter(QString);
    bool importDataFromFile();
    QString addSelectFilter(QString, QString);
    DataStore importDatabase(QString filename);
    QStringList connectionString(const QString &key) { return m_connectionStrings.dataHash()[key]; }
    const static QString connectionFile;
};

#endif // MAINWINDOW_H
