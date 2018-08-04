#pragma once

#include <vulkan/vulkan.h>

struct VulkanDeviceInterface {
    VkInstance Instance;

    bool                     DebugLayersEnabled;
    VkDebugReportCallbackEXT DebugCallback;

    VkPhysicalDevice PhysicalDevice;
};
