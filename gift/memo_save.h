#ifndef MEMO_SAVE_H
#define MEMO_SAVE_H

#include "juldate.h"

#include <QDialog>
#include <QMenu>

namespace Ui {
class memo_save;
}

class memo_save : public QDialog
{
    Q_OBJECT

public:
    explicit memo_save(QWidget *parent = 0,int year=0,int month=0,int day=0);
    ~memo_save();

    void get_now_date();

    QString s2q(const std::string &s);

    std::string q2s(const QString &s);

private slots:

    void onMenu_1_Triggered(QAction *);

    void on_spinBox_year_editingFinished();

    void on_spinBox_month_editingFinished();

    void on_spinBox_date_editingFinished();

    void on_spinBox_hour_editingFinished();

    void on_spinBox_minute_editingFinished();

    void on_buttonBox_accepted();

private:
    Ui::memo_save *ui;

    int year;
    int month;
    int day;
    int hour=8;
    int minute=0;
    int type=0;

    QString memo_info="";
    QString memo_info_d="";
    QString location="";
    QString name="";
    QString content_name="";

};

#endif // MEMO_SAVE_H
