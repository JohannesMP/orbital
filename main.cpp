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
    System system{"planets.yml", "solar-system", S_PER_HOUR * 2};

    graphics.scale(1 / (2 * AU));

    for (;;)
    {
        system.stepSimulation();

        // Render:
        graphics.clear();
        system.foreach([&](Body &body) {
            graphics.label(body.getPosition(), body.getName());
        });
        graphics.border();
        graphics.present();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

#pragma clang diagnostic pop