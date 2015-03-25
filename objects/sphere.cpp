#include "sphere.h"
#include <math.h>

Sphere::Sphere(int nbpoint)
    : TriMesh()
{
    _name = "Sphere";


    nbcercle=nbpoint-1;
    vector<vector<GLfloat> > points;
    vector<vector<GLint> > cercle;
    vector<GLint> atc;
    vector<GLfloat> atp;

    float z;
    float angle=(M_PI)/(nbcercle);
    z=RadToDeg(angle);
    float y=-90;

    for(int j=0; j<nbcercle+1; j++)
    {
        if(y==-90){
            atp.push_back(0);
            atp.push_back(-1);
            atp.push_back(0);
            points.push_back(atp);
            atp.clear();
            y=y+z;
        }else if(y==90){
            atp.push_back(0);
            atp.push_back(1);
            atp.push_back(0);
            points.push_back(atp);
            atp.clear();
        }else{
            for(int i=1; i<=nbpoint; i++)
            {

                    atp.push_back((cos((i*2*M_PI)/nbpoint))*cos(DegToRad(y)));
                    atp.push_back(sin(DegToRad(y)));
                    atp.push_back((sin((i*2*M_PI)/nbpoint))*cos(DegToRad(y)));
                    points.push_back(atp);
                    atp.clear();
                    atc.push_back(points.size()-1);
            }
            cercle.push_back(atc);
            atc.clear();
            y=y+z;
        }
    }
/*
    for(int i=0; i<points.size(); i++)
        cout<<" points"<< points[i][0]<<" "<< points[i][1]<<" "<< points[i][2]<<endl;

    for(int i=0; i<cercle.size(); i++)
        cout<<" cercle"<< cercle[i][0]<<" "<< cercle[i][1]<<" "<< cercle[i][2]<<" "<< cercle[i][3]<<endl;
*/
    vector<vector<GLint> > triangles;
    vector<GLint> att;

    for(int i=0; i<nbpoint; i++)
    {
        att.push_back(0);
        att.push_back(i+1);
        if((i+1)%nbpoint==0)
        {
          att.push_back(1);
        }else{
          att.push_back(i+2);
        }
        triangles.push_back(att);
        att.clear();
    }

    //lier cercle entre eux
    for(int i=0; i<cercle.size()-1; i++)
    {
        for(int j=0; j<nbpoint; j++)
        {
            att.push_back(cercle[i+1][j]);
            if((j+1)%nbpoint==0){
                  att.push_back(cercle[i][0]);
              }else{
                  att.push_back(cercle[i][j+1]);
              }
            att.push_back(cercle[i][j]);
            triangles.push_back(att);
            att.clear();

            att.push_back(cercle[i+1][j]);
            if((j+1)%nbpoint==0){
                  att.push_back(cercle[i+1][0]);
              }else{
                  att.push_back(cercle[i+1][j+1]);
              }
            if((j+1)%nbpoint==0){
               att.push_back(cercle[i][0]);
            }else{
              att.push_back(cercle[i][j+1]);
            }
            triangles.push_back(att);
            att.clear();
      }
    }

    for(int j=cercle.size(); j<=cercle.size(); j++)
    {
        for(int i=0; i<nbpoint; i++)
        {

            att.push_back(cercle[j-1][i]);
            att.push_back(points.size()-1);
            if((i+1)%nbpoint==0)
            {
              att.push_back(cercle[j-1][0]);
            }else{
              att.push_back(cercle[j-1][i+1]);
            }
            triangles.push_back(att);
            att.clear();
        }

    }



   // for (int i=0; i<triangles.size(); ++i)
     // cout<< " triangle " << triangles[i][0]<<" "<< triangles[i][1]<<" "<<triangles[i][2]<<endl;

    //--- Fill vertices and triangles vectors

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
