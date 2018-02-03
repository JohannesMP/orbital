//
// Created by jim on 25.01.18.
//

#pragma once

#include "constants.h"

class Transform
{

public:

    Transform();

    void
    reset();

    void
    translate(
            const vec &v
    );

    void
    scale(
            Decimal s
    );

    void
    rotate(
            Decimal radians
    );

    const mat &
    transformation() const;

private:

    mat mTranslation;
    mat mScale;
    mat mRotation;
    mat mTransform;

    void
    update();

};


