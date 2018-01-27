#include <iostream>
#include <iomanip>
#include <thread>
#include "System.h"
#include "Graphics.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

int
main()
{
    Ellipse ellipse{2, 0.5};
    ellipse.clipOld({{-2, 1}, 5, 1});

    /*
    Graphics graphics{45, 141};

    graphics.translate({1.5, 0});
    graphics.ellipse({0, -1});
    */

    /*
    System system{"planets.yml", "solar-system", S_PER_HOUR};

    auto &earth = system.find("Earth");

    for (int i = 0; i < 10000000; i++)
    {
        system.stepSimulation();

        // Set graphics transform to track earth:
        {
            graphics.resetTransform();
            graphics.scale(1 / (2 * AU));
            graphics.translate(-earth.getPosition());
        }

        // Render:
        graphics.clear();

        // Paint body names:
        system.foreach([&](Body &body) {

            graphics.push();
            graphics.translate(body.getTrajectory().fociPoints()[0]);
            graphics.overwrite(false);
            graphics.ellipse(body.getTrajectory());
            graphics.overwrite(true);
            graphics.pop();

            graphics.label(body.getPosition(), body.getName());
        });

        graphics.border();
        graphics.present();

        std::this_thread::sleep_for(std::chrono::milliseconds{50});
    }
     */
}

#pragma clang diagnostic pop
