#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>

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
    void initToolBoxHeaders();
    void initFileSystemModel();

    void on_listViewFileSystem_doubleClicked(const QModelIndex &index);

protected:
    void closeEvent(QCloseEvent *) override;


private:
    Ui::MainWindow *ui;
    int previousIndex;

    QFileSystemModel *fileSystemModel;

    QSystemTrayIcon *trayIcon;
};
#endif // MAINWINDOW_H
