#include "base64.h"

#include <QIODevice>
#include <QDataStream>

#define B64_EOLN            0xF0    // 换行\n
#define B64_CR              0xF1    // 回车\r
#define B64_EOF             0xF2    // 连字符-
#define B64_WS              0xE0    // 跳格或者空格（\t、space）
#define B64_ERROR           0xFF    // 错误字符
#define B64_NOT_BASE64      0xF3    // 空白字符、回车换行字符、连字符

static const char *DATA_BIN2ASCII = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const quint8 DATA_ASCII2BIN[128] = {
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xF0,0xFF,0xFF,0xF1,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3E,0xFF,0xF2,0xFF,0x3F,
    0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,
    0xFF,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,
    0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
    0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0xFF,0xFF,0xFF,0xFF,0xFF
};

Base64::Base64()
{
}

QString Base64::encode(const QByteArray &in)
{
    if(in.isEmpty()) return QString();

    QString sb;
    int index = 0;
    for(int i = in.length(); i > 0; i -= 3)  {  // 将3字节数据转换成4个ASCII字符
        if(i >= 3) {
            int b0 = in[index++] & 0xFF;
            int b1 = in[index++] & 0xFF;
            int b2 = in[index++] & 0xFF;
            sb.append(DATA_BIN2ASCII[b0 >> 2]);
            sb.append(DATA_BIN2ASCII[((b0 << 4) | (b1 >> 4)) & 0x3F]);
            sb.append(DATA_BIN2ASCII[((b1 << 2) | (b2 >> 6)) & 0x3F]);
            sb.append(DATA_BIN2ASCII[b2 & 0x3F]);
        } else {
            int b0 = in[index++] & 0xFF;
            int b1;
            if(i == 2)
                b1 = in[index++] & 0xFF;
            else
                b1 = 0;

            sb.append(DATA_BIN2ASCII[b0 >> 2]);
            sb.append(DATA_BIN2ASCII[((b0 << 4) | (b1 >> 4)) & 0x3F]);
            if(i == 1)
                sb.append('=');  // 填充字符
            else
                sb.append(DATA_BIN2ASCII[(b1 << 2) & 0x3F]);
            sb.append('=');  // 填充字符
        }
    }

    return sb;
}

QString Base64::decode(const QString &in)
{
    if(in.isEmpty()) return QString();

    int index = 0;
    int previous = 0;
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);

    for (int i = 0; i < in.length(); i++) {
        ushort charValue = in[i].unicode();
        if(charValue >= 0x80) return QString();

        int orderValue = DATA_ASCII2BIN[charValue];
        if (B64_ERROR == orderValue) return QString();

        // 跳过空白字符、回车换行字符、连字符
        if (B64_NOT_BASE64 == (orderValue | 0x13))
            continue;

        if (0 == index) {
            if ('=' == charValue) return QString();
            previous = orderValue;
            index++;
        } else if (1 == index) {
            if ('=' == charValue) return QString();
            out << static_cast<quint8>((previous << 2) | (orderValue >> 4));
            previous = orderValue;
            index++;
        } else if (2 == index) {
            if ('=' == charValue) {
                // 简化处理，不再判断第二个'='
                index = 0;
                break;
            }
            out << static_cast<quint8>((previous << 4) | (orderValue >> 2));
            previous = orderValue;
            index++;
        } else {
            index = 0;
            if ('=' == charValue) break;
            out << static_cast<quint8>((previous << 6) | orderValue);
        }
    }

    if (0 == index) {
        return QString::fromUtf8(ba);
    } else {
        return QString();
    }
}
