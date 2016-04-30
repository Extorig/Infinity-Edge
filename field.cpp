#include "field.h"
#include <QPainter>

Field::Field(FieldObject** objs, unsigned int width, unsigned int height, qreal objectsize)
    : width(width),height(height),objs(objs),objectsize(objectsize)
{

}

void Field::resetLevel(int easiness){
    bool firstrun=true;
    while(this->solved() || firstrun){
        for(unsigned int i = 0;i<width;i++){
            for(unsigned int j = 0;j<height;j++){
                int k = 0;
                if((rand()%1000)<easiness+100)
                while(k<rand()%4){
                    objs[i][j].rotate();
                    k++;
                }
            }
        }
        firstrun=false;
    }
}

void Field::redraw(QPainter *painter){
    for(unsigned int i = 0;i<width;i++){
        for(unsigned int j = 0;j<height;j++){
            objs[i][j].paint(painter);
        }
    }
}


void Field::clicked(unsigned int x, unsigned int y){
    x/=objectsize;
    y/=objectsize;
    if(x<width && y<height)
        objs[x][y].rotate();
}


bool Field::solved(){
    for(unsigned int i = 0;i<width;i++){
        for(unsigned int j = 0;j<height;j++){
            if(i==0 && objs[i][j].filled(LEFT)) return false;
            if(i==width-1 && objs[i][j].filled(RIGHT)) return false;
            if(j==0 && objs[i][j].filled(TOP)) return false;
            if(j==height-1 && objs[i][j].filled(BOTTOM)) return false;
            if(i>0){
                if(objs[i][j].filled(LEFT) && !objs[i-1][j].filled(RIGHT)) return false;
                if(!objs[i][j].filled(LEFT) && objs[i-1][j].filled(RIGHT)) return false;
            }
            if(i<width-1){
                if(objs[i][j].filled(RIGHT) && !objs[i+1][j].filled(LEFT)) return false;
                if(!objs[i][j].filled(RIGHT) && objs[i+1][j].filled(LEFT)) return false;
            }
            if(j>0){
                if(objs[i][j].filled(TOP) && !objs[i][j-1].filled(BOTTOM)) return false;
                if(!objs[i][j].filled(TOP) && objs[i][j-1].filled(BOTTOM)) return false;
            }
            if(j<height-1){
                if(objs[i][j].filled(BOTTOM) && !objs[i][j+1].filled(TOP)) return false;
                if(!objs[i][j].filled(BOTTOM) && objs[i][j+1].filled(TOP)) return false;
            }
        }
    }

    return true;
}
