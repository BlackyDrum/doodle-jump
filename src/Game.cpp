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
    float moveSpeed = 6, gravityForce = 0.6, jumpForce = 20.0, featherForce = 30.0;
    int volume = 25;

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

    Sound sound(volume);
    if (!sound.loadAssets())
        return;
    sound.setup();

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
        
        if (player.shoot())
            sound.playShootSound();

        world.moveBackground();
        world.update(player.getPlayer());

        score.update(world.getView(), player.getHighestPosition());

        if (Collision::checkFeatherCollision(player, world.getFeather()))
        {
            player.setVelocityUp(featherForce);

            player.setIsJumping(true);
            player.setIsFalling(false);

            world.setFeatherTexture();

            sound.playerFeatherSound();
        }

        for (auto& p : world.getPlatforms())
        {
            if (Collision::checkPlatformCollision(player, p))
            {
                player.setIsJumping(true);
                player.setIsFalling(false);

                sound.playJumpSound();
            }
        }

        for (int i = 0; i < world.getBrokenPlatforms().size(); i++)
        {
            if (Collision::checkPlatformCollision(player, world.getBrokenPlatforms()[i]))
            {
                sound.playBreakSound();

                world.setBrokenPlatformIsFalling(i);
            }
                
        }
            

        if (showSettings)
            Settings::settings(showSettings, moveSpeed, jumpForce);

        player.setJumpForce(jumpForce);
       
        window.clear();

        Renderer::draw(window, world.getBackgrounds(), player.getPlayer(), world.getPlatforms(), world.getBrokenPlatforms(), player.getProjectiles());
        //window.draw(player.getBoundingBox());

        window.draw(score.getScore()); window.draw(world.getFeather());

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
}