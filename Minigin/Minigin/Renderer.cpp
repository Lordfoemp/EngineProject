#include "MiniginPCH.h"
#include "Renderer.h"
//#include <SDL.h>
#include "SceneManager.h"
//#include "Texture2D.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"


int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}


Helheim::Renderer::Renderer()
	    : m_ShowDemoWindow(false)
	    , m_ShowControlWindow(true)
	    , m_pWindow(nullptr)
	    , m_pRenderer(nullptr)
{}

Helheim::Renderer::~Renderer()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_pRenderer != nullptr)
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}
}

void Helheim::Renderer::Init(SDL_Window * window)
{
	m_pWindow = window;

	m_pRenderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_pRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	//ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void Helheim::Renderer::Render() const
{
	SDL_RenderClear(m_pRenderer);

	//SceneManager::GetInstance().Render();
	Locator::GetSceneService()->Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();
	
	if (m_ShowDemoWindow)
		ImGui::ShowDemoWindow();
	else
		RenderUI();
	
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_pRenderer);
}

//void Helheim::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
//{
//	SDL_Rect dst;
//	dst.x = static_cast<int>(x);
//	dst.y = static_cast<int>(y);
//	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
//	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
//}
//
//void Helheim::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
//{
//	SDL_Rect dst;
//	dst.x = static_cast<int>(x);
//	dst.y = static_cast<int>(y);
//	dst.w = static_cast<int>(width);
//	dst.h = static_cast<int>(height);
//	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
//}

void Helheim::Renderer::RenderUI() const
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();

	bool windowActive{ m_ShowControlWindow };
	ImGui::SetNextWindowPos(ImVec2(10, 230));
	ImGui::SetNextWindowSize(ImVec2(240, 240));
	ImGui::Begin("Programming 4", &windowActive, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::PushAllowKeyboardFocus(false);

	ImGui::Separator();
	ImGui::Text("CONTROLS");
	ImGui::Separator();
	ImGui::Text("General");
	ImGui::Indent();
	ImGui::Text("START: Change buttons");
	ImGui::Text("BACK: Stop application");
	ImGui::Unindent();
	ImGui::Text("Commands - Player 1");
	ImGui::Indent();
	ImGui::Text("DIE: A");
	ImGui::Text("SCORE: B");
	ImGui::Unindent();
	ImGui::Text("Commands - Player 2=");
	ImGui::Indent();
	ImGui::Text("DIE: X");
	ImGui::Text("SCORE: Y");
	ImGui::Unindent();
	ImGui::Separator();

	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.59f, 0.52f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.60f, 0.56f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.61f, 0.60f, 1.f));
	ImGui::Button("Single Player");

	ImGui::SameLine();
	ImGui::Button("Co-Op");

	ImGui::SameLine();
	ImGui::Button("Versus");
	ImGui::PopStyleColor(3);

	ImGui::PopAllowKeyboardFocus();
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}