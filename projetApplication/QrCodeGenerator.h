/*
 * Copyright (c) 2023 Alex Spataru <https://github.com/alex-spataru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include <QImage>
#include <QObject>
#include <QString>

#include "qrcodegen/qrcodegen.h"

class QrCodeGenerator : public QObject
{
public:

    explicit QrCodeGenerator(QObject *parent = nullptr);


    QImage generateQr(const QString &data, const quint16 size = 1000, const quint16 borderSize = 1,
                      qrcodegen::QrCode::Ecc errorCorrection = qrcodegen::QrCode::Ecc::MEDIUM);


    QString generateSvgQr(const QString &data, const quint16 borderSize = 1,
                          qrcodegen::QrCode::Ecc errorCorrection = qrcodegen::QrCode::Ecc::MEDIUM);

private:

    QString toSvgString(const qrcodegen::QrCode &qr, quint16 border) const;


    QImage qrCodeToImage(const qrcodegen::QrCode &qrCode, quint16 border, const quint16 size) const;
};
