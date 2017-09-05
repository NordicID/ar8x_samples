/****************************************************************************
** Meta object code from reading C++ file 'errorhandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Norma/errorhandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'errorhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ErrorHandler_t {
    QByteArrayData data[24];
    char stringdata[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ErrorHandler_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ErrorHandler_t qt_meta_stringdata_ErrorHandler = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 11),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 19),
QT_MOC_LITERAL(4, 46, 7),
QT_MOC_LITERAL(5, 54, 5),
QT_MOC_LITERAL(6, 60, 19),
QT_MOC_LITERAL(7, 80, 8),
QT_MOC_LITERAL(8, 89, 12),
QT_MOC_LITERAL(9, 102, 9),
QT_MOC_LITERAL(10, 112, 12),
QT_MOC_LITERAL(11, 125, 8),
QT_MOC_LITERAL(12, 134, 8),
QT_MOC_LITERAL(13, 143, 8),
QT_MOC_LITERAL(14, 152, 11),
QT_MOC_LITERAL(15, 164, 16),
QT_MOC_LITERAL(16, 181, 10),
QT_MOC_LITERAL(17, 192, 14),
QT_MOC_LITERAL(18, 207, 13),
QT_MOC_LITERAL(19, 221, 11),
QT_MOC_LITERAL(20, 233, 10),
QT_MOC_LITERAL(21, 244, 8),
QT_MOC_LITERAL(22, 253, 11),
QT_MOC_LITERAL(23, 265, 8)
    },
    "ErrorHandler\0ErrorObject\0\0ECommandMessageType\0"
    "msgType\0msgID\0QList<QJsonObject>*\0"
    "pobjects\0QJsonObject*\0errObject\0"
    "ErrorStrInfo\0erroType\0QString*\0errorStr\0"
    "DeviceError\0errorDescription\0EventError\0"
    "EParameterType\0ParameterType\0EStatusCode\0"
    "statuscode\0FieldNum\0Fstatuscode\0"
    "complete"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ErrorHandler[] = {

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
       1,    3,   54,    2, 0x06 /* Public */,
       1,    1,   61,    2, 0x06 /* Public */,
      10,    2,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    1,   69,    2, 0x0a /* Public */,
      16,    6,   72,    2, 0x0a /* Public */,
      16,    4,   85,    2, 0x0a /* Public */,
      16,    4,   94,    2, 0x0a /* Public */,
      16,    3,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt, 0x80000000 | 6,    4,    5,    7,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 12,   11,   13,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12,   15,
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt, 0x80000000 | 17, 0x80000000 | 19, QMetaType::UShort, 0x80000000 | 19,    4,    5,   18,   20,   21,   22,
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt, QMetaType::UShort, 0x80000000 | 19,    4,    5,   21,   20,
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt, 0x80000000 | 19, 0x80000000 | 12,    4,    5,   20,   15,
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt, QMetaType::Bool,    4,    5,   23,

       0        // eod
};

void ErrorHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ErrorHandler *_t = static_cast<ErrorHandler *>(_o);
        switch (_id) {
        case 0: _t->ErrorObject((*reinterpret_cast< ECommandMessageType(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< QList<QJsonObject>*(*)>(_a[3]))); break;
        case 1: _t->ErrorObject((*reinterpret_cast< QJsonObject*(*)>(_a[1]))); break;
        case 2: _t->ErrorStrInfo((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2]))); break;
        case 3: _t->DeviceError((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 4: _t->EventError((*reinterpret_cast< ECommandMessageType(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< EParameterType(*)>(_a[3])),(*reinterpret_cast< EStatusCode(*)>(_a[4])),(*reinterpret_cast< quint16(*)>(_a[5])),(*reinterpret_cast< EStatusCode(*)>(_a[6]))); break;
        case 5: _t->EventError((*reinterpret_cast< ECommandMessageType(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3])),(*reinterpret_cast< EStatusCode(*)>(_a[4]))); break;
        case 6: _t->EventError((*reinterpret_cast< ECommandMessageType(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< EStatusCode(*)>(_a[3])),(*reinterpret_cast< QString*(*)>(_a[4]))); break;
        case 7: _t->EventError((*reinterpret_cast< ECommandMessageType(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ErrorHandler::*_t)(ECommandMessageType , quint32 , QList<QJsonObject> * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ErrorHandler::ErrorObject)) {
                *result = 0;
            }
        }
        {
            typedef void (ErrorHandler::*_t)(QJsonObject * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ErrorHandler::ErrorObject)) {
                *result = 1;
            }
        }
        {
            typedef void (ErrorHandler::*_t)(bool , QString * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ErrorHandler::ErrorStrInfo)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject ErrorHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ErrorHandler.data,
      qt_meta_data_ErrorHandler,  qt_static_metacall, 0, 0}
};


const QMetaObject *ErrorHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ErrorHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ErrorHandler.stringdata))
        return static_cast<void*>(const_cast< ErrorHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int ErrorHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ErrorHandler::ErrorObject(ECommandMessageType _t1, quint32 _t2, QList<QJsonObject> * _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ErrorHandler::ErrorObject(QJsonObject * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ErrorHandler::ErrorStrInfo(bool _t1, QString * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
