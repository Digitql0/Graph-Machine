#include "MiniGL.h"
#include "graph_maker.hpp"

float quadratic_function(float x) { return tan(x); }

int main() {
  int screenWidth = 1920;
  int screenHeight = 1080;
  float x = 0;
  float y = 0;

  Graph myGraph = make_graph({x, quadratic_function(x)},
                             {(float)screenWidth / 2, (float)screenHeight / 2},
                             quadratic_function);
  myGraph.horizontal_stretch = 10;
  myGraph.vertical_stretch = 50;
  myGraph.step = 0.01;

  MGL_makeWindow(screenWidth, screenHeight, "Graph Maker");
  MGL_lineWidth(3);

  makeGrid = false;
  showXY = false;
  showOriginLines = false;

  while (!MGL_windowShouldClose()) {
    MGL_beginDrawing();
    MGL_clearBackground(0, 0, 255 / 4);

    render_graph(myGraph, screenWidth, screenHeight);

    if (MGL_isKeyPressed(GLFW_KEY_RIGHT)) {
      advance_graph(myGraph);
      std::cout << "Advanced" << std::endl;
    }

    if (MGL_isKeyPressed(GLFW_KEY_LEFT)) {
      reduce_graph(myGraph);
      std::cout << "Reduced" << std::endl;
    }

    if (MGL_isKeyPressed(GLFW_KEY_SPACE)) {
      for (int i = 0; i < 1000; i++) {
        advance_graph(myGraph);
      }
    }

    if (MGL_isKeyPressed(GLFW_KEY_S)) {
      y++;
    }

    MGL_drawLine(0, y, screenWidth, y, 255, 255, 255);
    MGL_endDrawing();
  }

  MGL_closeWindow();
}
