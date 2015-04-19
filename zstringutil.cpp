#include "zstringutil.h"

#include <QTextCodec>

ZStringUtil::ZStringUtil()
{
}

QString ZStringUtil::getSizeStr(quint64 size)
{
    if(size >= 1073741824) {
        return QString().sprintf("%.2fG", size / 1073741824.0f);
    } else if(size >= 1048576) {
        return QString().sprintf("%.2fM", size / 1048576.0f);
    } else if(size >= 1024) {
        return QString().sprintf("%.2fK", size / 1024.0f);
    }
    return QString().sprintf("%lldB", size);
}

QString ZStringUtil::fromGBK(const QByteArray &data) {
    QTextCodec *c = QTextCodec::codecForName("GB2312");
    if(NULL == c) {
        return QString();
    }
    return c->toUnicode(data);
}

QByteArray ZStringUtil::toGBK(const QString &in) {
    QTextCodec *c = QTextCodec::codecForName("GB2312");
    if(NULL == c) {
        return QByteArray();
    }
    return c->fromUnicode(in);
}

QString ZStringUtil::fromUTF8(const QByteArray &data) {
    return QString::fromUtf8(data);
}

QByteArray ZStringUtil::toUTF8(const QString &in) {
    return in.toUtf8();
}

QString ZStringUtil::getBaseName(const QString &in) {
    int n = in.lastIndexOf('/');
    if(-1 != n) {
        return in.mid(n + 1);
    }

    n = in.lastIndexOf('\\');
    if(-1 != n) {
        return in.mid(n + 1);
    }
    return in;
}
