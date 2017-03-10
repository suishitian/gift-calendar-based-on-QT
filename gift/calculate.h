#ifndef CALCULATE_H
#define CALCULATE_H

#include <QDialog>

#include <string>

static const int CALCULATE = 1;
static const int INPUT = 0;

namespace Ui {
class calculate;
}

class calculate : public QDialog
{
    Q_OBJECT

public:
    explicit calculate(QWidget *parent = 0);
    ~calculate();

    void refresh_lineedit();

    std::string q2s(const QString &s);
    QString s2q(const std::string &s);
private slots:
    void on_pushButton_AC_clicked();

    void on_pushButton_num1_clicked();

    void on_pushButton_num2_clicked();

    void on_pushButton_num3_clicked();

    void on_pushButton_num4_clicked();

    void on_pushButton_num5_clicked();

    void on_pushButton_num6_clicked();

    void on_pushButton_num7_clicked();

    void on_pushButton_num8_clicked();

    void on_pushButton_num9_clicked();

    void on_pushButton_plus_clicked();

    void on_pushButton_minus_clicked();

    void on_pushButton_time_clicked();

    void on_pushButton_devide_clicked();

    void on_pushButton_num0_clicked();

    void on_pushButton_equal_clicked();

    void on_pushButton_point_clicked();

private:
    Ui::calculate *ui;
    std::string last_string;
    double last_value=0;
    double store_value=0;
    int click_time=0;
    //int state=0;
    int flag=0;
    int point=0;
    int end=0;
};

#endif // CALCULATE_H
