#include "infinityedge.h"
#include "ui_infinityedge.h"
#include <QPainter>
#include <QMouseEvent>
#include "field.h"
#include "fieldgenerator.h"
#include <QMessageBox>

InfinityEdge::InfinityEdge(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InfinityEdge)
{
    ui->setupUi(this);
    levelGenerated = false;
    generator = new FieldGenerator();
    field = NULL;
    on_cmdGenerate_clicked();
}

InfinityEdge::~InfinityEdge()
{
    delete ui;
}

void InfinityEdge::on_cmdGenerate_clicked()
{
    QMap<FieldType,qreal> probs;
    probs.insert(EMPTY,ui->slidEmpty->value());
    probs.insert(TEND,ui->slidEnd->value());
    probs.insert(BEND,ui->slidEnd->value());
    probs.insert(REND,ui->slidEnd->value());
    probs.insert(LEND,ui->slidEnd->value());
    probs.insert(RTC,ui->slidCorners->value());
    probs.insert(LTC,ui->slidCorners->value());
    probs.insert(RBC,ui->slidCorners->value());
    probs.insert(LBC,ui->slidCorners->value());
    probs.insert(TT,ui->slidTriangles->value());
    probs.insert(TB,ui->slidTriangles->value());
    probs.insert(TR,ui->slidTriangles->value());
    probs.insert(TL,ui->slidTriangles->value());
    probs.insert(TBCROSS,ui->slidCross->value());
    probs.insert(TRCROSS,ui->slidCross->value());
    probs.insert(TLCROSS,ui->slidCross->value());
    probs.insert(HLINE,ui->slidLine->value());
    probs.insert(VLINE,ui->slidLine->value());
    bool ok = true;
    unsigned int width = ui->txtWidth->text().toInt(&ok);
    if(!ok)width=7;
    else
        if(width>70)width=70;
    ok=true;
    unsigned int height = ui->txtHeight->text().toInt(&ok);
    if(!ok)height=7;
    else
        if(height>70)height=70;
    field = generator->generateLevel(std::min(30.,std::min(460./width,360./height)),width,height,probs);
    levelGenerated = false;

    if(ui->chkRand->isChecked()){
        unsigned int easiness = ui->slidRand->value();
        field->resetLevel(easiness);
        levelGenerated = true;
    }

    this->repaint();
}

void InfinityEdge::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));

    if(field!=NULL){
        field->redraw(&painter);
    }
}


void InfinityEdge::mousePressEvent(QMouseEvent *event)
{
    if(levelGenerated){
        if(event->button()==Qt::LeftButton)
        {
            field->clicked(event->x(),event->y());
            repaint();
            if(field->solved()){
                QMessageBox msg;
                msg.setText("Solved!");
                msg.exec();
                levelGenerated=false;
            }
        }
    }


}

void InfinityEdge::on_cmdRandomize_clicked()
{
    unsigned int easiness = ui->slidRand->value();
    field->resetLevel(easiness);
    levelGenerated=true;
    this->repaint();
}
