#ifndef ZSTRINGUTIL_H
#define ZSTRINGUTIL_H

#include <QString>

class ZStringUtil
{
public:
    ZStringUtil();

    static QString getSizeStr(quint64 size);

    static QString fromGBK(const QByteArray &data);
    static QByteArray toGBK(const QString &in);
    static QString fromUTF8(const QByteArray &data);
    static QByteArray toUTF8(const QString &in);

    static QString getBaseName(const QString &in);

};

#endif // ZSTRINGUTIL_H
