/****************************************************************************
** Meta object code from reading C++ file 'lmessageencoder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Norma/lmessageencoder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lmessageencoder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LMessageEncoder_t {
    QByteArrayData data[24];
    char stringdata[289];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LMessageEncoder_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LMessageEncoder_t qt_meta_stringdata_LMessageEncoder = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 10),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 5),
QT_MOC_LITERAL(4, 34, 10),
QT_MOC_LITERAL(5, 45, 17),
QT_MOC_LITERAL(6, 63, 17),
QT_MOC_LITERAL(7, 81, 12),
QT_MOC_LITERAL(8, 94, 9),
QT_MOC_LITERAL(9, 104, 18),
QT_MOC_LITERAL(10, 123, 19),
QT_MOC_LITERAL(11, 143, 7),
QT_MOC_LITERAL(12, 151, 5),
QT_MOC_LITERAL(13, 157, 19),
QT_MOC_LITERAL(14, 177, 8),
QT_MOC_LITERAL(15, 186, 6),
QT_MOC_LITERAL(16, 193, 20),
QT_MOC_LITERAL(17, 214, 5),
QT_MOC_LITERAL(18, 220, 8),
QT_MOC_LITERAL(19, 229, 15),
QT_MOC_LITERAL(20, 245, 2),
QT_MOC_LITERAL(21, 248, 10),
QT_MOC_LITERAL(22, 259, 25),
QT_MOC_LITERAL(23, 285, 3)
    },
    "LMessageEncoder\0encodedMsg\0\0pdata\0"
    "closingAll\0CommandBackToIdle\0"
    "encodeDeviceError\0QJsonObject*\0errObject\0"
    "encodeErrorMessage\0ECommandMessageType\0"
    "msgType\0msgID\0QList<QJsonObject>*\0"
    "pobjects\0encode\0EResponseMessageType\0"
    "mtype\0jsObject\0CloseConnection\0id\0"
    "setVersion\0ESupportedProtocolVersion\0"
    "ver"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LMessageEncoder[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,
       5,    0,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   59,    2, 0x0a /* Public */,
       9,    3,   62,    2, 0x0a /* Public */,
      15,    2,   69,    2, 0x0a /* Public */,
      19,    1,   74,    2, 0x0a /* Public */,
      21,    1,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10, QMetaType::UInt, 0x80000000 | 13,   11,   12,   14,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 7,   17,   18,
    QMetaType::Void, QMetaType::UInt,   20,
    QMetaType::Void, 0x80000000 | 22,   23,

       0        // eod
};

void LMessageEncoder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LMessageEncoder *_t = static_cast<LMessageEncoder *>(_o);
        switch (_id) {
        case 0: _t->encodedMsg((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->closingAll(); break;
        case 2: _t->CommandBackToIdle(); break;
        case 3: _t->encodeDeviceError((*reinterpret_cast< QJsonObject*(*)>(_a[1]))); break;
        case 4: _t->encodeErrorMessage((*reinterpret_cast< ECommandMessageType(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< QList<QJsonObject>*(*)>(_a[3]))); break;
        case 5: _t->encode((*reinterpret_cast< EResponseMessageType(*)>(_a[1])),(*reinterpret_cast< QJsonObject*(*)>(_a[2]))); break;
        case 6: _t->CloseConnection((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 7: _t->setVersion((*reinterpret_cast< ESupportedProtocolVersion(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LMessageEncoder::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LMessageEncoder::encodedMsg)) {
                *result = 0;
            }
        }
        {
            typedef void (LMessageEncoder::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LMessageEncoder::closingAll)) {
                *result = 1;
            }
        }
        {
            typedef void (LMessageEncoder::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LMessageEncoder::CommandBackToIdle)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject LMessageEncoder::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LMessageEncoder.data,
      qt_meta_data_LMessageEncoder,  qt_static_metacall, 0, 0}
};


const QMetaObject *LMessageEncoder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LMessageEncoder::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LMessageEncoder.stringdata))
        return static_cast<void*>(const_cast< LMessageEncoder*>(this));
    return QObject::qt_metacast(_clname);
}

int LMessageEncoder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void LMessageEncoder::encodedMsg(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LMessageEncoder::closingAll()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void LMessageEncoder::CommandBackToIdle()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
