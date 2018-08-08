#ifndef LINESHADER_H
#define LINESHADER_H

#include <QtGui/QColor>

#include <QtQuick/QSGSimpleMaterial>

#include "LineMaterial.h"

class LineShader : public QSGSimpleMaterialShader<LineMaterial> {
	QSG_DECLARE_SIMPLE_SHADER(LineShader, LineMaterial)

  public:
	LineShader();

	QList<QByteArray> attributes() const;

	void updateState(const LineMaterial *m, const LineMaterial *);

	void resolveUniforms();

  private:
	int id_color;
	int id_spread;
	int id_size;
};
#endif // LINESHADER_H
