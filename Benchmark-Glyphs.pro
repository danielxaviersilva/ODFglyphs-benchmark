QT       += core gui opengl #openglwidgets widgets
#QT += widgets opengl openglwidgets


CONFIG += c++11 console
#CONFIG += c++17
CONFIG -= app_bundle

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS



SOURCES += \
        Models/ODFSamples.cpp \
        Models/ODFSamplesHemisphere.cpp \
        Models/Visualization/ODFRenderer.cpp \
        Models/Visualization/ODFRendererInstanced.cpp \
        Models/Visualization/ODFRendererInstancedSymmetric.cpp \
        Models/Visualization/ODFRendererInstancedSymmetricCoalescent.cpp \
        Models/Visualization/ODFRendererMultiResolution.cpp \
        Models/Visualization/ODFRendererOnDemand.cpp \
        Utilities/CGUtilities.cpp \
        Utilities/Camera.cpp \
        Utilities/IndexBuffer.cpp \
        Utilities/Shader.cpp \
        Utilities/Texture.cpp \
        Utilities/Timer.cpp \
        Utilities/VertexArray.cpp \
        Utilities/VertexBuffer.cpp \
        main.cpp \
        window.cpp


QMAKE_CXXFLAGS += -Xpreprocessor -fopenmp -I/usr/local/include
#QMAKE_CXXFLAGS += -stdlib=libstdc++
QMAKE_LFLAGS += -lomp

INCLUDEPATH += "Externals/glm/include" \

LIBS += -L /usr/local/lib /usr/local/lib/libomp.dylib

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Models/ODFSamples.h \
    Models/ODFSamplesHemisphere.h \
    Models/Visualization/ODFRenderer.h \
    Models/Visualization/ODFRendererInstanced.h \
    Models/Visualization/ODFRendererInstancedSymmetric.h \
    Models/Visualization/ODFRendererInstancedSymmetricCoalescent.h \
    Models/Visualization/ODFRendererMultiResolution.h \
    Models/Visualization/ODFRendererOnDemand.h \
    QBallGlyphsCoefficientsSample.h \
    Utilities/CGUtilities.h \
    Utilities/Camera.h \
    Utilities/IndexBuffer.h \
    Utilities/Shader.h \
    Utilities/Texture.h \
    Utilities/Timer.h \
    Utilities/VertexArray.h \
    Utilities/VertexBuffer.h \
    window.h

OTHER_FILES += \

DISTFILES += \
    Models/Visualization/renderODF.frag \
    Models/Visualization/renderODF.vert \
    Models/Visualization/renderODFInstanced.frag \
    Models/Visualization/renderODFInstanced.vert \
    Models/Visualization/renderODFInstancedSymmetrical.frag \
    Models/Visualization/renderODFInstancedSymmetrical.vert \
    Models/Visualization/renderODFInstancedSymmetricalCoalescent.frag \
    Models/Visualization/renderODFInstancedSymmetricalCoalescent.vert

RESOURCES += \
    Shaders.qrc

unix:macx {
    DESTDIR=bin/macos #Target file directory
}
unix:!macx {
    DESTDIR=bin/linux
}
OBJECTS_DIR=generated_files #Intermediate object files directory
MOC_DIR=generated_files #Intermediate moc files directory
unix:QMAKE_RPATHDIR += /Users/daniel_mac/Qt/5.12.3/clang_64/lib

