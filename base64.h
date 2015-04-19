#ifndef BASE64_H
#define BASE64_H

#include <QString>

class Base64
{
public:
    Base64();

    static QString encode(const QByteArray &in);
    static QString decode(const QString &in);
};

#endif // BASE64_H
