-- RuiEngine Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/RuiEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/RuiEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/RuiEngine/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/RuiEngine/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/RuiEngine/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/RuiEngine/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/RuiEngine/vendor/yaml-cpp/include"
IncludeDir["Box2D"] = "%{wks.location}/RuiEngine/vendor/Box2D/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/RuiEngine/vendor/ImGuizmo"
IncludeDir["shaderc"] = "%{wks.location}/RuiEngine/vendor/shaderc"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/RuiEngine/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
-- Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"



