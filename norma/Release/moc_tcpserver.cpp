/****************************************************************************
** Meta object code from reading C++ file 'tcpserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TCP/tcpserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_server_t {
    QByteArrayData data[25];
    char stringdata[295];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_server_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_server_t qt_meta_stringdata_server = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 7),
QT_MOC_LITERAL(2, 15, 0),
QT_MOC_LITERAL(3, 16, 11),
QT_MOC_LITERAL(4, 28, 4),
QT_MOC_LITERAL(5, 33, 26),
QT_MOC_LITERAL(6, 60, 12),
QT_MOC_LITERAL(7, 73, 13),
QT_MOC_LITERAL(8, 87, 18),
QT_MOC_LITERAL(9, 106, 13),
QT_MOC_LITERAL(10, 120, 15),
QT_MOC_LITERAL(11, 136, 18),
QT_MOC_LITERAL(12, 155, 5),
QT_MOC_LITERAL(13, 161, 11),
QT_MOC_LITERAL(14, 173, 7),
QT_MOC_LITERAL(15, 181, 6),
QT_MOC_LITERAL(16, 188, 16),
QT_MOC_LITERAL(17, 205, 6),
QT_MOC_LITERAL(18, 212, 12),
QT_MOC_LITERAL(19, 225, 11),
QT_MOC_LITERAL(20, 237, 15),
QT_MOC_LITERAL(21, 253, 8),
QT_MOC_LITERAL(22, 262, 9),
QT_MOC_LITERAL(23, 272, 7),
QT_MOC_LITERAL(24, 280, 14)
    },
    "server\0gotData\0\0QByteArray*\0data\0"
    "getReaderEventNotification\0clientAdress\0"
    "stopkeepalive\0clientDisconnected\0"
    "clientAddress\0clientConnected\0"
    "secureStateChanged\0state\0usedVersion\0"
    "version\0Errors\0QList<QSslError>\0errors\0"
    "commonErrors\0allowClient\0SocketEncrypted\0"
    "readData\0writeData\0closing\0commandClosing"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_server[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       5,    1,   92,    2, 0x06 /* Public */,
       7,    0,   95,    2, 0x06 /* Public */,
       8,    1,   96,    2, 0x06 /* Public */,
      10,    1,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,  102,    2, 0x0a /* Public */,
      13,    1,  105,    2, 0x0a /* Public */,
      15,    1,  108,    2, 0x0a /* Public */,
      18,    0,  111,    2, 0x0a /* Public */,
      19,    0,  112,    2, 0x0a /* Public */,
      20,    0,  113,    2, 0x0a /* Public */,
      21,    0,  114,    2, 0x0a /* Public */,
      22,    1,  115,    2, 0x0a /* Public */,
      23,    0,  118,    2, 0x0a /* Public */,
      24,    0,  119,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::UChar,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        server *_t = static_cast<server *>(_o);
        switch (_id) {
        case 0: _t->gotData((*reinterpret_cast< QByteArray*(*)>(_a[1]))); break;
        case 1: _t->getReaderEventNotification((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->stopkeepalive(); break;
        case 3: _t->clientDisconnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->clientConnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->secureStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->usedVersion((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 7: _t->Errors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 8: _t->commonErrors(); break;
        case 9: _t->allowClient(); break;
        case 10: _t->SocketEncrypted(); break;
        case 11: _t->readData(); break;
        case 12: _t->writeData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 13: _t->closing(); break;
        case 14: _t->commandClosing(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (server::*_t)(QByteArray * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&server::gotData)) {
                *result = 0;
            }
        }
        {
            typedef void (server::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&server::getReaderEventNotification)) {
                *result = 1;
            }
        }
        {
            typedef void (server::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&server::stopkeepalive)) {
                *result = 2;
            }
        }
        {
            typedef void (server::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&server::clientDisconnected)) {
                *result = 3;
            }
        }
        {
            typedef void (server::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&server::clientConnected)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject server::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_server.data,
      qt_meta_data_server,  qt_static_metacall, 0, 0}
};


const QMetaObject *server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *server::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_server.stringdata))
        return static_cast<void*>(const_cast< server*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void server::gotData(QByteArray * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void server::getReaderEventNotification(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void server::stopkeepalive()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void server::clientDisconnected(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void server::clientConnected(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
