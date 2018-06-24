#include <fstream>
#include "triMesh.h"
using namespace std;


void loadData(ifstream &off, triMesh &object);
void offLoad(string file, triMesh &object);

void loadData(ifstream &off, triMesh &object){
	int numberPoints;
	int numberFaces;
	double x,y,z;
	int relation;

	off.ignore(256,'\n');  //ignore 'OFF'
	off >> numberPoints;
	object.setNumberPoints(numberPoints);
	off >> numberFaces;
	object.setNumberRelations(numberFaces);

	off >> relation; //number of edges this is ignored

	//loadpoints
	for(int i = 0;i<numberPoints;i++){
		off >> x >> y >> z;
		object.setMax(x,y,z);
		object.setMin(x,y,z);
		object.points[i].setX(x);
		object.points[i].setY(y);
		object.points[i].setZ(z);
	}

	//loadfaces
	for(int i = 0;i<numberFaces;i++){
		off >> relation;

		object.polygonSize(i,relation);

		for(int j = 1;j<=relation;j++){
			off >> y;
			object.faceRelation[i][j] = y;
		}
	}
	object.computeNormals();

}

void offLoad(string file, triMesh &object){
	ifstream off (file);
	loadData(off, object);
	off.close();
}



