#include <calcium.hpp>
#include <clx_imgui.hpp>
#include <clx_imgui_vulkan.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
  cl::ContextCreateInfo context_info;
  context_info.backend = cl::Backend::kVulkan;
  context_info.extensions = { clx::imgui::LoadExtension() };
  auto context = cl::Context::CreateContext(context_info);

  cl::WindowCreateInfo window_info;
  window_info.enable_vsync;
  auto window = context->CreateWindow(window_info);

  auto shader = context->CreateShader("res/shaders/shader.vert.spv", "res/shaders/shader.frag.spv");

  cl::MeshCreateInfo mesh_info;
  mesh_info.vertex_input_layout = shader->GetInputLayout();
  mesh_info.vertices = {
  //  x      y     z   
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
  };
  mesh_info.indices = {
    0, 1, 2, 
    1, 3, 2, 
  };
  auto mesh = context->CreateMesh(mesh_info);

  glm::vec4 colour(0,0,0,1);

  while (window->IsOpen()) {
    window->PollEvents();
    
    context->BeginFrame();
      window->SetClearColour({colour.r, colour.g, colour.b, colour.a});

        shader->Bind();
        mesh->Draw();

      clx::imgui::Begin();

        ImGui::Begin("background colour picker");
          ImGui::ColorEdit4("BG Col", glm::value_ptr(colour));
          ImGui::Text("hello");
          ImGui::Button("button");
        ImGui::End();

        ImGui::ShowDemoWindow();

      clx::imgui::End();

    context->EndFrame();

  }
}
