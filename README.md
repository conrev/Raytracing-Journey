# Raytracing-Journey

An interactive CPU Raytracer written in pure C++.

## Showcase

<img width="965" alt="image" src="https://github.com/conrev/Raytracing-Journey/assets/18559322/4ee17675-fae4-4dff-9159-0f4014b2a4ae">
<img width="965" alt="image" src="https://github.com/conrev/Raytracing-Journey/assets/18559322/097cacae-3cca-44bb-99ea-793cdfa6f402">



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
- Interative Features:
  - Multiple Cameras and

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
