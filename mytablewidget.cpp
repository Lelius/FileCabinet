#include "mytablewidget.h"

MyTableWidget::MyTableWidget(QWidget *parent) :
    QTableWidget(parent)
{

}

bool MyTableWidget::event(QEvent *event)
{
    if (event->type() == QEvent::HoverEnter) {
        emit signalMyTableWidgetHoverEnter();
    }
    if (event->type() == QEvent::HoverLeave) {
        emit signalMyTableWidgetHoverLeave();
    }
    return QWidget::event(event);
}
