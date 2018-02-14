//
// Created by jim on 24.01.18.
//

#include <list>
#include <orbital/common/common.h>
#include <orbital/math/Ellipse.h>
#include <orbital/math/Transform.h>
#include <string>
#include <string_view>
#include <vector>
#include "FramebufferVector.h"
#include "FramebufferLocation.h"

#pragma once

/**
 * Paints text graphics into a framebuffer.
 * Provides a transformation stack, whereas the final transform matrix is built bottom-to-top.
 */
class Graphics
{

public:

    struct WorldVector
            : public vec
    {
        using vec::vec;
    };


    /**
     * Character width to height ration.
     */
    static constexpr Decimal
    charRatio()
    {
        return 1 / 2.0;
    }

    /**
     * Create a new graphics with a given count of rows and columns.
     * Pushes an initial layer of transformation.
     * @param rows Count of rows.
     * @param cols Count of columns.
     */
    explicit Graphics(
            size_t rows = 21,
            size_t cols = 0
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
     * @param vec Framebuffer coordinate
     * @return Mapped to transformed space.
     */
    WorldVector
    mapToWorld(
            FramebufferVector const &vec
    );

    /**
     * Write a string at a position.
     * @param worldVector Untransformed position.
     * @param text Text to write.
     */
    void
    label(
            WorldVector const &worldVector,
            std::string_view const &text
    );

    /**
     * Write a single character to a position.
     * @param worldVector Untransformed position.
     * @param c Character to write.
     */
    void
    pixel(
            WorldVector const &worldVector,
            char const c
    );

    /**
     * Draw an ellipse.
     * @param ellipse Ellipse to draw.
     */
    void
    ellipse(
            Ellipse<Decimal> const &ellipse
    );

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
            WorldVector const &v
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
     * @param theta Amount of rotation, in Radians.
     */
    void
    rotate(
            Radian<Decimal> theta
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
    std::size_t
    columns() const;

    /**
     * @return Count of framebuffer rows.
     */
    std::size_t
    rows() const;

    /**
     * Print framebuffer to the console.
     */
    void
    present();

    /**
     * @return Total transform, including of the whole transformation stack, i.e. considering all layers.
     */
    mat const &
    transformation();

private:

    /**
     * Stack of transformations.
     */
    std::list<Transform<Decimal>> mTransformStack;

    /**
     * Projection matrix, calculated once.
     */
    mat mProjection;

    /**
     * Total transform, update every time the transform stack is modified.
     */
    mat mTransform;

    /**
     * Overwrite content in framebuffer flag.
     */
    bool mOverwrite;

    /**
     * Row major scan-line framebuffer
     */
    std::vector<std::string> mScanlines;

    /**
     * Maps an untransformed vector to the framebuffer coordinate space.
     * @param vec Vector to map.
     * @return Location within framebuffer.
     */
    FramebufferVector
    mapToFramebuffer(
            WorldVector const &vec
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
    bool
    withinFramebufferBounds(
            FramebufferVector const &v
    ) const;

    /**
     * Internal function, used to render ellipses.
     * @param ellipse Ellipse to render.
     * @param ts Start ellipse parameter.
     * @param te End ellipse parameter.
     */
    void
    stepper(
            Ellipse<Decimal> const &ellipse,
            Radian<Decimal> ts,
            Radian<Decimal> te
    );

    /**
     * Give a reference to a pixel within the framebuffer.
     * @param loc Target location of pixel.
     * @return Reference.
     */
    char &
    framebufferPixel(
            FramebufferLocation const &loc
    );

    /**
     * Give a const reference to a pixel within the framebuffer.
     * @param loc Target location of pixel.
     * @return Const reference.
     */
    const char &
    framebufferPixel(
            FramebufferLocation const &loc
    ) const;

};


