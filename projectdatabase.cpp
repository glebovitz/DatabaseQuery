#include "projectdatabase.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QDate>
#include <QList>
#include <QStringList>
#include <QVariant>
#include <QApplication>
#include <QMessageBox>
#include <iostream>

//static QString queryString =
//        QString("SELECT\n")
//        + "\"project\".\"author\" AS \"Author\", \n"
//        + "COUNT(\"project\".\"author\") AS \"Projects\",\n"
//        + "FROM \"public\".\"project\" AS \"project\"\n"
//        + "GROUP BY \"project\".\"author\"\n"
//        ;

static QString queryString =
        QString("SELECT\n")
        + "\"user\".\"id\",\n"
        + "\"profile\".\"normalize_handle\",\n"
        + "\"profile\".\"display\" AS \"Full_Name\",\n"
        + "\"profile\".\"company\" AS \"Company\",\n"
        + "\"user\".\"email\" AS \"Email\",\n"
        + "count(\"project\".\"author\")\n"
        + "FROM \"public\".\"user\" AS \"user\"\n"
        + "LEFT JOIN \"public\".\"project\" AS \"project\"\n"
        + "ON \"user\".\"id\"=\"project\".\"author\"\n"
        + "LEFT JOIN \"public\".\"profile\" AS \"profile\"\n"
        + "ON \"user\".\"id\"=\"profile\".\"user\"\n"
        + "WHERE \"user\".\"verified\" = TRUE AND CHAR_LENGTH(\"profile\".\"normalized_handle\") <> 0\n"
        + "GROUP BY \"user\".\"id\", \"profile\".\"normalized_handle\", \"profile\".\"display\", \"profile\".\"company\"\n"
        ;

//static QString queryString =
//        QString("SELECT\n")
//        + "\"user\".\"id\" AS \"Owner\",\n"
//        + "\"profile\".\"normalized_handle\" AS \"Username\",\n"
//        + "\"profile\".\"display\" AS \"Full_Name\",\n"
//        + "\"profile\".\"company\" AS \"Company\",\n"
//        + "\"user\".\"email\" AS \"Email\",\n"
//        + "\"user\".\"verified\" AS \"Verified\"\n"
//        + "FROM \"public\".\"user\" AS \"user\"\n"
//        + "LEFT JOIN \"public\".\"profile\" AS \"profile\"\n"
//        + "ON \"user\".\"id\" = \"profile\".\"user\"\n"
//        + "WHERE \"user\".\"verified\" = TRUE AND CHAR_LENGTH(\"profile\".\"normalized_handle\") <> 0\n";

static QString queryName = QString("Project Query %1");


ProjectDatabase::ProjectDatabase(QString connectionName, QObject *parent) :
    HashDatabase(connectionName, parent)
{
    m_host = "ec2-54-225-112-115.compute-1.amazonaws.com";
    m_database = "d1luuabearldo9";
    m_user = "u5l24ngapsbfqg";
    m_port = 5452;
    m_connectionName = connectionName;
    m_password = "p2p3j5a0g815mf1qekmik6rrqal";
    setQueryString(queryString);
    setOptions();
}

void ProjectDatabase::runQuery() {
    // qDebug() << m_queryString;
    // qDebug() << dbase.hostName() << dbase.userName() << dbase.password() << dbase.port() << dbase.databaseName();
    if (dbase.open()) {
        QSqlQuery query(dbase);
        if (query.exec(m_queryString)) {
//            qDebug() << queryString;
            if (query.isActive()) {
                int count = query.record().count();
                qDebug() << count << query.size();
                for (int i = 0; i < count; i++) {
                    m_dataHeader.append(query.record().fieldName(i));
                }
                // qDebug() << m_dataHeader;
                for (int row = 0; query.next(); row++) {
                    QStringList list;
                    for (int i = 0; i < count; i++) {
                        list.append(formatData(query.value(i)));
                    }
                    m_dataList.append(list);
                    m_hashTable[list[0].toInt()] = list;
                }
                query.finish();
            }
        } else { QMessageBox::warning(0, queryName.arg("Exec"), query.lastError().text()); }
        dbase.close();
    } else { QMessageBox::warning(0, queryName.arg("Open"), dbase.lastError().text()); }
    qDebug() << "DONE";
    emit queryCompleted();
}
