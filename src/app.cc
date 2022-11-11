#include "app.h"

namespace example
{
    std::shared_ptr<group> create_random_scene()
    {
        std::shared_ptr<group> scene = std::make_shared<group>();

        std::shared_ptr<lambertian> diffusegrey = std::make_shared<lambertian>(glm::vec3(0.5, 0.5, 0.5));
        std::shared_ptr<lambertian> diffusered = std::make_shared<lambertian>(glm::vec3(0.7, 0.3, 0.3));
        std::shared_ptr<dielectric> glass = std::make_shared<dielectric>(1.5);
        std::shared_ptr<metal> metalgrey = std::make_shared<metal>(glm::vec3(0.5, 0.5, 0.5), 0.2f);
        for (int a = -11; a < 11; a++)
        {
            for (int b = -11; b < 11; b++)
            {
                auto choose_mat = random_float();
                glm::vec3 center(a + 0.9 * random_float(), 0.2, b + 0.9 * random_float());

                if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9)
                {
                    std::shared_ptr<material> sphere_material;

                    if (choose_mat < 0.8)
                    {
                        // diffuse
                        auto albedo = glm::linearRand(glm::vec3(0.0f), glm::vec3(1.0f)) * glm::linearRand(glm::vec3(0.0f), glm::vec3(1.0f));
                        sphere_material = std::make_shared<lambertian>(albedo);
                        scene->add_object(std::make_shared<sphere>(center, 0.2, sphere_material));
                    }
                    else if (choose_mat < 0.95)
                    {
                        // metal
                        auto albedo = glm::linearRand(glm::vec3(0.5f), glm::vec3(1.0f));
                        auto fuzz = random_float(0, 0.5);
                        sphere_material = std::make_shared<metal>(albedo, fuzz);
                        scene->add_object(std::make_shared<sphere>(center, 0.2, sphere_material));
                    }
                    else
                    {
                        // glass
                        sphere_material = std::make_shared<dielectric>(1.5);
                        scene->add_object(std::make_shared<sphere>(center, 0.2, sphere_material));
                    }
                }
            }
        }

        scene->add_object(std::make_shared<sphere>(sphere{glm::vec3(-4.0f, 1.0f, 0.0f), 1.0f, diffusered}));
        scene->add_object(std::make_shared<sphere>(sphere{glm::vec3(4.0f, 1.0, 0.0f), 1.0f, metalgrey}));
        scene->add_object(std::make_shared<sphere>(sphere{glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, glass}));

        scene->add_object(std::make_shared<sphere>(sphere{glm::vec3{0.0, -1000.0f, 0.0f}, 1000.0f, diffusegrey}));

        return scene;
    }
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
    m_active_scene = example::create_random_scene();
    glm::vec3 lookfrom = glm::vec3{13.0f, 2.0f, 3.0f};
    glm::vec3 lookat = glm::vec3{0.0f, 0.0f, 0.0f};
    camera cam(lookfrom, lookat, glm::vec3{0, 1, 0}, 20, 1254 / 1061, 0.1f, 10.0f);
    m_renderer = std::make_unique<renderer>(cam, 1254, 1061);

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

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Viewport");

    m_viewport_width = ImGui::GetContentRegionAvail().x;
    m_viewport_height = ImGui::GetContentRegionAvail().y;

    util::timer time_clock;

    ImGui::Image((void *)(intptr_t)m_render_target_id, ImVec2(m_viewport_width, m_viewport_height));
    //               ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
    ImGui::PopStyleVar();

    ImGui::Begin("Settings");
    ImGui::Text("Last render: %.3fms", m_lastrender_time);
    if (ImGui::Button("Render"))
    {

        time_clock.start();
        m_renderer->on_resize(m_viewport_width, m_viewport_height);
        m_renderer->render(m_active_scene);
        time_clock.stop();
        m_lastrender_time = time_clock.elapsedMilliseconds();

        glBindTexture(GL_TEXTURE_2D, m_render_target_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_viewport_width, m_viewport_height, 0, GL_RGB, GL_FLOAT, m_renderer->get_image_data());
        glBindTexture(GL_TEXTURE_2D, 0);
        // Render();
    }
    ImGui::End();

    ImGui::Begin("Scene");

    ImGui::End();
}