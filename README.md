# AMOTech_Igloo
This is the basic geometry of the Igloo for AMOTech.

## How to setup

In order to run this simulation you have to install **CMake**, a compiler and **Geant4** 

We run without local installation of gcc nor Geant4. We make a source to them (in order):
```console
   source /cvmfs/sft.cern.ch/lcg/views/LCG_103/x86_64-centos7-gcc12-opt/setup.sh
   source /cvmfs/sft.cern.ch/lcg/views/LCG_103/x86_64-centos7-gcc12-opt/bin/geant4.sh
```
After this we have to create a new folder for building (delete if cloning the repository):
```console
   mkdir build
   cd build 
```
Inside this folder we have to use cmake to prepare compilation (each time there are new files also):
```console
   cmake -DGeant4_DIR=/cvmfs/sft.cern.ch/lcg/releases/Geant4/11.1.1-be329/x86_64-centos7-gcc12-opt/ ../
```
Finally we compile with:
```console
   make
```
You have to do this every time you change any header or source file.

Now we have an executable file called "sim". We can execute it with:
```console
   ./sim
```

## How to use the simulation

If you just do 
```console
   ./sim
```
it starts the visualization window. There you can use all the defaults commands of Geant4 and also you can change the thickness of the ceillind and the walls of the Igloo.

You can also create your own macro file for the simulation.
```console
   ./sim mymacro.mac
```

You have write the path of your macro file. By default, when you do cmake it copies every macro file to the build folder.