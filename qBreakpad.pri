message("BREAKPAD_crash_handler_attached")

INCLUDEPATH += $$PWD/handler/

HEADERS += \
    $$PWD/handler/QBreakpadHandler.h \
    $$PWD/handler/QBreakpadHttpUploader.h

#debug {
#LIBS += \
#    -L$$PWD/handler-build-debug/debug -lqBreakpad
#}

#release {
LIBS += \
    -L$$PWD/handler-build-release/release -lqBreakpad
#}
