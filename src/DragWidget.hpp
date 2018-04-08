#include <QWidget>
#include <QFrame>

class DragWidget : public QFrame
{
public:
    explicit DragWidget(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragEnterEvent *event) override;
    void dropEvent(QDragEnterEvent *event) override;
    void mousePressEvent(QDragEnterEvent *event) override;
};