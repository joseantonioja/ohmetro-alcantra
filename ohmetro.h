#ifndef OHMETRO_H
#define OHMETRO_H

#include <QMainWindow>
#include <voltagereader.h>

namespace Ui {
class Ohmetro;
}

class Ohmetro : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ohmetro(QWidget *parent = 0);
    ~Ohmetro();
    VoltageReader *vr;

private slots:
    void on_rKOhms_clicked(bool);
    void on_rOhms_clicked(bool);
    void on_new_read(int);

private:
    Ui::Ohmetro *ui;
    QImage led_on;
    QImage led_off;
    int current_resistance;
    void changeValue(int);
    void display_kOhms();
    void display_ohms();
};

#endif // OHMETRO_H
