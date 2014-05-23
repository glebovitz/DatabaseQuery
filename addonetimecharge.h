#ifndef ADDONETIMECHARGE_H
#define ADDONETIMECHARGE_H

#include <QDialog>

namespace Ui {
class AddOneTimeCharge;
}

class AddOneTimeCharge : public QDialog
{
    Q_OBJECT

public:
    explicit AddOneTimeCharge(QWidget *parent = 0);
    ~AddOneTimeCharge();

private:
    Ui::AddOneTimeCharge *ui;
};

#endif // ADDONETIMECHARGE_H
