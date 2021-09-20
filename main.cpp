/**
 * @file main.cpp
 *
 * @brief main function of glyph benchmark
 *
 * @author Daniel Xavier Silva
 * Contact: danielxaviers@gmail.com
 *
 */

//#include <GL/glew.h>
#include <QGuiApplication>
#include "window.h"


int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);
  // Set OpenGL Version information
  // Note: This format must be set before show() is called.
  QSurfaceFormat format;
  format.setRenderableType(QSurfaceFormat::OpenGL);
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setDepthBufferSize(24);
  //format.setProfile(QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile);
  QSurfaceFormat::setDefaultFormat(format);
  format.setVersion(4,0);
  format.setSwapInterval(0);

  // Set the window up
  Window window;
//  window.setDefaultParameters();
  if(argc == 1) {
      std::cout << "Benchmark Not Enabled. Visualization Only. For Benchmark usage:" << std::endl;
      std::cout << "[1]: Icosahedron order: 0,1,2,3,4 stands for (1, 2, 4, 8, 16) tesselation order" << std::endl;
      std::cout << "[2]: Performance benchmark mode: 0,1,2,3,4 stands for the added functionalities (Indexing, Instancing, Symmetry, Coalescent lookup, MultiResolution)" << std::endl;
      std::cout << "[3] (optional): Path for output data file:" << std::endl;
  } else if(argc == 2) {
      window.setIcosahedronIterations(atoi(argv[1]));
       std::cout << "Benchmark Not Enabled. Visualization Only. For Benchmark usage:" << std::endl;
       std::cout << "[1]: Icosahedron order: 0, 1, 2, 3, 4 stands for tesselation order (1, 2, 4, 8, 16) of the icosahedron" << std::endl;
        std::cout << "[2]: Performance benchmark mode: 0,1,2,3,4 stands for the added functionalities (Indexing, Instancing, Symmetry, Coalescent lookup, MultiResolution)" << std::endl;
       std::cout << "[3] (optional): Path for output data file:" << std::endl;
  } else if(argc == 3) {
      window.setIcosahedronIterations(atoi(argv[1]));
      window.setbenchmarkCategory(atoi(argv[2]));
       std::cout << "Benchmark Not Enabled. Visualization Only. For Benchmark usage:" << std::endl;
       std::cout << "[1]: Icosahedron order: 0, 1, 2,3, 4 stands for tesselation order (1, 2, 4, 8, 16) of the icosahedron" << std::endl;
        std::cout << "[2]: Performance benchmark mode: 0,1,2,3,4 stands for the added functionalities (Indexing, Instancing, Symmetry, Coalescent lookup, MultiResolution)" << std::endl;
       std::cout << "[3] (optional): Path for output data file:" << std::endl;
  }
  else if(argc == 4) {
        window.setIcosahedronIterations(atoi(argv[1]));
        window.setbenchmarkCategory(atoi(argv[2]));
        window.setPath(std::string(argv[3]));
        std::cout << "Benchmark Enabled." << std::endl;
        std::cout << "For Modes 0, 1, 2, 3: glyphs will be drawn from 25 to 10000, 100 times." << std::endl;
        std::cout << "For Modes 4: 105^2 glyphs rendered and a scaling factor will zoom gradually the scene to 21x. The image is rendered 100 times." << std::endl;
        //std::cout << "The file generated is | #glyphs | time taken to draw in us|" << std::endl;
    }

  window.setFormat(format);
  //The resolution of resize on mac's with retina screens (where the benchmark was done) is doubled the size
  window.resize(QSize(600, 600));
  window.show();

  return app.exec();
}
