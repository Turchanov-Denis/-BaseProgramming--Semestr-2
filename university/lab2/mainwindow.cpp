#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPoint>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool intersectionRect(QRectF r1, QRectF r2) { 
    QRectF inter(r1 & r2);
    if (((inter.width() * inter.height()) / (r1.width() * r1.height())) > 0.6) 
        return true;
    return false;
}

bool containsPoint(QCircle c, QPointF p) { 
    QPointF dp = c.center - p;
    return (QPointF::dotProduct(dp, dp) <= c.radius * c.radius) ? true : false;
}

bool containsCircle(QCircle c1, QCircle c2) {
    QPointF dp = c1.center - c2.center;
    return (QPointF::dotProduct(dp, dp) <= (c1.radius + c2.radius)*(c1.radius + c2.radius)) ? true : false;
}

bool containsRect1(QCircle c, QRectF r) { 
    return containsPoint(c, r.topLeft())&&containsPoint(c, r.bottomRight());
}

bool containsRect2(QCircle c, QRectF r) { 
    return r.marginsAdded(QMargins(c.radius, c.radius, c.radius, c.radius)).contains(c.center); 

void MainWindow::paintEvent(QPaintEvent *) {

    QPainter painter (this);

    QImage waterTexture(":/src/src/water.jpg");
    QImage grassTexture(":/src/src/grass.jpg");

    QBrush water, grass, potCircle(QColor(255, 15, 203, 255)), potSquare(QColor(128, 0, 0, 255)); 

    water.setTextureImage(waterTexture);
    grass.setTextureImage(grassTexture);

    painter.setBrush(grass);
    painter.drawRect(contentsRect());

    pool = QRectF(QPointF(200, 200), QSizeF(250, 150)); 
    painter.setBrush(water);
    painter.drawRect(pool);

    painter.setBrush(potCircle);
    for (int i = 0; i < circles.size(); i++)
        painter.drawEllipse(circles[i].center, circles[i].radius, circles[i].radius);

    painter.setBrush(potSquare);
    for (int i = 0; i < squares.size(); i++) 
        painter.drawRect(squares[i]); 
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    bool doNotAppend = false; 

    if (Qt::LeftButton & event->buttons()) {

        QCircle tempCircle = {event->pos(), 30};

        if (pool.contains(tempCircle.center)) 
            doNotAppend = true;

        for (int i = 0; i < circles.size(); i++)
            if (containsCircle(circles[i], tempCircle)) {
                break;
            }

        for (int i = 0; i < squares.size(); i++)
            if (containsRect1(tempCircle, squares[i])) { 
                break;
            }

        if (!doNotAppend)
            circles.append(tempCircle);
    }

    if (Qt::RightButton & event->buttons()) { 

        QRectF tempRect(event->pos(), pool.size() * 0.2);

        if (pool.contains(tempRect.center())) 
            doNotAppend = true;

        for (int i = 0; i < squares.size(); i++)
            if (intersectionRect(tempRect, squares[i])) { 
                doNotAppend = true;
                break;
            }

        for (int i = 0; i < circles.size(); i++) {
            if (containsRect1(circles[i], tempRect)) 
                break; 
            if (containsRect2(circles[i], tempRect))
                doNotAppend = true; 
        }

        if (!doNotAppend)
            squares.append(tempRect);
    }

    repaint();
}


