#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

//实现一个可以点击的QLabel
class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
    ~ClickableLabel();

private:
    void setPaletteDefault();
    void setPalettePressed();

signals:
    void clicked();
    void pressed();
    void released();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

};

#endif // CLICKABLELABEL_H
