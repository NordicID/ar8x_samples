/****************************************************************************
** Meta object code from reading C++ file 'instancecontrol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../instancecontrol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'instancecontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_InstanceControl_t {
    QByteArrayData data[19];
    char stringdata[232];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InstanceControl_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InstanceControl_t qt_meta_stringdata_InstanceControl = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 6),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 12),
QT_MOC_LITERAL(4, 37, 8),
QT_MOC_LITERAL(5, 46, 14),
QT_MOC_LITERAL(6, 61, 5),
QT_MOC_LITERAL(7, 67, 9),
QT_MOC_LITERAL(8, 77, 5),
QT_MOC_LITERAL(9, 83, 15),
QT_MOC_LITERAL(10, 99, 12),
QT_MOC_LITERAL(11, 112, 4),
QT_MOC_LITERAL(12, 117, 9),
QT_MOC_LITERAL(13, 127, 12),
QT_MOC_LITERAL(14, 140, 22),
QT_MOC_LITERAL(15, 163, 9),
QT_MOC_LITERAL(16, 173, 26),
QT_MOC_LITERAL(17, 200, 6),
QT_MOC_LITERAL(18, 207, 24)
    },
    "InstanceControl\0toIdle\0\0instanceName\0"
    "toActive\0NormaIdentity*\0newID\0TLSstatus\0"
    "state\0checkFileStatus\0readerStatus\0"
    "name\0connected\0clientStatus\0"
    "updateInstanceIdentity\0updatedID\0"
    "handleUpdateDeviceErrorStr\0errStr\0"
    "handleUpdateLLRPErrorStr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InstanceControl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    2,   62,    2, 0x06 /* Public */,
       7,    1,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   70,    2, 0x0a /* Public */,
      10,    2,   71,    2, 0x0a /* Public */,
      13,    2,   76,    2, 0x0a /* Public */,
      14,    1,   81,    2, 0x0a /* Public */,
      16,    2,   84,    2, 0x0a /* Public */,
      18,    2,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 5,    3,    6,
    QMetaType::Void, QMetaType::Bool,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   11,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   11,   12,
    QMetaType::Void, 0x80000000 | 5,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   17,

       0        // eod
};

void InstanceControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InstanceControl *_t = static_cast<InstanceControl *>(_o);
        switch (_id) {
        case 0: _t->toIdle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->toActive((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< NormaIdentity*(*)>(_a[2]))); break;
        case 2: _t->TLSstatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->checkFileStatus(); break;
        case 4: _t->readerStatus((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->clientStatus((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->updateInstanceIdentity((*reinterpret_cast< NormaIdentity*(*)>(_a[1]))); break;
        case 7: _t->handleUpdateDeviceErrorStr((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->handleUpdateLLRPErrorStr((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (InstanceControl::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InstanceControl::toIdle)) {
                *result = 0;
            }
        }
        {
            typedef void (InstanceControl::*_t)(QString , NormaIdentity * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InstanceControl::toActive)) {
                *result = 1;
            }
        }
        {
            typedef void (InstanceControl::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InstanceControl::TLSstatus)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject InstanceControl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_InstanceControl.data,
      qt_meta_data_InstanceControl,  qt_static_metacall, 0, 0}
};


const QMetaObject *InstanceControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InstanceControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InstanceControl.stringdata))
        return static_cast<void*>(const_cast< InstanceControl*>(this));
    return QObject::qt_metacast(_clname);
}

int InstanceControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void InstanceControl::toIdle(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void InstanceControl::toActive(QString _t1, NormaIdentity * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void InstanceControl::TLSstatus(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
