#include<iostream>
#include "include/threeDPoint.h"

using namespace std;

bool RayIntersectsTriangle(threeDPoint orig,threeDPoint dir,threeDPoint& outIntersectionPoint,threeDPoint v0,threeDPoint v1,threeDPoint v2);

int main(){
    threeDPoint v0(-1,-1,0),v1(1,-1,0),v2(0,1,0),ray(0,0,-1),origin(0,0,3),inter;
    
    if(RayIntersectsTriangle(origin,ray,inter,v0,v1,v2)){
        cout<<inter<<endl;
    }

    return 0;
}

bool RayIntersectsTriangle(threeDPoint orig,threeDPoint dir,threeDPoint& outIntersectionPoint,threeDPoint v0,threeDPoint v1,threeDPoint v2){
    const double kEpsilon = 0.0000001; 
    double det,invDet,u,v,t;

    threeDPoint v0v1 = v1 - v0; 
    threeDPoint v0v2 = v2 - v0; 

    /* BACK FACE CULLING */
    threeDPoint pvec = dir.crossProduct(v0v2); 
    det = v0v1.dotProduct(pvec); 
    if (det < kEpsilon) return false; 
    if (fabs(det) < kEpsilon) return false;
    /* END OF CULLING */

    /* BARYCENTRIC CORDINATES CALCULATION*/
    invDet = 1 / det; 
    threeDPoint tvec = orig - v0;
    u = tvec.dotProduct(pvec) * invDet; 
    if (u < 0 || u > 1) return false;
 
    threeDPoint qvec = tvec.crossProduct(v0v1); 
    v = dir.dotProduct(qvec) * invDet; 
    if (v < 0 || u + v > 1) return false;
    /* END BARYCENTRIC */
 
    double t = v0v2.dotProduct(qvec) * invDet; 
    threeDPoint point = orig + t*dir;
    outIntersectionPoint.setX(point.x());
    outIntersectionPoint.setY(point.y());
    outIntersectionPoint.setZ(point.z());
 
    return true;
}