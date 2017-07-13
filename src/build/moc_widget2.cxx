/****************************************************************************
** Meta object code from reading C++ file 'widget2.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../widget2.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Widget2[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      34,    8,    8,    8, 0x08,
      55,    8,    8,    8, 0x08,
      85,    8,    8,    8, 0x08,
     120,  116,    8,    8, 0x08,
     151,    8,    8,    8, 0x08,
     174,    8,    8,    8, 0x08,
     203,  198,    8,    8, 0x08,
     234,    8,    8,    8, 0x08,
     261,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Widget2[] = {
    "Widget2\0\0on_btnPrevious_clicked()\0"
    "on_btnNext_clicked()\0on_radioBtnComplete_clicked()\0"
    "on_radioBtnComponent_clicked()\0val\0"
    "on_threshold_valueChanged(int)\0"
    "on_btnRemove_clicked()\0on_btnRemove2_clicked()\0"
    "mode\0on_tabMode_currentChanged(int)\0"
    "on_btnAnnotation_clicked()\0"
    "on_btnPrint_clicked()\0"
};

void Widget2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Widget2 *_t = static_cast<Widget2 *>(_o);
        switch (_id) {
        case 0: _t->on_btnPrevious_clicked(); break;
        case 1: _t->on_btnNext_clicked(); break;
        case 2: _t->on_radioBtnComplete_clicked(); break;
        case 3: _t->on_radioBtnComponent_clicked(); break;
        case 4: _t->on_threshold_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_btnRemove_clicked(); break;
        case 6: _t->on_btnRemove2_clicked(); break;
        case 7: _t->on_tabMode_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_btnAnnotation_clicked(); break;
        case 9: _t->on_btnPrint_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Widget2::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Widget2::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget2,
      qt_meta_data_Widget2, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Widget2::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Widget2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Widget2::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Widget2))
        return static_cast<void*>(const_cast< Widget2*>(this));
    return QWidget::qt_metacast(_clname);
}

int Widget2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
