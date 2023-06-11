#include "../include/Game.h"

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Doodle Jump!");
    window.setFramerateLimit(60);

    srand(time(NULL));

    ImGui::SFML::Init(window);
    sf::Clock delta;

    bool showSettings = false;
    float moveSpeed = 6, gravityForce = 0.6, jumpForce = 20.0;

    World world;
    if (!world.loadAssets())
        return;
    world.setup();
    window.setView(world.getView());

    Player player(0, jumpForce);
    if (!player.loadAssets())
        return;
    player.setup(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * -1.0));

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

        ImGui::SFML::Update(window, delta.restart());;

        player.move(moveSpeed);
        player.gravity(gravityForce);
        if (player.jump(gravityForce))
        {
            world.updateView(window, player);
        }

        player.update();

        world.moveBackground();
        world.update(player.getPlayer());

        for (auto& p : world.getPlatforms())
            Collision::checkPlatformCollision(player, p);

        if (showSettings)
            Settings::settings(showSettings);

        
       
        window.clear();

        Renderer::draw(window, world.getBackgrounds(), player.getPlayer(), world.getPlatforms());
        //window.draw(player.getBoundingBox());

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
}