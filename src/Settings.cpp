#include "../include/Settings.h"

void Settings::settings(bool& showSettings, float& movementSpeed, float& jumpForce)
{
	ImGui::Begin("Settings", &showSettings);

	ImGui::SliderFloat("Movement Speed", &movementSpeed, 1, 15);

	ImGui::SliderFloat("Jump Force", &jumpForce, 10, 50);

	ImGui::End();
}