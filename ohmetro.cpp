#include "ohmetro.h"
#include "ui_ohmetro.h"
#include <QImage>
#include <QPixmap>
#include <QString>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <thread>
using namespace std;
Ohmetro::Ohmetro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ohmetro)
{
    QString dir = "/home/jose/Ohmetro/imgs/";//Directorio de las imágenes del led
    ui->setupUi(this);
    this->led_on = QImage(dir + "red_circle.png");
    this->led_off = QImage(dir + "white_circle.png");
    this->current_resistance = 0;
    ui->lblDown->setPixmap(QPixmap::fromImage(led_off));
    ui->lblUp->setPixmap(QPixmap::fromImage(led_off));
    QPalette palette = ui->lcdNumber->palette();
    palette.setColor(ui->lcdNumber->backgroundRole(), QColor(91, 252, 85));
    ui->lcdNumber->setPalette(palette);
    ui->lcdNumber->setAutoFillBackground(true);
    changeValue(this->current_resistance);
    vr = new VoltageReader(this);
    vr->start();
    connect(vr, SIGNAL(new_read(float)), this, SLOT(on_new_read(float)),Qt::UniqueConnection);

}

void Ohmetro::changeValue(int v){
    if(v>=100 && v<=1000){
        if(ui->rKOhms->isChecked()){
            display_kOhms();
        }
        else{
            display_ohms();
        }
        ui->lblDown->setPixmap(QPixmap::fromImage(led_off));
        ui->lblUp->setPixmap(QPixmap::fromImage(led_off));
    }
    else if(v<100){
        ui->lcdNumber->display("----");
        ui->lblDown->setPixmap(QPixmap::fromImage(led_on));
        ui->lblUp->setPixmap(QPixmap::fromImage(led_off));
    }
    else{
        ui->lcdNumber->display("----");
        ui->lblDown->setPixmap(QPixmap::fromImage(led_off));
        ui->lblUp->setPixmap(QPixmap::fromImage(led_on));
    }
}
Ohmetro::~Ohmetro()
{
    delete ui;
}

void Ohmetro::on_rOhms_clicked(bool checked)
{
    if(checked){
        display_ohms();
    }
}

void Ohmetro::on_rKOhms_clicked(bool checked)
{
    if(checked){
        display_kOhms();
    }
}

void Ohmetro::display_kOhms(){
    if(this->current_resistance>=100 && this->current_resistance<=1000){
        char stringValue[6];
        QString newValue;
        sprintf(stringValue, "%1.2f",this->current_resistance/(float)1000);
        for(int i=0; i<5; i++){
            if(stringValue[i]==' ')
                stringValue[i]='0';
        }
        newValue = stringValue;
        ui->lcdNumber->display(newValue);
    }
}
void Ohmetro::display_ohms(){
    if(this->current_resistance>=100 && this->current_resistance<=1000){
        char stringValue[6];
        QString newValue;
        sprintf(stringValue, "%4d", this->current_resistance);
        for(int i=0; i<5; i++){
            if(stringValue[i]==' ')
                stringValue[i]='0';
        }
        newValue = stringValue;
        ui->lcdNumber->display(newValue);
    }
}
void Ohmetro::on_new_read(float vin){
    float error = 0.1;
    cout << "Leyendo "<<vin<<"V"<<endl;
    if(vin>5){
        if(vin-5 < error)
            vin = 5;
    }
    if(vin<0){
        if(0-vin < error)
            vin = 0;
    }
    vin = vin/6.1728;
    this->current_resistance = (int)((10000*(101*vin + 10))/(1000-101*vin));
    this->changeValue(this->current_resistance);
}
