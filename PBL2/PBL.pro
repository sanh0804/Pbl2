QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    arrayadmin.cpp \
    arraybed.cpp \
    arraydepartement.cpp \
    arraydoctor.cpp \
    arraypatient.cpp \
    arrayroom.cpp \
    bed.cpp \
    departement.cpp \
    doctor.cpp \
    main.cpp \
    mainwindow.cpp \
    patient.cpp \
    people.cpp \
    room.cpp

HEADERS += \
    admin.h \
    arrayadmin.h \
    arraybed.h \
    arraydepartement.h \
    arraydoctor.h \
    arraypatient.h \
    arrayroom.h \
    bed.h \
    departement.h \
    doctor.h \
    mainwindow.h \
    patient.h \
    people.h \
    room.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
