//
// Created by jim on 24.01.18.
//

#include <list>
#include <string>
#include <vector>
#include "constants.h"
#include "Transform.h"
#include "Ellipse.h"

#pragma once

/**
 * Paints text graphics into a framebuffer.
 * Provides a transformation stack, whereas the final transform matrix is built bottom-to-top.
 */
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
    overwrite(
            bool b
    );

    /**
     * Map framebuffer coordinates to transform space coordinates, i.e. the transformed coordinated which would map
     * to this framebuffer coordinate.
     * @param loc Framebuffer coordinate
     * @return Mapped to transformed space.
     */
    vec
    mapToTransformed(
            const glm::ivec2 &loc
    );

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
    ellipse(const Ellipse &ellipse);

    void
    push();

    void
    pop();

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

    int
    rows() const;

    auto
    begin()
    {
        return mScanlines.begin();
    }

    auto
    end()
    {
        return mScanlines.end();
    }

    void
    present();

    const glm::mat3 &
    transformation();

private:

    std::list<Transform> mTransformStack;
    glm::mat3 mProjection;
    glm::mat3 mTransform;
    bool mOverwrite;

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

    void
    stepper(
            const Ellipse &ellipse,
            double ts,
            double te
    );

};


