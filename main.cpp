#include "mainwindow.h"
#include <QApplication>

#include "zstringutil.h"
#include "base64.h"

#include <QTextCodec>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    // size str
//    qDebug() << ZStringUtil::getSizeStr(1048576);

//    // codec
//    QTextCodec *codec = QTextCodec::codecForName("UTF8");
//    QString encodedString = codec->toUnicode("我爱杭州");
//    qDebug() << encodedString << QString().fromLocal8Bit("我爱中国");

    // base64
    QString encode = Base64::encode(QString().fromUtf8("我爱中国").toUtf8());
    qDebug() << encode;
    qDebug() << Base64::decode(encode);


    return a.exec();
}
