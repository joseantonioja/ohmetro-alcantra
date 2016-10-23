#include "voltagereader.h"
#include <stdio.h>
#include <iostream>
VoltageReader::VoltageReader(QObject* parent)
    : QThread(parent)
{
    std::cout << "Nuevo hilo"<<std::endl;
}
void VoltageReader::run(){
    //FILE* file = fopen("/dev/ttyUSB0","r");
    FILE* f = fopen("/home/jose/Ohmetro/voltages.txt","r");
    float value;
    while((fscanf(f, "%f", &value))!=EOF){
        std::cout << value<<std::endl;
        emit new_read(value);
        this->msleep(3000);
    }
    std::cout << "Fin de archivo"<<std::endl;
    this->exit(0);
}

