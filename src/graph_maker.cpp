#include "graph_maker.hpp"

#include <iostream>

bool makeGrid = true;
bool showXY = true;
bool showOriginLines = true;
float maxJump = 50.0f;

Graph make_graph(Vec null_value, Vec origin, float (*func)(float)) {
    return (Graph){
        {null_value.y}, {null_value.y}, null_value, origin, 1, 1, 1, func};
}

void advance_graph(Graph &g) {
    float last_positive_element =
        g.null_value.x + (g.positive_values.size() * g.step - g.step);
    float next_positive_element = last_positive_element + g.step;
    float next_positive_value = g.func(next_positive_element);

    float last_negative_element =
        g.null_value.x - (g.positive_values.size() * g.step - g.step);
    float next_negative_element = last_negative_element - g.step;
    float next_negative_value = g.func(next_negative_element);

    g.positive_values.push_back(next_positive_value);
    g.negative_values.push_back(next_negative_value);

    for (auto &w : g.positive_values) {
        std::cout << w << " ";
    }
    std::cout << std::endl;

    for (auto &w : g.negative_values) {
        std::cout << w << " ";
    }
    std::cout << std::endl;
}

void reduce_graph(Graph &g) {
    if (g.positive_values.size() > 1) {
        g.positive_values.pop_back();
    }

    if (g.negative_values.size() > 1) {
        g.negative_values.pop_back();
    }

    for (auto &w : g.positive_values) {
        std::cout << w << " ";
    }
    std::cout << std::endl;

    for (auto &w : g.negative_values) {
        std::cout << w << " ";
    }
    std::cout << std::endl;
}

void render_graph(Graph g, float screenWidth, float screenHeight) {
    for (int i = 1; i < g.positive_values.size(); i++) {
        if (std::isnan(g.positive_values[i]) ||
            std::isinf(g.positive_values[i])) {
            continue;
        }
        float current_y = -g.positive_values[i] * g.vertical_stretch;
        float last_y = -g.positive_values[i - 1] * g.vertical_stretch;
        if (fabs(current_y - last_y) > maxJump) {
            continue;
        }
        float current_X = i * (g.horizontal_stretch * g.step);
        float last_x = (i - 1) * (g.horizontal_stretch * g.step);
        MGL_drawLine(g.origin.x + current_X, g.origin.y + current_y,
                     g.origin.x + last_x, g.origin.y + last_y, 255, 255, 255);
    }
    for (int i = 1; i < g.negative_values.size(); i++) {
        if (std::isnan(g.positive_values[i]) ||
            std::isinf(g.positive_values[i])) {
            continue;
        }
        float current_y = -g.negative_values[i] * g.vertical_stretch;
        float last_y = -g.negative_values[i - 1] * g.vertical_stretch;
        if (fabs(current_y - last_y) > maxJump) {
            continue;
        }
        float current_X = i * -(g.horizontal_stretch * g.step);
        float last_x = (i - 1) * -(g.horizontal_stretch * g.step);
        MGL_drawLine(g.origin.x + current_X, g.origin.y + current_y,
                     g.origin.x + last_x, g.origin.y + last_y, 255, 255, 255);
    }

    MGL_lineWidth(0.5);

    if (makeGrid) {
        for (int i = g.origin.y; i < screenHeight; i += g.vertical_stretch) {
            MGL_drawLine(0, i, screenWidth, i, 255, 255, 255);
        }

        for (int i = g.origin.y; i > 0; i -= g.vertical_stretch) {
            MGL_drawLine(0, i, screenWidth, i, 255, 255, 255);
        }

        for (int i = g.origin.x; i < screenWidth; i += g.horizontal_stretch) {
            MGL_drawLine(i, 0, i, screenHeight, 255, 255, 255);
        }

        for (int i = g.origin.x; i > 0; i -= g.horizontal_stretch) {
            MGL_drawLine(i, 0, i, screenHeight, 255, 255, 255);
        }
    }

    if (showOriginLines) {
        MGL_drawLine(g.origin.x, 0, g.origin.x, screenHeight, 255, 255, 255);
        MGL_drawLine(0, g.origin.y, screenWidth, g.origin.y, 255, 255, 255);
    }
    if (showXY) {
        MGL_drawLine(g.origin.x, g.origin.y, g.origin.x + 200, g.origin.y, 255,
                     0, 0);
        MGL_drawLine(g.origin.x, g.origin.y, g.origin.x, g.origin.y + 200, 0,
                     255, 0);
    }
}
