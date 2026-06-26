#ifndef HEMODIALYSIS_DIALOG_H
#define HEMODIALYSIS_DIALOG_H

#include <QDialog>
#include "progressbar_check.h"
#include "progressbar_round.h"
#include "progressbar_splash.h"
namespace Ui {
class Hemodialysis_Dialog;
}

class Hemodialysis_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Hemodialysis_Dialog(QWidget *parent = nullptr);
    ~Hemodialysis_Dialog();
    void drawRoundProgress();

private slots:
    void on_btn_open_clicked();
    void on_btn_connectJ_clicked();
    void on_btn_connectD_clicked();
    void on_btn_claen_clicked();
    void on_btn_fill_clicked();

    void on_btn_start_clicked();
    void on_btn_emergency_clicked();
    void on_btn_check_clicked();
    void on_btn_quit_clicked();
    void updateProgress();


private:
    Ui::Hemodialysis_Dialog *ui;

    QTimer *m_timer;
    ProgressBar_Splash *m_splash;
    ProgressBar_Round *m_fillBar;
    ProgressBar_Round *m_startBar;

};

#endif // HEMODIALYSIS_DIALOG_H
