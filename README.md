# 2D Rendering Application - Computer Graphics Project

This project is a 2D rendering application that demonstrates core computer graphics techniques. The focus is on rendering geometric shapes, handling transformations, and using line drawing algorithms like **Bresenham's Line Algorithm** and **DDA** (Digital Differential Analyzer) to create efficient, pixel-perfect graphics.

## Features

- **Line Drawing Algorithms**:  
  The project implements **Bresenham's Line Algorithm** and **DDA**, both of which allow the rendering of lines without gaps or distortions, crucial for smooth graphical output.

- **Geometric Transformations**:  
  The application supports matrix-based transformations such as:
  - **Scaling**
  - **Rotation**
  - **Translation**

  These operations enable the manipulation of geometric shapes, offering dynamic and visually appealing transformations.

- **Scanline Algorithm**:  
  The **Scanline Fill Algorithm** is used for solid and interpolated color filling of polygons, particularly triangles, ensuring that all shapes are filled correctly with minimal computational overhead.

- **Spaceship Design and Animation**:  
  A custom spaceship is rendered using line segments and can be rotated based on user input, showcasing the transformation capabilities of the rendering system.

## Screenshots

### 1. Spaceship in Asteroid Environment:

![Spaceship in Asteroid Environment](https://github.com/AyeshaRahman2002/ComputerGraphics-2d-Rendering/blob/main/images/Screenshot%202024-10-16%20at%2003.16.01.png)

*Example of a spaceship rendered among asteroids.*

### 2. Spaceship Flying Through Asteroids:

![Spaceship in Asteroid Environment 2](https://github.com/AyeshaRahman2002/ComputerGraphics-2d-Rendering/blob/main/images/Screenshot%202024-10-16%20at%2003.16.17.png)

*Spaceship moving through asteroid field.*

### 3. Spacecraft in Orbit Near Earth:

![Spacecraft Near Earth](https://github.com/AyeshaRahman2002/ComputerGraphics-2d-Rendering/blob/main/images/Screenshot%202024-10-16%20at%2003.16.24.png)

*The spacecraft moving towards Earth.*

### 4. Close-up of Spaceship Design:

![Close-up of Spaceship Design](https://github.com/AyeshaRahman2002/ComputerGraphics-2d-Rendering/blob/main/images/Screenshot%202024-10-16%20at%2003.16.32.png)

*Detailed design of the custom spaceship.*

## Technologies Used

- **C++**:  
  The project is implemented in modern C++, leveraging object-oriented principles and efficient memory handling for graphics rendering.
  
- **SDL2 (Simple DirectMedia Layer)**:  
  SDL2 is used for managing the window, rendering the graphics, and handling user inputs.

## How to Run the Project

1. **Clone the repository**:  
   ```bash
   git clone https://github.com/AyeshaRahman2002/ComputerGraphics-2d-Rendering.git
   ```
   
2. **Install SDL2**:  
   Ensure you have SDL2 installed on your system. You can find installation instructions on the official SDL [website](https://www.libsdl.org/download-2.0.php).

3. **Build the project**:  
   Compile the project using a C++ compiler that supports modern C++ standards (e.g., g++ or clang++).
   ```bash
   g++ -o 2d_rendering main.cpp -lSDL2
   ```
   
4. **Run the executable**:  
   ```bash
   ./2d_rendering
   ```

## Key Algorithms Implemented

### 1. **Bresenham's Line Algorithm**:
   A pixel-perfect algorithm used for drawing straight lines between two points efficiently, minimizing computation by avoiding floating-point arithmetic.

### 2. **Digital Differential Analyzer (DDA)**:
   Another line-drawing algorithm that uses incremental error accumulation to plot points along a line, ensuring smooth transitions between points.

### 3. **Scanline Fill Algorithm**:
   A technique for filling polygons, such as triangles, by scanning horizontal lines and interpolating colors between edges.

### 4. **Matrix-based Transformations**:
   Matrix operations are used to perform 2D transformations (scaling, rotation, translation), allowing for dynamic manipulation of shapes.

## Conclusion

This project showcases fundamental concepts in 2D computer graphics by utilizing efficient algorithms and geometric transformations to render and manipulate shapes dynamically. The custom spaceship and asteroid game simulation highlights both the practical application of these techniques and their real-time graphical performance.
