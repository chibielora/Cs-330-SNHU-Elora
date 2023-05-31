#pragma once
#include <glm.hpp>

struct Vertex {
    glm::vec3 Position {0.f, 0.f, 0.f};
    glm::vec3 Color {1.f, 1.f, 1.f};
    glm::vec3 Normal {0.f, 0.f, 0.f};
    glm::vec2 Uv {1.f, 1.f};
};

struct TridimensionalShapes {
    static inline std::vector<Vertex> cubeVertices {
        // front
        {
            .Position = {-.5f, .5f, .5f},
            .Color = {1.f, .5f, .5f} 
        },
        {
            .Position = {-.5f, -.5f, .5f},
            .Color = {1.f, .5f, .5f}
        },
        {
            .Position = {.5f, -.5f, .5f},
            .Color = {1.f, .5f, .5f}
        },
        {
            .Position = {.5f, .5f, .5f},
            .Color = {1.f, .5f, .5f}
        },
        // right
        {
            .Position = {.5f, .5f, .5f},
            .Color = {.5f, .5f, .5f}
        },
        {
            .Position = {.5f, -.5f, .5f},
            .Color = {.5f, .5f, .5f}
        },
        {
            .Position = {.5f, -.5f, -.5f},
            .Color = {.5f, .5f, .5f}
        },
        {
            .Position = {.5f, .5f, -.5f},
            .Color = {.5f, .5f, .5f}
        },
        // back
        {
            .Position = {.5f, .5f, -.5f},
            .Color = {1.f, 1.f, .5f}
        },
        {
            .Position = {.5f, -.5f, -.5f},
            .Color = {1.f, 1.f, .5f}
        },
        {
            .Position = {-.5f, -.5f, -.5f},
            .Color = {1.f, 1.f, .5f}
        },
        {
            .Position = {-.5f, .5f, -.5f},
            .Color = {1.f, 1.f, .5f}
        },
        // left
        {
            .Position = {-.5f, .5f, -.5f},
            .Color = {.0f, .5f, .0f}
        },
        {
            .Position = {-.5f, -.5f, -.5f},
            .Color = {.0f, .5f, .0f}
        },
        {
            .Position = {-.5f, -.5f, .5f},
            .Color = {.0f, .5f, .0f}
        },
        {
            .Position = {-.5f, .5f, .5f},
            .Color = {.0f, .5f, .0f}
        },
        // top
        {
            .Position = {-.5f, .5f, -.5f},
            .Color = {.0f, 1.f, .0f}
        },
        {
            .Position = {-.5f, .5f, .5f},
            .Color = {.0f, 1.f, .0f}
        },
        {
            .Position = {.5f, .5f, .5f},
            .Color = {.0f, 1.f, .0f}
        },
        {
            .Position = {.5f, .5f, -.5f},
            .Color = {.0f, 1.f, .0f}
        },
        // bottom
        {
            .Position = {.5f, -.5f, .5f},
            .Color = {.0f, .5f, .0f}
        },
        {
            .Position = {.5f, -.5f, -.5f},
            .Color = {.0f, .5f, .0f}
        },
        {
            .Position = {-.5f, -.5f, -.5f},
            .Color = {.0f, .5f, .0f}
        },
        {
            .Position = {-.5f, -.5f, .5f},
            .Color = {.0f, .5f, .0f}
        },
    };
    static inline std::vector<uint32_t> cubeElements {
        0, 1, 3, 1, 2, 3, // front 
        4, 5, 7, 5, 6, 7, // right 
        8, 9, 11, 9, 10, 11, // back
        12, 13, 15, 13, 14, 15, // left
        16, 17, 19, 17, 18, 19, // top
        20, 21, 23, 21, 22, 23, // bottom
    };
};