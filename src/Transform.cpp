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
    mRotation = mScale = mTranslation = glm::mat3{1};
}

void
Transform::update()
{
    mTransform = mRotation * mScale * mTranslation;
}

const glm::mat3 &
Transform::transformation() const
{
    return mTransform;
}

void
Transform::translate(const vec &v)
{
    mTranslation = glm::translate(mTranslation, glm::vec2{v});
    update();
}

void
Transform::scale(Decimal s)
{
    mScale = glm::scale(mScale, glm::vec2{s, s});
    update();
}

void
Transform::rotate(Decimal radians)
{
    mRotation = glm::rotate(mRotation, static_cast<float>(radians)); // TODO: implement own rotate function, which is capable of Decimal
    update();
}
