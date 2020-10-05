#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setPreviousIndex(0);

    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    ui->treeViewFileSystem->setModel(model);

    connect  (ui->actionExitTheProgram, &QAction::triggered, [=]() {setCurrentIndexInStackWidget(1);} );
    connect ( ui->pushButtonYes, &QPushButton::clicked, [=]() {MainWindow::close();});
    connect ( ui->pushButtonNo, &QPushButton::clicked, [=]() {returnPreviousIndexInStackWidget();} );
    connect ( ui->actionListFileSystem, &QAction::triggered, [=]() {setCurrentIndexInStackWidget(2);} );
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

