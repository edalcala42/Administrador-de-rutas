#include "arrowline.h"

ArrowLine::ArrowLine(QPoint s, QPoint e)
{
a=s;
b=e;
}

void ArrowLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
DrawLineWithArrow(painter,a,b);
}
void ArrowLine::DrawLineWithArrow(QPainter* painter, QPoint start, QPoint end) {
  painter->setRenderHint(QPainter::Antialiasing, true);
  qreal arrowSize = 40; // size of head
  painter->setPen(Qt::black);
  painter->setBrush(Qt::black);
  QLineF line(end, start);
  ouble angle = std::atan2(-line.dy(), line.dx());
  QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
  QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);
  QPolygonF arrowHead;
  arrowHead.clear();
  arrowHead << line.p1() << arrowP1 << arrowP2;
  painter->drawLine(line);
  painter->drawPolygon(arrowHead);
}

