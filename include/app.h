#ifndef APP_H
#define APP_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include <glad/glad.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "core/camera.h"
#include "core/renderer.h"
#include "objects/sphere.h"
#include "objects/plane.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "material/dielectric.h"
#include "util/timer.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

class app
{
public:
    app() = default;
    app(const std::string &window_name, int window_width, int window_height)
    {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // glfw window creation
        // --------------------
        m_window = glfwCreateWindow(window_width, window_height, window_name.c_str(), NULL, NULL);
        if (m_window == NULL)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            std::exit(1);
        }
        glfwMakeContextCurrent(m_window);
        glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            std::exit(1);
        }

        // imgui setup
        bool show_demo_window = true;
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        // set up image render targets (textures)
        glGenTextures(1, &m_render_target_id);
        glBindTexture(GL_TEXTURE_2D, m_render_target_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    ~app()
    {

        glBindTexture(GL_TEXTURE_2D, 0);
        glDeleteTextures(1, &m_render_target_id);

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void run();
    void update();

private:
    GLFWwindow *m_window;
    GLuint m_render_target_id;
    bool m_toolbox_menu_active;
    bool m_viewport_menu_active;
    double m_lastrender_time;
    std::unique_ptr<renderer> m_renderer;
};

#endif
