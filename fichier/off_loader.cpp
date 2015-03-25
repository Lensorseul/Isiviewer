#include "off_loader.h"
#include <sstream>
#include <stdio.h>
#include <string.h>

Offloader::Offloader(string nomfic)
  : TriMesh()
{
    _name = "Fichier";
    nomfichier=nomfic;
    charger();
}

void Offloader::charger()
{
    fichier.open(nomfichier.c_str(), ios_base::in);

    if(fichier.is_open()!=true)
    {
        cout<<"Fichier non ouvert"<<endl;
    }else{
        cout<<"Fichier ouvert "<<nomfichier<<endl;
        recupEntete();
        recupPoint();
        recupPoly();
        //--- Fill vertices and triangles vectors

        // Fill vertices vector
        for (int i=0; i<points.size(); ++i)
          this->addVertex(points[i][0], points[i][1], points[i][2]);


        // Fill triangles vector
        for (int i=0; i<triangles.size(); ++i)
          this->addTriangle(triangles[i][0], triangles[i][1], triangles[i][2]);

        cout<<" triangle - size "<<triangles.size()<<endl;
        // Fill normals vectors
            computeNormalsT();  // to be fixed
            computeNormalsV();  // to be fixed

    }
    fichier.close();
}

void Offloader::recupPoly()
{
    for(int i=0; i<nbtriangle; i++)
    {
        int n;
        fichier >> n;
        if(n==3)
        {
            for(int j=0; j<n; j++)
            {
                int t;
                fichier>>t;
                att.push_back(t);
            }
            triangles.push_back(att);
            att.clear();
            recupCouleur();
            tcouleur.push_back(couleur);
            couleur.clear();
        }else{
            for(int j=0; j<n; j++)
            {
                int t;
                fichier>>t;
                att.push_back(t);
            }
            for(int k=1; k<att.size()-1; k++)
            {
                vector<GLint> temp;
                temp.push_back(att[0]);
                temp.push_back(att[k]);
                temp.push_back(att[k+1]);
                triangles.push_back(temp);
            }
            att.clear();
            recupCouleur();
            tcouleur.push_back(couleur);
            for(int u=0; u<n; u++){
                tcouleur.push_back(couleur);
            }
            couleur.clear();
        }
    }
}

void Offloader::recupCouleur()
{
    vector<string> couleurtemp;
    string ligne;
    getline(fichier,ligne);

    char *str = (char*)ligne.c_str();
    char * pch;
    pch = strtok (str," ");
    while (pch != NULL)
    {
    couleurtemp.push_back((string)pch);
    pch = strtok (NULL, " ");
    }

    float R,G,B,T;
    for(int i=0; i<couleurtemp.size(); i++)
    {
        istringstream iss(couleurtemp[i]);
        if(i==0){
            iss>>R;
            couleur.push_back(R);
        }

        if(i==1){
            iss>>G;
            couleur.push_back(G);
        }

        if(i==2){
            iss>>B;
            couleur.push_back(B);
        }
        if(i==3){
            iss>>T;
            couleur.push_back(T);
        }
    }
}

void Offloader::recupPoint()
{
    float min,max,sum;
    min=0;
    max=0;
    for(int i=0; i<nbpoint; i++)
    {
        for(int j=0; j<3; j++)
        {
            float val;
            fichier>>val;
            atp.push_back(val);
            if(val>max)
                max=val;
            if(val<min)
                min=val;
        }
        points.push_back(atp);
        atp.clear();
    }
    sum=max-min;

    //mise a lechelle
    for(int i=0; i<points.size(); i++)
    {
        for(int j=0; j<3; j++)
        {
            points[i][j]=(points[i][j]/sum)*2;
        }
    }
}

void Offloader::recupEntete()
{
    fichier >> name >> nbpoint >> nbtriangle >> nbarrete;
}

void Offloader::affichEntete()
{
    cout<<"Entete "<<name <<" "<<nbpoint << " "<< nbtriangle << " "<< nbarrete<<endl;
}

void Offloader::affichPoints()
{
    for(int i=0; i<points.size(); i++)
            cout<<" Points"<< points[i][0]<<" "<< points[i][1]<<" "<< points[i][2]<<endl;
}

void Offloader::affichTriangles()
{
     for (int i=0; i<triangles.size(); ++i)
       cout<< " triangle " << triangles[i][0]<<" "<< triangles[i][1]<<" "<<triangles[i][2]<<endl;
}

void Offloader::affichCol()
{

    for (int i=0; i<tcouleur.size(); ++i)
      cout<< " tcouleur " << tcouleur[i][0]<<" "<< tcouleur[i][1]<<" "<<tcouleur[i][2]<< " "<<tcouleur[i][3]<<endl;

}


void Offloader::draw(bool flipnormals){
    unsigned int i,t;
    bool smooth;
    Normal n;

    GLint mode[1];
    glGetIntegerv(GL_SHADE_MODEL, mode);
    smooth= mode[0]==GL_SMOOTH && _normalsV.size()==_triangles.size()*3;

    if(smooth){
        glBegin(GL_TRIANGLES);
        for(t=0; t<_triangles.size(); ++t){
            if(tcouleur[t].size()==3){
                glColor3f(tcouleur[t][0],tcouleur[t][1],tcouleur[t][2]);
            }
            if(tcouleur[t].size()==4){
                 glColor4f(tcouleur[t][0],tcouleur[t][1],tcouleur[t][2],tcouleur[t][3]);
            }
            for(i=0; i<3; i++){
                n=_normalsV[3*t+i];
                if(flipnormals) n*=-1;
                //        glNormal3fv(&n[0]);
                glNormal3fv(glm::value_ptr(n));
                glVertex3fv(glm::value_ptr(_vertices[_triangles[t][i]]));
            }
        }
        glEnd();
    }else{
        glBegin(GL_TRIANGLES);
        for(t=0; t<_triangles.size(); ++t){
            if(tcouleur[t].size()==3){
                glColor3f(tcouleur[t][0],tcouleur[t][1],tcouleur[t][2]);
            }
            if(tcouleur[t].size()==4){
                glColor4f(tcouleur[t][0],tcouleur[t][1],tcouleur[t][2],tcouleur[t][3]);
            }
            n=_normalsT[t];
            if(flipnormals) n*=-1;
            glNormal3fv(glm::value_ptr(n));
            for(i=0; i<3; i++)
                glVertex3fv(glm::value_ptr(_vertices[_triangles[t][i]]));
        }
        glEnd();
    }

}
