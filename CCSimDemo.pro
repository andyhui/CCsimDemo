HEADERS += \
    mainwindow.h \
    node_item.h \
    bullet_item.h \
    sim_scene.h    \
    titlebar/frame.h \
    titlebar/titlebar.h

SOURCES += \
    node_item.cpp \
    bullet_item.cpp \
    sim_scene.cpp \
    main.cpp \
    BEcharToDouble.cpp \
    getSendMsg.cpp \
    IpToChar.cpp \
    parseRecvMsg.cpp \
    recieveMsg.cpp \
    sendMsg.cpp \
    mainwindow.cpp  \
    titlebar/frame.cpp \
    titlebar/titlebar.cpp

QT += \
    network

OTHER_FILES += \
    qss/candy.qss

RESOURCES += \
    CCSimDemo.qrc
