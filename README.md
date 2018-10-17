# Castlevania

## Project Configuration (Visual studio)

Here are some configurations you may want to change to build the project successfully (using Visual Studio).
Open the project settings by select current project, right click and choose `Properties`

-  Convert string in legacy code API `Configuration Properties` -> `Character Set` -> `Use Unicode Character Set`
-  Set C++ standard version to the minimum (C++17): `C/C++` -> `Language` -> `C++ Language Standard` -> `C++17 Standard`
-  Enable native event *'feature'*: `C/C++` -> `Language` -> `Conformance mode` -> Leave Empty

Also take a look at the following places and copy from the [sample project] if
there are still errors

-  `General` -> `Windows SDK Version` -> Latest Version
-  `VC++ Directories` -> `Include Directories`
-  `VC++ Directories` -> `Library Directories`

## Developement Environment

-  Visual Studio 2017
-  C++17

### Libraries

-  DirectX 9 SDK
-  pugixml

[sample project]: https://github.com/dungdna2000/gamedev-intro-tutorials/

## References
- [Back to the Basics! Essentials of Modern C++ Style]
- [UIT-SE102-Game-Project ]
- [Game Programming Patterns]
- [Monogame Framework]
- [Monogame Samples]


[Back to the Basics! Essentials of Modern C++ Style]: https://github.com/CppCon/CppCon2014/blob/master/Presentations/Back%20to%20the%20Basics!%20Essentials%20of%20Modern%20C%2B%2B%20Style/Back%20to%20the%20Basics!%20Essentials%20of%20Modern%20C%2B%2B%20Style%20-%20Herb%20Sutter%20-%20CppCon%202014.pdf
[UIT-SE102-Game-Project ]: https://github.com/danhph/UIT-SE102-Game-Project 
[Game Programming Patterns]: http://gameprogrammingpatterns.com/contents.html
[Monogame Framework]: https://github.com/MonoGame/MonoGame
[Monogame Samples]: https://github.com/CartBlanche/MonoGame-Samples