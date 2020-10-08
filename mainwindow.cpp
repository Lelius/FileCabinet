#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setPreviousIndex(0);

    initSystemTray();

    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    ui->treeViewFileSystem->setModel(model);

    connect ( ui->actionExitTheProgram, &QAction::triggered, [=]() {setCurrentIndexInStackWidget(1);} );
    connect ( ui->pushButtonYes, &QPushButton::clicked, [=]() {MainWindow::close();});
    connect ( ui->pushButtonNo, &QPushButton::clicked, [=]() {returnPreviousIndexInStackWidget();} );
    connect ( ui->actionOpenListFileDatabase, &QAction::triggered, [=]() {setCurrentIndexInStackWidget(2);} );
    connect ( ui->actionListCard, &QAction::triggered, [=]() {setCurrentIndexInStackWidget(0);} );
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
    connect(actCloseTheProgramm, &QAction::triggered, [=]() {this->close();} );
    connect(trayIcon, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason reason) {if (reason == QSystemTrayIcon::DoubleClick)
                                                                                                    {this->isVisible() ? this->hide() : this->show();} } );
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
                                 tr("Программа свернута, но остается в рабочем состоянии."), trayIcon->icon(), 2000);
        hide();
        event->ignore();
    }
}
