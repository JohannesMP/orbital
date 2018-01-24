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
    mProjection = glm::scale(mProjection, {rows / (double)cols / CHAR_RATIO, 1});   // Scale against viewport distort

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
    if(!withinFramebufferBounds(loc))
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
    auto span = std::min<int>(static_cast<int>(text.length()), static_cast<int>(columns() - loc.x));

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
    return {transformed.x, transformed.y};
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
    mTranslation = glm::translate(mTranslation, glm::vec2{v});
    updateTransform();
}

void
Graphics::scale(double s)
{
    mScale = glm::scale(mScale, glm::vec2{s, s});
    updateTransform();
}

void
Graphics::rotate(float degrees)
{
    mRotation = glm::rotate(mRotation, glm::radians(degrees));
    updateTransform();
}

void
Graphics::updateTransform()
{
    mTransform = mProjection * mRotation * mScale * mTranslation;
}

int
Graphics::columns() const
{
    return static_cast<int>(mScanlines[0].length());
}

void
Graphics::resetTransform()
{
    mRotation = mScale = mTranslation = glm::mat3{1};
    updateTransform();
}

void
Graphics::present()
{
    for (auto &scanline : mScanlines)
    {
        std::cout << scanline << std::endl;
    }
}

bool
Graphics::withinFramebufferBounds(const glm::ivec2 &v)
{
    return v.y >= 0 && v.y < mScanlines.size() && v.x >= 0 && v.x < mScanlines[0].length();
}
