
<p align="center">
    <img src="doc/project_cover.jpg" alt="Example Image">
</p>

<h1 align="center">Tele Driving of a Mobile Robot</h1>

## Project description

The construction of the README file is ongoing. The project is still under development.

## Known issues
1. The opencv library sometimes cannot be found by the compiler. And the following error message is displayed.
    ```
    The code execution cannot proceed because opencv_world480.dll was not found. Reinstalling the program may fix this problem.

    The code execution cannot proceed because opencv_world480d.dll was not found. Reinstalling the program may fix this problem.
    ```
    This is could be caused by the fact that the library is not installed in the default location. To solve this issue, find the following files in the `opencv/build/x64/vc16/bin` folder and copy them to the `C:\Windows\System32` folder.
    - opencv_world480.dll
    - opencv_world480d.dll