//
// Created by jim on 27.01.18.
//

#include <Ellipse.h>
#include "common.h"

TEST(Ellipse, ProperConstruction)
{
    Ellipse ellipse{2, 0.5};

    ASSERT_EQ(ellipse.a(), 2);
    ASSERT_EQ(ellipse.e(), 0.5);
    assertDouble(ellipse.b(), "1.73");
}
