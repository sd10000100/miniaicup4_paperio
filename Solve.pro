TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        gamestate.cpp \
        graphcell.cpp \
        main.cpp \
        GameWorld.cpp \
        bonus.cpp \
        player.cpp \
        solve.cpp

HEADERS += \
    bonus.h \
    gamestate.h \
    gameworld.h \
    helper.h \
    player.h
