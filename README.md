# Physics Simulation

This project, "Physics Simulation," offers a dynamic and interactive environment for exploring fundamental physics principles. Built with a focus on real-time visualization and user interaction, it allows for experimentation with various physical phenomena.

## Features

* **Configurable Environment:** Adjust parameters like gravity, air resistance, and restitution to observe their impact on simulations.
* **Interactive Object Manipulation:** Add, remove, and manipulate objects within the simulation, controlling their initial conditions and properties.
* **Collision Detection and Response:** Experience realistic interactions between objects, including elastic and inelastic collisions.
* **Performance Monitoring:** Keep an eye on simulation performance with real-time metrics.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

* **Raylib:** This project uses Raylib for graphics and input. Ensure you have Raylib set up for your development environment.
* **C++ Compiler:** A C++11 compatible compiler (e.g., GCC, Clang, MSVC).
* **CMake (Optional but Recommended):** For easier project configuration and building.

### Installation

1.  **Clone the repository:**

    ```bash
    git clone [https://github.com/AJGamess/Physics.git](https://github.com/AJGamess/Physics.git)
    cd Physics
    ```

2.  **Build the project:**

    * **Using CMake (Recommended for all platforms, including Visual Studio):**
        ```bash
        mkdir build
        cd build
        cmake .. 
        # On Windows, this will generate Visual Studio solution and project files.
        # On Linux/macOS, this typically generates Makefiles.
        cmake --build .
        # This command builds the project using the generated build system (e.g., MSBuild for Visual Studio, make for Makefiles).
        ```
    * **Manual Compilation (Example - adapt for your system and compiler):**
        ```bash
        g++ -o physics_simulation src/*.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
        ```
        (Note: The exact compilation command may vary depending on your Raylib installation and operating system.)

### Usage

Once compiled, run the executable. If you built with Visual Studio, you can typically run it directly from the IDE or find the executable in the `build/Debug` or `build/Release` folder (depending on your build configuration).

```bash
./physics_simulation

![main simulation window](https://github.com/user-attachments/assets/be1b4083-1c09-4fbc-bd36-8547196a5c61)


### Adding Objects:

To add an object all you need to do is left click.


![Screenshot showing object creation](https://github.com/user-attachments/assets/75f3be30-0234-4731-8e42-18fa6b44fb2a)
### Manipulating Objects:


To connect object using a string, right click on the circle (to select it) and drag to a different circle to connect. 

![Screenshot of an object being manipulated](https://github.com/user-attachments/assets/4d8104b0-cadf-427f-9cc8-7137bf948679)


### Adjusting Parameters:

Using the UI you can adjust size, mass, gravity, gravitation and more.
After adjusting click to add the circle, it will now have those properties.
Then just press the space bar or click on simulate to start. Click again to freeze.

![Screenshot of the UI showing parameter adjustments](https://github.com/user-attachments/assets/586fe10e-cb04-4e6b-9a37-88a0aa098420)

```
# I used Gemini for assisting me on generating this README.md for you guys.
