#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPoint>
#include <QVector>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#define s 20 

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPoint optimalPoint(QPoint cur, QCircle tree, VecPoints net) { 
    QPoint optimalPoint;
    int minD = s;
    for (int i = 0; i < net.size(); i++) {
        if (QCircle(cur, s).containsPoint(net[i])&&(!tree.containsPoint(net[i]))) { 
            int diff = (cur - net[i]).manhattanLength();
            if (diff < minD)
                minD = diff, optimalPoint = net[i];
        }
    }
    return optimalPoint;
}

void MainWindow::paintEvent(QPaintEvent *) {

    QPainter painter(this);

    int w = contentsRect().width(), h = contentsRect().height();

    for (int x = 0; x < w; x += s)
        painter.drawLine(QPoint(x, 0), QPoint(x, h)); 

    for (int y = 0; y < h; y += s)
        painter.drawLine(QPoint(0, y), QPoint(w, y)); 

    painter.setPen(QPen(QColor(128, 64, 48)));
    painter.setBrush(QBrush(QColor(128, 64, 48)));
    if (!tree.getCentre().isNull())
        painter.drawEllipse(tree.getCentre(), tree.getRadius(), tree.getRadius());

    painter.setPen(QPen(QColor(255, 165, 0), 4));
    if (path.size() > 1)
        for (int i = 1; i < path.size(); i++)
            painter.drawLine(path.getPath()[i-1], path.getPath()[i]);

    painter.setPen(QPen(Qt::red));
    painter.setBrush(QBrush(Qt::red));
    if (!ant.isNull())
        painter.drawEllipse(ant, 4, 4);

    painter.setPen(QPen(Qt::blue));
    painter.setBrush(QBrush (Qt::blue));
    if (!fly.isNull())
        painter.drawEllipse(fly, 4, 4);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    QPoint cur(event->pos());

    if (screen != contentsRect()) { 
        net.clear();
        screen = contentsRect();
        for (int x = 0; x < screen.width(); x += s)
            for (int y = 0; y < screen.height(); y += s)
                net.append(QPoint(x, y));
    }

    if (event->buttons() & Qt::LeftButton) {
        tree = {cur, 70 + (rand()% 130)};  
        ant *= tree.containsPoint(ant) ? 0 : 1;
        fly *= tree.containsPoint(fly) ? 0 : 1; 
        for (int i = 0; i < path.size(); i++) 
            if (tree.containsPoint(path.getPath()[i]))
                path.clear();
    }

    if ((event->buttons() & Qt::RightButton)&&!(event->modifiers() & Qt::ControlModifier)) { 
        QPoint oP = optimalPoint(cur, tree, net);
        ant *= (oP != ant) ? 0 : 1; 
        if (oP != fly) 
            ant = oP;
    }

    if ((event->buttons() & Qt::RightButton)&&(event->modifiers() & Qt::ControlModifier)) { /
        QPoint oP = optimalPoint(cur, tree, net);
        fly *= (oP != fly) ? 0 : 1; 
        if (oP != ant) 
            fly = oP;
    }

    path.clear();
    if (!fly.isNull() && !ant.isNull())
        path.findPath(ant, fly, tree, net, screen, s);

    repaint();
}
