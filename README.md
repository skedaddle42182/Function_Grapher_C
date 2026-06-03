# Function Grapher C++

A lightweight and efficient function graphing library built with SDL2 and C++.

This project focuses on fast function visualization, clean architecture, and real-time graph rendering. Functions are converted into cached screen-space points and only recalculated when necessary, reducing unnecessary computation during rendering.

## Screenshots

<img width="801" height="667" alt="Screenshot 2026-06-02 180429" src="https://github.com/user-attachments/assets/fe8e058f-cb0c-4a77-bba5-b028d4d678ba" />

<img width="798" height="668" alt="Screenshot 2026-06-02 173212" src="https://github.com/user-attachments/assets/3afc0c07-2640-4bdb-a8fe-9b873cd37fdb" />

<img width="800" height="627" alt="image" src="https://github.com/user-attachments/assets/d458f869-765a-4e30-b591-987d66ca824f" />

## Features

- Real-time function graphing
- Automatic coordinate normalization
- Dynamic window resizing support
- Cartesian grid rendering
- X and Y axis rendering
- Multiple functions displayed simultaneously
- Cached graph points for improved performance
- Custom graph scaling
- SDL2-based rendering

## Example

```cpp
std::function<double(double)> sin_function = [](double x)
{
    return std::exp(1.0) * sin(x);
};

engine.grid.initialize_line(-100, 100, "e * sin(x)");

engine.grid.add_function(
    engine.renderer,
    engine.window,
    0.001,
    sin_function,
    Colors::white,
    "e * sin(x)"
);
```

## Architecture

The library is divided into several components:

### Window

Handles:

- SDL window creation
- Event processing
- Window resizing
- Window state management

### Renderer

Handles:

- SDL rendering operations
- Drawing primitives
- Buffer presentation
- Clear operations

### Grid

Handles:

- Grid generation
- Cell management
- Axis rendering
- Coordinate transformations
- Function point generation
- Function caching

### Function Grapher

Handles:

- Main application loop
- Frame updates
- Render pipeline execution

### Engine

Provides a single interface that combines:

- Window
- Renderer
- Grid

## Performance

Functions are sampled once and stored internally as screen-space points.

When the graph does not need updating:

- No function recalculation occurs
- Cached points are reused
- Rendering is performed directly from stored data

This reduces CPU usage and avoids unnecessary recalculation every frame.

The graphing calculations are already asymptotically optimal since every point must be sampled at least once.

## Current Capabilities

- Trigonometric functions
- Inverse trigonometric functions
- Exponential functions
- Damped oscillations
- Arbitrary user-defined functions using `std::function`

Examples:

```cpp
e * sin(x)

e * atan(x)

pow(e, (-0.1 * x)) * sin(5 * x)
```

## Planned Features

- Equation parser
- Text input system
- Zooming
- Panning
- Function management system
- FFT visualization
- Sound wave analysis
- Material property calculations
- JSON-based formula database
- Graph styling options

## Dependencies

- C++17 or newer
- SDL2

## Build

Example using g++:

```bash
g++ *.cpp -lSDL2 -O2 -std=c++17
```

## License

MIT License

## Author

Built as a personal project focused on efficient mathematical visualization and graphing in C++.
