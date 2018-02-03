//
// Created by jim on 25.01.18.
//

#include "Transform.h"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/transform.hpp>

Transform::Transform()
{
    reset();
}

void
Transform::reset()
{
    mTransform = mRotation = mScale = mTranslation = IDENTITY_MATRIX;
}

void
Transform::update()
{
    mTransform = mRotation * mScale * mTranslation;
}

const mat &
Transform::transformation() const
{
    return mTransform;
}

void
Transform::translate(const vec &v)
{
    mTranslation = glm::translate(mTranslation, vec{v});
    update();
}

void
Transform::scale(Decimal s)
{
    mScale = glm::scale(mScale, vec{s, s});
    update();
}

void
Transform::rotate(Decimal radians)
{
    mRotation = glm::rotate(mRotation, radians);
    update();
}
