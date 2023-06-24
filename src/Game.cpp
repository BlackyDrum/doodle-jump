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

    const sf::View defaultView = window.getView();

    bool showSettings = false, gamePause = false, gameLost = false, lostSoundPlayed = false;
    float moveSpeed = 6, jumpForce = 20.0, projectileFireSpeed = 0.25;
    float gravityForce = 0.6;
    float featherForce = 30.0, trampolineForce = 40.0;
    int volume = 10;

    const int MaxMemoryHistory = 100;
    float memoryHistory[MaxMemoryHistory] = {};
    int memoryIndex = 0;

    World world;
    if (!world.loadAssets())
        return;
    world.setup();
    window.setView(world.getView());

    Player player(0, jumpForce, 20);
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

    UI ui;
    if (!ui.loadAssets())
        return;
    ui.setup();

    Settings settings;

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
                if (event.key.code == sf::Keyboard::Escape && !gameLost)
                    gamePause = !gamePause;
            }
        }

        ImGui::SFML::Update(window, delta.restart());;

        if (!gamePause && !gameLost) {
            player.move(moveSpeed);
            player.gravity(gravityForce);
            if (player.jump(gravityForce))
            {
                world.updateView(window, player);
            }

            player.update(world.getView());
            player.setProjectileFireSpeed(projectileFireSpeed);

            if (player.checkLose(window.getView()))
            {
                gameLost = true;

                if (!lostSoundPlayed)
                {
                    sound.playLoseSound();

                    lostSoundPlayed = true;
                }
            }

            if (player.shoot())
                sound.playShootSound();

            world.moveBackground();
            world.update(player.getPlayer());

            score.update(world.getView(), player.getHighestPosition());

            if (Collision::checkTileCollision(player, world.getFeather()))
            {
                player.setVelocityUp(featherForce);

                player.setIsJumping(true);
                player.setIsFalling(false);

                world.setFeatherTexture();

                sound.playerFeatherSound();
            }
            if (Collision::checkTileCollision(player, world.getTrampoline()))
            {
                player.setVelocityUp(trampolineForce);

                player.setIsJumping(true);
                player.setIsFalling(false);

                world.setTrampolineTexture();

                sound.playTrampolineSound();
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
                    if (!world.getBrokenPlatformIsFalling()[i])
                        sound.playBreakSound();

                    world.setBrokenPlatformIsFalling(i);
                }

            }

            ui.update(window.getView());
        }
            
        if (gameLost && ui.restart(window))
        {
            gameLost = false;
            lostSoundPlayed = false;

            player.setup(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 * -1.0));
            player.setIsFalling(false);
            player.setIsJumping(true);

            world.setup();

            score.setup();

            world.setView(window.getDefaultView());
            world.getView().move(0, SCREEN_HEIGHT * -1.0);
            window.setView(world.getView());
        }

        if (showSettings)
            settings.settings(showSettings, moveSpeed, jumpForce, featherForce, trampolineForce, gravityForce, volume, MaxMemoryHistory, memoryHistory, memoryIndex, projectileFireSpeed);

        player.setJumpForce(jumpForce);

        sound.updateVolume(volume);
       
        window.clear();

        Renderer::draw(window, world.getBackgrounds(), player.getPlayer(), world.getPlatforms(), world.getBrokenPlatforms(), player.getProjectiles(), world.getFeather(), world.getTrampoline());
        //window.draw(player.getBoundingBox());

        window.draw(score.getScore());
        if (gamePause)
            window.draw(ui.getPause());

        if (gameLost)
            window.draw(ui.getLostScreen());

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
}