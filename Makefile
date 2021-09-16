TARGET := iphone:clang:14.3:7.0
ARCHS = arm64 arm64e
include $(THEOS)/makefiles/common.mk

TOOL_NAME = mount_bindfs listvfs testchroot

#mount_bindfs_FILES = mount_update.c getmntopts.c
mount_bindfs_FILES = mount_bindfs.c getmntopts.c
mount_bindfs_CFLAGS = -fobjc-arc
mount_bindfs_CODESIGN_FLAGS = -Sentitlements.plist
mount_bindfs_INSTALL_PATH = /usr/local/bin

listvfs_FILES = listvfs.c
listvfs_CFLAGS = -fobjc-arc -Ilibkrw/include
listvfs_LDFLAGS = -Llibkrw -lkrw
listvfs_CODESIGN_FLAGS = -Sentitlements.plist
listvfs_INSTALL_PATH = /usr/local/bin

testchroot_FILES = test.c
#testchroot_LDFLAGS = -static
listvfs_CODESIGN_FLAGS = -Sentitlements.plist
listvfs_INSTALL_PATH = /usr/local/bin

include $(THEOS_MAKE_PATH)/tool.mk
