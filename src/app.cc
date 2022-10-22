#include "app.h"

std::vector<std::shared_ptr<hittable>> create_random_scene()
{
    std::vector<std::shared_ptr<hittable>>
        objects;

    std::shared_ptr<lambertian> diffusered = std::make_shared<lambertian>(glm::vec3(0.7, 0.3, 0.3));
    std::shared_ptr<lambertian> diffusewhite = std::make_shared<lambertian>(glm::vec3(0.8, 0.8, 0.8));
    std::shared_ptr<metal> metalgreen = std::make_shared<metal>(glm::vec3(0.0, 0.8, 0.0), 1.0f);
    std::shared_ptr<metal> metalgrey = std::make_shared<metal>(glm::vec3(0.5, 0.5, 0.5), 0.2f);

    objects.push_back(std::make_shared<sphere>(sphere{glm::vec3(0.0, 0.0, -1.0f), 0.5f, diffusered}));
    objects.push_back(std::make_shared<sphere>(sphere{glm::vec3(1.0f, 0.0, -1.0f), 0.4f, metalgrey}));
    objects.push_back(std::make_shared<sphere>(sphere{glm::vec3(-1.0f, 0.0, -1.0f), 0.4f, metalgreen}));
    //   objects.push_back(sphere{vec3(-1.0f, 1.0, -1.7f), 0.3f});
    objects.push_back(std::make_shared<plane>(plane{glm::vec3{0.0, -0.5f, -0.0f}, glm::vec3{0.0, 1.0, 0.0}, diffusewhite}));

    return objects;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void app::run()
{
    // start the raytracer
    std::vector<std::shared_ptr<hittable>> objects = create_random_scene();
    camera cam(glm::vec3{0.0f}, glm::vec3{0.0f}, 130, 1254 / 1061);
    m_renderer = std::make_unique<renderer>(cam, objects, 1254);

    while (!glfwWindowShouldClose(m_window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // actual draw calls & imgui begin
        update();

        ImGui::Render();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void app::update()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    ImGui::ShowDemoWindow();
    ImGui::Begin("Settings");
    ImGui::Text("Last render: %.3fms", m_lastrender_time);
    if (ImGui::Button("Render"))
    {
        timer time_clock;
        time_clock.start();
        m_renderer->render();
        time_clock.stop();
        m_lastrender_time = time_clock.elapsedMilliseconds();

        glBindTexture(GL_TEXTURE_2D, m_render_target_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1254, 1061, 0, GL_RGB, GL_FLOAT, m_renderer->get_image_data());
        glBindTexture(GL_TEXTURE_2D, 0);
        // Render();
    }
    ImGui::End();

    ImGui::Begin("Scene");
    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Viewport");

    int image_width = ImGui::GetContentRegionAvail().x;
    int image_height = ImGui::GetContentRegionAvail().y;
    // auto image = m_Renderer.GetFinalImage();
    // if (image)
    timer time_clock;

    ImGui::Image((void *)(intptr_t)m_render_target_id, ImVec2(image_width, image_height));
    //               ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
    ImGui::PopStyleVar();
    // called every frame
}