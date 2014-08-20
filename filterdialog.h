#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDialog(QWidget *parent = 0);
    ~FilterDialog();
    void closeEvent(QCloseEvent *);

signals:
    void usernameChanged(QString);
    void emailChanged(QString);
    void uidChanged(QString);

public slots:
    void accept();
    void reject();

    void setUsername(const QString&);
    void setEmail(const QString&);
    void setUid(const QString&);

private:
    Ui::FilterDialog *ui;
};

#endif // FILTERDIALOG_H
