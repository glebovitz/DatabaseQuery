#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QAction>
#include <QClipboard>
#include <QHash>
#include <QList>
#include <QListIterator>
#include <QMetaObject>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>
#include <QSortFilterProxyModel>

#include "database.h"
#include "databasedialog.h"
#include "databasequery.h"
#include "databasequeryrequest.h"
#include "datastore.h"
#include "datastoremodel.h"
#include "querystrings.h"

const QString AllwhereClause = QString()
        + "WHERE "
        + "(bundle.id <> 0) "
//        + "AND (one_time_charge.completed IS NULL) "
//        + "AND ( " + LICENSE_EXPIRED + ") "
//        + "AND (NOT " + LICENSE_ACTIVATED + ")"
        ;

const QString FPASwhereClause = QString()
        + "WHERE "
        + "(bundle.id <> 0) "
        + "AND purchased_license.type LIKE 'app%'"
//        + "AND (one_time_charge.completed IS NULL) "
//        + "AND ( " + LICENSE_EXPIRED + ") "
//        + "AND (NOT " + LICENSE_ACTIVATED + ")"
        ;

const QString IDEwhereClause = QString()
        + "WHERE "
        + "(bundle.id <> 0) "
        + "AND purchased_license.type LIKE 'ide%'"
//        + "AND (one_time_charge.completed IS NULL) "
//        + "AND ( " + LICENSE_EXPIRED + ") "
//        + "AND (NOT " + LICENSE_ACTIVATED + ")"
        ;

const QString UserwhereClause = QString()
//        + "WHERE "
//        + "(bundle.id <> 0) "
//        + "AND purchased_license.type LIKE 'ide%'"
        ;

QString MainWindow::addSelectFilter(QString where, QString str) {
    if (!str.isEmpty()) {
        if (where.isEmpty()) {
            where = "WHERE " + str;
        } else {
            where += "AND " + str;
        }
    }
    return where;
}

const QString MainWindow::selectFilter(QString where) {
    QString condition;
    if (!m_username.isEmpty()) {
        condition = QString("account.username = '%1'").arg(m_username);
    } else if (!m_email.isEmpty()) {
        condition = QString("account.email LIKE '%1\%'").arg(m_email);
    } else if (!m_uid.isEmpty()) {
        condition += QString( "account.owner = '%1'").arg(m_uid);
    }
    return addSelectFilter(where, condition);
}

const QString MainWindow::userSelectFilter(QString where) {
    QString condition;
    if (!m_username.isEmpty()) {
        condition = QString("profile.normalized_handle = '%1'").arg(m_username);
    } else if (!m_email.isEmpty()) {
        condition = QString("fp_user.email LIKE '%1\%'").arg(m_email);
    } else if (!m_uid.isEmpty()) {
        condition += QString( "fp_user.id = '%1'").arg(m_uid);
    }
    return addSelectFilter(where, condition);
}

void MainWindow::on_actionIDELicenses_triggered() {
    statusMessage("Starting individual purchase");
    qDebug() << selectFilter(AllwhereClause);
    m_dbq.addQueryRequest(connectionString("BLUE") /*connectionString("BLUE")*/,
                          licenseQueryString + selectFilter(IDEwhereClause));
    m_dbq.start();
}

void MainWindow::on_actionAppLicenses_triggered() {
    statusMessage("Starting individual purchase");
    qDebug() << selectFilter(AllwhereClause);
    m_dbq.addQueryRequest(connectionString("BLUE") /*connectionString("BLUE")*/,
                          licenseQueryString + selectFilter(FPASwhereClause));
    m_dbq.start();
}

void MainWindow::on_actionCleanup_triggered() {
    QSet<QString> id_headerSet = id_headers.toSet();
    QHash<QString, int> headerHash;
    QHash<int, QStringList> columnHash;

    if (m_model->rowCount() > 0) {
        int index = 0;
        foreach (QString name, m_model->dataHeader()) {
            if (id_headerSet.contains(name)) {
                headerHash[name] = index;
            }
            index++;
        }
        foreach (QStringList list, m_model->dataList()) {
            foreach (int value, headerHash.values()) {
                if (!list[value].isEmpty() && list[value] != "0") {
                    columnHash[value].append(list[value]);
                }
            }
        }
        qDebug() << headerHash.values();

        QHash<QString, int>::iterator i;
        for (i = headerHash.begin(); i != headerHash.end(); i++) {
            columnHash[i.value()].removeDuplicates();
            qDebug() << i.key() + ":" << i.value() << columnHash[i.value()];
        }

    }
}

void MainWindow::on_actionAllLicenses_triggered() {
    statusMessage("Starting individual purchase");
    qDebug() << selectFilter(AllwhereClause);

    m_dbq.addQueryRequest(connectionString("BLUE"), licenseQueryString + selectFilter(AllwhereClause));
    m_dbq.addQueryRequest(connectionString("SILVER"), userQueryString, true);
    m_dbq.setRunType(DatabaseQuery::Join);
    m_dbq.start();
}

void MainWindow::on_actionFreeLicenses_triggered() {
    qDebug() << "Free";
    statusMessage("Starting Free");
    qDebug() << selectFilter(AllwhereClause);

    m_dbq.addQueryRequest(connectionString("BLUE"), freeQueryString + selectFilter(AllwhereClause));
    m_dbq.addQueryRequest(connectionString("SILVER"), userQueryString, true);
    m_dbq.setRunType(DatabaseQuery::Join);
    m_dbq.start();
}

void MainWindow::on_actionUsers_triggered() {
    statusMessage("Starting Users");
    qDebug() << selectFilter(AllwhereClause);
    m_dbq.addQueryRequest(connectionString("SILVER"),
                          userQueryString + selectFilter(UserwhereClause));
    m_dbq.start();
}

//void MainWindow::on_actionSubscriptions_triggered() {
//    statusMessage("Starting Subscription License");
//    clearDatabases();
//    Database *subscriptionsDB = new Database(connectionString("BLUE"), this);
//    subscriptionsDB->setQueryString(subscriptionQuery);
//    addDatabase(subscriptionsDB);

//    Database *userDB = new Database(connectionString("SILVER"), this);
//    userDB->setQueryString(userQueryString);
//    userDB->setHash();
//    addDatabase(userDB);

//    setRunType(Join);
//    runQuery();
//    qDebug() << "subscription query done";
//}

//void MainWindow::on_actionUser_Query_triggered() {
//    QMessageBox::information(this, "User Query String", userQueryString, QMessageBox::Ok);
//}

//void MainWindow::on_actionCharges_triggered() {
//    qDebug() << "Charges";
//    statusMessage("Starting Charges");
//    clearDatabases();
//    Database *licenseDB = new Database(connectionString("BLUE"), this);
//    licenseDB->setQueryString(oneTimeChargeQueryString);
//    addDatabase(licenseDB);

//    Database *userDB = new Database(connectionString("SILVER"), this);
//    userDB->setQueryString(userQueryString);
//    userDB->setHash();
//    addDatabase(userDB);

//    setRunType(Join);
//    runQuery();
//}

//void MainWindow::on_actionProject_triggered() {
//    statusMessage("Starting Project");
//    clearDatabases();
//    Database *merchantDB = new Database(connectionString("SILVER"), this);
//    merchantDB->setQueryString(SELECT + " * FROM public.project;");
//    addDatabase(merchantDB);

//    setRunType(Query);
//    runQuery();
//}

//void MainWindow::on_actionProjectCount_triggered() {
//    statusMessage("Starting Project Count");
//    clearDatabases();
//    Database *licenseDB = new Database(connectionString("BLUE"), this);
//    licenseDB->setQueryString(trialQueryString);
//    addDatabase(licenseDB);

//    setRunType(Query);
//    runQuery();
//}

//void MainWindow::on_actionPurchase_triggered() {
//    statusMessage("Starting Purchase");
//    clearDatabases();
//    Database *merchantDB = new Database(connectionString("BLUE"), this);
//    merchantDB->setQueryString(SELECT + " * FROM public.purchase;");
//    addDatabase(merchantDB);

//    setRunType(Query);
//    runQuery();
//}

//void MainWindow::on_actionPurchased_License_triggered() {
//    statusMessage("Starting Purchased Licenses");
//    clearDatabases();
//    Database *merchantDB = new Database(connectionString("BLUE"), this);
//    merchantDB->setQueryString(SELECT + " * FROM public.purchased_license;");
//    addDatabase(merchantDB);

//    setRunType(Query);
//    runQuery();
//}

//void MainWindow::on_actionTrials_triggered() {
//    statusMessage("Starting Trials");
//    Databases();
//    Database *licenseDB = new Database(connectionString("BLUE"), this);
//    licenseDB->setQueryString(trialQueryString);
//    addDatabase(licenseDB);

//    Database *userDB = new Database(connectionString("SILVER"), this);
//    userDB->setQueryString(userQueryString);
//    userDB->setHash();
//    addDatabase(userDB);

//    setRunType(Join);
//    setRunType(Query);
//    runQuery();
//}



