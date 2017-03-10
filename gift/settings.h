#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QDir>

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    ~settings();

    void set_check();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::settings *ui;

    QString location=QDir::currentPath();
    int popup_flag=0;
    int music_flag=0;
};

#endif // SETTINGS_H
