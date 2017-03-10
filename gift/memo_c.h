#ifndef MEMO_C_H
#define MEMO_C_H

#include <QDialog>

namespace Ui {
class memo_c;
}

class memo_c : public QDialog
{
    Q_OBJECT

public:
    explicit memo_c(QWidget *parent = 0 , int memo_num=0 , int type=0, QString memo_info="", QString memo_path="", QString path="", int date=0);
    ~memo_c();

    QString s2q(const std::string &s);

    std::string q2s(const QString &s);

    void set_check();

    void get_num(int&,int&,std::string content);

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::memo_c *ui;

    int memo_num;
    int type;
    int date_num;
    QString memo_info;
    QString memo_path;
    QString location;

    int popup_flag=0;
};

#endif // MEMO_C_H
