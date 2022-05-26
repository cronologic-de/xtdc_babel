# TimeTagger4 User Guide Example

## About

### Overview
This directory contains a project to compile the C++ example show in the user guide of the cronologic TimeTagger time-to-digital converter.

You can download the user guide from the [product web page](https://www.cronologic.de/products/tdcs/timetagger).

### Copyright and Licence
This code is created entirely by cronologic GmbH & Co. KG. All rights reserved.

### Supported Environments
| Platform     | Architecture | Configuration |
| ------------ | ------------ | ------------- |
| Windows  | `x64` | Debug   |
|          | `x64` | Release |
|          | `x86` | Debug   |
|          | `x86` | Release |
| Linux    | `x64` | Debug   |
|          | `x64` | Release |

## Build the Project on Windows

### Prerequisites
1. Copy the `driver` folder from the `TimeTagger` installation folder (e.g. on <_C:\Program Files\cronologic\TimeTagger4_>) to the `timetagger4_user_guide_example` folder. If the driver not already installed, you can install it from [product web pag](https://www.cronologic.de/products/tdcs/timetagger).
2. [`CMake`](https://cmake.org/install/) is installed.

### Output File
The built output file `timetagger4_user_guide_example` is created under `timetagger4_user_guide_example\driver` sub-directory as following:
| Architecture | Configuration | Sub-directory | 
| ------------ | ------------- | ------------- | 
| `x64` | Debug   | `x64\Debug`   | 
| `x64` | Release | `x64\Release` |
| `x86` | Debug   | `x86\Debug`   |
| `x86` | Release | `x86\Release` |
* You need to copy the DLLs from the uppoer folder (e.g. `x64` and `x86`) to the sub-directory to be able to run the executable if the DLLs are not already on the path.

### 1. Build Using Visual Studio
- The project is built by using `Visual Studio "C++ CMake Tools` that reads speciificaitions got from `tools\CMakeSettings.json`, and configures `CMakeLists.txt`, then  builds the generated buildsystem files.
- `CMakeSettings.json` and the steps mentioned here are compatible with Visual Studio 2022. 

### Additional Prerequisites
1. Visual Studio 2022 is installed.
2. [Visual Studio "C++ CMake Tools"](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio) is installed.

#### Open the Project 
1. Open Visual Studio.
2. Select `Open a local folder`.
3. Select the project folder, i.e. `timetagger4_user_guide_example`.
4. If "CMake Integration" message _to enable Visual Studio's CMake support with this workspace_ is displayed
   1. Select `Enable and set source directory` button.
   2. In "Select CMakeLists.txt" Dialog, navigate to the <path\to\project\folder>\tools, and open our project `CMakeLists.txt` file, i.e. `timetagger4_user_guide_example\tools\CMakeLists.txt`

#### Configure `CMake`
Configure `CMake` to create _Project Buildsystem_ files, either:
1. Select the underlying configuration from the `Configurations` drop-box in the Visual Studio toolbar, which will automatically configure `CMake`.
2. Select `Project -> Configure cache` from menu.

#### Compile and Link
Select `Build -> Build All` from menu, or any standard Visual Studio way to build the project.

### 2. Build Using `CMake`

#### Configure `CMake`
To configure `CMake` to create _Project Buildsystem_ files, go to tools: `cd tools`, then run the following command:
| Platform | Configurations     | Sample Command                    | 
| -------- | --------------     |---------------------------------- |
| Win64    | `Debug`, `Release` | `cmake -B ..\build\bf -A x64`     | 
| Win32    | `Debug`, `Release` | `cmake -B ..\build\bf32 -A Win32` | 

#### Compile and Link
Build the project using `CMake`.
| Platform | Configuration | Sample Command                           | 
| ------   | ------------  |----------------------------------------- |
| `x64`    | Debug   | `cmake --build ..\build\bf  --config Debug`    |
| `x64`    | Release | `cmake --build ..\build\bf  --config Release`  | 
| `x86`    | Debug   | `cmake --build ..\build\bf32 --config Debug`   | 
| `x86`    | Release | `cmake --build ..\build\bf32 --config Release` | 

---

## Build the Project on Linux

### Prerequisites
[TBD]

### Using `CMake`
[TBD]
