# AMOTech_Igloo
This is the basic geometry of the Igloo for AMOTech.

## How to setup

In order to run this simulation you have to install **CMake**, a compiler and **Geant4**.

We run without local installation of gcc nor Geant4. We make a source to them (in order):
```console
   source /cvmfs/sft.cern.ch/lcg/views/LCG_103/x86_64-centos7-gcc12-opt/setup.sh
   source /cvmfs/sft.cern.ch/lcg/views/LCG_103/x86_64-centos7-gcc12-opt/bin/geant4.sh
```

After this we have to create a new folder to build the project (delete if cloning the repository):
```console
   mkdir build
   cd build 
```
Inside this folder we have to use CMake to prepare compilation (each time there are new files also):
```console
   cmake -DGeant4_DIR=/cvmfs/sft.cern.ch/lcg/releases/Geant4/11.1.1-be329/x86_64-centos7-gcc12-opt/ ../
```
Finally we compile with:
```console
   make
```
You have to do this every time you change any header or source file.
(If it doesn't find the "G4AnalysisManager.hh" package, you may have an older version of Geant4. To fix this, you can update the version of Geant4 or use "g4root.hh" instead.)

Now we have an executable file called "Igloo". We can execute it with:
```console
   ./Igloo
```

## How to use the simulation

If you just do 
```console
   ./Igloo
```
it starts the visualization window. There you can use all the defaults commands of Geant4 and also you can change the thickness of the ceilling and the walls of the Igloo with the commands:
```console
   /shield/ceilingThick 0.8
   /shield/wallThick 1.5
```
(units in meters)

You can also create your own macro file for the simulation.
```console
   ./Igloo mymacro.mac
```

You have to write the path of your macro file. By default, when you do cmake it copies every macro from the main project directory to the "macros" folder.

## Exmaple

You have one macro file as an example. If you start the simulation with this example
```console
   ./Igloo ../macros/run.mac
```
it will give you back two ROOT files: output0.root and output1.root, corresponding to two runs of the simulation.

## Notes

This project uses the General Particle Source (GPS) of Geant4. There is commented code to use the Particle Gun (PG) instead. You can use it if you want, but you have to change the macro file to use the PG instead of the GPS.

The GPS is set to monoenergetic but it uses a random energy generator to set the energy of the particle. You can't change the energy of the particle in the macro file!