TARGET := iphone:clang:latest:14.0
ARCHS := arm64 arm64e

DEBUG = 0
FINALPACKAGE = 1
FOR_RELEASE = 1

include $(THEOS)/makefiles/common.mk

TWEAK_NAME = ReimanPrimeiOS

ReimanPrimeiOS_FILES = MenuMetalOverlay.mm \
                       imgui/imgui.cpp \
                       imgui/imgui_draw.cpp \
                       imgui/imgui_widgets.cpp \
                       imgui/imgui_tables.cpp \
                       imgui/backends/imgui_impl_metal.mm

ReimanPrimeiOS_FRAMEWORKS = UIKit Foundation Metal MetalKit QuartzCore
ReimanPrimeiOS_CFLAGS = -fobjc-arc -Iimgui -Iimgui/backends -Wall -Wno-unused-variable -Wno-unused-function
ReimanPrimeiOS_CCFLAGS = -std=c++17 -stdlib=libc++

include $(THEOS_MAKE_PATH)/tweak.mk

after-install::
	install.exec "killall -9 SpringBoard"
