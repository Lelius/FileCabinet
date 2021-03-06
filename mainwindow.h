#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int getPreviousIndex() const;
    void setPreviousIndex(int value);

private slots:
    void setCurrentIndexInStackWidget(int);
    void returnPreviousIndexInStackWidget();

    void setMyTableWidgetHoverSize(int, bool);

private:
    Ui::MainWindow *ui;
    int previousIndex;
};
#endif // MAINWINDOW_H
