#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


class Arduino
{
public:
    Arduino();
    ~Arduino();
    int connect_arduino();
    int close_arduino();
    void write_to_arduino ( QByteArray ); // envoyer des données vers arduino.
    QByteArray read_from_arduino(); //recevoir des données de la carte Arduino
    QSerialPort* getserial();// accesseur
    QString getarduino_port_name();
    //void sendMessageToArduino(const QString & message);




    //
    void buzzer_on();   // Pour activer le buzzer
    void buzzer_off();  // Pour désactiver le buzzer

private:
    QSerialPort * serial;
    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_producy_id=67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;

};

#endif // ARDUINO_H
