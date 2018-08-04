#include <glitter/vulkan/vulkan-helpers.h>
#include <glitter/api-data-inl.h>

#include <vulkan/vulkan.h>

#include <array>
#include <cassert>
#include <memory>
#include <utility>
#include <cstdint>
#include <cstdio>

namespace {
bool ValidationLayerFound(std::uint32_t const      checkCount,
                          char const* const* const check_names,
                          std::uint32_t const      layer_count,
                          VkLayerProperties*       layers) {

    for (std::uint32_t i = 0; i < checkCount; i++) {
        bool found = false;

        for (std::uint32_t j = 0; j < layer_count; j++) {
            if (!std::strcmp(check_names[i], layers[j].layerName)) {
                found = true;
                break;
            }
        }
        if (!found) { return false; }
    }

    return true;
}

char const* const instanceValidationLayersAlt1[] = {"VK_LAYER_LUNARG_standard_validation"};
const int         layersAlt1Count =
  sizeof(instanceValidationLayersAlt1) / sizeof(instanceValidationLayersAlt1[0]);

char const* const instanceValidationLayersAlt2[] = {"VK_LAYER_GOOGLE_threading",
                                                    "VK_LAYER_LUNARG_parameter_validation",
                                                    "VK_LAYER_LUNARG_object_tracker",
                                                    "VK_LAYER_LUNARG_core_validation",
                                                    "VK_LAYER_GOOGLE_unique_objects"};
const int         layersAlt2Count =
  sizeof(instanceValidationLayersAlt2) / sizeof(instanceValidationLayersAlt2[0]);

std::tuple<std::uint32_t, char const* const*, std::uint32_t>
  EnableDebugLayer(int const instanceLayerCount, VkLayerProperties* vkLayerProps) {

    std::uint32_t      validationLayerCount     = 0;
    char const* const* instanceValidationlayers = nullptr;
    std::uint32_t      enabledLayerCount        = 0;

    instanceValidationlayers = instanceValidationLayersAlt1;

    bool validationFound = false;

    if (instanceLayerCount > 0) {

        validationFound = ValidationLayerFound(
          layersAlt1Count, instanceValidationlayers, instanceLayerCount, vkLayerProps);

        if (validationFound) {
            enabledLayerCount = layersAlt1Count;
            // enabled_layers[0]      = "VK_LAYER_LUNARG_standard_validation";
            validationLayerCount = layersAlt1Count;

        } else {
            instanceValidationlayers = instanceValidationLayersAlt2;
            enabledLayerCount        = layersAlt2Count;

            validationFound = validationFound = ValidationLayerFound(
              layersAlt1Count, instanceValidationlayers, instanceLayerCount, vkLayerProps);

            validationLayerCount = layersAlt2Count;

            // for (uint32_t i = 0; i < validationLayerCount; i++) {
            //    enabled_layers[i] = instanceValidationlayers[i];
            //}
        }
    }

    return {validationLayerCount, instanceValidationlayers, enabledLayerCount};
}

bool HasExtensionName(VkExtensionProperties* extensions,
                      std::uint32_t          instanceExtensionCount,
                      char const*            extension_names) {
    for (uint32_t i = 0; i < instanceExtensionCount; i++) {
        if (!std::strcmp(extension_names, extensions[i].extensionName)) { return true; }
    }

    return false;
}

VkApplicationInfo CreateApplicationInfo() {
    VkApplicationInfo appInfo  = {};
    appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName   = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName        = "No Engine";
    appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion         = VK_API_VERSION_1_0;

    return appInfo;
}

VkInstanceCreateInfo CreateInstanceInfo(VkApplicationInfo const& appInfo,
                                        std::uint32_t const      extensionCount,
                                        char const* const*       enabledExtensionNames,
                                        std::uint32_t const      enabledLayersCount,
                                        char const* const*       enabledLayerNames) {

    VkInstanceCreateInfo createInfo    = {};
    createInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo        = &appInfo;
    createInfo.enabledExtensionCount   = extensionCount;
    createInfo.ppEnabledExtensionNames = enabledExtensionNames;
    createInfo.enabledLayerCount       = enabledLayersCount;
    createInfo.ppEnabledLayerNames     = enabledLayerNames;

    return createInfo;
}

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(VkDebugReportFlagsEXT flags,
                                                   VkDebugReportObjectTypeEXT,
                                                   std::uint64_t,
                                                   std::size_t,
                                                   std::int32_t,
                                                   char const* layerPrefix,
                                                   char const* msg,
                                                   void*) {

    std::fprintf(stderr, "VkVL: %s-%d %s", layerPrefix, flags, msg);

    return VK_FALSE;
}

bool SetupDebugCallback(const VkInstance& instance, VkDebugReportCallbackEXT& callback) {
    VkDebugReportCallbackCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT |
                       VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
    createInfo.pfnCallback = VulkanDebugCallback;

    auto const func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(
      instance, "vkCreateDebugReportCallbackEXT");

    if (func == nullptr) return false;

    auto const allocatorPointer = nullptr;
    auto const result           = func(instance, &createInfo, allocatorPointer, &callback);

    return result == VK_SUCCESS;
}

} // namespace

namespace glitt {
gget::ErrorValue<std::unique_ptr<GraphicsDeviceInterface>>
  Vulkan::Init(bool const enableDebugLayer) {

    auto const appInfo = CreateApplicationInfo();

    std::uint32_t instanceLayerCount = 0;
    {
        auto const result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);
        if (result != VK_SUCCESS) {
            return {
              GADGET_ERMSG("vkEnumerateInstanceLayerProperties failed to populate layer count")};
        }
    }

    auto const instanceLayers = std::make_unique<VkLayerProperties[]>(instanceLayerCount);
    {
        auto const result =
          vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayers.get());

        if (result != VK_SUCCESS)
            return {GADGET_ERMSG(
              "vkEnumerateInstanceLayerProperties failed to populate instance layers")};
    }

    auto const [validationLayerCount, instanceValidationlayers, enabledLayerCount] =
      EnableDebugLayer(instanceLayerCount, instanceLayers.get());
    if (enableDebugLayer) {

        if (validationLayerCount == 0)
            return {GADGET_ERMSG("Failed to initialise debug validation layer")};
    }

    std::uint32_t instanceExtensionCount = 0;
    {
        auto const result =
          vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, nullptr);

        if (result != VK_SUCCESS)
            return {GADGET_ERMSG(
              "vkEnumerateInstanceExtensionProperties failed to populate instance extension "
              "layers")};
    }

    auto const instanceExtensions =
      std::make_unique<VkExtensionProperties[]>(instanceExtensionCount);
    {
        auto const result = vkEnumerateInstanceExtensionProperties(
          nullptr, &instanceExtensionCount, instanceExtensions.get());
        if (result != VK_SUCCESS)
            return {GADGET_ERMSG(
              "vkEnumerateInstanceExtensionProperties failed to populate instance extension "
              "layers")};
    }

    bool const surfaceExtFound = HasExtensionName(
      instanceExtensions.get(), instanceExtensionCount, VK_KHR_SURFACE_EXTENSION_NAME);

    if (!surfaceExtFound)
        return {
          GADGET_ERMSG("Failed to find the surface extension. Possible missing Vulkan driver")};

    bool const platformSurfaceExtFound = HasExtensionName(
      instanceExtensions.get(), instanceExtensionCount, VK_KHR_WIN32_SURFACE_EXTENSION_NAME);

    if (!platformSurfaceExtFound)
        return {GADGET_ERMSG(
          "Failed to find the platform surface extension. Possible missing Vulkan driver")};

    bool const debugExtensionFound = HasExtensionName(
      instanceExtensions.get(), instanceExtensionCount, VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

    if (enableDebugLayer && !debugExtensionFound)
        return {GADGET_ERMSG("Failed to initalize debug extension")};

    char const* extensionNames[64] = {VK_KHR_SURFACE_EXTENSION_NAME,
                                      VK_KHR_WIN32_SURFACE_EXTENSION_NAME};

    if (enableDebugLayer) extensionNames[2] = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;

    // (Debug) + Default extension + platform extension
    auto const extensionCount = enableDebugLayer ? 3U : 2U;

    auto const instanceInfo = CreateInstanceInfo(
      appInfo, extensionCount, extensionNames, enabledLayerCount, instanceValidationlayers);

    auto deviceInterface = std::make_unique<VulkanDeviceInterface>();

    deviceInterface->DebugLayersEnabled = enableDebugLayer;

    if (vkCreateInstance(&instanceInfo, nullptr, &deviceInterface->Instance) == VK_SUCCESS)
        return {GADGET_ERMSG("Failed to create Vulkan Instance")};

    if (enableDebugLayer &&
        !SetupDebugCallback(deviceInterface->Instance, deviceInterface->DebugCallback))
        return {GADGET_ERMSG("Failed to setup debug callback")};

    return {gget::Error::NoError, std::move(deviceInterface)};
}

void Vulkan::Destroy(GraphicsDeviceInterface* deviceInterface) {

    auto const& instance = deviceInterface->Instance;

    if (deviceInterface->DebugLayersEnabled) {
        auto const func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(
          instance, "vkDestroyDebugReportCallbackEXT");

        if (func != nullptr) { func(instance, deviceInterface->DebugCallback, nullptr); }
    }

    vkDestroyInstance(instance, nullptr);
}

} // namespace glitt
