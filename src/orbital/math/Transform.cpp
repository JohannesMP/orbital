//
// Created by jim on 25.01.18.
//

#include "Radian.h"
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
    mTransform = identityMatrix();
}

mat const &
Transform::transformation() const
{
    return mTransform;
}

void
Transform::translate(const vec &v)
{
    mTransform = glm::translate(mTransform, vec{v});
}

void
Transform::scale(Decimal const s)
{
    mTransform = glm::scale(mTransform, vec{s, s});
}

void
Transform::rotate(Radian<Decimal> const radians)
{
    mTransform = glm::rotate(mTransform, radians.getRaw());
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
    result.mTransform = glm::inverse(mTransform);
    return result;
}
