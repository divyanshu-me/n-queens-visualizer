#include <SFML/Graphics.hpp>
#include "BacktrackingSolver.hpp"
#include <sstream>
#include <algorithm>

int main()
{
    sf::RenderWindow window(sf::VideoMode({600u,600u}), "N-Queens Backtracking");

    int   N      = 8;
    bool  paused = false;
    float delay  = 0.2f;  // seconds per auto-step

    BacktrackingSolver solver(N);
    solver.start();

    sf::Clock clock;
    sf::Font  font;
    if (!font.openFromFile("arial.ttf")) {
        // Make sure arial.ttf is next to the .exe or adjust this path
    }

    while (window.isOpen())
    {
        // Poll all events
        while (auto evtOpt = window.pollEvent())
        {
            auto& evt = *evtOpt;
            if (evt.getIf<sf::Event::Closed>())
            {
                window.close();
                break;
            }

            if (auto kp = evt.getIf<sf::Event::KeyPressed>())
            {
                switch (kp->code)
                {
                    // toggle pause/resume
                    case sf::Keyboard::Key::Space:
                        paused = !paused;
                        break;

                    // manual single step
                    case sf::Keyboard::Key::Right:
                        if (solver.step())
                            paused = true;   // found a solution
                        break;

                    // increase board size
                    case sf::Keyboard::Key::Add:
                    case sf::Keyboard::Key::Equal:
                        if (N < 16) {
                            N++;
                            solver = BacktrackingSolver(N);
                            solver.start();
                            paused = false;
                        }
                        break;

                    // decrease board size
                    case sf::Keyboard::Key::Subtract:
                    case sf::Keyboard::Key::Hyphen:
                        if (N > 4) {
                            N--;
                            solver = BacktrackingSolver(N);
                            solver.start();
                            paused = false;
                        }
                        break;

                    // slow down
                    case sf::Keyboard::Key::Up:
                        delay = std::min(delay + 0.05f, 1.0f);
                        break;

                    // speed up
                    case sf::Keyboard::Key::Down:
                        delay = std::max(delay - 0.05f, 0.01f);
                        break;

                    default:
                        break;
                }
            }
        }

        // automatic stepping
        if (!paused && clock.getElapsedTime().asSeconds() >= delay)
        {
            if (solver.step())
                paused = true;  // hit a solution → pause
            clock.restart();
        }

        // draw
        window.clear();
        solver.draw(window);

        // HUD: draw in yellow now
        if (!font.getInfo().family.empty())
        {
            std::ostringstream ss;
            ss << "N=" << N
               << " [" << (paused ? "Paused" : "Running") << "] "
               << int(1.0f / delay) << "Hz";

            sf::Text hud{font, ss.str(), 16};
            hud.setFillColor(sf::Color::Yellow);
            hud.setPosition({5.f, 5.f});
            window.draw(hud);
        }

        window.display();
    }

    return 0;
}
