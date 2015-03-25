    /**
    * @file   main.cpp
    * @author Bruno Jobard
    * @author Author1
    * @author Author2
    * @date   Sep 2012
    *
    * @brief  Declares an application, a main window and a 3D scene
    *
    *
    */
    #include <QApplication>
    #include "my_main_window.h"

#include <tclap/CmdLine.h>

    #include "my_object3d.h"
    #include "objects/cube.h"
    #include "objects/pyramid.h"
    #include "objects/cone.h"
    #include "objects/cylindre.h"
    #include "objects/disk.h"
    #include "objects/diskhole.h"
    #include "objects/cubecorner.h"
    #include "objects/sphere.h"
    #include "objects/tore.h"
    #include "objects/func_surface.h"
    #include "fichier/off_loader.h"

    /**
    * Program usage
    * Should be handled with the tclap library
    */
    void usage(char* name){
    cout<< "usage: " << name << " [options]" <<endl;
    cout<< "options:" <<endl;
    cout<< "  -h, --help                 shows this message" <<endl;
    cout<< "  --off file                 loads OFF file" <<endl;
    }

    int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    // Parse program arguments here
    // with the tclap library
    // http://tclap.sourceforge.net/manual.html

    TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
    TCLAP::MultiArg<std::string> nameArg("o","off","Nom fichier a ouvrir",false,"string");
    cmd.add( nameArg );
    cmd.parse( argc, argv );


    // initialize my custom 3D scene
    float objectRadius = 1.;
    QPointer<MyScene> myScene = new MyScene(objectRadius);
    //add simple objects
    myScene->addObject(new Cube());
    myScene->addObject(new Cubecorner());
    myScene->addObject(new Pyramid());
    myScene->addObject(new Disk(50));
    myScene->addObject(new Diskhole(50,0.6));
    myScene->addObject(new Cone(50));
    myScene->addObject(new Cylindre(50,50));
    myScene->addObject(new Sphere(20));
    myScene->addObject(new Tore(50));


    // add surface functions
    myScene->addObject(new FuncSurface(50,50,-M_PI,M_PI,-M_PI,M_PI,FuncSurface::func_expcos));
    myScene->addObject(new FuncSurface(50,50,-M_PI,M_PI,-M_PI,M_PI,FuncSurface::func_expsin));

    // add user defined OFF files
    vector<string> argument;
    argument = nameArg.getValue();
    for(int i=0; i<argument.size(); i++)
    {
        string fichier = argument[i];
        myScene->addObject(new Offloader(fichier));
    }
    // initialize my custom main window
    QPointer<MyMainWindow> myMainWindow = new MyMainWindow(myScene);
    // display the window
    myMainWindow->show();
    // enter in the main loop
    return app.exec();
    }

