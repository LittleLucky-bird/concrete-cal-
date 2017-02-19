#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<cmath>
#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();



    void on_AsBox_valueChanged(double arg1);

    void on_cocBox_currentTextChanged(const QString &arg1);
    void on_steelBox_currentTextChanged(const QString &arg1);

    void on_AspBox_valueChanged(double arg1);

    void on_hBox_valueChanged(double arg1);

    void on_bBox_valueChanged(double arg1);

    void on_aBox_valueChanged(double arg1);

    void on_apBox_valueChanged(double arg1);




    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
    int fa[4001];
    double Mx[4001];
};

#endif // MAINWINDOW_H
