#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcircle.h> 
#include <path.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;

    QPoint ant; 
    QPoint fly; 

    QRect screen;

    QCircle tree;

    VecPoints net; 
    Path path; 
};

#endif // MAINWINDOW_H
