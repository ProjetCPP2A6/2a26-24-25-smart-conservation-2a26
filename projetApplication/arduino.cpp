#include "arduino.h"
#include "qserialport.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

Arduino::Arduino() {
    serial = new QSerialPort;
    arduino_is_available = false;
}

int Arduino::connect_arduino() {
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        // Vérifiez que l'Arduino est bien présent par son identifiant
        if (info.hasVendorIdentifier() && info.hasProductIdentifier()) {
            // Vous pouvez vérifier ici les IDs du vendeur et du produit Arduino si nécessaire
            arduino_port_name = info.portName();
            arduino_is_available = true;
        }
    }

    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);
        if (serial->open(QIODevice::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            qDebug() << "Arduino connecté sur le port:" << arduino_port_name;
            return 0; // Connexion réussie
        } else {
            qDebug() << "Erreur d'ouverture du port série.";
        }
    }
    return 1; // Échec
}

int Arduino::close_arduino() {
    if (serial->isOpen()) {
        serial->close();
        return 0;
    }
    return 1;
}

void Arduino::write_to_arduino(QByteArray data) {
    if (serial->isWritable()) {
        serial->write(data);
        qDebug() << "Commande envoyée à Arduino:" << data;
    } else {
        qDebug() << "Impossible d'écrire sur le port série.";
    }
}

QByteArray Arduino::read_from_arduino() {
    QByteArray data;
    if (serial->isReadable()) {
        data = serial->readAll();
    }
    return data;
}

QSerialPort* Arduino::getserial() {
    return serial;
}

QString Arduino::getarduino_port_name() {
    return arduino_port_name;
}
