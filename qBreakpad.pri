message("BREAKPAD_crash_handler_attached")

INCLUDEPATH += $$PWD/handler/

HEADERS += \
    $$PWD/handler/QBreakpadHandler.h \
    $$PWD/handler/QBreakpadHttpUploader.h

CONFIG(debug, debug|release) {
LIBS += \
    -L$$PWD/handler-build-debug/debug -lqBreakpad
}

CONFIG(release, debug|release) {
LIBS += \
    -L$$PWD/handler-build-release/release -lqBreakpad
}
