#include "addonetimecharge.h"
#include "ui_addonetimecharge.h"

AddOneTimeCharge::AddOneTimeCharge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOneTimeCharge)
{
    ui->setupUi(this);
}

AddOneTimeCharge::~AddOneTimeCharge()
{
    delete ui;
}
