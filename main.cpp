#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "./include/open_gl_loader.h"
#include "./include/hyper_cube.h"
#include "./include/rubik.h"

// ── Globals ──────────────────────────────────────────────────────────
float diameter = 0.1f;

OpenGlLoader OpenGL(SCR_WIDTH, SCR_HEIGHT);
Point center(0.0f, 0.0f, 0.0f);

enum class AppMode { Menu, Rubik, HyperCube };

static AppMode appMode = AppMode::Menu;
static Rubik* singleCube = nullptr;
static HyperCube* hyperCube = nullptr;
static bool prime = false;       // shift modifier latched per-press
static bool showHelp = true;     // help overlay visibility
static double helpAutoHideAt = 0.0;

void key_callback(GLFWwindow*, int, int, int, int);
void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow*, double, double);

static void drawMainMenu();
static void drawHelpOverlay();
static void drawSolvingBanner();

// ── Helpers ──────────────────────────────────────────────────────────
static bool worldBusy()
{
	if (appMode == AppMode::Rubik    && singleCube) return singleCube->is_busy();
	if (appMode == AppMode::HyperCube && hyperCube)  return hyperCube->is_busy();
	return false;
}

// Translates a single-letter move code into the standard notation used
// in the banner (e.g. 'f' → "F'", 'U' → "U").
static const char* moveLabel(char c)
{
	switch (c)
	{
		case F_MOVEMENT: return "F";  case F_PRIME_MOVEMENT: return "F'";
		case B_MOVEMENT: return "B";  case B_PRIME_MOVEMENT: return "B'";
		case U_MOVEMENT: return "U";  case U_PRIME_MOVEMENT: return "U'";
		case D_MOVEMENT: return "D";  case D_PRIME_MOVEMENT: return "D'";
		case L_MOVEMENT: return "L";  case L_PRIME_MOVEMENT: return "L'";
		case R_MOVEMENT: return "R";  case R_PRIME_MOVEMENT: return "R'";
		default: return "";
	}
}

// Banner text describing what the world is currently doing.
// Returns nullptr when the world is idle.
static const char* worldStatus()
{
	bool scrambling = false, solving = false;
	char move = 0;

	if (appMode == AppMode::Rubik && singleCube)
	{
		if (!singleCube->is_busy()) return nullptr;
		scrambling = singleCube->scrambling;
		solving    = singleCube->solution_entered && !singleCube->scrambling;
		move       = singleCube->current_move;
	}
	else if (appMode == AppMode::HyperCube && hyperCube)
	{
		if (!hyperCube->is_busy()) return nullptr;
		scrambling = hyperCube->scrambling;
		solving    = hyperCube->solving;
		move       = hyperCube->current_move;
	}
	else return nullptr;

	static char buf[64];
	const char* label = moveLabel(move);
	if      (scrambling && *label) std::snprintf(buf, sizeof(buf), "Scrambling - %s",   label);
	else if (scrambling)           std::snprintf(buf, sizeof(buf), "Scrambling...");
	else if (solving && *label)    std::snprintf(buf, sizeof(buf), "Auto-solving - %s", label);
	else if (solving)              std::snprintf(buf, sizeof(buf), "Auto-solving...");
	else if (*label)               std::snprintf(buf, sizeof(buf), "Moving %s",         label);
	else                           std::snprintf(buf, sizeof(buf), "Working...");
	return buf;
}

static void enterMode(AppMode m)
{
	delete singleCube; singleCube = nullptr;
	delete hyperCube;  hyperCube  = nullptr;

	if (m == AppMode::Rubik)
		singleCube = new Rubik(center, diameter);
	else if (m == AppMode::HyperCube)
		hyperCube = new HyperCube(center, diameter);

	// scene_pivot is the cluster centroid; classical_movement() tilts around
	// it so the camera can sit straight on world XY=0.
	delete camera;
	if (m == AppMode::HyperCube)
	{
		scene_pivot = glm::vec3(0.0f, 0.0f, 0.395f);
		// Extra pull-back leaves headroom for the expand-and-reassemble pass.
		camera = new Camera(glm::vec3(0.0f, 0.0f, 3.20f));
	}
	else
	{
		scene_pivot = glm::vec3(0.0f, 0.0f, 0.10f);
		camera = new Camera(glm::vec3(0.0f, 0.0f, 1.40f));
	}

	prime = false;
	showHelp = true;
	firstMouse = true;
	appMode = m;
	glfwSetInputMode(OpenGL.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

static void backToMenu()
{
	delete singleCube; singleCube = nullptr;
	delete hyperCube;  hyperCube  = nullptr;
	appMode = AppMode::Menu;
	glfwSetInputMode(OpenGL.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

static void playMove(char move)
{
	if (worldBusy()) return;
	if (appMode == AppMode::Rubik    && singleCube) singleCube->play_move(move);
	if (appMode == AppMode::HyperCube && hyperCube)  hyperCube->play_move(move);
}

static void scrambleCurrent()
{
	if (worldBusy()) return;
	if (appMode == AppMode::Rubik    && singleCube) singleCube->scramble();
	if (appMode == AppMode::HyperCube && hyperCube)  hyperCube->scramble();
}

static void solveCurrent()
{
	if (worldBusy()) return;
	if (appMode == AppMode::Rubik    && singleCube) singleCube->solve();
	if (appMode == AppMode::HyperCube && hyperCube)  hyperCube->solve_Rubiks();
}

// `--screenshot <path>` and `--screenshot-view <view> <path>` (view =
// hyper|rubik|menu). Used by CI smoke tests and README image capture.
static void write_ppm(const char* path)
{
	int w, h;
	glfwGetFramebufferSize(OpenGL.window, &w, &h);
	std::vector<unsigned char> pixels(w * h * 3);
	glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

	FILE* f = std::fopen(path, "wb");
	if (!f) { std::fprintf(stderr, "screenshot: cannot open %s\n", path); return; }
	std::fprintf(f, "P6\n%d %d\n255\n", w, h);
	for (int y = h - 1; y >= 0; y--)
		std::fwrite(pixels.data() + y * w * 3, 1, w * 3, f);
	std::fclose(f);
	std::fprintf(stderr, "screenshot: wrote %s (%dx%d)\n", path, w, h);
}

static void initImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::GetIO().IniFilename = nullptr;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(OpenGL.window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

static void dump_screenshot(const char* view, const char* path)
{
	initImGui();

	int warmup = 5;
	if (std::strcmp(view, "rubik") == 0)
	{
		enterMode(AppMode::Rubik);
		singleCube->scramble();
		warmup = 240;
	}
	else if (std::strcmp(view, "menu") != 0)
	{
		enterMode(AppMode::HyperCube);
		hyperCube->scramble();
		warmup = 240;
	}

	for (int i = 0; i < warmup; i++)
	{
		OpenGL.clearBuffers();
		if (appMode == AppMode::Rubik    && singleCube) singleCube->render();
		if (appMode == AppMode::HyperCube && hyperCube)  hyperCube->render();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		if (appMode == AppMode::Menu) drawMainMenu();
		else { drawHelpOverlay(); drawSolvingBanner(); }
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		OpenGL.update();
	}

	write_ppm(path);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

// ── ImGui panels ─────────────────────────────────────────────────────
static void drawMainMenu()
{
	const ImGuiViewport* vp = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(vp->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(420, 0));

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize
	                       | ImGuiWindowFlags_NoMove
	                       | ImGuiWindowFlags_NoCollapse
	                       | ImGuiWindowFlags_NoSavedSettings;

	ImGui::Begin("Rubik's Cube -Choose a mode", nullptr, flags);

	ImGui::TextWrapped("Pick what to render. You can return to this menu at any time with Tab.");
	ImGui::Separator();
	ImGui::Spacing();

	if (ImGui::Button("Rubik's Cube  (3 x 3 x 3)", ImVec2(-1, 48)))
		enterMode(AppMode::Rubik);

	ImGui::Spacing();

	if (ImGui::Button("HyperCube  (27 cubes synchronized)", ImVec2(-1, 48)))
		enterMode(AppMode::HyperCube);

	ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
	ImGui::TextDisabled("Esc closes the application.");

	ImGui::End();
}

static void drawHelpOverlay()
{
	if (!showHelp) return;

	// Auto-hide the first time around, after the timer expires.
	if (helpAutoHideAt > 0.0 && glfwGetTime() > helpAutoHideAt)
	{
		showHelp = false;
		helpAutoHideAt = 0.0;
		return;
	}

	const ImGuiViewport* vp = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(vp->WorkPos.x + 12, vp->WorkPos.y + 12), ImGuiCond_Always);
	ImGui::SetNextWindowBgAlpha(0.78f);

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration
	                       | ImGuiWindowFlags_AlwaysAutoResize
	                       | ImGuiWindowFlags_NoSavedSettings
	                       | ImGuiWindowFlags_NoFocusOnAppearing
	                       | ImGuiWindowFlags_NoNav;

	if (ImGui::Begin("Controls", &showHelp, flags))
	{
		ImGui::Text("Controls  (toggle with H)");
		ImGui::Separator();
		if (ImGui::BeginTable("controls", 2, ImGuiTableFlags_SizingFixedFit))
		{
			auto row = [](const char* k, const char* v) {
				ImGui::TableNextRow();
				ImGui::TableNextColumn(); ImGui::TextDisabled("%s", k);
				ImGui::TableNextColumn(); ImGui::Text("%s", v);
			};
			row("F B U D L R", "Rotate face clockwise");
			row("Shift + F/B/U/D/L/R", "Rotate face counter-clockwise");
			row("S", "Scramble (random)");
			row("Space", "Solve with Kociemba");
			row("Tab", "Back to menu");
			row("H", "Toggle this help");
			row("Mouse / arrows", "Look around / move camera");
			row("Esc", "Quit");
			ImGui::EndTable();
		}
	}
	ImGui::End();
}

static void drawSolvingBanner()
{
	const char* status = worldStatus();
	if (!status) return;

	const ImGuiViewport* vp = ImGui::GetMainViewport();
	ImVec2 pos(vp->GetCenter().x, vp->WorkPos.y + 40);
	ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.5f, 0.0f));
	ImGui::SetNextWindowBgAlpha(0.6f);

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration
	                       | ImGuiWindowFlags_AlwaysAutoResize
	                       | ImGuiWindowFlags_NoSavedSettings
	                       | ImGuiWindowFlags_NoFocusOnAppearing
	                       | ImGuiWindowFlags_NoNav
	                       | ImGuiWindowFlags_NoInputs;

	ImGui::Begin("Working", nullptr, flags);
	ImGui::Text("%s", status);
	ImGui::End();
}

// ── Entry point ──────────────────────────────────────────────────────
int main(int argc, char** argv)
{
	std::srand((unsigned int)std::time(nullptr));

	if (argc >= 3 && std::strcmp(argv[1], "--screenshot") == 0)
	{
		dump_screenshot("hyper", argv[2]);
		return 0;
	}
	if (argc >= 4 && std::strcmp(argv[1], "--screenshot-view") == 0)
	{
		dump_screenshot(argv[2], argv[3]);
		return 0;
	}

	initImGui();

	while (OpenGL.isOpen())
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		OpenGL.clearBuffers();

		if (appMode == AppMode::Rubik    && singleCube) singleCube->render();
		if (appMode == AppMode::HyperCube && hyperCube)  hyperCube->render();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (appMode == AppMode::Menu) drawMainMenu();
		else { drawHelpOverlay(); drawSolvingBanner(); }

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		OpenGL.update();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	delete singleCube;
	delete hyperCube;
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (appMode == AppMode::Menu && ImGui::GetIO().WantCaptureKeyboard) return;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (action == GLFW_PRESS && key == GLFW_KEY_TAB)
	{
		backToMenu();
		return;
	}

	if (action == GLFW_PRESS && key == GLFW_KEY_H)
	{
		showHelp = !showHelp;
		helpAutoHideAt = 0.0;
		return;
	}

	// Camera arrows are held, not press-once.
	if (glfwGetKey(window, GLFW_KEY_UP)    == GLFW_PRESS) camera->ProcessKeyboard(FORWARD,  deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN)  == GLFW_PRESS) camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT)  == GLFW_PRESS) camera->ProcessKeyboard(LEFT,     deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) camera->ProcessKeyboard(RIGHT,    deltaTime);

	if (action != GLFW_PRESS) return;
	if (appMode == AppMode::Menu) return;

	bool shift = (mods & GLFW_MOD_SHIFT) != 0;
	auto turn = [shift](char cw, char ccw) { playMove(shift ? ccw : cw); };

	switch (key)
	{
		case GLFW_KEY_F: turn(F_MOVEMENT, F_PRIME_MOVEMENT); break;
		case GLFW_KEY_B: turn(B_MOVEMENT, B_PRIME_MOVEMENT); break;
		case GLFW_KEY_U: turn(U_MOVEMENT, U_PRIME_MOVEMENT); break;
		case GLFW_KEY_D: turn(D_MOVEMENT, D_PRIME_MOVEMENT); break;
		case GLFW_KEY_L: turn(L_MOVEMENT, L_PRIME_MOVEMENT); break;
		case GLFW_KEY_R: turn(R_MOVEMENT, R_PRIME_MOVEMENT); break;
		case GLFW_KEY_S: scrambleCurrent(); break;
		case GLFW_KEY_SPACE: solveCurrent(); break;
		default: break;
	}
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	if (ImGui::GetIO().WantCaptureMouse) return;
	if (process_Camera) camera->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (ImGui::GetIO().WantCaptureMouse) return;
	camera->ProcessMouseScroll(static_cast<float>(yoffset));
}
