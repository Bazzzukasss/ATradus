#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace atradus
{

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
};

} //namespace atradus

#endif // MAINWINDOW_H
