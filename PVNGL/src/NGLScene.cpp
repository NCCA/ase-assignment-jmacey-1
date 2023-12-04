#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <iostream>
#include "PointVizReader.h"
#include <ngl/ShaderLib.h>
#include <ngl/Util.h>
#include <ngl/SimpleVAO.h>
#include <ngl/VAOFactory.h>

NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("PV NGL");
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
  m_project = ngl::perspective(45.0f,float(_w)/_h,0.1f,2000.0f);
}


void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::initialize();
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
  m_pv=std::make_unique<pv::PointVizReader>("pvfiles/Particle.csv");
  m_pv->parse();
  m_pv->print();

  ngl::ShaderLib::loadShader("PVShader","shaders/PVVertex.glsl","shaders/PVFragment.glsl");
  m_view    = ngl::lookAt({0,20,20},{0,0,0},{0,1,0});
  m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_POINTS);
    loadFrame(m_frame);
}

void NGLScene::loadFrame(int _frame)
{
    //m_pv
    std::vector<ngl::Vec3> points;
    auto frame=m_pv->getFrame(_frame);
    for(auto p : frame->m_frameData)
    {
        auto x= p[0];
        auto y= p[1];
        auto z= p[2];
        points.push_back(ngl::Vec3(std::get<float>(x),std::get<float>(y),std::get<float>(z)));
    }
    m_vao->bind();
    m_vao->setData(ngl::SimpleVAO::VertexData(points.size()*sizeof(ngl::Vec3),points[0].m_x));
    m_vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);
    m_vao->setNumIndices(points.size());
    m_vao->unbind();
}

void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);
  ngl::ShaderLib::use("PVShader");
  ngl::ShaderLib::setUniform("MVP",m_project*m_view);
  glPointSize(5);
  m_vao->bind();
  m_vao->draw();
  m_vao->unbind();
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      m_modelPos.set(ngl::Vec3::zero());

  break;
  case Qt::Key_1 : m_frame-=1;
          loadFrame(m_frame);
          break;
  case Qt::Key_2 : m_frame+=1;
          loadFrame(m_frame);
          break;


  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}
