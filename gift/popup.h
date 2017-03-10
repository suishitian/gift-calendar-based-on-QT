#ifndef POPUP_H
#define POPUP_H

#include "memo_c.h"

#include <QDialog>
#include <QDir>
namespace Ui {
class popup;
}

class popup : public QDialog
{
    Q_OBJECT

public:
    explicit popup(QWidget *parent = 0);
    ~popup();

    void reset_popup();

    void read_file();

    bool analyze_file(int& year,int& month,int& day,int& hour,int& minute,std::string content);

    bool analyze_popup(int num, int& type, std::string line);

    QString s2q(const std::string &s);

    std::string q2s(const QString &s);

    void sort_popup();

    void sort(int&,int&);

    void popup_show();

    void tv_show_p();

    void reset_tv();

    void analyze_tv(int& ,int& ,std::string content);

    void set_check();

private slots:

    void on_pushButton_close_clicked();

    void popup_doubleclicked(int,int);

private:

    Ui::popup *ui;
    int now_num=0;

    int date_time[200][6];
    QString popup_qs[200][2];
    QString location = QDir::currentPath();
    int size=0;
    int check_flag=-1;
    int tv_num[200][2];
    int tv_size=0;
    QString tv_name[200];
};

#endif // POPUP_H
