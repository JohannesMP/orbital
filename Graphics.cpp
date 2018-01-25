//
// Created by jim on 24.01.18.
//

#include <stdexcept>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "Graphics.h"

const double Graphics::CHAR_RATIO = 1 / 2.0;

Graphics::Graphics(
        int rows,
        int cols
)
{
    if (0 == rows)
    {
        throw std::runtime_error{"graphics cannot have 0 rows"};
    }

    if (0 == cols)
    {
        cols = static_cast<int>(rows / CHAR_RATIO);
    }

    mScanlines.resize(static_cast<unsigned long>(rows));
    for (auto &scanline : mScanlines)
    {
        scanline.resize(static_cast<unsigned long>(cols));
    }
    clear();

    mProjection = glm::scale(glm::mat3{1}, {cols / 2.0, rows / 2.0});               // Span over whole viewport
    mProjection = glm::translate(mProjection, glm::vec2{1, 1});                     // Origin should sit in the center
    mProjection = glm::scale(mProjection, {1, -1});                                 // Y-Axis should point upwards
    mProjection = glm::scale(mProjection, {rows / (double) cols / CHAR_RATIO, 1});   // Scale against viewport distort

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

    mScanlines.at(static_cast<unsigned long>(loc.y)).at(static_cast<unsigned long>(loc.x)) = c;
}

void
Graphics::label(
        vec pos,
        const std::string &text
)
{
    auto loc = mapToFramebuffer(pos);
    auto span = std::min<int>(static_cast<int>(text.length()), columns() - loc.x);

    if (0 >= span || !withinFramebufferBounds(loc))
    {
        return;
    }

    std::copy(text.begin(), text.begin() + span, mScanlines[loc.y].begin() + loc.x);
}

glm::ivec2
Graphics::mapToFramebuffer(const vec &v)
{
    glm::vec3 transformed = mTransform * glm::vec3{v, 1.0};
    return transformed;
}

vec
Graphics::mapToTransformed(const glm::ivec2 &loc)
{
    glm::vec3 v = glm::inverse(mTransform) * glm::vec3{loc, 1.0};
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
Graphics::scale(double s)
{
    mTransformStack.back().scale(s);
    updateTransform();
}

void
Graphics::rotate(float degrees)
{
    mTransformStack.back().rotate(degrees);
    updateTransform();
}

void
Graphics::updateTransform()
{
    glm::mat3 view{1};
    for (auto iter = mTransformStack.rbegin(); iter != mTransformStack.rend(); iter++)
    {
        view *= iter->transformation();
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
    for (auto &scanline : *this)
    {
        std::cout << scanline << std::endl;
    }
}

bool
Graphics::withinFramebufferBounds(const glm::ivec2 &v)
{
    return v.y >= 0 && v.y < mScanlines.size() && v.x >= 0 && v.x < mScanlines[0].length();
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
}

const glm::mat3 &
Graphics::transformation()
{
    return mTransform;
}

void
Graphics::ellipse(
        float a,
        float e
)
{
    // Since the stepper calculates the pixel distance based on vector subtraction and *not* on ellipse arc length,
    // the ellipse must be divided into 4 quarters
    stepper(a, ellipseB(a, e), 0, PI * 0.5);
    stepper(a, ellipseB(a, e), PI * 0.5, PI);
    stepper(a, ellipseB(a, e), PI, PI * 1.5);
    stepper(a, ellipseB(a, e), PI * 1.5, 2 * PI);
}

void
Graphics::stepper(
        double a,
        double b,
        double ts,
        double te
)
{
    // Calculate distance the painted pixels of the start and end arc would have within the framebuffer:
    vec vs = ellipseT(a, b, ts);
    vec ve = ellipseT(a, b, te);
    double d = distance({mapToFramebuffer(ve)}, {mapToFramebuffer(vs)});

    // 1.4142... is the distance between to diagonal pixels:
    if (1.5 < d)
    {
        // Distance between painted pixels in framebuffers spans over at least one pixel,
        // continue stepping in smaller steps:
        double tHalf = (te - ts) / 2;
        stepper(a, b, ts, ts + tHalf);
        stepper(a, b, ts + tHalf, te);
    }

    else
    {
        // Paint pixel:
        pixel(vs, '#');
    }
}
