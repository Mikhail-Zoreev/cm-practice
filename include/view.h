#pragma once

#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>

class View : public QOpenGLWidget
{
private:
    QOpenGLShaderProgram shader_program;

    GLfloat vertexes[12];
    int vertexes_location;

public:
    View(QWidget *parent = 0);
    ~View();

protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
};
