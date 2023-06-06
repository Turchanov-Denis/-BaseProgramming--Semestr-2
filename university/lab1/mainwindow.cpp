#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPoint>
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *) {

    QPainter painter(this);

   
    QLineF line1(dot1, dot2);
    QLineF line2(line1); 
    line2.setAngle(line1.angle() + 30); 

    QPointF a1 = dot2 - dot1;
    QPointF a2 = line2.p2() - line2.p1(); 

    if (!(dot1.isNull())&&!(dot2.isNull())) {
        painter.drawLine(line1); 
        painter.drawLine(line2); 

    }

    if ((!obj.isNull())&&(!(dot1.isNull())&&!(dot2.isNull()))) {
        painter.drawEllipse(obj, 5, 5);

        QPointF b1 = obj - dot1;
        QPointF b2 = obj - line2.p1();

      
        int sign1 = a1.x()*b1.y() - a1.y()*b1.x();
        int sign2 = a2.x()*b2.y() - a2.y()*b2.x();

        if (sign1 <= 0 && sign2 >= 0)
            qDebug() << "I see";
        else if (sign1 <= 0 && sign2 <= 0) 
            qDebug() << "I can't see, it's to the left";
        else if (sign1 >= 0 && sign2 >= 0) 
            qDebug() << "I can't see, it's to the right";
        else  // сзади от фонарика
            qDebug() << "I can't see, it's behind";
    }

#if 0

    QPointF inter; 

    QLineF line1 (100, 100, 150, 140);



    QLineF line2 (110, 150, 160, 80);

    line1.intersects(line2, &inter); 

    qDebug() << line1.intersects(line2, &inter);

    painter.drawLine(line1);

    painter.drawLine(line2);

    QBrush black (Qt::black);

    painter.setBrush(black);

    painter.drawEllipse(inter, 2, 2);
#endif
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    if (!(Qt::ControlModifier & event->modifiers())&&(Qt::LeftButton & event->buttons()))
        dot1 = event->pos();

    if (Qt::RightButton & event->buttons())
        dot2 = event->pos();

    if ((Qt::ControlModifier & event->modifiers())&&(Qt::LeftButton & event->buttons()))
        obj = event->pos();

    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {

}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {

    if (!(Qt::ControlModifier & event->modifiers())&&(Qt::LeftButton & event->buttons())) {
        dot1 = event->pos();
        repaint();
    }

    if (Qt::RightButton & event->buttons()) {
        dot2 = event->pos();
        repaint();
    }

    if ((Qt::ControlModifier & event->modifiers())&&(Qt::LeftButton & event->buttons())) {
        obj = event->pos();
        repaint();
    }
}
