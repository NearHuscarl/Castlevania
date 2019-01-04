# Troubleshooting

## Project Configuration (Visual studio)

Here are some configurations you may want to change to build the project successfully (using Visual Studio).
Open the project settings by selecting the current project, right click and choose `Properties`

-  Convert string in legacy code API: `General` -> `Character Set` -> `Use Unicode Character Set`
-  Set C++ standard version to the minimum (C++17): `C/C++` -> `Language` -> `C++ Language Standard` -> `C++17 Standard`
-  Enable [native event] _'feature'_: `C/C++` -> `Language` -> `Conformance mode` -> Leave Empty
-  To use DirectSound framework: `C/C++` -> `Preprocessor` -> `Preprocessor Definitions` -> Add `_CRT_SECURE_NO_WARNINGS`

Also take a look at the following places and copy from the [sample project] if
there are still errors

-  `General` -> `Windows SDK Version` -> Latest Version
-  `VC++ Directories` -> `Include Directories`
-  `VC++ Directories` -> `Library Directories`

### How to add DirectX SDK to your project

-  Step 1: Install DirectX SDK

-  Step 2: Go to DirectX SDK installation path

![DirectX_SDK_Path](images/DirectX_SDK_Path.png)

-  Step 3: Copy into your game project. Something like this

![SlnTree](images/SlnTree.png)

-  Step 4: Reconfigure Include and Library directory to the new relative path

![Include_Header_And_Lib](images/Include_Header_And_Lib.png)

-  Step 5: Add those lib files in the Lib folder to Linker input

Go to `Configuration Properties` -> `Linker` -> `Input` -> `Additional Dependencies` and add

```
d3d9.lib;d3dx9.lib;dinput8.lib;dxguid.lib;dsound.lib;dxerr.lib;winmm.lib;%(AdditionalDependencies);legacy_stdio_definitions.lib
```

### How to add third-party dll files

-  Go to `Configuration Properties` -> `Build Events` -> `Post-Build Event`
-  Add this line in the Command Line

```
XCOPY "$(ProjectDir)lib\*.dll" "$(TargetDir)" /D /K /Y
```

By default, Visual Studio only copy `*.dll` files in the `$(ProjectDir)`. If you put
them in some subfolder, you have to specify the path manually to that subfolder
(in this case `lib\`) so Visual Studio know where to find and copy them

### Fix linker error when having 2 files with the same name

```
LNK4042: object specified more than once; extras ignored
```

-  Go to `Configuration Properties` -> `C/C++` -> `Output Files` -> `Object File Name` -> `$(IntDir)/%(RelativeDir)/`

With the default configuration, Visual will toss all object files into one big folder, leading to name conflict if there are source files with the same name in different folders, replace to `$(IntDir)/%(RelativeDir)/` will put those object files in a mirror source tree, solving name conflicts
