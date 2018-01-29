//
// Created by jim on 25.01.18.
//

#pragma once

#include "constants.h"

class Transform
{

public:

    Transform();

    void reset();

    void
    translate(
            const vec &v
    );

    void
    scale(
            double s
    );

    void
    rotate(
            float radians
    );

    const glm::mat3 &
    transformation() const;

private:

    glm::mat3 mTranslation;
    glm::mat3 mScale;
    glm::mat3 mRotation;
    glm::mat3 mTransform;

    void
    update();

};


