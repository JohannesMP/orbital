//
// Created by jim on 24.01.18.
//

#include "Ellipse.h"
#include "Transform.h"
#include "constants.h"
#include <list>
#include <string>
#include <vector>
#include <string_view>

#pragma once

/**
 * Paints text graphics into a framebuffer.
 * Provides a transformation stack, whereas the final transform matrix is built bottom-to-top.
 */
class Graphics
{

public:

    /**
     * A position of a pixel within the framebuffer.
     * Can have negative values, since a framebuffer location is nothing else but an position within the framebuffer
     * coordinate space. Whether or not the location lies within the framebuffers bounds has nothing do to with the
     * location itself and can be tested using withinFramebufferBounds().
     */
    using FramebufferLocation = glm::ivec2;

    /**
     * Character width to height ration.
     */
    static constexpr Decimal CHAR_RATIO = 1 / 2.0;

    /**
     * Create a new graphics with a given count of rows and columns.
     * Pushes an initial layer of transformation.
     * @param rows Count of rows.
     * @param cols Count of columns.
     */
    explicit Graphics(
            int rows = 21,
            int cols = 0
    );

    /**
     * Clear the framebuffer.
     */
    void
    clear();

    /**
     * Set the framebuffer overwrite bit.
     * If set, any write operation is permitted to overwrite existing content within the framebuffer.
     * If not set, following write operations guarantee to not write to pixels which already have a value.
     * @param b Overwrite enable bit.
     */
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
            const FramebufferLocation &loc
    );

    /**
     * Write a string at a position.
     * @param pos Untransformed position.
     * @param text Text to write.
     */
    void
    label(
            vec pos,
            std::basic_string_view<char> const &text
    );

    /**
     * Write a single character to a position.
     * @param pos Untransformed position.
     * @param c Character to write.
     */
    void
    pixel(
            vec pos,
            char c
    );

    /**
     * Draw an ellipse.
     * @param ellipse Ellipse to draw.
     */
    void
    ellipse(const Ellipse &ellipse);

    /**
     * Add a new layer of transformation, being marked as the current one.
     */
    void
    push();

    /**
     * Remove the top-most transform layer, if any.
     * Marks the second top-most layer as the current transform layer.
     */
    void
    pop();

    /**
     * Reset any transform of the current layer.
     */
    void
    resetTransform();

    /**
     * Add translation to the current transform.
     * @param v Translation vector.
     */
    void
    translate(
            const vec &v
    );

    /**
     * Add scale to the current transform.
     * @param s Scale amount.
     */
    void
    scale(
            Decimal s
    );

    /**
     * Add rotation to the current transform.
     * @param theta Amount of rotation, in radians.
     */
    void
    rotate(
            float theta
    );

    /**
     * Draws a border at the framebuffer edges.
     * Ignores the overwrite bit.
     */
    void
    border();

    /**
     * @return Count of framebuffer columns.
     */
    int
    columns() const;

    /**
     * @return Count of framebuffer rows.
     */
    int
    rows() const;

    /**
     * Print framebuffer to the console.
     */
    void
    present();

    /**
     * @return Total transform, including of the whole transformation stack, i.e. considering all layers.
     */
    const mat &
    transformation();

private:

    std::list<Transform> mTransformStack;   ///< Stack of transformations.
    mat mProjection;                  ///< Projection matrix, calculated once.
    mat mTransform;                   ///< Total transform, update every time the transform stack is modified.
    bool mOverwrite;

    /**
     * Row major scan-line framebuffer
     */
    std::vector<std::string> mScanlines;

    /**
     * Maps an untransformed vector to the framebuffer coordinate space.
     * @param v Vector to map.
     * @return Location within framebuffer.
     */
    FramebufferLocation
    mapToFramebuffer(
            const vec &v
    );

    /**
     * Recalculates the total transform.
     */
    void
    updateTransform();

    /**
     * @param v Location to check for.
     * @return True if framebuffer location is within the framebuffer size, and therefore legally accessible.
     */
    constexpr bool
    withinFramebufferBounds(
            const FramebufferLocation &v
    ) const;

    /**
     * Internal function, used to render ellipses.
     * @param ellipse Ellipse to render.
     * @param ts Start ellipse parameter.
     * @param te End ellipse parameter.
     */
    void
    stepper(
            const Ellipse &ellipse,
            Decimal ts,
            Decimal te
    );

    /**
     * Give a reference to a pixel within the framebuffer.
     * @param loc Target location of pixel.
     * @return Reference.
     */
    char &
    framebufferPixel(
            const FramebufferLocation &loc
    );

    /**
     * Give a const reference to a pixel within the framebuffer.
     * @param loc Target location of pixel.
     * @return Const reference.
     */
    const char &
    framebufferPixel(
            const FramebufferLocation &loc
    ) const;

};


