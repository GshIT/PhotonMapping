#include "threeDPoint.h"

#ifndef TRIMESH_H
#define TRIMESH_H

class triMesh{

    private:
        int numberOfPoint;
        int numberOfRelations;
       

    public:
        int **faceRelation;
        threeDPoint *points;
        threeDPoint *normals;
        double maxX,maxY,maxZ,minX,minY,minZ;

        triMesh(int nup = 0,threeDPoint *point = NULL, int nur = 0, int **far = NULL, threeDPoint *nor =NULL): numberOfPoint(nup),points(point),numberOfRelations(nur),faceRelation(far),maxX(-9999),maxY(-9999),maxZ(-9999),minX(9999),minY(9999),minZ(9999),normals(NULL) {};
        
        inline double numberPoint() const {return this->numberOfPoint;};
        inline  double numberFaces() const {return this->numberOfRelations;};

        void setNumberPoints(int point);
        void setNumberRelations(int relation);  
        void polygonSize(int face, int polygonNum);
        void scale(double times);
        void setMax(double x, double y, double z);
        void setMin(double x, double y, double z);
        void computeNormals();

        ~triMesh();   
};

void triMesh::setNumberPoints(int point){
    this->numberOfPoint = point;
    this->points = new threeDPoint [point];
}

void triMesh::setNumberRelations(int relation){
    this->numberOfRelations = relation;
    this->faceRelation = new int* [relation];
}

void triMesh::polygonSize(int face, int polygonNum){
    this->faceRelation[face] = new int [polygonNum+1];
    this->faceRelation[face][0] = polygonNum;
}

void triMesh::scale(double times){
    int points = this->numberOfPoint;
    for(int i=0;i<points;i++){
        this->points[i].setX(this->points[i].x()/times);
        this->points[i].setY(this->points[i].y()/times);
        this->points[i].setZ(this->points[i].z()/times);
    }
}

void triMesh::computeNormals(){
    int faces = this->numberFaces();
    threeDPoint v0,v1,v2,v0v1,v0v2,N;
    int p0,p1,p2;

    this->normals = new threeDPoint[faces];
    for(int i = 0;i<faces;i++){
        p0 = this->faceRelation[i][1];
        p1 = this->faceRelation[i][2];
        p2 = this->faceRelation[i][3];
        v0 = this->points[p0];
        v1 = this->points[p1];
        v2 = this->points[p2];
        v0v1 = v1 - v0;
        v0v2 = v2 - v0;
        N = v0v1.crossProduct(v0v2);
        N.normalize();
        this->normals[i] = N;
    }      
}

void triMesh::setMax(double x, double y, double z){
    if(this->maxX < x) this->maxX = x;
    if(this->maxY < y) this->maxY = y;
    if(this->maxZ < z) this->maxZ = z;
}

void triMesh::setMin(double x, double y, double z){
    if(this->minX > x) this->minX = x;
    if(this->minY > y) this->minY = y;
    if(this->minZ > z) this->minZ = z;
}

triMesh::~triMesh(){
    delete [] this->points;
    delete [] this->normals; 
    for(int i = 0;i < this->numberOfRelations;i++){
        delete[] this->faceRelation[i];
    }
    delete[] this->faceRelation;
    this->numberOfPoint = 0;
    this->numberOfRelations = 0;
    this->points = NULL;
    this->faceRelation = NULL;
}

#endif