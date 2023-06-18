#include "../include/Game.h"

void Game::run()
{
#if defined(_WIN32) && defined(NDEBUG)
    ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Doodle Jump", sf::Style::Close);
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

    Score score;
    if (!score.loadAssets())
        return;
    score.setup();

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

        player.update(world.getView());
        player.shoot();

        world.moveBackground();
        world.update(player.getPlayer());

        score.update(world.getView(), player.getHighestPosition());

        for (auto& p : world.getPlatforms())
        {
            if (Collision::checkPlatformCollision(player, p))
            {
                player.setIsJumping(true);
                player.setIsFalling(false);
            }
        }

        for (int i = 0; i < world.getBrokenPlatforms().size(); i++)
        {
            if (Collision::checkPlatformCollision(player, world.getBrokenPlatforms()[i]))
            {
                world.setBrokenPlatformIsFalling(i);
            }
        }
            

        if (showSettings)
            Settings::settings(showSettings);

        
       
        window.clear();

        Renderer::draw(window, world.getBackgrounds(), player.getPlayer(), world.getPlatforms(), world.getBrokenPlatforms(), player.getProjectiles());
        //window.draw(player.getBoundingBox());

        window.draw(score.getScore());

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
}