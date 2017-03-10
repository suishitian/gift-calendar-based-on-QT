#ifndef TV_INPUT_H
#define TV_INPUT_H

#include <QDialog>

namespace Ui {
class tv_input;
}

class tv_input : public QDialog
{
    Q_OBJECT

public:
    explicit tv_input(QWidget *parent = 0,QString location_tv="");
    ~tv_input();

    QString s2q(const std::string &s);

    std::string q2s(const QString &s);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::tv_input *ui;

    int season=1;
    int chapter=1;
    QString tv_name="";
    QString location_tv;
};

#endif // TV_INPUT_H
