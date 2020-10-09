#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    int getPreviousIndex() const;
    void setPreviousIndex(int value);

private slots:
    void setCurrentIndexInStackWidget(int);
    void returnPreviousIndexInStackWidget();

    void initSystemTray();

protected:
    void closeEvent(QCloseEvent *) override;

    void setMyTableWidgetHoverSize(int, bool);

private:
    Ui::MainWindow *ui;
    int previousIndex;

    QSystemTrayIcon *trayIcon;
};
#endif // MAINWINDOW_H
