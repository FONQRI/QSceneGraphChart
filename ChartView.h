#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QQuickItem>

class ChartView : public QQuickItem {
	Q_OBJECT
	Q_PROPERTY(
	int gridSize READ gridSize WRITE setGridSize NOTIFY gridSizeChanged)
  public:
	ChartView();

	int gridSize() const;

  protected:
	QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
	void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

  public slots:
	void appendSample(qreal value);
	void removeFirstSample();

	void setGridSize(int gridSize);

  signals:
	void gridSizeChanged(int gridSize);

  private:
	QList<qreal> m_samples;

	bool m_samplesChanged;
	bool m_geometryChanged;
	int m_gridSize;
};

#endif // CHARTVIEW_H
