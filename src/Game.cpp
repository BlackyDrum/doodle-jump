#include "../include/Game.h"

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Doodle Jump!");

    srand(time(NULL));

    ImGui::SFML::Init(window);
    sf::Clock delta;

    bool showSettings = false;

    World world(b2Vec2(0, 0.2));
    if (!world.loadAssets())
        return;
    world.setup();
    window.setView(world.getView());

    Player player;
    if (!player.loadAssets())
        return;
    player.setup(world.getWorld(), sf::Vector2f(100,100));

    Platform platform;
    if (!platform.loadAssets())
        return;
    platform.setup(world.getWorld(), sf::Vector2f(100, 400));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
                showSettings = !showSettings;
            else if (event.type == sf::Event::KeyPressed)
            {                   
            }
        }

        ImGui::SFML::Update(window, delta.restart());

        player.update();
        player.move(10);

        Collision::checkCollision(player, platform, 40000);     

        if (showSettings)
            Settings::settings(showSettings);

        
        world.getWorld()->Step(1.0 / 60.0, 8, 3);

        window.clear();

        Renderer::draw(window, world.getBackgrounds(), player.getPlayer(), platform.getPlatform());

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
}