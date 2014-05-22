LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                   ../../Classes/AppDelegate.cpp \
#                   ../../Classes/HelloWorldScene.cpp
#
#LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# ����Ŀ¼����Ŀ¼�ĺ���
define walk
    $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef
 
# ����ClassesĿ¼
ALLFILES = $(call walk, $(LOCAL_PATH)/../../Classes)
 
FILE_LIST := hellocpp/main.cpp
# �������ļ�����ȡ������.cpp�ļ�
FILE_LIST += $(filter %.cpp, $(ALLFILES))
 
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
#FILE_INCLUDES := $(shell find $(LOCAL_PATH)/../../Classes -type d)
#LOCAL_C_INCLUDES := $(FILE_INCLUDES)

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
