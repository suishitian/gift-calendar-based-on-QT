#ifndef TV_H
#define TV_H

#include <QDialog>

namespace Ui {
class tv;
}

class tv : public QDialog
{
    Q_OBJECT

public:
    explicit tv(QWidget *parent = 0,QString tv_name="",int season=0,int chapter=0,QString location_tv="");
    ~tv();

    QString s2q(const std::string &s);

    std::string q2s(const QString &s);

    void browser_show();

private slots:
    void on_pushButton_season_minus_clicked();

    void on_pushButton_season_add_clicked();

    void on_pushButton_chapter_minus_clicked();

    void on_pushButton_chapter_add_clicked();

    void on_pushButton_over_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::tv *ui;

    QString tv_name;
    int season;
    int chapter;
    QString location_tv;

    int season_new;
    int chapter_new;

    QString content="";
    QString info="";
};

#endif // TV_H
