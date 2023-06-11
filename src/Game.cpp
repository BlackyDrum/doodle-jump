#include "../include/Game.h"

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Doodle Jump!");
    window.setFramerateLimit(60);

    srand(time(NULL));

    ImGui::SFML::Init(window);
    sf::Clock delta;

    bool showSettings = false;
    float moveSpeed = 5, gravityForce = 0.2, jumpForce = 0.2;

    World world;
    if (!world.loadAssets())
        return;
    world.setup();
    window.setView(world.getView());

    Player player(0,10);
    if (!player.loadAssets())
        return;
    player.setup(sf::Vector2f(SCREEN_WIDTH / 2,-100));

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
        if (player.jump(jumpForce))
        {
            world.updateView(window, player);
        }

        player.update();

        world.moveBackground();
        world.update(player.getPlayer());

        for (auto& p : world.getPlatforms())
            Collision::checkCollision(player, p);

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