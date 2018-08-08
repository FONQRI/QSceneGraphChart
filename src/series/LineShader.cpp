#include "LineShader.h"

LineShader::LineShader() : id_color(-1), id_spread(-1), id_size(-1)
{
	setShaderSourceFile(QOpenGLShader::Vertex, ":/shaders/line.vsh");
	setShaderSourceFile(QOpenGLShader::Fragment, ":/shaders/line.fsh");
}

QList<QByteArray> LineShader::attributes() const
{
	return QList<QByteArray>() << "pos"
				   << "t";
}

void LineShader::updateState(const LineMaterial *m, const LineMaterial *)
{
	program()->setUniformValue(id_color, m->color);
	program()->setUniformValue(id_spread, m->spread);
	program()->setUniformValue(id_size, m->size);
}

void LineShader::resolveUniforms()
{
	id_spread = program()->uniformLocation("spread");
	id_size = program()->uniformLocation("size");
	id_color = program()->uniformLocation("color");
}
