#include "arduino.h"
#include<QByteArray>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QSqlError>

Arduino::Arduino()
{
    serial = new QSerialPort();
    arduino_is_available = false;


}

Arduino::~Arduino()
{
    if (serial->isOpen()) {
        serial->close();
    }
    delete serial;
}

int Arduino::connect_arduino()
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Port name: " << serial_port_info.portName();
        qDebug() << "Vendor ID: " << serial_port_info.vendorIdentifier();
        qDebug() << "Product ID: " << serial_port_info.productIdentifier();
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
            }
        }
    }
    qDebug() << "arduino_port_name is:" << arduino_port_name;
    if (!arduino_is_available) {
        qDebug() << "Arduino non trouvé sur les ports disponibles!";
        return 1; // Arduino not found
    }
    if (arduino_is_available) {
        qDebug() << "Arduino connected on port:" << arduino_port_name;
        serial->setPortName(arduino_port_name);
        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0; // Success
        }
        qDebug() << "Failed to open the serial port!";
    }
    return 1; // If execution reaches here, it means failure
}

int Arduino::close_arduino()
{
    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;
}

QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable()){
        data=serial->readAll();
        return data;
    }
    return QByteArray();
}

void Arduino::write_to_arduino(QByteArray d)
{
    if(serial->isWritable()){
        serial->write(d);
        serial->flush();
    }else{
        qDebug()<<"Couldn't write to serial!";
    }
}
void Arduino::sendMessageToArduino(const QString& message) {
    QByteArray byteArrayMessage = message.toUtf8();
    write_to_arduino(byteArrayMessage);
}
