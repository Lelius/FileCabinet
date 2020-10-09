#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QTableWidget>
#include <QEvent>

class MyTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    enum MyTableWidgetCurrentHoverEvent
    {
        ChangeAccounting,
        Applicability,
        IssuanceOfCopies,
        CopyAccounting
    };

public:
    MyTableWidget(QWidget *parent = nullptr);

    bool event(QEvent *);

signals:
    void signalMyTableWidgetHoverEnter();
    void signalMyTableWidgetHoverLeave();
};

#endif // MYTABLEWIDGET_H
