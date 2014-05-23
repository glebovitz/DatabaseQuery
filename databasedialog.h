#ifndef DATABASEDIALOG_H
#define DATABASEDIALOG_H

#include <QDialog>

namespace Ui {
class DatabaseDialog;
}

class DatabaseDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::DatabaseDialog *ui;
    virtual void closeEvent(QCloseEvent *);

public:
    explicit DatabaseDialog(QObject *parent = 0);
    ~DatabaseDialog();

public slots:
    virtual void accept();
    virtual void reject();
    void setHostName(QString name);
    void setDatabaseName(QString name);
    void setUserName(QString name);
    void setPort(int value);
    void setConnectionName(QString name);
    void setPassword(QString name);

signals:
    void databaseNameChanged(QString name);
    void hostNameChanged(QString name);
    void userNameChanged(QString name);
    void passwordChanged(QString password);
    void portChanged(int port);
};

#endif // DATABASEDIALOG_H
