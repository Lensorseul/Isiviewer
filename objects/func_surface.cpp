#include "func_surface.h"
#include <math.h>


#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

FuncSurface::FuncSurface(int nbx, int nby, float minx, float maxx, float miny, float maxy,float (*pointer1)(float,float)):TriMesh()
{
    _name = "FuncSurface";

    vector<vector<GLfloat> > points;
    vector<GLfloat> atp;

    vector<vector<GLint> > droite;
    vector<GLint> atd;

    float pasx,pasy,distx,disty;
    distx=(float)(maxx-minx);
    disty=(float)(maxy-miny);
    pasx=(float)distx/(nbx);
    pasy=(float)disty/(nby);


    for(float i=minx; i<=maxx; i+=pasx)
    {
        for(float j=miny; j<=maxy; j+=pasy)
        {
            atp.push_back(i/(distx/2));
            atp.push_back(j/(disty/2));
            atp.push_back((*pointer1)(i,j));
            points.push_back(atp);
            atp.clear();
            atd.push_back(points.size()-1);
        }
        droite.push_back(atd);
        atd.clear();
    }


    vector<vector<GLint> > triangles;
    vector<GLint> att;

    for(int i=0; i<droite.size()-1; i++)
    {
        for(int j=0; j<nbx-1; j++)
        {
                att.push_back(droite[i][j]);
                att.push_back(droite[i+1][j+1]);
                att.push_back(droite[i][j+1]);
                triangles.push_back(att);
                att.clear();

                att.push_back(droite[i][j]);
                att.push_back(droite[i+1][j]);
                att.push_back(droite[i+1][j+1]);
                triangles.push_back(att);
                att.clear();
      }
    }

    // Fill vertices vector
    for (int i=0; i<points.size(); ++i)
      this->addVertex(points[i][0], points[i][1], points[i][2]);


    // Fill triangles vector
    for (int i=0; i<triangles.size(); ++i)
      this->addTriangle(triangles[i][0], triangles[i][1], triangles[i][2]);

    // Fill normals vectors
        computeNormalsT();  // to be fixed
        computeNormalsV();  // to be fixed


}


float FuncSurface::func_expcos(float x, float y) {
    return exp(-(x*x/2+y*y/2))*cos(2*x*x+2*y*y);
}

float FuncSurface::func_expsin(float x, float y) {
    return exp(-(x*x/2+y*y/2))*sin(2*x*x+2*y*y);
}

