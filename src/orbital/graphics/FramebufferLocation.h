//
// Created by jim on 14.02.18.
//

#pragma once

#include <orbital/common/common.h>

/**
 * A vector in framebuffer space, exactly denoting one pixel. Cannot have negative values and is integral.
 */
struct FramebufferLocation
        : public glm::tvec2<std::size_t>
{
    using glm::tvec2<std::size_t>::tvec2;
};
