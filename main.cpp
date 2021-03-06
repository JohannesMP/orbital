#include <iostream>
#include <iomanip>
#include <thread>
#include <orbital/common/convert.h>
#include "src/orbital/physical/System.h"
#include "src/orbital/graphics/Graphics.h"

int
main()
{
    /*Ellipse ellipse{2, 0.5};
    Graphics graphics{35};

    graphics.translate({-2, 0});
    graphics.scale(2000);
    graphics.ellipse(ellipse);

    graphics.border();
    graphics.present();*/

    Graphics graphics{35, 121};
    System system{"planets.yml", "solar-system", 60 * 60};

    auto &earth = system.find("Mars");

    for (int i = 0; i < 10000000; i++)
    {
        system.stepSimulation();

        // Set graphics transform to track earth:
        {
            graphics.resetTransform();
            //graphics.rotate(0.5_pi);
            graphics.scale(1 / au(1.6));
            graphics.translate(convert<Graphics::WorldVector>(-earth.getPosition()));
        }

        // Render:
        graphics.clear();

        // Paint body names:
        system.foreach([&](Body &body) {

            graphics.push();
            graphics.translate(convert<Graphics::WorldVector>(body.getTrajectory().focalPoints()[0]));
            graphics.overwrite(false);
            graphics.ellipse(body.getTrajectory());
            graphics.overwrite(true);
            graphics.pop();

            graphics.label(convert<Graphics::WorldVector>(body.getPosition()), body.getName());
        });

        graphics.border();
        graphics.present();

        std::this_thread::sleep_for(std::chrono::milliseconds{50});
    }
}
