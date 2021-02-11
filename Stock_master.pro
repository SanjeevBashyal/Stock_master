QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog_table.cpp \
    dialog_text.cpp \
    fa_db.cpp \
    main.cpp \
    mainwindow.cpp \
    html.cpp \
    nepse.cpp \
    nepse_calc.cpp \
    request.cpp \
    special_table_parser.cpp \
    sqlite_database.cpp \
    super_special_table_parser.cpp \
    table_parser.cpp

HEADERS += \
    dialog_table.h \
    dialog_text.h \
    mainwindow.h \
    html.h \
    nepse.h \
    nepse_calc.h \
    request.h \
    special_table_parser.h \
    sqlite_database.h \
    super_special_table_parser.h \
    table_parser.h

FORMS += \
    dialog_table.ui \
    dialog_text.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    others.qrc
