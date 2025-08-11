#ifndef GRAPH_MAKER_HPP
#define GRAPH_MAKER_HPP

#include <vector>
#include "MiniGL.h"

typedef struct {
    float x;
    float y;
} Vec;

typedef struct {
    std::vector<float> positive_values;
    std::vector<float> negative_values;
    Vec null_value;
    Vec origin;
    float horizontal_stretch;
    float vertical_stretch;
    float step;
    float (*func) (float value);
} Graph;

extern bool makeGrid;
extern bool showXY;
extern bool showOriginLines;
extern float maxJump;

void advance_graph(Graph& g);
void reduce_graph(Graph& g);
void render_graph(Graph g, float screenWidth, float screenHeight);
Graph make_graph(Vec null_value, Vec origin, float (*func) (float value));

#endif
