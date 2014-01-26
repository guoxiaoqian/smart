TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# unix:LIBS += -L/usr/local/lib -lmath
# win32:LIBS += c:/mylibs/math.lib
win32:LIBS += \
        E:/smart/src/base/3dparty/pthread_win/lib/x86/pthreadVC2.lib \
        E:/smart/src/base/3dparty/pthread_win/lib/x86/pthreadVCE2.lib \
        E:/smart/src/base/3dparty/pthread_win/lib/x86/pthreadVSE2.lib \
        E:/smart/src/base/3dparty/tinyxml2/lib/tinyxml2.lib

SOURCES += main.cpp \
    base/thread/thread.cpp \
    base/setting/setting.cpp \
    base/logger/logger.cpp \
    base/kernel/sig_slot_test.cpp \
    base/thread/timer.cpp \
    base/thread/thread_timer.cpp

HEADERS += \
    base/thread/thread.h \
    base/thread/waitcond.h \
    base/thread/mutex.h \
    base/thread/time.h \
    base/thread/rwlock.h \
    base/thread/spinlock.h \
    base/kernel/env.h \
    base/kernel/global.h \
    base/logger/logger.h \
    base/setting/setting.h \
    base/thread/semaphore.h \
    base/kernel/sig_slot.hpp \
    base/kernel/global.h \
    base/kernel/env.h \
    base/thread/timer.h \
    base/thread/thread_timer.h

win32:INCLUDEPATH += "E:/smart/src/base/3dparty/libevent2/include" \
                     "E:/smart/src/base/3dparty/pthread_win/include" \
                     "E:/smart/src/base/3dparty/tinyxml2/include"

OTHER_FILES +=


