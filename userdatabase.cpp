#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QDebug>
#include <QList>
#include <QStringList>
#include <QApplication>
#include <QMessageBox>
#include "databasedialog.h"
#include "userdatabase.h"
#include <iostream>

//static QString queryString =
//        QString("SELECT\n")
//        + "\"profile\".\"user\" AS \"Owner\", \n"
//        + "\"profile\".\"normalized_handle\" AS \"Username\",\n"
//        + "\"profile\".\"display\" AS \"Full_Name\",\n"
//        + "\"profile\".\"company\" AS \"Company\", \"user\".\"email\" AS \"Email\"\n"
//        + "FROM \"public\".\"profile\" AS \"profile\", \"public\".\"user\" AS \"user\"\n"
//        + "WHERE \"profile\".\"user\" = \"user\".\"id\" AND \"user\".\"verified\" = TRUE\n";

//static QString queryString =
//        QString("SELECT\n")
//        + "\"profile\".\"user\" AS \"Owner\", \n"
//        + "\"profile\".\"normalized_handle\" AS \"Username\",\n"
//        + "\"profile\".\"display\" AS \"Full_Name\",\n"
//        + "\"profile\".\"company\" AS \"Company\",\n"
//        + "\"user\".\"email\" AS \"Email\"\n"
//        + "FROM \"public\".\"profile\" AS \"profile\", \"public\".\"user\" AS \"user\"\n"
//        + "WHERE \"profile\".\"user\" = \"user\".\"id\" AND \"user\".\"verified\" = TRUE\n";

//static QString queryString =
//        QString("SELECT * FROM \"public\".\"user\" AS \"user\"\n")
//        + "ORDER BY \"user\".\"email\" ASC;";

//static QString queryString =
//        QString("SELECT * from \"public\".\"profile\"\n");


//static QString queryString =
//        QString("SELECT\n")
//        + "\"user\".\"id\" AS \"Owner\",\n"
//        + "\"profile\".\"normalized_handle\" AS \"Username\",\n"
//        + "\"profile\".\"display\" AS \"Full_Name\",\n"
//        + "\"profile\".\"company\" AS \"Company\", \"user\".\"email\" AS \"Email\",\n"
//        + "\"user\".\"verified\" AS \"Verified\"\n"
//        + "FROM \"public\".\"user\" AS \"user\"\n"
//        + "LEFT JOIN \"public\".\"profile\" AS \"profile\"\n"
//        + "ON \"user\".\"id\" = \"profile\".\"user\"\n"
//        + "WHERE \"user\".\"verified\" = TRUE AND CHAR_LENGTH(\"profile\".\"normalized_handle\") <> 0\n";

UserDatabase::UserDatabase(QString connectionName, QObject *parent) :
    Database(connectionName, parent)
{
}

UserDatabase::UserDatabase(QStringList connectionString, QObject *parent) :
    Database(connectionString, parent)
{
}
