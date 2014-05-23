#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QAction>
#include <QClipboard>
#include <QHash>
#include <QList>
#include <QListIterator>
#include <QMetaObject>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>
#include <QSortFilterProxyModel>

#include "database.h"
#include "databasedialog.h"
#include "databasequery.h"
#include "databasequeryrequest.h"
#include "datastore.h"
#include "datastoremodel.h"
#include "querystrings.h"

#include "filterdialog.h"
#include "ui_filterdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_model(0)
{
    qRegisterMetaType<DataStore>("DataStore");
    importConnectionStrings();
    ui->setupUi(this);
    m_model = new DataStoreModel(this);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(m_model);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect( ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), SLOT(contextMenu_triggered(QPoint)) );
    connect( &m_dbq, SIGNAL(logStatus(QString)), SLOT(statusMessage(QString)) );
    connect( &m_dbq, SIGNAL(resultsReady(DataStore)), SLOT(displayResults(DataStore)) );
    connect( &m_dbq, SIGNAL(errorMessageBox(QString,QString)), SLOT(errorMessageBox(QString,QString)) );

    enableActions(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClose_triggered()
{
    qApp->exit();
}

void MainWindow::contextMenu_triggered(const QPoint & pos) {
    if (ui->tableView->currentIndex().isValid()) {
        QMenu menu;
        QAction *action = menu.addAction("Copy");
        connect(action, SIGNAL(triggered()), SLOT(actionCopy_triggered()) );
        menu.exec(ui->tableView->mapToGlobal(pos));
    }
}

void MainWindow::actionCopy_triggered() {
    QModelIndex index = ui->tableView->currentIndex();
    QAbstractItemModel *model = ui->tableView->model();
    if (model && index.isValid()) {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(model->data(index).toString());
    }
}

void MainWindow::importConnectionStrings() {
    m_connectionStrings = importDatabase("connectionStrings.csv");

}

DataStore MainWindow::importDatabase(QString filename)
{
    DataStore store(true);
    if ( filename.isEmpty() || !QDir().exists(filename) ) {
        filename = QFileDialog::getOpenFileName(0, "Import CSV File", m_savedFileName);
    }
    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QFile::ReadOnly)) {
            QTextStream stream(&file);
            for (int row = 0; !stream.atEnd(); row++) {
                if (row == 0) {
                    store.setHeader(stream.readLine().remove("\"").split(QRegExp(",[ ]*")));
                    for (int i = 0; i < m_dataHeaders.count(); i++) {
                        store.appendType(QVariant::String);
                    }
                } else {
                    QStringList list(stream.readLine().remove("\"").split(QRegExp(",[ ]*")));
                    store.appendData(list);
                }
            }
            if (!store.rowCount() == 0) {
                return store;
            }
        } else { QMessageBox::warning(0, "Open CSV File", "Could not open file " + filename + "for reading"); }
    } else { QMessageBox::warning(0, "Open CSV File", "Could not find file " + filename); }
    return store;
}

void MainWindow::enableActions(const bool fla) {
    if (m_actionList.isEmpty()) {
        m_actionList = this->findChildren<QAction *>();
    }
    foreach (QAction *action, m_actionList) {
        action->setEnabled(fla);
    }
}

void MainWindow::append(const QString &string) {
    Q_UNUSED(string)
    //if (ui) ui->logDisplay->append(string);
}

void MainWindow::statusMessage(const QString &string) {
    qDebug() << string;
    ui->statusArea->append(string);
    QApplication::processEvents();
}

void MainWindow::errorMessageBox(const QString &title, const QString &text)
{
    QMessageBox::warning(this, title, text);
}

void MainWindow::on_actionFilter_triggered(){
    FilterDialog *filterUi = new FilterDialog;

    filterUi->setUsername(m_username);
    filterUi->setEmail(m_email);
    filterUi->setUid(m_uid);

    connect(filterUi, SIGNAL(usernameChanged(QString)), SLOT(setUsername(QString)) );
    connect(filterUi, SIGNAL(emailChanged(QString)), SLOT(setEmail(QString)) );
    connect(filterUi, SIGNAL(uidChanged(QString)), SLOT(setUid(QString)) );

    filterUi->show();
}

void MainWindow::on_actionSave_triggered() {
//    if (!ui->logDisplay->document()->isEmpty()) {
//        QString fileName = QFileDialog::getSaveFileName(this, "Save CSV File", m_savedFileName);
//        if (!fileName.isEmpty()) {
//            QFile file(fileName);
//            if (file.open(QFile::WriteOnly)) {
//                QTextStream stream(&file);
//                m_savedFileName = fileName;
//                stream << ui->logDisplay->toPlainText();
//            } else QMessageBox::warning(this, "Save CSV File", "Could not open file " + fileName + "for writing");
//        }
//    } else QMessageBox::warning(this, "Save CSV File", "Can not save CSV file. Text Buffer is empty");
}

void MainWindow::on_actionSave_As_triggered() {
//    if (!ui->logDisplay->document()->isEmpty()) {
//        QString fileName = QFileDialog::getSaveFileName(this, "Save CSV File", m_savedFileName);
//        if (!fileName.isEmpty()) {
//            QFile file(fileName);
//            if (file.open(QFile::WriteOnly)) {
//                QTextStream stream(&file);
//                m_savedFileName = fileName;
//                stream << ui->logDisplay->toPlainText();
//            } else QMessageBox::warning(this, "Save CSV File", "Could not open file " + fileName + "for writing");
//        }
//    } else QMessageBox::warning(this, "Save CSV File", "Can not save CSV file. Text Buffer is empty");
}



void MainWindow::displayResults(DataStore base)
{
    m_model->setDataStore(base);
}
