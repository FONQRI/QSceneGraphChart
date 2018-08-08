#include "BackgroundNode.h"

#include <QtQuick/QQuickWindow>
#include <QtQuick/QSGSimpleMaterialShader>
#include <QtQuick/QSGTexture>

// internal
#include "BackgroundMaterial.h"
#include "BackgroundShader.h"

#define NOISE_SIZE 64

BackgroundNode::BackgroundNode(QQuickWindow *window)
{
	// Make some noise...
	QImage image(NOISE_SIZE, NOISE_SIZE, QImage::Format_RGB32);
	uint *data = reinterpret_cast<uint *>(image.bits());
	for (int i = 0; i < NOISE_SIZE * NOISE_SIZE; ++i) {
		uint g = rand() & 0xff;
		data[i] = 0xff000000 | (g << 16) | (g << 8) | g;
	}

	QSGTexture *t = window->createTextureFromImage(image);
	t->setFiltering(QSGTexture::Nearest);
	t->setHorizontalWrapMode(QSGTexture::Repeat);
	t->setVerticalWrapMode(QSGTexture::Repeat);

	QSGSimpleMaterial<BackgroundMaterial> *m =
	BackgroundShader::createMaterial();
	m->state()->texture = t;
	m->state()->color = QColor::fromRgbF(0.95, 0.95, 0.97);
	m->setFlag(QSGMaterial::Blending);

	setMaterial(m);
	setFlag(OwnsMaterial, true);

	QSGGeometry *g =
	new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 4);
	QSGGeometry::updateTexturedRectGeometry(g, QRect(), QRect());
	setGeometry(g);
	setFlag(OwnsGeometry, true);
}

void BackgroundNode::setRect(const QRectF &bounds)
{
	QSGGeometry::updateTexturedRectGeometry(geometry(), bounds,
						QRectF(0, 0, 1, 1));
	markDirty(QSGNode::DirtyGeometry);
}
