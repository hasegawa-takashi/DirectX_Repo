LOCAL_PATH := $(call my-dir)
CRI_DIR := $(LOCAL_PATH)/../../../../../../../../cri/

include $(CLEAR_VARS)
LOCAL_MODULE := cri_ware_cocos2dx
LOCAL_SRC_FILES := ../../../../../../../../cri/cocos2dx/libs/android/$(TARGET_ARCH_ABI)/libcri_ware_android_le.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/AtomUtil.cpp \
				   ../../Classes/Scenes/AtomBasicScene.cpp \
				   ../../Classes/Scenes/AtomAisacScene.cpp \
				   ../../Classes/Scenes/MenuScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(CRI_DIR)cocos2dx/include/android
                    
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

LOCAL_LDLIBS += \
        -llog \
        -lOpenSLES \

LOCAL_SHARED_LIBRARIES := libcri_ware_cocos2dx

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
$(call import-module,editor-support/cocostudio)
# $(call import-module,network)
$(call import-module,extensions)
