#ifndef VENTILATOR_DIALOG_H
#define VENTILATOR_DIALOG_H
#include <QDialog>
#include "user_data.h"
#include "serial_tool.h"

namespace Ui {
class Ventilator_Dialog;
}

enum VentilationMode {
    VCV,
    PCV,
    PSV
};

enum ParamType {
    SET_PARAM,
    MONITOR_PARAM,
    DERIVED_PARAM,
    NA_PARAM
};

class Ventilator_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Ventilator_Dialog(QWidget *parent = nullptr);
    ~Ventilator_Dialog();

    void showGif();
    void alarmLight();
    void switchMode(VentilationMode mode);
    void updateParamStatus(const QString& paramName, ParamType type);
    void sendSetParams();
    ParamType getParamType(VentilationMode mode, const QString& paramName);

private slots:
    void on_btn_lock_clicked();
    void on_btn_quit_clicked();
    void updateLight();
    void receiveData();
    void on_comboBox_ventilationMode_currentIndexChanged(int index);

private:
    Ui::Ventilator_Dialog *ui;

    Serial_Tool *m_serial;
    QTimer *m_timer;
    bool m_lock;
    int m_lightState;
    VentilationMode m_currentMode;
    bool serialportInit();

};

#endif // VENTILATOR_DIALOG_H