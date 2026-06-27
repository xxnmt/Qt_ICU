#ifndef MAIN_DIALOG_H
#define MAIN_DIALOG_H
#include "ecgtest_dialog.h"
#include "hemodialysis_dialog.h"
#include "bloodpressure_dialog.h"
// #include "ventilator_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Main_Dialog;
}
QT_END_NAMESPACE

class Main_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Main_Dialog(QWidget *parent = nullptr);
    ~Main_Dialog() override;

private slots:
    void on_btn_Heart_clicked();

    void on_btn_Pressure_clicked();

    void on_btn_Blood_clicked();

    void on_btn_Quit_clicked();

    void on_btn_Breath_clicked();

private:
    Ui::Main_Dialog *ui;
};
#endif // MAIN_DIALOG_H


