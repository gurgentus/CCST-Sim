#ifndef ADJUSTINGSCROLLAREA_H
#define ADJUSTINGSCROLLAREA_H

#include <QScrollArea>

class AdjustingScrollArea : public QScrollArea {
    bool eventFilter(QObject * obj, QEvent * ev) {
        if (obj == widget() && ev->type() != QEvent::Resize) {
            // Essential vvv
            setMaximumWidth(width() - viewport()->width() + widget()->width());
        }
        return QScrollArea::eventFilter(obj, ev);
    }
public:
    AdjustingScrollArea(QWidget * parent = 0) : QScrollArea(parent) {}
    void setWidget(QWidget *w) {
        QScrollArea::setWidget(w);
        // It so happens that QScrollArea already filters widget events,
        // but that's an implementation detail that we shouldn't rely on.
        w->installEventFilter(this);
    }
};

#endif // ADJUSTINGSCROLLAREA_H

