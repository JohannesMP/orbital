//
// Created by jim on 24.01.18.
//

#include "Graphics.h"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <orbital/math/elementary.h>

Graphics::Graphics(
        size_t const rows,
        size_t cols
)
{
    if (0 == rows)
    {
        throw std::runtime_error{"graphics cannot have 0 rows"};
    }

    if (0 == cols)
    {
        cols = static_cast<size_t>(rows / charRatio());
    }

    mScanlines.resize(rows);
    for (auto &scanline : mScanlines)
    {
        scanline.resize(cols);
    }
    clear();

    // Span over whole viewport
    mProjection = glm::scale(mat{1}, {cols / 2.0, rows / 2.0});

    // Origin should sit in the center
    mProjection = glm::translate(mProjection, {1, 1});

    // Y-Axis should point upwards
    mProjection = glm::scale(mProjection, {1, -1});

    // Scale against viewport distort
    mProjection = glm::scale(mProjection, {rows / static_cast<Decimal>(cols) / charRatio(), 1});

    push();
    updateTransform();
}

void
Graphics::clear()
{
    for (auto &scanline : mScanlines)
    {
        std::fill(scanline.begin(), scanline.end(), ' ');
    }
}

void
Graphics::pixel(
        vec pos,
        char c
)
{
    auto loc = mapToFramebuffer(pos);
    if (!withinFramebufferBounds(loc))
    {
        return;
    }

    char &target = framebufferPixel(loc);
    if (mOverwrite || (!mOverwrite && ' ' == target))
    {
        target = c;
    }
}

void
Graphics::label(
        vec pos,
        std::string_view const &text
)
{
    auto loc = mapToFramebuffer(pos);
    if (!withinFramebufferBounds(loc))
    {
        return;
    }

    // If text length exceeds scanline length from a given column,
    // the text must be trimmed to a smaller size to avoid:
    auto span = std::min<int>(static_cast<int>(text.length()), columns() - loc.x);

    if (mOverwrite)
    {
        // Simply copy the whole text into framebuffer:
        std::copy(text.begin(), text.begin() + span, mScanlines[loc.y].begin() + loc.x);
    }
    else
    {
        for (int i = 0; i < span; i++)
        {
            char &target = framebufferPixel(loc);
            if (' ' == target)
            {
                target = text[i];
            }
        }
    }
}

Graphics::FramebufferLocation
Graphics::mapToFramebuffer(
        const vec &v
)
{
    vec3 transformed = mTransform * vec3{v, 1.0};
    return transformed;
}

vec
Graphics::mapToTransformed(
        const FramebufferLocation &loc
)
{
    vec3 v = glm::inverse(mTransform) * vec3{loc, 1.0};
    return v;
}

void
Graphics::border()
{
    for (std::string &scanline : mScanlines)
    {
        scanline.front() = scanline.back() = '|';
    }

    std::fill(mScanlines.front().begin() + 1, mScanlines.front().end() - 1, '-');
    std::fill(mScanlines.back().begin() + 1, mScanlines.back().end() - 1, '-');

    mScanlines.front().front() = '+';
    mScanlines.front().back() = '+';
    mScanlines.back().front() = '+';
    mScanlines.back().back() = '+';
}

void
Graphics::translate(const vec &v)
{
    mTransformStack.back().translate(v);
    updateTransform();
}

void
Graphics::scale(Decimal s)
{
    mTransformStack.back().scale(s);
    updateTransform();
}

void
Graphics::rotate(Radian theta)
{
    mTransformStack.back().rotate(theta);
    updateTransform();
}

void
Graphics::updateTransform()
{
    mat view{1};
    for (auto transform : mTransformStack)
    {
        view *= transform.transformation();
    }
    mTransform = mProjection * view;
}

int
Graphics::columns() const
{
    return static_cast<int>(mScanlines[0].length());
}

void
Graphics::resetTransform()
{
    mTransformStack.back().reset();
    updateTransform();
}

void
Graphics::present()
{
    for (auto &scanline : mScanlines)
    {
        std::cout << scanline << '\n';
    }
    std::cout << std::flush;
}

constexpr bool
Graphics::withinFramebufferBounds(
        const FramebufferLocation &v
) const
{
    return v.y >= 0 && v.y < rows() && v.x >= 0 && v.x < columns();
}

void
Graphics::push()
{
    mTransformStack.emplace_back();
}

void
Graphics::pop()
{
    mTransformStack.pop_back();
    updateTransform();
}

mat const &
Graphics::transformation()
{
    return mTransform;
}

void
Graphics::ellipse(const Ellipse &ellipse)
{
    // Skip ellipse rendering if the viewport is completely contained by the ellipse shape,
    // i.e. no lines are visible anyway.
    vec ll = mapToTransformed({0, rows() - 1});
    vec ur = mapToTransformed({columns() - 1, 0});
    if (ellipse.contains(Rectangle{ll, ur}))
    {
        //std::cout << "Skip ellipse rendering" << std::endl;
        return;
    }
    //std::cout << "Render ellipse ..." << std::endl;

    // Since the stepper calculates the pixel distance based on vector subtraction and *not* on ellipse arc length,
    // the ellipse must be divided into 4 quarters
    stepper(ellipse, 0_pi, 0.5_pi);
    stepper(ellipse, 0.5_pi, 1_pi);
    stepper(ellipse, 1_pi, 1.5_pi);
    stepper(ellipse, 1.5_pi, 2_pi);
}

void
Graphics::stepper(
        const Ellipse &ellipse,
        Radian const ts,
        Radian const te
)
{
    // Calculate distance the painted pixels of the start and end arc would have within the framebuffer:
    vec vs = ellipse.point(ts);
    vec ve = ellipse.point(te);
    Decimal d = distance({mapToFramebuffer(ve)}, {mapToFramebuffer(vs)});

    // 1.4142... is the distance between to diagonal pixels:
    if (1.5 < d)
    {
        // Distance between painted pixels in framebuffers spans over at least one pixel,
        // continue stepping in smaller steps:
        Radian ta = average(ts, te);
        stepper(ellipse, ts, ta);
        stepper(ellipse, ta, te);
    }

    else
    {
        // Paint pixel:
        pixel(vs, '+');
    }
}

void
Graphics::overwrite(bool b)
{
    mOverwrite = b;
}

int
Graphics::rows() const
{
    return static_cast<int>(mScanlines.size());
}

char &
Graphics::framebufferPixel(const Graphics::FramebufferLocation &loc)
{
    return mScanlines.at(loc.y).at(loc.x);
}

char const &
Graphics::framebufferPixel(const Graphics::FramebufferLocation &loc) const
{
    return mScanlines.at(loc.y).at(loc.x);
}
