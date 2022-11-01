# Raytracing-Journey

An interactive CPU Raytracer written in pure C++.

## Showcase

## Features:

- Material:
  - Dielectrics (Refraction and Total Internal Reflection w/ Schlick's Approximation)
  - Diffuse / Pure Lambertian
  - Purely Reflective and Roughly Reflective (fuzzy) Metal
- Postprocessing:
  - Depth of Field
  - Multi-sampling Anti-aliasing
- Primitives:
  - Spheres
  - Planes

## Dependencies:

- **[GLM](https://github.com/g-truc/glm)**
- **[Dear ImGUI](https://github.com/g-truc/glm)**
- **[GLAD](https://github.com/Dav1dde/glad)**
- **[GLFW](https://github.com/glfw/glfw)**
- **OpenMP**

All dependencies are included in the repository as a submodule, make sure to use `--recursive` flag when cloning.

## Build Routine

This project follows the standard CMake build routine.

    mkdir build
    cd build
    cmake ..
    make

## License

Distributed under the MIT License. See `LICENSE` for more information.
