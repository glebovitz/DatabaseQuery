#include "filterdialog.h"
#include "ui_filterdialog.h"
#include <QCloseEvent>
#include <QDebug>

FilterDialog::FilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);
}

FilterDialog::~FilterDialog()
{
    delete ui;
}

void FilterDialog::closeEvent(QCloseEvent *e) {
    qDebug() << "CLOSE EVENT";
    deleteLater();
    QWidget::closeEvent(e);
}

void FilterDialog::accept() {
    if (!ui->usernameEdit->text().isEmpty()) {
        emit usernameChanged(ui->usernameEdit->text());
    }
    if (!ui->emailEdit->text().isEmpty()) {
        emit emailChanged(ui->emailEdit->text());
    }
    if (!ui->uidEdit->text().isEmpty()) {
        emit uidChanged(ui->uidEdit->text());
    }
    close();
}

void FilterDialog::reject() {
    close();
}

void FilterDialog::setUsername(const QString &str) {
    ui->usernameEdit->setText(str);
}

void FilterDialog::setEmail(const QString &str) {
    ui->emailEdit->setText(str);
}

void FilterDialog::setUid(const QString &str) {
    ui->uidEdit->setText(str);
}
