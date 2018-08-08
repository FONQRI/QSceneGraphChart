#ifndef GRIDNODE_H
#define GRIDNODE_H

#include <QtQuick/QSGFlatColorMaterial>
#include <QtQuick/QSGGeometryNode>

class GridNode : public QSGGeometryNode {
  public:
	GridNode();

	void setRect(const QRectF &rect);

	int gridSize() const;
	void setGridSize(int gridSize);

  private:
	QSGFlatColorMaterial m_material;
	QSGGeometry m_geometry;
	int m_gridSize;
};

#endif // GRIDNODE_H
