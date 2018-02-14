//
// Created by jim on 25.01.18.
//

#pragma once

#include "Radian.h"
#include <orbital/common/common.h>

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
            Radian radians
    );

    const mat &
    transformation() const;

    Transform
    inverse() const;

    vec
    apply(
            vec v
    ) const;

private:

    mat mTranslation;
    mat mScale;
    mat mRotation;
    mat mTransform;

    void
    update();

};


