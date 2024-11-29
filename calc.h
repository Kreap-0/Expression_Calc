#ifndef CALC_H
#define CALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calc;
}
QT_END_NAMESPACE

class Calc : public QMainWindow
{
    Q_OBJECT

public:
    Calc(QWidget *parent = nullptr);
    ~Calc();

private slots:

    void on_bpls_clicked();

    void on_bsub_clicked();

    void on_btime_clicked();

    void on_bdiv_clicked();

    void on_b7_clicked();

    void on_b8_clicked();

    void on_b9_clicked();

    void on_bl_clicked();

    void on_b4_clicked();

    void on_b5_clicked();

    void on_b6_clicked();

    void on_br_clicked();

    void on_b1_clicked();

    void on_b2_clicked();

    void on_b3_clicked();

    void on_beq_clicked();

    void Invalid_Input();

    void on_b0_clicked();

    void on_bdel_clicked();

    void on_bc_clicked();

private:
    Ui::Calc *ui;
    QString Input;
    QString Output;
};
#endif // CALC_H
