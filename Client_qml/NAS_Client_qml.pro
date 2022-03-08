QT += quick network core
CONFIG += c++17

SOURCES += \
        main.cpp \
        source/FileFormat.cpp \
        source/c_network.cpp \
    source/mylistdata.cpp \
    source/mylistmodel.cpp

resources.files = \
main.qml \
qml/MyListView.qml \
qml/MyListViewForm.ui.qml \
qml/MyMenuBar.qml \
qml/MyMenuBarForm.ui.qml \
qml/NewUser.qml \
qml/NewUserForm.ui.qml \

resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    source/FileFormat.h \
    source/c_network.h \
    source/mylistdata.h \
    source/mylistmodel.h
