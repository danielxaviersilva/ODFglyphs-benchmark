#include "window.h"
#include <iostream>


Window::Window()
{
    //CONSTANTS
    m_IcosahedronIterations = 2;
    m_isRenderingInstanced = true;
    m_isRenderingHemispherical = true;
    m_isTextureOptimized = true;
    m_benchmarkMaxSamplesAmount = 10001;
    m_executionsAmount = 100;
    m_step = 5;
    m_writingEnabled = false;
    m_path = "./";
    m_isResolutionSet = false;
    m_isCategorySet = false;
    m_isPathSet = false;

    //INITIAL Values PARAMETERS
    m_rows = 5;

}

Window::~Window()
{
  makeCurrent();
  teardownGL();
}

/*******************************************************************************
 * OpenGL Events
 ******************************************************************************/
void Window::initializeGL()
{

    m_odfSamplesAmount = m_rows*m_rows;
    m_counter = 0;
    m_indexAmount = m_odfSamplesAmount;
    m_glyphsIndex.resize(m_indexAmount);
    std::iota (std::begin(m_glyphsIndex), std::end(m_glyphsIndex), 0);


    initializeOpenGLFunctions();

    if(m_isResolutionSet && m_isCategorySet && m_isPathSet) {
        m_writingEnabled = true;
    }

    if (m_isRenderingInstanced) {
         if (m_isRenderingHemispherical) {
            m_odfSampleSet = new ODFSamplesHemisphere(m_odfSamplesAmount, m_IcosahedronIterations);
            if(m_isTextureOptimized) {
                m_odfSampleSetRenderer = new ODFRendererInstancedSymmetricCoalescent();
                m_file.setFileName(QString::fromStdString(m_path + "/InstancedSymmetricCoalescent_V" + std::to_string(m_odfSampleSet->getBaseDirections().size()) + ".txt"));
            } else {
                m_odfSampleSetRenderer = new ODFRendererInstancedSymmetric();
                m_file.setFileName(QString::fromStdString(m_path + "/InstancedSymmetric_V" + std::to_string(m_odfSampleSet->getBaseDirections().size()) + ".txt"));
            }
        } else {
                m_odfSampleSet = new ODFSamples(m_odfSamplesAmount, m_IcosahedronIterations);
                m_odfSampleSetRenderer = new ODFRendererInstanced();
                m_file.setFileName(QString::fromStdString(m_path + "/Instanced_V" + std::to_string(m_odfSampleSet->getBaseDirections().size()) + ".txt"));
        }
    } else {
        m_odfSampleSet = new ODFSamples(m_odfSamplesAmount, m_IcosahedronIterations);
        m_odfSampleSetRenderer = new ODFRenderer();
        m_file.setFileName(QString::fromStdString(m_path + "/Standard_V" + std::to_string(m_odfSampleSet->getBaseDirections().size()) + ".txt"));
    }

    if( m_writingEnabled ){
        std::cout << "Benchmark file: " << m_file.fileName().toStdString() << std::endl;
        m_file.open(QIODevice::WriteOnly | QIODevice::Text);
    }
    m_odfSampleSet->computeODFs();
    m_odfSampleSetRenderer->initialize(m_odfSampleSet);
    resizeGL(this->width(), this->height());
    m_startTimePoint = std::chrono::high_resolution_clock::now();
}



void Window::paintGL()
{

    draw();
    update();

    if(m_counter == m_executionsAmount && m_writingEnabled) {
        updateBenchmarkParameters();
        m_startTimePoint = std::chrono::high_resolution_clock::now();
        return;
    }
    m_counter++;

    m_endTimePoint = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(m_endTimePoint).time_since_epoch().count();
    auto duration = end - start;
    if ( m_writingEnabled ) {
        QTextStream out(&m_file);
        out << m_glyphsIndex.size() << ", " << duration << "\n";
    }

//    std::cout << m_glyphsIndex.size() << ", " << duration << std::endl;
    m_startTimePoint = std::chrono::high_resolution_clock::now();

}

void Window::teardownGL()
{
    glUseProgram(0);
    exit(0);
}
void Window::viewPort()
{
    if(m_currentWidth < m_currentHeight)
        glViewport(0, (m_currentHeight-m_currentWidth)/2, m_currentWidth, m_currentWidth);
    else
        glViewport((m_currentWidth-m_currentHeight)/2, 0, m_currentHeight, m_currentHeight);

}

void Window::updateBenchmarkParameters()
{
    delete m_odfSampleSet;
    delete m_odfSampleSetRenderer;
    m_rows +=m_step;
    m_odfSamplesAmount = m_rows*m_rows;
    m_counter = 0;
    m_indexAmount = m_odfSamplesAmount;
    m_glyphsIndex.resize(m_indexAmount);
    std::iota (std::begin(m_glyphsIndex), std::end(m_glyphsIndex), 0);

    if ( m_odfSamplesAmount > m_benchmarkMaxSamplesAmount ) {
        std::cout << "BENCHMARK FINISHED!" << std::endl;
        exit(0);
    }
    if (m_isRenderingInstanced) {
       if (m_isRenderingHemispherical) {
            m_odfSampleSet = new ODFSamplesHemisphere(m_odfSamplesAmount, m_IcosahedronIterations);
            if(m_isTextureOptimized) {
                m_odfSampleSetRenderer = new ODFRendererInstancedSymmetricCoalescent();
            } else {
                m_odfSampleSetRenderer = new ODFRendererInstancedSymmetric();
            }
       } else {
            m_odfSampleSet = new ODFSamples(m_odfSamplesAmount, m_IcosahedronIterations);
            m_odfSampleSetRenderer = new ODFRendererInstanced();
       }
    } else {
            m_odfSampleSet = new ODFSamples(m_odfSamplesAmount, m_IcosahedronIterations);
            m_odfSampleSetRenderer = new ODFRenderer();
    }
    m_odfSampleSet->computeODFs();
    m_odfSampleSetRenderer->initialize(m_odfSampleSet);

}

void Window::setPath(const std::string &path)
{
    m_path = path;
    m_isPathSet = true;
}

void Window::setIcosahedronIterations(unsigned int IcosahedronIterations)
{
    m_IcosahedronIterations = IcosahedronIterations;
    m_isResolutionSet = true;
}

void Window::setbenchmarkCategory(int benchmarkCategory)
{
    if(benchmarkCategory == 0) {
        m_isRenderingInstanced = m_isRenderingHemispherical = m_isTextureOptimized = false;
    } else if(benchmarkCategory == 1) {
        m_isRenderingInstanced = true;
        m_isRenderingHemispherical = false;
        m_isTextureOptimized = false;
    } else if(benchmarkCategory == 2) {
        m_isRenderingInstanced = true;
        m_isRenderingHemispherical = true;
        m_isTextureOptimized = false;
    } else if(benchmarkCategory == 3) {
        m_isRenderingInstanced = true;
        m_isRenderingHemispherical = true;
        m_isTextureOptimized = true;
    }

    m_isCategorySet = true;
}

/*******************************************************************************
 * Private Helpers
 ******************************************************************************/

void Window::printContextInformation()
{
  QString glType;
  QString glVersion;
  QString glProfile;

  // Get Version Information
  glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
  glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

//  std::cout << glVersion.toStdString()  << std::endl;
  // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
  switch (format().profile())
  {
    CASE(NoProfile);
    CASE(CoreProfile);
    CASE(CompatibilityProfile);
  }
#undef CASE

  // qPrintable() will print our QString w/o quotes around it.
  qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}

void Window::keyPressEvent(QKeyEvent *event)
{

    float angle = 1.5f;
    switch(event->key())
    {
        case Qt::Key_Left: //std::cout << "Tecla esquerda" << std::endl;
        m_camera.walkAround(glm::vec3(1.0,0.0,0.0));
        break;

        case Qt::Key_Right: //std::cout << "Tecla Direita" << std::endl;
        m_camera.walkAround(glm::vec3(-1.0,0.0,0.0));
        break;

        case Qt::Key_Up: //std::cout << "Tecla Cima" << std::endl;
        m_camera.walkAround(glm::vec3(0.0,1.0,0.0));
        break;

        case Qt::Key_Down: //std::cout << "Tecla baixo" << std::endl;
        m_camera.walkAround(glm::vec3(0.0,-1.0,0.0));
        break;

        case Qt::Key_Plus: //std::cout << "Tecla +" << std::endl;
        m_camera.zoomCommand(1.0);
        break;

        case Qt::Key_Minus: //std::cout << "Tecla -" << std::endl;
        m_camera.zoomCommand(-1.0);
         break;

        case Qt::Key_D: //std::cout << "Tecla D" << std::endl;
        m_camera.rotateObserver(glm::vec3(0.0f,1.0f,0.0f), angle);
         break;

        case Qt::Key_A: //std::cout << "Tecla A" << std::endl;
        m_camera.rotateObserver(glm::vec3(0.0f,-1.0f,0.0f), angle);
         break;

    case Qt::Key_W: //std::cout << "Tecla W" << std::endl;
    m_camera.rotateObserver(glm::vec3(-1.0f,0.0f,0.0f), angle);
     break;

    case Qt::Key_S: //std::cout << "Tecla S" << std::endl;
    m_camera.rotateObserver(glm::vec3(1.0f,0.0f,0.0f), angle);
     break;

    case Qt::Key_J: //std::cout << "Tecla J" << std::endl;
    m_camera.rotateObserver(glm::vec3(0.0f,0.0f,-1.0f), angle);
     break;

    case Qt::Key_K: //std::cout << "Tecla K" << std::endl;
    m_camera.rotateObserver(glm::vec3(0.0f,0.0f,1.0f), angle);
     break;

    case Qt::Key_R: //std::cout << "Tecla R" << std::endl;
    m_camera.resetCamera();
     break;

    case Qt::Key_G:
     break;
    }
    m_odfSampleSetRenderer->setProjectionMatrix(m_camera.projection());
    m_odfSampleSetRenderer->setMVMatrix(m_camera.view());
    draw();

//    renderCrossLine();



}


void Window::resizeGL(int width, int height)
{
    m_currentWidth = QPaintDevice::devicePixelRatio()*width;
    m_currentHeight = QPaintDevice::devicePixelRatio()*height;
//    std::cout << "(m_currentWidth , m_currentHeight): (" << m_currentWidth << " , " << m_currentHeight << ")" << std::endl;
    viewPort();
    draw();


}

void Window::draw()
{
    viewPort();
    const float bg[] = {1.0f,
                  1.0f,
                  1.0f,1.0f};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearBufferfv(GL_COLOR, 0, bg);
    //Timer - begin
//    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint = std::chrono::high_resolution_clock::now();
    //
    m_odfSampleSetRenderer->render(m_glyphsIndex);
    //
    //Timer - end
}

//int i = 0;
//void Window::voidmouseMoveEvent(QM    ouseEvent *ev)
//{
//    std::cout << "Alguem arrastou o mouse? " << i++ << std::endl;
//}

//void Window::mousePressEvent(QMouseEvent *ev)
//{
//    std::cout << "Alguem mexeu no mouse? " << i++ << std::endl;
//}

//void Window::moveEvent(QMoveEvent *ev)
//{
//    std::cout << "Alguem arrastou o mouse? " << i++ << std::endl;
//}
