/*
 * Vulkan Program
 *
 * Copyright (C) 2016 Valve Corporation
 * Copyright (C) 2016 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
Vulkan C++ Project Template
Create and destroy a simple Vulkan instance.
*/

#include <vulkan/vulkan.hpp>

#include <iostream>
#include <stdio.h>
#include <vector>
#include <GLFW/glfw3.h>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;
GLFWwindow* window;
class VtsFps {
public:
    
void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    VkInstance instance;
    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

    }
    void createinst() {
        // Use validation layers if this is a debug build
        std::vector<const char*> layers;
#if defined(_DEBUG)
        layers.push_back("VK_LAYER_KHRONOS_validation");
#endif

        // VkApplicationInfo allows the programmer to specifiy some basic information about the
        // program, which can be useful for layers and tools to provide more debug information.
        vk::ApplicationInfo appInfo = vk::ApplicationInfo()
            .setPApplicationName("Scratch of FPS in Vulkan")
            .setApplicationVersion(1)
            .setPEngineName("LunarG SDK")
            .setEngineVersion(1)
            .setApiVersion(VK_API_VERSION_1_0);

        // VkInstanceCreateInfo is where the programmer specifies the layers and/or extensions that
        // are needed. For now, none are enabled.
        vk::InstanceCreateInfo instInfo = vk::InstanceCreateInfo()
            .setFlags(vk::InstanceCreateFlags())
            .setPApplicationInfo(&appInfo)
            .setEnabledExtensionCount(0)
            .setPpEnabledExtensionNames(NULL)
            .setEnabledLayerCount(static_cast<uint32_t>(layers.size()))
            .setPpEnabledLayerNames(layers.data());

        // Create the Vulkan instance.
        vk::Instance instance;
        try {
            instance = vk::createInstance(instInfo);
        }
        catch (std::exception e) {
            std::cout << "Could not create a Vulkan instance: " << e.what() << std::endl;
        }
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }

    }
    void initVulkan() {
        createinst();
    }

    void cleanup() {
    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window);

    glfwTerminate();
    }
};

int main()
{
    VtsFps app;

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
