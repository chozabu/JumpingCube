!include("../Common/retroshare_plugin.pri"): error("Could not include file ../Common/retroshare_plugin.pri")

CONFIG += qt uic qrc resources

SOURCES = JumpingCubePlugin.cpp \
    gui/paintwidget.cpp \
    topjcdialog.cpp \
    RSExampleItems.cpp \
    p3ExampleRS.cpp
HEADERS = JumpingCubePlugin.h \
    gui/paintwidget.h \
    topjcdialog.h \
    p3ExampleRS.h \
    RSExampleItems.h
FORMS   = \
    topjcdialog.ui

TARGET = JumpingCube

RESOURCES = JumpingCube_images.qrc lang/JumpingCube_lang.qrc

TRANSLATIONS +=  \
                        lang/JumpingCube_cs.ts \
                        lang/JumpingCube_da.ts \
                        lang/JumpingCube_de.ts \
                        lang/JumpingCube_el.ts \
                        lang/JumpingCube_en.ts \
                        lang/JumpingCube_es.ts \
                        lang/JumpingCube_fi.ts \
                        lang/JumpingCube_fr.ts \
                        lang/JumpingCube_hu.ts \
                        lang/JumpingCube_it.ts \
                        lang/JumpingCube_ja_JP.ts \
                        lang/JumpingCube_ko.ts \
                        lang/JumpingCube_nl.ts \
                        lang/JumpingCube_pl.ts \
                        lang/JumpingCube_ru.ts \
                        lang/JumpingCube_sv.ts \
                        lang/JumpingCube_tr.ts \
                        lang/JumpingCube_zh_CN.ts

OTHER_FILES += \
    cptest.sh
