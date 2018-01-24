#include <iostream>
#include <iomanip>
#include <thread>
#include "System.h"
#include "Graphics.h"

int
main()
{
    Graphics graphics{40, 120};
    System system{{"Sun", 1.9884e30, 348171, ZERO, 0}, S_PER_DAY * 2};

    graphics.scale(1 / (3 * AU));

    system.addBody({"Earth", 5.9737e27, 3189, 1.00000011 * AU, 0.01671022});

    for (int i = 0; i < 365; i++)
    {
        system.stepSimulation();

        // Render:
        //graphics.clear();
        system.foreach([&](Body &body) {
            graphics.pixel(body.getPosition(), body.getName()[0]);
        });
        graphics.border();
        graphics.present();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
