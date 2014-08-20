#include "databasedialog.h"
#include "ui_databasedialog.h"
#include <QDebug>
#include <QCloseEvent>

DatabaseDialog::DatabaseDialog(QObject *parent) :
    QDialog(0),
    ui(new Ui::DatabaseDialog)
{
    Q_UNUSED(parent);
    ui->setupUi(this);
}

DatabaseDialog::~DatabaseDialog()
{
    delete ui;
}

void DatabaseDialog::closeEvent(QCloseEvent *event) {
    deleteLater();
    QDialog::closeEvent(event);
}

void DatabaseDialog::accept() {
    emit databaseNameChanged(ui->databaseName->text());
    emit hostNameChanged(ui->hostName->text());
    emit userNameChanged(ui->userName->text());
    emit passwordChanged(ui->password->text());
    emit portChanged(ui->port->value());
    QDialog::accept();
}

void DatabaseDialog::reject() {
    QDialog::reject();
}

void DatabaseDialog::setHostName(QString name) {
    if (ui) { ui->hostName->setText(name); }
}
void DatabaseDialog::setDatabaseName(QString name) {
    if (ui) { ui->databaseName->setText(name); }
}
void DatabaseDialog::setUserName(QString name) {
    if (ui) { ui->userName->setText(name); }
}
void DatabaseDialog::setPort(int value) {
    if(ui) { ui->port->setValue(value); }
}
void DatabaseDialog::setConnectionName(QString name) {
    if(ui) { ui->connectionName->setText(name); }
}
void DatabaseDialog::setPassword(QString name) {
    if(ui) { ui->password->setText(name); }
}
