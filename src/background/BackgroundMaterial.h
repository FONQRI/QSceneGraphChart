#ifndef BACKGROUNDMATERIAL_H
#define BACKGROUNDMATERIAL_H

#include <QtQuick/QSGSimpleMaterialShader>
#include <QtQuick/QSGTexture>

struct BackgroundMaterial {
	~BackgroundMaterial() { delete texture; }

	QColor color;
	QSGTexture *texture;
};

#endif // BACKGROUNDMATERIAL_H
