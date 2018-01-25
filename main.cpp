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
    Graphics graphics{31, 121};

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
            graphics.translate(-vec{ellipseFoci(body.getA(), body.getE()) / 2 / AU, 0});
            graphics.ellipse(body.getA(), body.getE());
            graphics.pop();

            graphics.label(body.getPosition(), body.getName());
        });

        graphics.border();
        graphics.present();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

#pragma clang diagnostic pop