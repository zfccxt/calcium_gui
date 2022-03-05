#include <calcium.hpp>
#include <clx_imgui.hpp>

int main() {
  cl::ContextCreateInfo context_info;
  context_info.backend = cl::Backend::kVulkan;
  context_info.extensions = { clx::imgui::LoadExtension() };
  auto context = cl::Context::CreateContext(context_info);
  auto window = context->CreateWindow();

  auto shader = context->CreateShader("res/shaders/shader.vert.spv", "res/shaders/shader.frag.spv");

  cl::MeshCreateInfo mesh_info;
  mesh_info.vertex_input_layout = shader->GetInputLayout();
  std::vector<float> vertices = {
  //  x      y     z   
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
  };
  std::vector<uint32_t> indices = {
    0, 1, 2, 
    1, 3, 2, 
  };
  mesh_info.vertices = vertices.data();
  mesh_info.num_vertices = vertices.size();
  mesh_info.indices = indices.data();
  mesh_info.num_indices = indices.size();
  auto mesh = context->CreateMesh(mesh_info);

  while (window->IsOpen()) {
    window->PollEvents();
    
    context->BeginRenderPass();
    shader->Bind();
    mesh->Draw();

    clx::imgui::BeginFrame();
    ImGui::ShowDemoWindow();
    clx::imgui::EndFrame();

    context->EndRenderPass();
  }
}