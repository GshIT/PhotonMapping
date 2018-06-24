#include<iostream>
#include "threeDPoint.h"
#include "triMesh.h"
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<algorithm>

#include <OpenGL/gl.h>


using namespace std;

void photonTrace(int nPhotons,double pointmax,double pointmix,double pointmay,double pointmiy,double planeDist,triMesh &object);
bool RayIntersectsTriangle(threeDPoint orig,threeDPoint dir,threeDPoint& outIntersectionPoint,threeDPoint v0,threeDPoint v1,threeDPoint v2,int front);
double rnd(double pointmax, double pointmin);
threeDPoint* randPoint(double pointmax,double pointmix,double pointmay,double pointmiy,double planeDist);
double snell(double angle, double n1, double n2);
threeDPoint refract(threeDPoint &I, threeDPoint &N, double &ior);
double clamp(double n);


double clamp(double n){
	if(n < -1) return -1;
	else{
		if(n > 1) return 1;
		else return n;
	}
}

void photonTrace(int nPhotons,double pointmax,double pointmix,double pointmay,double pointmiy,double planeDist,triMesh &object){
	threeDPoint *position,direction(0,0,-1),inter,v0,v1,v2,ray,normal,dir2;
	int p0,p1,p2,faces = object.numberFaces();
	double n2 = 1.52;
	
	srand(time(NULL));

	for(int k=0;k<nPhotons;k++){
		position = randPoint(pointmax,pointmix,pointmay,pointmiy,planeDist); //photon initial point
		for(int i = 0;i<faces;i++){
			normal = object.normals[i];
			p0 = object.faceRelation[i][1];
	    	p1 = object.faceRelation[i][2];
	    	p2 = object.faceRelation[i][3];
	    	v0 = object.points[p0];
	    	v1 = object.points[p1];
	    	v2 = object.points[p2];
			if(RayIntersectsTriangle(*position,direction,inter,v0,v1,v2,-1)){

				
	    		glVertex3f(inter.x(),inter.y(),inter.z()); //debug borrar

				ray = inter - *position;
				ray.normalize();
				dir2 = refract(ray,normal,n2);
				if(!dir2.isNul()){
					for(int j = 0;j<faces;j++){
						normal = object.normals[j];
						p0 = object.faceRelation[j][1];
				    	p1 = object.faceRelation[j][2];
				    	p2 = object.faceRelation[j][3];
				    	v0 = object.points[p0];
				    	v1 = object.points[p1];
				    	v2 = object.points[p2];
						if(RayIntersectsTriangle(inter,dir2,inter,v0,v1,v2,1)){

							glVertex3f(inter.x(),inter.y(),inter.z()); //debug borrar

							ray = inter - *position;
							ray.normalize();
							dir2 = refract(ray,normal,n2);
							if(!dir2.isNul()){
								//save photon
							}
						}
					}
				}
			}
		}
		delete position;
	}
}

threeDPoint refract(threeDPoint &I, threeDPoint &N, double &ior){ 
    double cosi = clamp(I.dotProduct(N)); 
    double etai = 1, etat = ior; 
    threeDPoint n = N,nul(0,0,0); 
    if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= -1 * N; } 
    double eta = etai / etat; 
    double k = 1 - eta * eta * (1 - cosi * cosi); 
    return k < 0 ? nul : eta * I + (eta * cosi - sqrt(k)) * n; 
} 

bool RayIntersectsTriangle(threeDPoint orig,threeDPoint dir,threeDPoint& outIntersectionPoint,threeDPoint v0,threeDPoint v1,threeDPoint v2,int front){
    const double kEpsilon = 0.0000001; 
    double det,invDet,u,v,t;

    threeDPoint v0v1 = v1 - v0; 
    threeDPoint v0v2 = v2 - v0; 
    threeDPoint normal = v0v1.crossProduct(v0v2);

    /* BACK FACE CULLING */
    normal = front * normal;
    normal.normalize();
    if(normal.dotProduct(dir) < 0) return false;
    /* END OF CULLING */


    threeDPoint pvec = dir.crossProduct(v0v2); 
    det = v0v1.dotProduct(pvec);
    /* BARYCENTRIC CORDINATES CALCULATION*/
    invDet = 1 / det; 
    threeDPoint tvec = orig - v0;
    u = tvec.dotProduct(pvec) * invDet; 
    if (u < 0 || u > 1) return false;
 
    threeDPoint qvec = tvec.crossProduct(v0v1); 
    v = dir.dotProduct(qvec) * invDet; 
    if (v < 0 || u + v > 1) return false;
    /* END BARYCENTRIC */
 
    t = v0v2.dotProduct(qvec) * invDet; 
    if(t <= 0) return false;
    threeDPoint point = orig + t*dir;
    outIntersectionPoint.setX(point.x());
    outIntersectionPoint.setY(point.y());
    outIntersectionPoint.setZ(point.z());
 
    return true;
}

threeDPoint* randPoint(double pointmax,double pointmix,double pointmay,double pointmiy,double planeDist){
	threeDPoint* point;
	point = new threeDPoint;
	point->setX(rnd(pointmax,pointmix));
	point->setY(rnd(pointmay,pointmiy));
	point->setZ(planeDist);
	return point;
}

double rnd(double pointmax, double pointmin){
	double value,scale = pointmin;
	double mult = pointmax-pointmin;
	value = (double)rand()/RAND_MAX;
	value = (value * mult)+scale;
	return value;
}