/****************************************************************************
** Meta object code from reading C++ file 'nurapidecoder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Norma/nurapidecoder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nurapidecoder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NurAPIDecoder_t {
    QByteArrayData data[35];
    char stringdata[492];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NurAPIDecoder_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NurAPIDecoder_t qt_meta_stringdata_NurAPIDecoder = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 15),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 20),
QT_MOC_LITERAL(4, 52, 4),
QT_MOC_LITERAL(5, 57, 12),
QT_MOC_LITERAL(6, 70, 8),
QT_MOC_LITERAL(7, 79, 7),
QT_MOC_LITERAL(8, 87, 18),
QT_MOC_LITERAL(9, 106, 15),
QT_MOC_LITERAL(10, 122, 11),
QT_MOC_LITERAL(11, 134, 8),
QT_MOC_LITERAL(12, 143, 16),
QT_MOC_LITERAL(13, 160, 8),
QT_MOC_LITERAL(14, 169, 9),
QT_MOC_LITERAL(15, 179, 22),
QT_MOC_LITERAL(16, 202, 6),
QT_MOC_LITERAL(17, 209, 10),
QT_MOC_LITERAL(18, 220, 5),
QT_MOC_LITERAL(19, 226, 15),
QT_MOC_LITERAL(20, 242, 19),
QT_MOC_LITERAL(21, 262, 23),
QT_MOC_LITERAL(22, 286, 24),
QT_MOC_LITERAL(23, 311, 22),
QT_MOC_LITERAL(24, 334, 10),
QT_MOC_LITERAL(25, 345, 17),
QT_MOC_LITERAL(26, 363, 5),
QT_MOC_LITERAL(27, 369, 14),
QT_MOC_LITERAL(28, 384, 14),
QT_MOC_LITERAL(29, 399, 5),
QT_MOC_LITERAL(30, 405, 19),
QT_MOC_LITERAL(31, 425, 17),
QT_MOC_LITERAL(32, 443, 18),
QT_MOC_LITERAL(33, 462, 13),
QT_MOC_LITERAL(34, 476, 15)
    },
    "NurAPIDecoder\0MessageResponse\0\0"
    "EResponseMessageType\0type\0QJsonObject*\0"
    "jsObject\0ROStart\0QList<QJsonObject>\0"
    "RoSpecParamList\0DeviceError\0QString*\0"
    "errorDescription\0PingStop\0PingStart\0"
    "ReaderConnectionStatus\0status\0napidecode\0"
    "mtype\0ROSpecOperation\0ConnectionPingCheck\0"
    "ConnectionPingCheckStop\0"
    "ConnectionPingCheckStart\0"
    "USBConnectionPingCheck\0BackToIdle\0"
    "handleReaderState\0state\0ReaderInitials\0"
    "NormaIdentity*\0newID\0PeriodicRoSpecStart\0"
    "CheckNotification\0ClientDisconnected\0"
    "clientAddress\0ClientConnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NurAPIDecoder[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  109,    2, 0x06 /* Public */,
       7,    1,  114,    2, 0x06 /* Public */,
      10,    1,  117,    2, 0x06 /* Public */,
      13,    0,  120,    2, 0x06 /* Public */,
      14,    0,  121,    2, 0x06 /* Public */,
      15,    1,  122,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    2,  125,    2, 0x0a /* Public */,
      19,    1,  130,    2, 0x0a /* Public */,
      20,    0,  133,    2, 0x0a /* Public */,
      21,    0,  134,    2, 0x0a /* Public */,
      22,    0,  135,    2, 0x0a /* Public */,
      23,    0,  136,    2, 0x0a /* Public */,
      24,    0,  137,    2, 0x0a /* Public */,
      25,    1,  138,    2, 0x0a /* Public */,
      27,    1,  141,    2, 0x0a /* Public */,
      30,    0,  144,    2, 0x0a /* Public */,
      31,    0,  145,    2, 0x0a /* Public */,
      32,    1,  146,    2, 0x0a /* Public */,
      34,    1,  149,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,

 // slots: parameters
    QMetaType::Void, QMetaType::UShort, 0x80000000 | 5,   18,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   26,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   33,
    QMetaType::Void, QMetaType::QString,   33,

       0        // eod
};

void NurAPIDecoder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NurAPIDecoder *_t = static_cast<NurAPIDecoder *>(_o);
        switch (_id) {
        case 0: _t->MessageResponse((*reinterpret_cast< EResponseMessageType(*)>(_a[1])),(*reinterpret_cast< QJsonObject*(*)>(_a[2]))); break;
        case 1: _t->ROStart((*reinterpret_cast< QList<QJsonObject>(*)>(_a[1]))); break;
        case 2: _t->DeviceError((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 3: _t->PingStop(); break;
        case 4: _t->PingStart(); break;
        case 5: _t->ReaderConnectionStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->napidecode((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< QJsonObject*(*)>(_a[2]))); break;
        case 7: _t->ROSpecOperation((*reinterpret_cast< QList<QJsonObject>(*)>(_a[1]))); break;
        case 8: _t->ConnectionPingCheck(); break;
        case 9: _t->ConnectionPingCheckStop(); break;
        case 10: _t->ConnectionPingCheckStart(); break;
        case 11: _t->USBConnectionPingCheck(); break;
        case 12: _t->BackToIdle(); break;
        case 13: _t->handleReaderState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->ReaderInitials((*reinterpret_cast< NormaIdentity*(*)>(_a[1]))); break;
        case 15: _t->PeriodicRoSpecStart(); break;
        case 16: _t->CheckNotification(); break;
        case 17: _t->ClientDisconnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->ClientConnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QJsonObject> >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QJsonObject> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NurAPIDecoder::*_t)(EResponseMessageType , QJsonObject * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NurAPIDecoder::MessageResponse)) {
                *result = 0;
            }
        }
        {
            typedef void (NurAPIDecoder::*_t)(QList<QJsonObject> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NurAPIDecoder::ROStart)) {
                *result = 1;
            }
        }
        {
            typedef void (NurAPIDecoder::*_t)(QString * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NurAPIDecoder::DeviceError)) {
                *result = 2;
            }
        }
        {
            typedef void (NurAPIDecoder::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NurAPIDecoder::PingStop)) {
                *result = 3;
            }
        }
        {
            typedef void (NurAPIDecoder::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NurAPIDecoder::PingStart)) {
                *result = 4;
            }
        }
        {
            typedef void (NurAPIDecoder::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NurAPIDecoder::ReaderConnectionStatus)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject NurAPIDecoder::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NurAPIDecoder.data,
      qt_meta_data_NurAPIDecoder,  qt_static_metacall, 0, 0}
};


const QMetaObject *NurAPIDecoder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NurAPIDecoder::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NurAPIDecoder.stringdata))
        return static_cast<void*>(const_cast< NurAPIDecoder*>(this));
    return QObject::qt_metacast(_clname);
}

int NurAPIDecoder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void NurAPIDecoder::MessageResponse(EResponseMessageType _t1, QJsonObject * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NurAPIDecoder::ROStart(QList<QJsonObject> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NurAPIDecoder::DeviceError(QString * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NurAPIDecoder::PingStop()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void NurAPIDecoder::PingStart()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void NurAPIDecoder::ReaderConnectionStatus(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
