#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T13:02:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CardGame
TEMPLATE = app


SOURCES += main.cpp\
        gameboard.cpp \
    card.cpp \
    pile.cpp \
    rule.cpp \
    game.cpp \
    cardmove.cpp \
    freecell.cpp \
    winningdialog.cpp \
    klondike.cpp \
    aboutdialog.cpp \
    ruleswindow.cpp \
    spider.cpp


win32:RC_ICONS += appicon.ico

HEADERS  += gameboard.h \
    card.h \
    pile.h \
    rule.h \
    game.h \
    cardmove.h \
    freecell.h \
    winningdialog.h \
    klondike.h \
    aboutdialog.h \
    ruleswindow.h \
    spider.h

FORMS    += gameboard.ui \
    winningdialog.ui \
    aboutdialog.ui \
    ruleswindow.ui

RESOURCES += \
    cardimgs.qrc
