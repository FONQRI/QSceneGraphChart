#ifndef BACKGROUNDNODE_H
#define BACKGROUNDNODE_H

#include <QQuickWindow>
#include <QSGGeometryNode>

class BackgroundNode : public QSGGeometryNode {
  public:
	BackgroundNode(QQuickWindow *window);
	void setRect(const QRectF &bounds);
};

#endif // BACKGROUNDNODE_H
