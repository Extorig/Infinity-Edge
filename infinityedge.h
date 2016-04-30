#ifndef INFINITYEDGE_H
#define INFINITYEDGE_H

#include <QMainWindow>

namespace Ui {
class InfinityEdge;
}

class Field;
class FieldGenerator;
class QPainter;

class InfinityEdge : public QMainWindow
{
    Q_OBJECT

public:
    explicit InfinityEdge(QWidget *parent = 0);
    ~InfinityEdge();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_cmdGenerate_clicked();

    void on_cmdRandomize_clicked();

private:
    FieldGenerator *generator;
    bool levelGenerated;
    Field *field;
    Ui::InfinityEdge *ui;
    QPainter *painter;
};

#endif // INFINITYEDGE_H
