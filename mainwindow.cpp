#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytablewidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setPreviousIndex(0);

    initSystemTray();

    ui->tableWidgetChangeAccounting->setAttribute(Qt::WA_Hover);
    ui->tableWidgetApplicability->setAttribute(Qt::WA_Hover);
    ui->tableWidgetIssuanceOfCopies->setAttribute(Qt::WA_Hover);
    ui->tableWidgetCopyAccounting->setAttribute(Qt::WA_Hover);

    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    ui->treeViewFileSystem->setModel(model);

    connect ( ui->actionExitTheProgram, &QAction::triggered, [=]() {setCurrentIndexInStackWidget(1);} );
    connect ( ui->pushButtonYes, &QPushButton::clicked, [=]() {MainWindow::hide(); MainWindow::close();}); //closeEvent переопределен
    connect ( ui->pushButtonNo, &QPushButton::clicked, [=]() {returnPreviousIndexInStackWidget();} );
    connect ( ui->actionOpenListFileDatabase, &QAction::triggered, [=]() {setCurrentIndexInStackWidget(2);} );
    connect ( ui->actionListCard, &QAction::triggered, [=]() {setCurrentIndexInStackWidget(0);} );
    connect ( ui->tableWidgetChangeAccounting, &MyTableWidget::signalMyTableWidgetHoverEnter, [=]() {setMyTableWidgetHoverSize(MyTableWidget::ChangeAccounting, true);} );
    connect ( ui->tableWidgetChangeAccounting, &MyTableWidget::signalMyTableWidgetHoverLeave, [=]() {setMyTableWidgetHoverSize(MyTableWidget::ChangeAccounting, false);} );
    connect ( ui->tableWidgetApplicability, &MyTableWidget::signalMyTableWidgetHoverEnter, [=]() {setMyTableWidgetHoverSize(MyTableWidget::Applicability, true);} );
    connect ( ui->tableWidgetApplicability, &MyTableWidget::signalMyTableWidgetHoverLeave, [=]() {setMyTableWidgetHoverSize(MyTableWidget::Applicability, false);} );
    connect ( ui->tableWidgetIssuanceOfCopies, &MyTableWidget::signalMyTableWidgetHoverEnter, [=]() {setMyTableWidgetHoverSize(MyTableWidget::IssuanceOfCopies, true);} );
    connect ( ui->tableWidgetIssuanceOfCopies, &MyTableWidget::signalMyTableWidgetHoverLeave, [=]() {setMyTableWidgetHoverSize(MyTableWidget::IssuanceOfCopies, false);} );
    connect ( ui->tableWidgetCopyAccounting, &MyTableWidget::signalMyTableWidgetHoverEnter, [=]() {setMyTableWidgetHoverSize(MyTableWidget::CopyAccounting, true);} );
    connect ( ui->tableWidgetCopyAccounting, &MyTableWidget::signalMyTableWidgetHoverLeave, [=]() {setMyTableWidgetHoverSize(MyTableWidget::CopyAccounting, false);} );
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setMyTableWidgetHoverSize(int currentWidget, bool hover)
{
    if (hover == true){
        ui->widgetSideBListCard->setFixedSize(ui->widgetSideBListCard->size());
        if (currentWidget != MyTableWidget::ChangeAccounting) {
            ui->tableWidgetChangeAccounting->hide();
            ui->labelChangeAccounting->hide();
        }
        if (currentWidget != MyTableWidget::Applicability) {
            ui->tableWidgetApplicability->hide();
            ui->labelApplicability->hide();
        }
        if (currentWidget != MyTableWidget::IssuanceOfCopies) {
            ui->tableWidgetIssuanceOfCopies->hide();
            ui->labelIssuanceOfCopies->hide();
        }
        if (currentWidget != MyTableWidget::CopyAccounting) {
            ui->tableWidgetCopyAccounting->hide();
            ui->labelCopyAccounting->hide();
        }
    } else {
        ui->widgetSideBListCard->setMaximumSize(0, 0);
        ui->widgetSideBListCard->setMaximumSize(MainWindow::maximumSize());
        ui->tableWidgetChangeAccounting->show();
        ui->labelChangeAccounting->show();
        ui->tableWidgetApplicability->show();
        ui->labelApplicability->show();
        ui->tableWidgetIssuanceOfCopies->show();
        ui->labelIssuanceOfCopies->show();
        ui->tableWidgetCopyAccounting->show();
        ui->labelCopyAccounting->show();
    }
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
