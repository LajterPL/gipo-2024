QT += gui opengl widgets
CONFIG += debug c++11


equals(QT_MAJOR_VERSION, 6) {
    QT += openglwidgets
}

SOURCES += \
    geometry.cpp \
    main.cpp \
    glwidget.cpp \
    glslprogram.cpp \
    primitives.cpp \
    texture2d.cpp

HEADERS += \
    camera.h \
    frame.h \
    geometry.h \
    glwidget.h \
    glslprogram.h \
    primitives.h \
    texture2d.h \
    utils.h

unix {
    LIBS += -lGLU
}

win32 {
    LIBS += -lglu32 -lopengl32
}

DISTFILES += \
    shaders/shader.frag \
    shaders/shader.vert \
    shaders/uv_plane.frag \
    shaders/uv_plane.vert
