/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Widget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      39,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      29,    7,    7,    7, 0x08,
      54,    7,    7,    7, 0x08,
      85,   78,    7,    7, 0x08,
     113,   78,    7,    7, 0x08,
     143,   78,    7,    7, 0x08,
     174,   78,    7,    7, 0x08,
     211,   78,    7,    7, 0x08,
     239,   78,    7,    7, 0x08,
     267,   78,    7,    7, 0x08,
     295,   78,    7,    7, 0x08,
     323,   78,    7,    7, 0x08,
     351,   78,    7,    7, 0x08,
     379,   78,    7,    7, 0x08,
     407,   78,    7,    7, 0x08,
     435,   78,    7,    7, 0x08,
     463,   78,    7,    7, 0x08,
     492,   78,    7,    7, 0x08,
     521,   78,    7,    7, 0x08,
     550,   78,    7,    7, 0x08,
     579,   78,    7,    7, 0x08,
     608,   78,    7,    7, 0x08,
     641,  637,    7,    7, 0x08,
     670,  637,    7,    7, 0x08,
     699,   78,    7,    7, 0x08,
     728,  637,    7,    7, 0x08,
     757,  637,    7,    7, 0x08,
     786,   78,    7,    7, 0x08,
     815,  637,    7,    7, 0x08,
     844,  637,    7,    7, 0x08,
     873,   78,    7,    7, 0x08,
     902,  637,    7,    7, 0x08,
     931,  637,    7,    7, 0x08,
     960,   78,    7,    7, 0x08,
     989,  637,    7,    7, 0x08,
    1018,  637,    7,    7, 0x08,
    1052, 1047,    7,    7, 0x08,
    1083,    7,    7,    7, 0x08,
    1105,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Widget[] = {
    "Widget\0\0on_btnOpen_clicked()\0"
    "on_btnGenerate_clicked()\0"
    "on_extractVOI_clicked()\0status\0"
    "on_checkAxial_clicked(bool)\0"
    "on_checkCoronal_clicked(bool)\0"
    "on_checkSagittal_clicked(bool)\0"
    "on_checkPickPtsOnSlice_clicked(bool)\0"
    "on_checkBox_1_clicked(bool)\0"
    "on_checkBox_2_clicked(bool)\0"
    "on_checkBox_3_clicked(bool)\0"
    "on_checkBox_4_clicked(bool)\0"
    "on_checkBox_5_clicked(bool)\0"
    "on_checkBox_6_clicked(bool)\0"
    "on_checkBox_7_clicked(bool)\0"
    "on_checkBox_8_clicked(bool)\0"
    "on_checkBox_9_clicked(bool)\0"
    "on_checkBox_10_clicked(bool)\0"
    "on_checkBox_11_clicked(bool)\0"
    "on_checkBox_12_clicked(bool)\0"
    "on_checkBox_13_clicked(bool)\0"
    "on_checkBox_14_clicked(bool)\0"
    "on_checkBox_15_clicked(bool)\0val\0"
    "on_minBox1_valueChanged(int)\0"
    "on_maxBox1_valueChanged(int)\0"
    "on_checkBox_16_clicked(bool)\0"
    "on_minBox2_valueChanged(int)\0"
    "on_maxBox2_valueChanged(int)\0"
    "on_checkBox_17_clicked(bool)\0"
    "on_minBox3_valueChanged(int)\0"
    "on_maxBox3_valueChanged(int)\0"
    "on_checkBox_18_clicked(bool)\0"
    "on_minBox4_valueChanged(int)\0"
    "on_maxBox4_valueChanged(int)\0"
    "on_checkBox_19_clicked(bool)\0"
    "on_minBox5_valueChanged(int)\0"
    "on_maxBox5_valueChanged(int)\0mode\0"
    "on_tabMode_currentChanged(int)\0"
    "on_btnReset_clicked()\0on_btnHistogram_clicked()\0"
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Widget *_t = static_cast<Widget *>(_o);
        switch (_id) {
        case 0: _t->on_btnOpen_clicked(); break;
        case 1: _t->on_btnGenerate_clicked(); break;
        case 2: _t->on_extractVOI_clicked(); break;
        case 3: _t->on_checkAxial_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_checkCoronal_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_checkSagittal_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_checkPickPtsOnSlice_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_checkBox_1_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_checkBox_2_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_checkBox_3_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_checkBox_4_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_checkBox_5_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_checkBox_6_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_checkBox_7_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->on_checkBox_8_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->on_checkBox_9_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->on_checkBox_10_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->on_checkBox_11_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->on_checkBox_12_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->on_checkBox_13_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->on_checkBox_14_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->on_checkBox_15_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->on_minBox1_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->on_maxBox1_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->on_checkBox_16_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->on_minBox2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->on_maxBox2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->on_checkBox_17_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->on_minBox3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->on_maxBox3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->on_checkBox_18_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: _t->on_minBox4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->on_maxBox4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->on_checkBox_19_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->on_minBox5_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->on_maxBox5_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->on_tabMode_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->on_btnReset_clicked(); break;
        case 38: _t->on_btnHistogram_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Widget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget,
      qt_meta_data_Widget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Widget))
        return static_cast<void*>(const_cast< Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
