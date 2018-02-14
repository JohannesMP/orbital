//
// Created by jim on 25.01.18.
//

#pragma once

#include "Radian.h"
#include <orbital/common/common.h>

#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/transform.hpp>

template<class T>
class Transform
{

public:

    Transform()
        : mTransform{identityMatrix()}
    {
    }

    void
    reset()
    {
        mTransform = identityMatrix();
    }

    void
    translate(
            tvec<T> const &v
    )
    {
        mTransform = glm::translate(mTransform, v);
    }

    void
    scale(
            T const s
    )
    {
        mTransform = glm::scale(mTransform, tvec<T>{s, s});
    }

    void
    rotate(
            Radian<T> const radians
    )
    {
        mTransform = glm::rotate(mTransform, radians.getRaw());
    }

    const mat &
    transformation() const
    {
        return mTransform;
    }

    Transform<T>
    inverse() const
    {
        Transform<T> result;
        result.mTransform = glm::inverse(mTransform);
        return result;
    }

    tvec<T>
    apply(
            tvec<T> const vec
    ) const
    {
        return mTransform * glm::tvec3<T>{vec, 1.0};
    }

private:

    mat mTransform;

};


