# Castlevania

## Project Configuration (Visual studio)

Here are some configurations you may want to change to build the project successfully (using Visual Studio).
Open the project settings by select current project, right click and choose `Properties`

-  Convert string in legacy code API `Configuration Properties` -> `Character Set` -> `Use Unicode Character Set`
-  Set C++ standard version to the minimum (C++17): `C/C++` -> `Language` -> `C++ Language Standard` -> `C++17 Standard`
-  Enable usage of native event: `C/C++` -> `Language` -> `Conformance mode` -> Leave Empty

Also take a look at the following places and copy from the [sample project] if
there are still errors

-  `General` -> `Windows SDK Version` -> Latest Version
-  `VC++ Directories` -> `Executable Directories`
-  `VC++ Directories` -> `Include Directories`
-  `VC++ Directories` -> `Library Directories`

## Developement Environment

-  Visual Studio 2017
-  C++17

### Libraries

-  DirectX 9 SDK
-  pugixml

[sample project]: https://github.com/dungdna2000/gamedev-intro-tutorials/
