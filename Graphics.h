//
// Created by jim on 24.01.18.
//

#include <vector>
#include <string>
#include "constants.h"

#pragma once

class Graphics
{

public:

    static const double CHAR_RATIO;

    explicit Graphics(
            int rows = 21,
            int cols = 0
    );

    void
    clear();

    void
    label(
            vec pos,
            const std::string &text
    );

    void
    pixel(
            vec pos,
            char c
    );

    void
    resetTransform();

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
            float degrees
    );

    void
    border();

    int
    columns() const;

    auto begin()
    {
        return mScanlines.begin();
    }

    auto end()
    {
        return mScanlines.end();
    }

    void
    present();

private:

    glm::mat3 mTranslation{1};
    glm::mat3 mScale{1};
    glm::mat3 mRotation{1};
    glm::mat3 mProjection;
    glm::mat3 mTransform;

    /**
     * Row major scan-line framebuffer
     */
    std::vector<std::string> mScanlines;

    glm::ivec2
    mapToFramebuffer(
            const vec &v
    );

    void
    updateTransform();

    bool
    withinFramebufferBounds(
            const glm::ivec2 &v
    );

};


