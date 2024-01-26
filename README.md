
<p align="center">
    <img src="doc/project_cover.jpg" alt="Example Image">
</p>

<h1 align="center">Tele Driving of a Mobile Robot</h1>

## Project description

The construction of the README file is ongoing. The project is still under development.

## How to use
1. Specify the path to the opencv library in the `configuration.json` file. (Notice that `/` rather than `\` is used.) For instance:
    ```json
    {
        "opencv_dir": "D:/Program Files/opencv/build"
    }
    ```

2. Specify the ip address of the web camera in the `configuration.json` file. For instance:
    ```json
    {
        "cam_ip": "192.168.59.246"
    }
    ```

3. Run the 'CMakeLists.txt' file in the root directory of the project.
    

## Known issues
1. The opencv library sometimes cannot be found by the compiler. And the following error message is displayed.
    ```
    The code execution cannot proceed because opencv_world480.dll was not found. Reinstalling the program may fix this problem.

    The code execution cannot proceed because opencv_world480d.dll was not found. Reinstalling the program may fix this problem.
    ```
    This is could be caused by the fact that the library is not installed in the default location. To solve this issue, find the following files in the `opencv/build/x64/vc16/bin` folder and copy them to the `C:\Windows\System32` folder. (XXX is the version number of the library, for instance, 480 means version 4.8.0)
    - opencv_worldXXX.dll
    - opencv_worldXXXd.dll