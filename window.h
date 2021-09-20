/**
 * @file window.h
 *
 * @brief This class represents the window where the glyphs are displayed and benchmarked
 *
 * @author Daniel Xavier Silva
 * Contact: danielxaviers@gmail.com
 *
 */

#ifndef WINDOW_H
#define WINDOW_H
//#include <GL/glew.h>
#include <QOpenGLWindow>
#include <QDebug>
#include <QKeyEvent>
#include "./Utilities/Camera.h"
#include <chrono>

#include "Models/ODFSamples.h"
#include "Models/ODFSamplesHemisphere.h"


#include "Models/Visualization/ODFRendererInstanced.h"
#include "Models/Visualization/ODFRendererInstancedSymmetric.h"
#include "Models/Visualization/ODFRendererInstancedSymmetricCoalescent.h"
#include "Models/Visualization/ODFRendererMultiResolution.h"
#include "Models/Visualization/ODFRendererOnDemand.h"
#include "Models/Visualization/ODFRenderer.h"

#include <string>

class QOpenGLShaderProgram;

class Window : public QOpenGLWindow
             , protected QOpenGLFunctions
{
  Q_OBJECT

// OpenGL Events
public:
//    Window( int icosahedronIterations = 4,
//            bool benchmarkEnabled = false,
//           int benchmarkCategory = 3,
//            std::string path = "./");
//    void setDefaultParameters();
  ~Window();
   Window();

  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;
  inline void draw();
  void teardownGL();

  void setIcosahedronIterations(unsigned int IcosahedronIterations);
  void setbenchmarkCategory(int benchmarkCategory);

  void setPath(const std::string &path);

private:
  Camera m_camera;
  int m_currentWidth, m_currentHeight;

  void viewPort();

  void updateBenchmarkParameters();


  unsigned int m_odfSamplesAmount;
  std::string m_path;

  ODFSamples *m_odfSampleSet;
  ODFRendererInstanced *m_odfSampleSetRenderer;


  std::vector<unsigned int> m_glyphsIndex;
  unsigned int m_counter;
  unsigned int m_executionsAmount;
  unsigned int m_indexAmount;
  unsigned int m_step;
  unsigned int m_rows;
  unsigned int m_benchmarkMaxSamplesAmount;
  unsigned int m_IcosahedronIterations;


  unsigned int m_glyphsAmount;
  unsigned int m_currentMaxPixels;
  unsigned int m_currentResolution;

  unsigned int m_measurements;

  bool m_isResolutionSet;
  bool m_isCategorySet;
  bool m_isPathSet;

  bool m_isMultiResolution;
  bool m_isRenderingInstanced;
  bool m_isRenderingHemispherical;
  bool m_isTextureOptimized;
  bool m_writingEnabled;

  float m_sceneScaleFactor;
  float m_scaleFactorVariationConstant;

  QFile m_file;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint, m_endTimePoint;

  // Private Helpers
  void printContextInformation();
protected:
//  void mousePressEvent(QMouseEvent *ev);
//  void moveEvent(QMoveEvent *ev);
//     void voidmouseMoveEvent(QMouseEvent *ev);
  void keyPressEvent(QKeyEvent *event) override;
//  void screenChanged(QScreen* event) override;
//  void keyReleaseEvent(QKeyEvent *event);
//  void mousePressEvent(QMouseEvent *event);
//  void mouseReleaseEvent(QMouseEvent *event);
};

#endif // WINDOW_H
