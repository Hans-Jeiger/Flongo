#include "flopch.h"
#include "ImGuiLayer.h"
#include "Flongo/Application.h"
#include "Flongo/Core.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
//temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Flongo
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::onAttach()
	{
		// setup ImGui context
		IMGUI_CHECKVERSION(); 
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable gamepad controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable gamepad controls
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable gamepad controls
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
		
		ImGui::StyleColorsDark();
		
		//When viewports are enabled we tweak WindowRounding/WindowBG so platform windows can look identical to regular ones
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow().getNativeWindow());

		//Setup platform/renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");	
	}

	void ImGuiLayer::onDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext(); 
	}

	void ImGuiLayer::onImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	//void ImGuiLayer::onUpdate()
	//{

	//	ImGuiIO& io = ImGui::GetIO();
	//	Application& app = Application::get();
	//	io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

	//	float timeNow = (float)glfwGetTime();
	//	io.DeltaTime = time > 0.0f ? (timeNow - time) : (1.0f / 60.0f);
	//	time = timeNow;
	//	
	//	ImGui_ImplOpenGL3_NewFrame();
	//	ImGui::NewFrame();

	//	
	//	static bool show = true;
	//	ImGui::ShowDemoWindow(&show);

	//	ImGui::Render();
	//	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//}

	void ImGuiLayer::begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		io.DisplaySize = ImVec2((float)app.getWindow().getWidth(), (float)app.getWindow().getHeight());

		//rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}
	}
}