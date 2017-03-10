#ifndef CODE_H
#define CODE_H

#include <QDialog>
#include <QDir>

namespace Ui {
class code;
}

class code : public QDialog
{
    Q_OBJECT

public:
    explicit code(QWidget *parent = 0);
    ~code();

private slots:
    void on_pushButton_Hcal_clicked();

    void on_pushButton_Hcode_clicked();

    void on_pushButton_Hjul_clicked();

    void on_pushButton_Hmain_clicked();

    void on_pushButton_Hmemo_c_clicked();

    void on_pushButton_Hmemo_s_clicked();

    void on_pushButton_Hpopup_clicked();

    void on_pushButton_Hset_clicked();

    void on_pushButton_Htv_clicked();

    void on_pushButton_Htvin_clicked();

    void on_pushButton_Ccal_clicked();

    void on_pushButton_Ccode_clicked();

    void on_pushButton_Cjul_clicked();

    void on_pushButton_Cmain_clicked();

    void on_pushButton_Cmemo_c_clicked();

    void on_pushButton_Cmemo_s_clicked();

    void on_pushButton_Cpopup_clicked();

    void on_pushButton_Cset_clicked();

    void on_pushButton_Ctv_clicked();

    void on_pushButton_Ctvin_clicked();

private:
    Ui::code *ui;
    QString location=QDir::currentPath();
};

#endif // CODE_H
