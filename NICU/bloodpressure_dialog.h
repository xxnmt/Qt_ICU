#ifndef BLOODPRESSURE_DIALOG_H
#define BLOODPRESSURE_DIALOG_H
#include "bloodpressure.h"
#include <QDialog>

namespace Ui {
class BloodPressure_Dialog;
}

class BloodPressure_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit BloodPressure_Dialog(QWidget *parent = nullptr);
    ~BloodPressure_Dialog();

    void initBP();

private slots:

    void on_btn_quit_clicked();

private:
    Ui::BloodPressure_Dialog *ui;

    BloodPressure *m_bloodPressure;
};

#endif // BLOODPRESSURE_DIALOG_H
