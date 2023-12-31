#include "../include/Settings.h"

void Settings::settings(bool& showSettings, float& movementSpeed, float& jumpForce, float& featherForce, float& trampolineForce, float& gravity, int& volume, int MaxMemoryHistory, float memoryHistory[], int& memoryIndex, float& projectileFireSpeed, char* buf, size_t buf_size)
{
	ImGui::Begin("Settings", &showSettings);

    ImGui::InputText("Your Name", buf, buf_size);

    ImGui::NewLine();

    if (ImGui::CollapsingHeader("Player Settings"))
    {
        ImGui::SliderFloat("Movement Speed", &movementSpeed, 1, 15);
        ImGui::SliderFloat("Jump Force", &jumpForce, 10, 50);
        ImGui::SliderFloat("Rapid Fire Speed", &projectileFireSpeed, 0.05, 1.0);

    }

    if (ImGui::CollapsingHeader("World Settings"))
    {
        ImGui::SliderFloat("Gravity", &gravity, 0.1, 1.0);
    }
	
    if (ImGui::CollapsingHeader("Tile Settings"))
    {
        ImGui::SliderFloat("Feather Force", &featherForce, 30, 100);
        ImGui::SliderFloat("Trampoline Force", &trampolineForce, 40, 100);
    }

    if (ImGui::CollapsingHeader("Assets"))
    {
        ImGui::SliderInt("Volume", &volume, 0, 100);        
    }

    ImGui::NewLine();

    if (ImGui::Button("Reset Settings"))
    {
        movementSpeed = 6;
        jumpForce = 20.0;
        projectileFireSpeed = 0.25;

        gravity = 0.6;

        featherForce = 30.0;
        trampolineForce = 40.0;
    }

    ImGui::NewLine();

    if (ImGui::CollapsingHeader("Statistics"))
    {
        sf::Time elapsedTime = m_frameClock.restart();

        float deltaTime = elapsedTime.asSeconds();
        int fps = static_cast<int>(1.0f / deltaTime);

        ImGui::Text("FPS: %d", fps);

#ifdef _WIN32
        float currentMemoryUse = getMemoryUse();
        memoryHistory[memoryIndex] = static_cast<float>(currentMemoryUse);
        memoryIndex = (memoryIndex + 1) % MaxMemoryHistory;

        ImGui::Text("Current Memory usage: %.2f MB", currentMemoryUse);
        ImGui::PlotLines("", memoryHistory, MaxMemoryHistory, memoryIndex, "Memory Use", 0.0f, 150.0f, ImVec2(0, 80));
#else
        // Get used memory
        std::string useMemory = readStatus("VmRSS", "/proc/self/status");
        // Get total memory
        std::string totalMemory = readStatus("MemFree", "/proc/meminfo");
        ImGui::Text("Total Memory: %i MB", std::stoi(totalMemory) / 1024);
        ImGui::Text("Memory usage: %i MB", std::stoi(useMemory) / 1024);

#endif
    }

	ImGui::End();
}

#ifdef _WIN32
float Settings::getMemoryUse()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (!GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
    {
        // Error handling
        DWORD errorCode = GetLastError();
        LPSTR messageBuffer = nullptr;
        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
        if (messageBuffer)
        {
            std::cout << "Failed to retrieve memory usage: " << messageBuffer << std::endl;
            LocalFree(messageBuffer);
        }
        return 0.0f;
    }

    SIZE_T physicalMemory = pmc.WorkingSetSize;
    float memoryUsage = static_cast<float>(physicalMemory) / (1024.0f * 1024.0f); // Convert to MB

    return memoryUsage;
}
#else
std::string Settings::readStatus(const std::string& key, std::string fileName)
{
    std::ifstream file(fileName);
    std::string line;

    while (std::getline(file, line))
    {
        if (line.find(key) != std::string::npos)
        {
            std::string value = line.substr(line.find(':') + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            return value;
        }
    }

    return "";
}
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif

void Settings::deserialize(int& highscore, char* name)
{
    std::ifstream settings("game/settings.json");

    Json::Reader reader;

    Json::Value completeJsonData;

    reader.parse(settings, completeJsonData);

    highscore = completeJsonData["Assets"]["highscore"].asInt();

    const char* jsonName = completeJsonData["Assets"]["name"].asCString();
    if (jsonName)
        std::strcpy(name, jsonName);
    else
        std::strcpy(name, "Doodle");
}

void Settings::serialize(int highscore, char name[])
{
    std::ofstream settings("game/settings.json");

    Json::StyledWriter writer;

    Json::Value assets, data, root;

    assets["highscore"] = highscore;
    assets["name"] = name;

    root["Settings"] = data;
    root["Assets"] = assets;

    settings << writer.write(root);

    settings.close();
}