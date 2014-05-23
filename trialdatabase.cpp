#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDate>
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include <QStringList>
#include <QVariant>
#include "trialdatabase.h"

//static QString queryString =
//        QString("SELECT ")
//        + "\"account\".\"owner\" AS \"Owner\",\n"
//        + "\"account\".\"id\" AS \"Account_ID\",\n"
//        + "\"account\".\"type\" AS \"Account_Type\",\n"
//        + "\"account\".\"sign_on_date\" AS \"Sign_on_Date\",\n"
//        + "\"account\".\"email\" AS \"Account_Email\",\n"
//        + "\"salesforce\".\"salesforce_id\" AS \"Salesforce_ID\"\n"
//        + "FROM \"public\".\"account\" AS \"account\"\n"
//        + "LEFT JOIN \"public\".\"salesforce\" AS \"salesforce\"\n"
//        + "ON \"salesforce\".\"owner\" = \"account\".\"owner\"\n"
//        + "LEFT JOIN \"public\".\"agreement\" AS \"agreement\" "
//        + "ON \"account\".\"id\" = \"agreement\".\"account\" "
//        + "WHERE \"account\".\"type\" = 'AccountTrial' AND \"agreement\".\"active\" = False"
//        ;

static QString queryString =
        QString("set datestyle to 'ISO,MDY'; \nSELECT ")
        + "\"account\".\"owner\" AS \"Owner\",\n"
        + "\"account\".\"id\" AS \"Account_ID\",\n"
        + "\"account\".\"type\" AS \"Account_Type\",\n"
        + "\"account\".\"sign_on_date\" AS \"Sign_on_Date\",\n"
        + "\"account\".\"email\" AS \"Account_Email\",\n"

        + "\"agreement\".\"active\" AS \"Has_Agreement\",\n"
        + "\"agreement\".\"item_type\" AS \"Agreement_Type\", "
        + "\"agreement\".\"item_state\" AS \"Agreement_State\",\n"
        + "\"agreement\".\"expires\" AS \"Agreement_Expires\",\n"
        + "\"agreement\".\"next_bill_date\" AS \"Next_Bill_Date\",\n"

        + "\"product\".\"name\" AS \"SKU\",\n"
        + "\"product\".\"license_kind\" AS \"License_Type\",\n"

        + "\"salesforce\".\"salesforce_id\" AS \"Salesforce_ID\",\n"
        + "\"ide_access\".\"id\" AS \"IDE License\"\n"

        + "FROM \"public\".\"account\" AS \"account\"\n"
        + "LEFT JOIN \"public\".\"agreement\" AS \"agreement\"\n"
        + "ON \"account\".\"id\" = \"agreement\".\"account\"\n"

        + "LEFT JOIN \"public\".\"license_bundle\" AS \"license_bundle\"\n"
        + "ON \"license_bundle\".\"agreement\" = \"agreement\".\"id\"\n"

        + "LEFT JOIN \"public\".\"product\" AS \"product\"\n"
        + "ON \"product\".\"id\" = \"license_bundle\".\"product\"\n"

        + "LEFT JOIN \"public\".\"salesforce\" AS \"salesforce\"\n"
        + "ON \"salesforce\".\"owner\" = \"account\".\"owner\"\n"

        + "LEFT JOIN \"public\".\"license_ide_access\" AS \"ide_access\"\n"
        + "ON \"ide_access\".\"bundle\" = \"license_bundle\".\"id\"\n"
        + "WHERE \"account\".\"type\" = 'AccountTrial'"
        ;

static QString queryName = QString("Trial Query %1");

TrialDatabase::TrialDatabase(QString connectionName, QObject *parent) :
    Database(connectionName, parent)
{
    m_host = "ec2-54-221-199-215.compute-1.amazonaws.com";
    m_database = "df7dhc2ihb1166";
    m_user = "ul1gv6mtos8as";
    m_port = 5642;
    m_connectionName = connectionName;
    m_password = "p3epb0hq9s0r2j115m4ene8vjie";
    setQueryString(queryString);
    setOptions();
}

void TrialDatabase::runQuery() {
//     qDebug() << m_queryString;
//     qDebug() << dbase.hostName() << dbase.userName() << dbase.password() << dbase.port() << dbase.databaseName();
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
//                 qDebug() << m_dataHeader;
                for (int row = 0; query.next(); row++) {
                    QStringList list;
                    for (int i = 0; i < count; i++) {
                        list.append(formatData(query.value(i)));
                    }
                    m_dataList.append(list);
                }
                query.finish();
            }
        } else { QMessageBox::warning(0, queryName.arg("Exec"), query.lastError().text()); }
        dbase.close();
    } else { QMessageBox::warning(0, queryName.arg("Open"), dbase.lastError().text()); }
    qDebug() << "DONE";
    emit queryCompleted();
}
