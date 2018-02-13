//
// Created by jim on 25.01.18.
//

#include "Transform.h"
#include "Radian.h"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/transform.hpp>

Transform::Transform()
{
    reset();
}

void
Transform::reset()
{
    mTransform = mRotation = mScale = mTranslation = identityMatrix();
}

void
Transform::update()
{
    mTransform = mRotation * mScale * mTranslation;
}

mat const &
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
Transform::rotate(Radian radians)
{
    mRotation = glm::rotate(mRotation, radians.getRaw());
    update();
}

vec
Transform::apply(vec v) const
{
    return mTransform * vec3{v, 1.0};
}

Transform
Transform::inverse() const
{
    Transform result;
    result.mTransform = glm::inverse(mTransform); // todo: transformations do not separate rot/trans/scale
    return result;
}
