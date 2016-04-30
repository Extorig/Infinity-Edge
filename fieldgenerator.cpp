#include "fieldgenerator.h"
#include <QPainter>
#include <QTime>
#include <iostream>
#include <random>
#include <chrono>

FieldGenerator::FieldGenerator(QObject *parent)
    : QObject(parent)
{

}


Field *FieldGenerator::generateLevel(qreal objsize, int width, int height, QMap<FieldType, qreal> probabilities){

    FieldObject **objs = (FieldObject**)malloc(sizeof(FieldObject*)*width);
    for(int i = 0;i<width;i++){
        objs[i] = (FieldObject*)malloc(sizeof(FieldObject)*height);
    }

    for(int i = 0;i<width;i++){
        for(int j = 0;j<height;j++){
            objs[i][j] = FieldObject();
        }
    }

    QVector<FieldType> possibles;
    QVector<qreal> probs;

    std::mt19937_64 rng;
    // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    std::uniform_real_distribution<double> unif(0, 1);

    QVector<Side> tobe;
    QVector<Side> nottobe;


    for(int i = 0;i<width;i++){
        for(int j = 0;j<height;j++){

            tobe.clear();
            nottobe.clear();
            possibles.clear();
            probs.clear();

            if(i==0)nottobe.append(LEFT);
            else{
                if(objs[i-1][j].initialized()){
                    if(objs[i-1][j].filled(RIGHT))
                        tobe.append(LEFT);
                    else
                        nottobe.append(LEFT);
                }
            }

            if(i==width-1)nottobe.append(RIGHT);
            else{
                if(objs[i+1][j].initialized()){
                    if(objs[i+1][j].filled(LEFT))
                        tobe.append(RIGHT);
                    else
                        nottobe.append(RIGHT);
                }
            }

            if(j==0)nottobe.append(TOP);
            else{
                if(objs[i][j-1].initialized()){
                    if(objs[i][j-1].filled(BOTTOM))
                        tobe.append(TOP);
                    else
                        nottobe.append(TOP);
                }
            }

            if(j==height-1)nottobe.append(BOTTOM);
            else{
                if(objs[i][j+1].initialized()){
                    if(objs[i][j+1].filled(TOP))
                        tobe.append(BOTTOM);
                    else
                        nottobe.append(BOTTOM);
                }
            }


            foreach(FieldType type, probabilities.keys()){
                if(FieldObject::isPossible(tobe,nottobe,type)){
                    possibles.append(type);
                    probs.append(probabilities.find(type).value());
                }
            }
            qreal sum = 0;
            foreach(qreal prob, probs) sum+=prob;
            for(int n = 0;n<probs.count();n++)
                probs[n]/=sum;

            qreal val = unif(rng);
            for(int n = 0;n<probs.count();n++){
                if(probs[n]>val){
                    objs[i][j].init(possibles[n],QRectF(i*objsize,j*objsize,objsize,objsize));
                    break;
                }
                val-=probs[n];
            }

        }
    }


    return new Field(objs,width,height,objsize);
}
