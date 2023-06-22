#include "../include/Settings.h"

void Settings::settings(bool& showSettings, float& movementSpeed, float& jumpForce, float& featherForce, float& trampolineForce, float& gravity)
{
	ImGui::Begin("Settings", &showSettings);

	ImGui::Text("Player Settings");
	ImGui::SliderFloat("Movement Speed", &movementSpeed, 1, 15);
	ImGui::SliderFloat("Jump Force", &jumpForce, 10, 50);

	ImGui::NewLine();

	ImGui::Text("World Settings");
	ImGui::SliderFloat("Gravity", &gravity ,0.1, 1.0);

	ImGui::NewLine();

	ImGui::Text("Tile Settings");
	ImGui::SliderFloat("Feather Force", &featherForce, 30, 100);
	ImGui::SliderFloat("Trampoline Force", &trampolineForce, 40, 100);

	ImGui::End();
}