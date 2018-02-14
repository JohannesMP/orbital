//
// Created by jim on 24.01.18.
//

#include "Graphics.h"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <orbital/math/elementary.h>
#include <orbital/common/convert.h>

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
        WorldVector const &worldVector,
        char const c
)
{
    FramebufferVector vec = mapToFramebuffer(worldVector);
    if (!withinFramebufferBounds(vec))
    {
        return;
    }

    char &target = framebufferPixel(FramebufferLocation{vec});
    if (mOverwrite || (!mOverwrite && ' ' == target))
    {
        target = c;
    }
}

void
Graphics::label(
        WorldVector const &worldVector,
        std::string_view const &text
)
{
    auto vec = mapToFramebuffer(worldVector);
    if (!withinFramebufferBounds(vec))
    {
        return;
    }

    FramebufferLocation loc{vec};

    // If text length exceeds scanline length from a given column,
    // the text must be trimmed to a smaller size to avoid:
    auto span = std::min(text.length(), columns() - loc.x);

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

FramebufferVector
Graphics::mapToFramebuffer(
        WorldVector const &vec
)
{
    return mTransform * vec3{vec, 1.0};
}

Graphics::WorldVector
Graphics::mapToWorld(
        FramebufferVector const &vec
)
{
    return glm::inverse(mTransform) * vec3{vec, 1.0};
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
Graphics::translate(
        WorldVector const &v
)
{
    mTransformStack.back().translate(v);
    updateTransform();
}

void
Graphics::scale(
        Decimal const s
)
{
    mTransformStack.back().scale(s);
    updateTransform();
}

void
Graphics::rotate(
        Radian<Decimal> const theta
)
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

std::size_t
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

bool
Graphics::withinFramebufferBounds(
        const FramebufferVector &v
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
Graphics::ellipse(const Ellipse<Decimal> &ellipse)
{
    // Skip ellipse rendering if the viewport is completely contained by the ellipse shape,
    // i.e. no lines are visible anyway.
    vec ll = mapToWorld({0, rows() - 1});
    vec ur = mapToWorld({columns() - 1, 0});
    if (ellipse.contains(Rectangle<Decimal>{ll, ur}))
    {
        return;
    }

    // Since the stepper calculates the pixel distance based on vector subtraction and *not* on ellipse arc length,
    // the ellipse must be divided into 4 quarters
    stepper(ellipse, 0_pi, 0.5_pi);
    stepper(ellipse, 0.5_pi, 1_pi);
    stepper(ellipse, 1_pi, 1.5_pi);
    stepper(ellipse, 1.5_pi, 2_pi);
}

void
Graphics::stepper(
        const Ellipse<Decimal> &ellipse,
        Radian<Decimal> const ts,
        Radian<Decimal> const te
)
{
    // Calculate distance the painted pixels of the start and end arc would have within the framebuffer:
    auto const vs = convert<WorldVector>(ellipse.point(ts));
    auto const ve = convert<WorldVector>(ellipse.point(te));
    Decimal const d = vectorDistance(mapToFramebuffer(ve), mapToFramebuffer(vs));

    // 1.4142... is the distance between to diagonal pixels:
    if (1.5 < d)
    {
        // Distance between painted pixels in framebuffers spans over at least one pixel,
        // continue stepping in smaller steps:
        Radian<Decimal> const ta = average(ts, te);
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
Graphics::overwrite(
        bool const b
)
{
    mOverwrite = b;
}

std::size_t
Graphics::rows() const
{
    return static_cast<int>(mScanlines.size());
}

char &
Graphics::framebufferPixel(
        const FramebufferLocation &loc
)
{
    return mScanlines.at(loc.y).at(loc.x);
}

char const &
Graphics::framebufferPixel(
        FramebufferLocation const &loc
) const
{
    return mScanlines.at(loc.y).at(loc.x);
}
