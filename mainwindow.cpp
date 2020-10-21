#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setPreviousIndex(0);

    initSystemTray();
    initToolBoxHeaders();
    initFileSystemModel();

    connect ( ui->actionExitTheProgram, &QAction::triggered, [=]() {setCurrentIndexInStackWidget(1);} );
    connect ( ui->pushButtonYes, &QPushButton::clicked, [=]() {MainWindow::hide(); MainWindow::close();}); //closeEvent переопределен
    connect ( ui->pushButtonNo, &QPushButton::clicked, [=]() {returnPreviousIndexInStackWidget();} );
    connect ( ui->actionOpenListFileDatabase, &QAction::triggered, [=]() {setCurrentIndexInStackWidget(2);} );
    connect ( ui->actionListCard, &QAction::triggered, [=]() {setCurrentIndexInStackWidget(0);} );
    connect ( ui->listViewFileSystem, &QListView::doubleClicked, this, &MainWindow::on_listViewFileSystem_doubleClicked );

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::returnPreviousIndexInStackWidget()
{
    ui->stackedWidget->setCurrentIndex(getPreviousIndex());
}


void MainWindow::setCurrentIndexInStackWidget(int valueCurrentIndex)
{
    setPreviousIndex(ui->stackedWidget->currentIndex());
    ui->stackedWidget->setCurrentIndex(valueCurrentIndex);
}


int MainWindow::getPreviousIndex() const
{
    return previousIndex;
}


void MainWindow::setPreviousIndex(int value)
{
    previousIndex = value;
}


void MainWindow::initSystemTray()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/new/prefix1/arhiv.png"));

    QMenu *menuTrayIcon = new QMenu(this);
    QAction *actShowHide = new QAction("Показать/Спрятать", this);
    QAction *actCloseTheProgramm = new QAction("Выход", this);
    menuTrayIcon->addAction(actShowHide);
    menuTrayIcon->addAction(actCloseTheProgramm);
    trayIcon->setToolTip("Картотека");
    trayIcon->setContextMenu(menuTrayIcon);
    trayIcon->show();

    connect(actShowHide, &QAction::triggered, [=]() {this->isVisible() ? this->setVisible(false) : this->setVisible(true);} );
    connect(actCloseTheProgramm, &QAction::triggered, [=]() {this->hide(); this->close();} );
    connect(trayIcon, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason reason)
                                                        {if (reason == QSystemTrayIcon::DoubleClick)
        {this->isVisible() ? this->hide() : this->show();} } );
}


void MainWindow::initToolBoxHeaders()
{
    ui->toolBox->setItemText(0, "Выдача копий");
    ui->toolBox->setItemText(1, "Учет копий");
    ui->toolBox->setItemText(2, "Учет изменений");
    ui->toolBox->setItemText(3, "Применяемость");
}


void MainWindow::initFileSystemModel()
{
    fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setFilter(QDir::QDir::AllEntries);
    fileSystemModel->setRootPath(QDir::currentPath());
    ui->listViewFileSystem->setModel(fileSystemModel);
    ui->listViewFileSystem->setRootIndex(fileSystemModel->index(QDir::currentPath()));

    ui->lineEditFileSystem->setText(QDir::currentPath());
    ui->lineEditFileSystem->setReadOnly(true);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    #ifdef Q_OS_MACOS
    if (!event->spontaneous() || !isVisible()) {
        return;
    }
    #endif

    if (this->isVisible()) {
        trayIcon->showMessage(tr("Картотека"),
                                 tr("Программа свернута, но остается в рабочем состоянии."), trayIcon->icon(), 3000);
        MainWindow::hide();
        event->ignore();
    }
}


void MainWindow::on_listViewFileSystem_doubleClicked(const QModelIndex &index)
{
    QFileInfo fileInfo = fileSystemModel->fileInfo(index);

    if (fileInfo.fileName() == "..") {
        QDir dir = fileInfo.dir();
        dir.cdUp();
        ui->listViewFileSystem->setRootIndex(fileSystemModel->index(dir.absolutePath()));

        ui->lineEditFileSystem->clear();
        ui->lineEditFileSystem->setText(dir.absolutePath());
    }
    else if (fileInfo.fileName() == ".") {
        ui->listViewFileSystem->setRootIndex(fileSystemModel->index(""));
    }
    else if (fileInfo.isDir()) {
        ui->listViewFileSystem->setRootIndex(index);
    }
}
