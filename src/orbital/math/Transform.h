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

    Transform &
    reset()
    {
        mTransform = identityMatrix();
        return *this;
    }

    Transform &
    translate(
            tvec<T> const &v
    )
    {
        mTransform = glm::translate(mTransform, v);
        return *this;
    }

    Transform &
    scale(
            T const s
    )
    {
        mTransform = glm::scale(mTransform, tvec<T>{s, s});
        return *this;
    }

    Transform &
    rotate(
            Radian<T> const radians
    )
    {
        mTransform = glm::rotate(mTransform, radians.getRaw());
        return *this;
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
    applied(
            tvec<T> const vec
    ) const
    {
        return mTransform * glm::tvec3<T>{vec, 1.0};
    }

private:

    mat mTransform;

};


