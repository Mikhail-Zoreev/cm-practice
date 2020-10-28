#include "view.h"

View::View(QWidget *parent)
{
    vertexes[0] = -1;
    vertexes[1] = -1;
    vertexes[2] = 0;

    vertexes[3] = 1;
    vertexes[4] = -1;
    vertexes[5] = 0;

    vertexes[6] = 1;
    vertexes[7] = 1;
    vertexes[8] = 0;

    vertexes[9] = -1;
    vertexes[10] = 1;
    vertexes[11] = 0;
}

View::~View()
{

}

void View::initializeGL()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);

    QOpenGLShader vertex_shader(QOpenGLShader::Vertex);
    vertex_shader.compileSourceFile("shaders/shader.vert");

    QOpenGLShader fragment_shader(QOpenGLShader::Fragment);
    fragment_shader.compileSourceFile("shaders/shader.frag");

    shader_program.addShader(&vertex_shader);
    shader_program.addShader(&fragment_shader);
    if (!shader_program.link())
    {
        return;
    }

    vertexes_location = shader_program.attributeLocation("vertex");

    QOpenGLFunctions_4_3_Core *functions = QOpenGLContext().versionFunctions<QOpenGLFunctions_4_3_Core>();
}

void View::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
}

void View::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!shader_program.bind())
    {
        return;
    }

    shader_program.enableAttributeArray(vertexes_location);
    shader_program.setAttributeArray(vertexes_location, vertexes, 3);

    glDrawArrays(GL_QUADS, 0, 4);

    shader_program.disableAttributeArray(vertexes_location);

    shader_program.release();
}
