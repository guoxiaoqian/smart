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
        E:/smart/src/base/3dparty/tinyxml2/lib/tinyxml2.lib \
        E:/smart/src/base/3dparty/hilbert/lib/hilbert.lib \

SOURCES += main.cpp \
    base/thread/thread.cpp \
    base/setting/setting.cpp \
    base/logger/logger.cpp \
    base/kernel/sig_slot_test.cpp \
    base/thread/timer.cpp \
    core/center/Smart.cpp \
    core/center/Config.cpp \
    core/request/UpdateRequest.cpp \
    core/request/Request.cpp \
    core/request/RangeQueryRequest.cpp \
    core/request/KNNQueryRequest.cpp \
    core/thread/WorkThread.cpp \
    core/thread/UpdateThread.cpp \
    core/thread/ThreadPool.cpp \
    core/thread/RangeQueryThread.cpp \
    core/thread/KNNQueryThread.cpp \
    core/thread/AssignThread.cpp \
    core/index/OnlineTuning.cpp \
    core/index/KeyGen.cpp \
    core/index/Histogram.cpp \
    core/store/Rect.cpp \
    core/store/Point.cpp \
    core/store/MoveObject.cpp \
    core/store/Grid.cpp \
    core/store/Cell.cpp \
    core/request/RequestSource.cpp \
    core/thread/HandleThread.cpp \
    core/thread/PeriodTimer.cpp \
    core/index/ST2BTree/ST2BTree.cpp \
    core/index/ST2BTree/BPlus_tree.cpp \
    core/index/ST2BTree/BPlus_node.cpp \
    core/index/Index.cpp \
    core/index/DynamicIndex.cpp \
    core/index/StaticIndex.cpp \
    core/index/SpacePartition/VoronoiDiagram.cpp \
    core/index/SpacePartition/ReferenceTable.cpp \
    core/index/SpacePartition/ReferencePoint.cpp \
    core/index/SpacePartition/DelaunayTriangle.cpp



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
    base/kernel/sig_slot.hpp \
    base/kernel/global.h \
    base/kernel/env.h \
    base/thread/timer.h \
    core/center/type.h \
    core/center/Smart.h \
    core/center/Config.h \
    core/request/UpdateRequest.h \
    core/request/RequestQueue.h \
    core/request/Request.h \
    core/request/RangeQueryRequest.h \
    core/request/KNNQueryRequest.h \
    core/thread/WorkThread.h \
    core/thread/UpdateThread.h \
    core/thread/ThreadPool.h \
    core/thread/RangeQueryThread.h \
    core/thread/KNNQueryThread.h \
    core/thread/AssignThread.h \
    core/index/OnlineTuning.h \
    core/index/KeyGen.h \
    core/index/Histogram.h \
    core/store/Rect.h \
    core/store/Point.h \
    core/store/MoveObject.h \
    core/store/Grid.h \
    core/store/Cell.h \
    core/request/RequestSource.h \
    core/thread/HandleThread.h \
    core/thread/PeriodTimer.h \
    base/kernel/singleton.hpp \
    base/thread/semaph.h \
    base/tool/rand.h \
    core/index/ST2BTree/ST2BTree.h \
    core/index/ST2BTree/BPlus_tree.h \
    core/index/ST2BTree/BPlus_node.h \
    core/index/Index.h \
    core/index/DynamicIndex.h \
    core/index/StaticIndex.h \
    core/index/SpacePartition/VoronoiDiagram.h \
    core/index/SpacePartition/ReferenceTable.h \
    core/index/SpacePartition/ReferencePoint.h \
    core/index/SpacePartition/DelaunayTriangle.h



win32:INCLUDEPATH += "E:/smart/src/base/3dparty/libevent2/include" \
                     "E:/smart/src/base/3dparty/pthread_win/include" \
                     "E:/smart/src/base/3dparty/tinyxml2/include" \
                     "E:/smart/src/base/3dparty/hilbert/include" \

OTHER_FILES +=


