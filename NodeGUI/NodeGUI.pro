#-------------------------------------------------
#
# Project created by QtCreator 2019-05-31T17:16:02
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NodeGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# this should not change, it is shipped with the project
THIRD_PARTY_DIR = ../third_party

# OPENCV settings <- may change depending on your system
OPENCV_INCLUDE_DIR = "/usr/local/include/opencv4"
OPENCV_LIB_DIR = "/usr/local/lib/"
VIDEOCODEC = "/usr/lib/x86_64-linux-gnu"

# NVIDIA CODEC SDK settings <- may change depeding on your system
NV_CODEC_DIR = "/home/mfigueroa/Documents/NVidia Codec SDK/Video_Codec_SDK_9.0.20"

# CUDA settings <- may change depending on your system
CUDA_INSTALL_DIR = "/usr/local/cuda-10.1"
SYSTEM_NAME = x86-64         # Depending on your system either 'Win32', 'x64', or 'Win64'
SYSTEM_TYPE = 64            # '32' or '64', depending on your system
CUDA_ARCH = sm_50           # Type of CUDA architecture, for example 'compute_10', 'compute_11', 'sm_10'
NVCC_OPTIONS = --use_fast_math

THIRD_PARTY_CUDA_KERNELS += \
                         $$THIRD_PARTY_DIR/Utils/ColorSpace.cu \
                         $$THIRD_PARTY_DIR/Utils/BitDepth.cu \
                         $$THIRD_PARTY_DIR/Utils/Resize.cu

CONFIG += c++17

SOURCES += \
        UDPReceiver.cpp \
        main.cpp \
        mainwindow.cpp \
        node.cpp\
        $$THIRD_PARTY_DIR/NvDecoder.cpp

HEADERS += \
        UDPReceiver.h \
        mainwindow.h \
        node.h \
        $$THIRD_PARTY_DIR/NvDecoder.h \

FORMS += \
        mainwindow.ui \
        node.ui

# include paths
CUDA_INCLUDE_PATH += $$CUDA_INSTALL_DIR/include \
                     $$THIRD_PARTY_DIR/NvDecoder \
                     $$THIRD_PARTY_DIR/Utils

INCLUDEPATH += $$NV_CODEC_DIR/include \
               $$CUDA_INCLUDE_PATH \
               $$OPENCV_INCLUDE_DIR \
               $$THIRD_PARTY_DIR

# library directories
QMAKE_LIBDIR += $$CUDA_INSTALL_DIR/lib64 \
                $$OPENCV_LIB_DIR \
                $$VIDEOCODEC


# The following makes sure all path names (which often include spaces) are put between quotation marks
CUDA_INC += $$join(CUDA_INCLUDE_PATH,'" -I"','-I"','"')

# Add the necessary libraries
LIBS += -lcuda \
        -lcudart \
        -lnvcuvid \
        -lopencv_highgui \
        -lopencv_core\
        -lopencv_imgproc \
        -lopencv_video \
        -lopencv_videoio \
        -lopencv_imgcodecs

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

# Configuration of the Cuda compiler
CONFIG(debug, debug|release) {
    # Debug mode
    cuda_d.input = THIRD_PARTY_CUDA_KERNELS
    cuda_d.output = ${QMAKE_FILE_BASE}_cuda.o
    cuda_d.commands = $$CUDA_INSTALL_DIR/bin/nvcc -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC $$LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda_d.dependency_type = TYPE_C
    QMAKE_EXTRA_COMPILERS += cuda_d
}
else {
    # Release mode
    cuda.input = THIRD_PARTY_CUDA_KERNELS
    cuda.output = ${QMAKE_FILE_BASE}_cuda.o
    cuda.commands = $$CUDA_INSTALL_DIR/bin/nvcc $$NVCC_OPTIONS $$CUDA_INC $$LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda.dependency_type = TYPE_C
    QMAKE_EXTRA_COMPILERS += cuda
}
