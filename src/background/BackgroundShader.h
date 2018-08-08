#ifndef BACKGROUNDSHADER_H
#define BACKGROUNDSHADER_H

#include "BackgroundMaterial.h"

class BackgroundShader : public QSGSimpleMaterialShader<BackgroundMaterial> {
	QSG_DECLARE_SIMPLE_SHADER(BackgroundShader, BackgroundMaterial)

  public:
	BackgroundShader();

	QList<QByteArray> attributes() const;

	void updateState(const BackgroundMaterial *m, const BackgroundMaterial *);

	void resolveUniforms();

  private:
	int id_color;
	int id_texture;
	int id_textureSize;
};
#endif // BACKGROUNDSHADER_H
