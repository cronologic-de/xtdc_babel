# TimeTagger4 User Guide Example

## About

### Overview
This directory contains a project to compile the C++ example show in the user
guide of the [cronologic](https://www.cronologic.de) TimeTagger time-to-digital
converter.

You can download the user guide from the
[product web page](https://www.cronologic.de/products/tdcs/timetagger).

### Copyright and License
This code is created entirely by cronologic GmbH & Co. KG. All rights reserved.

### Supported Environments
| Platform     | Architecture | Configuration |
| ------------ | ------------ | ------------- |
| Windows  | `x64` | Debug   |
|          | `x64` | Release |
| Linux    | `x64` | Debug   |
|          | `x64` | Release |


---


## Build and Run the Project on Windows

You can build the project using either `CMake` directly, or using
Visual Studio 2019 (or later).

### Prerequisites
1. Copy the `driver` folder from the `TimeTagger` driver installation folder
   (e.g., `C:\Program Files\cronologic\TimeTagger4`) to the
   `timetagger4_user_guide_example` folder. If the driver is not already
   installed, you can install it from
   [product page](https://www.cronologic.de/products/tdcs/timetagger).
2. [`CMake`](https://cmake.org/install/) is installed.



### Build Using Visual Studio

The project is built by using `Visual Studio "C++ CMake Tools` which read
the specifications from `tools\CMakeSettings.json` to configure
`CMakeLists.txt` and build the generated _Project Buildsystem_ files.

>**Note**<br>
>`CMakeSettings.json` and the steps mentioned here are compatible with
>Visual Studio 2022.
>If you are using a different Visual Studio version, you need to change
>`generator` in `CMakeSettings.json` accordingly.


**Additional Prerequisites**

1. Visual Studio 2019 (or later) is installed.
2. [Visual Studio "C++ CMake Tools"](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio)
   is installed.


**Open the Project**

1. Open Visual Studio.
2. Select `Open a local folder`.
3. Select the project folder, i.e. `timetagger4_user_guide_example`.
4. If "CMake Integration" message to enable Visual Studio's CMake support with
   this workspace is displayed
   1. Select `Enable and set source directory` button.
   2. In "Select CMakeLists.txt" Dialog, navigate to the
      `<path\to\project\folder>\tools`, and open our project `CMakeLists.txt`
      file, e.g., `timetagger4_user_guide_example\tools\CMakeLists.txt`

>**Note**<br>
>You can debug it normally as well from Visual Studio.


**Configure `CMake`**

Configure `CMake` to create _Project Buildsystem_ files. Either
* select the underlying configuration from the `Configurations` drop-box in the
  Visual Studio toolbar, which will automatically configure `CMake`,
* or, select `Project -> Configure cache` from the toolbar menu.


**Compile and Link**

Select `Build -> Build All` from menu, or any standard Visual Studio way to
build the project.



### Build Using `CMake` Command line

In a terminal, navigate to `./ug_example/tools` and run the following command
to configure `CMake`

| Platform | Configurations     | Sample Command                    |
| -------- | --------------     |---------------------------------- |
| Win64    | `Debug`, `Release` | `cmake -B ..\build\bf -A x64`     |

To build the project, run

| Platform | Configuration | Sample Command                                 |
| ------   | ------------  |------------------------------------------------|
| `x64`    | Debug         | `cmake --build ..\build\bf  --config Debug`    |
| `x64`    | Release       | `cmake --build ..\build\bf  --config Release`  |



### Run the Example

1. Copy the driver DLL to `lib\x64\<config>`.
2. Run the executable file found on `lib\x64\<config>` folder as
   `timetagger4_user_guide_example.exe`.

---

## Build and Run the Project on Linux

>**Note**<br>
>The provided prebuilt Linux libraries are tested on Ubuntu/Debian.
>They might work for other distributions. If they do not, please get in
>contact with the [cronologic support team](https://www.cronologic.de/contact).

### Prerequisites
1. System is updated, e.g. `sudo apt-get update -y`, `sudo apt update`,
   then `sudo apt upgrade`.
2. Install Development Tools and `CMake`,
   e.g., `sudo apt-get install g++ cmake`.
3. `libxtdc4_driver.so` is copied to
   `timetagger4_user_guide_example/driver/x64`, and `xTDC4` include folder is
   copied to `timetagger4_user_guide_example/driver/include`. All are found on
   the repository already. If necessary, you can get them both from the
   support team.

### Build Using `CMake`

In a terminal, navigate to `./ug_example/tools` and run the following command
to configure `CMake`

| Configuration  | Sample Command                    |
| -------------- |---------------------------------- |
| `Debug`        | `cmake -B ../build/bfD -DCMAKE_BUILD_TYPE=Debug`   |
| `Release`      | `cmake -B ../build/bfR -DCMAKE_BUILD_TYPE=Release` |

To build the project, run

| Configuration | Sample Command         |
| ------------  |----------------------  |
| Debug   | `cmake --build ../build/bfD` |
| Release | `cmake --build ../build/bfR` |

The code is linked to the shared library `libxtdc4_driver.so`.

### Run the Example

1. `Cronologic PCI Linux Kernel Module` needs to be installed on the machine.
   You can build it from [`cronologic_linux_kernel`](https://github.com/cronologic-de/cronologic_linux_kernel)
   on GitHub.
2. Run the executable file found on `lib/x64` folder as
  `sudo LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./timetagger4_user_guide_example`.
