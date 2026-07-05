#ifndef BLOODPRESSURE_DIALOG_H
#define BLOODPRESSURE_DIALOG_H
#include "bloodpressure.h"
#include <QDialog>
#include<QMouseEvent>
namespace Ui {
class BloodPressure_Dialog;
}

class BloodPressure_Dialog : public QDialog
{
    Q_OBJECT

public:
    QPoint m_offset;
    explicit BloodPressure_Dialog(QWidget *parent = nullptr);
    ~BloodPressure_Dialog();

    void initBP();

private slots:

    void on_btn_quit_clicked();

private:
    Ui::BloodPressure_Dialog *ui;

    BloodPressure *m_bloodPressure;
protected:
    // 重写鼠标事件
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

};

#endif // BLOODPRESSURE_DIALOG_H
