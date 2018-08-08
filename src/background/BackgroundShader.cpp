#include "BackgroundShader.h"

BackgroundShader::BackgroundShader()
	: id_color(-1), id_texture(-1), id_textureSize(-1)
{
	setShaderSourceFile(QOpenGLShader::Vertex, ":/shaders/noisy.vsh");
	setShaderSourceFile(QOpenGLShader::Fragment, ":/shaders/noisy.fsh");
}

QList<QByteArray> BackgroundShader::attributes() const
{
	return QList<QByteArray>() << "aVertex"
				   << "aTexCoord";
}

void BackgroundShader::updateState(const BackgroundMaterial *m,
				   const BackgroundMaterial *)
{

	// Set the color
	program()->setUniformValue(id_color, m->color);

	// Bind the texture and set program to use texture unit 0 (the default)
	m->texture->bind();

	// Then set the texture size so we can adjust the texture coordinates
	// accordingly in the
	// vertex shader..
	QSize s = m->texture->textureSize();
	program()->setUniformValue(id_textureSize,
				   QSizeF(1.0 / s.width(), 1.0 / s.height()));
}

void BackgroundShader::resolveUniforms()
{
	id_texture = program()->uniformLocation("texture");
	id_textureSize = program()->uniformLocation("textureSize");
	id_color = program()->uniformLocation("color");

	// We will only use texture unit 0, so set it only once.
	program()->setUniformValue(id_texture, 0);
}
