#include<cmath>

#ifndef THREEDPOINT_H
#define THREEDPOINT_H

class threeDPoint{

    private:
        double xPoint;
        double yPoint;
        double zPoint;

    public:
        threeDPoint(double xCoord = 0,double yCoord = 0, double zCoord = 0): xPoint(xCoord), yPoint(yCoord), zPoint(zCoord) {};
        inline double x() const {return this->xPoint;};
        inline  double y() const {return this->yPoint;};
        inline double z() const {return this->zPoint;};
        void setX(double xCoord) {this->xPoint = xCoord;};
        void setY(double yCoord) {this->yPoint = yCoord;};
        void setZ(double zCoord) {this->zPoint = zCoord;}; 
        threeDPoint& operator=(const threeDPoint& other);
        threeDPoint crossProduct(const threeDPoint& other);
        double dotProduct(const threeDPoint& other);
        void normalize();
        double length();
        double angle(threeDPoint &other);
        bool isNul();

        friend threeDPoint operator * (const double c, const threeDPoint &p1);
        friend threeDPoint operator * (const threeDPoint &p1, const double c);
        friend threeDPoint operator + (const threeDPoint &p1, const threeDPoint &p2);
        friend threeDPoint operator - (const threeDPoint &p1, const threeDPoint &p2);
        friend std::ostream& operator<< (std::ostream& stream, const threeDPoint& p);
};
bool threeDPoint::isNul(){
    return (this->x() == 0 && this->y() == 0 && this->z() == 0) ? true : false;
}

double threeDPoint::angle(threeDPoint &other){
    return acos(this->dotProduct(other)/(this->length() * other.length()));
}

double threeDPoint::length(){
    return sqrt(this->x()*this->x() + this->y()*this->y() + this->z()*this->z());
}

void threeDPoint::normalize(){
    double le = this->length();

    this->setX(this->x()/le);
    this->setY(this->y()/le);
    this->setZ(this->z()/le);
}

threeDPoint operator * (const double c, const threeDPoint &p1){
    threeDPoint final;

    final.setX(p1.x() * c);
    final.setY(p1.y() * c);
    final.setZ(p1.z() * c);

    return final;
}

threeDPoint operator * (const threeDPoint &p1, const double c){
    return c * p1;
}

std::ostream& operator<< (std::ostream& stream, const threeDPoint& p){
    stream<<"("<<p.x()<<", "<<p.y()<<", "<<p.z()<<")";
    return stream;
}

threeDPoint operator - (const threeDPoint &p1, const threeDPoint &p2){
    threeDPoint final;
    final.setX(p1.x()-p2.x());
    final.setY(p1.y()-p2.y());
    final.setZ(p1.z()-p2.z());
    return final;
}

threeDPoint operator + (const threeDPoint &p1, const threeDPoint &p2){
    threeDPoint final;
    final.setX(p1.x()+p2.x());
    final.setY(p1.y()+p2.y());
    final.setZ(p1.z()+p2.z());
    return final;
}

double threeDPoint::dotProduct(const threeDPoint& other){
    return this->x()*other.x() + this->y()*other.y() + this->z()*other.z();
}

threeDPoint threeDPoint::crossProduct(const threeDPoint& other){
    threeDPoint final;
    double x,y,z;
    x = (this->y() * other.z()) - (this->z() * other.y());
    y = (other.x() * this->z()) - (other.z() * this->x());
    z = (this->x() * other.y()) - (this->y() * other.x());
    final.setX(x);
    final.setY(y);
    final.setZ(z);
    return final;
}

threeDPoint& threeDPoint::operator=(const threeDPoint& other){
    this->setX(other.x());
    this->setY(other.y());
    this->setZ(other.z());
    return *this;
}  

#endif