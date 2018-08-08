#include "ChartView.h"
#include "src/background/BackgroundNode.h"
#include "src/background/GridNode.h"
#include "src/series/LineNode.h"

ChartView::ChartView() : m_samplesChanged(false), m_geometryChanged(false)
{
	setFlag(ItemHasContents, true);
}

int ChartView::gridSize() const { return m_gridSize; }
void ChartView::appendSample(qreal value)
{
	m_samples << value;
	m_samplesChanged = true;
	update();
}

void ChartView::removeFirstSample()
{
	m_samples.removeFirst();
	m_samplesChanged = true;
	update();
}

void ChartView::setGridSize(int gridSize)
{
	if (m_gridSize == gridSize)
	return;

	m_gridSize = gridSize;
	emit gridSizeChanged(m_gridSize);
}

void ChartView::geometryChanged(const QRectF &newGeometry,
				const QRectF &oldGeometry)
{
	m_geometryChanged = true;
	update();
	QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

class GraphNode : public QSGNode {
  public:
	BackgroundNode *background;
	GridNode *grid;
	// TODO make add and delete
	QList<LineNode *> line;
};

QSGNode *ChartView::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
	GraphNode *node = static_cast<GraphNode *>(oldNode);

	QRectF rect = boundingRect();

	if (rect.isEmpty()) {
		delete node;
		return 0;
	}

	if (!node) {
		node = new GraphNode();

		node->background = new BackgroundNode(window());
		node->grid = new GridNode();
		node->grid->setGridSize(m_gridSize);
		node->line.append(new LineNode(10, 0.5, QColor("#2196F3")));

		node->appendChildNode(node->background);
		node->appendChildNode(node->grid);
		node->appendChildNode(node->line[0]);
	}

	if (m_geometryChanged) {
		node->background->setRect(rect);
		node->grid->setRect(rect);
	}

	if (m_geometryChanged || m_samplesChanged) {
		node->line[0]->updateGeometry(rect, m_samples);
	}

	m_geometryChanged = false;
	m_samplesChanged = false;

	return node;
}
