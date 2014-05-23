#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include <QStringList>
#include <QVariantList>
#include "importsftable.h"

static QString queryName = QString("import Salesforce Query %1");

ImportSFTable::ImportSFTable(QString connectionName, QObject *parent) :
    Database(connectionName, parent)
{
}

ImportSFTable::ImportSFTable(QStringList connectionString, QObject *parent) :
    Database(connectionString, parent)
{
}

//void ImportSFTable::runQuery() {
//    // qDebug() << m_queryString;
//    // qDebug() << dbase.hostName() << dbase.userName() << dbase.password() << dbase.port() << dbase.databaseName();
//    qDebug() << "Starting Salesforce import" << dbase.connectionName();
//    if (dbase.open()) {
//        QVariantList owners;
//        QVariantList salesforceids;
//        if (m_dataList.count() > 0) {
//            m_dataHeader = m_dataList.takeFirst();
//            foreach (const QStringList &list, m_dataList) {
//                owners.append(list[0]);
//                salesforceids.append(list[1]);
//            }
//            QSqlQuery query(dbase);
//            if (query.prepare(m_queryString)) {
//                query.addBindValue(owners);
//                query.addBindValue(salesforceids);
//                if (query.execBatch()) {
//                    qDebug() << "rows affected" << query.numRowsAffected();
//                } else { QMessageBox::warning(0, queryName.arg("ExecBatch"), dbase.lastError().text()); }
//            } else { QMessageBox::warning(0, queryName.arg("Prepare"), dbase.lastError().text()); }
//        }
//        dbase.close();
//    } else { QMessageBox::warning(0, queryName.arg("Open"), dbase.lastError().text()); }
//    qDebug() << "DONE" << dbase.connectionName();
//    emit queryCompleted();
//}

void ImportSFTable::runQuery() {
        QVariantList owners;
        QVariantList salesforceids;
        if (m_dataList.count() > 0) {
            m_dataHeader = m_dataList.takeFirst();
            foreach (const QStringList &list, m_dataList) {
                owners.append(list[0]);
                salesforceids.append(list[1]);
            }
        }
}
