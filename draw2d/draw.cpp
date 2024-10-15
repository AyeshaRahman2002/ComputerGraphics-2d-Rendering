#include "draw.hpp"

#include <algorithm>

#include <cmath>

#include "surface.hpp"

// Using Bresenham's Line algorithm
void draw_line_solid( Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor)
{
    // Converting float coordinates to integer coordinates
    int x0 = static_cast<int>(aBegin.x);
    int y0 = static_cast<int>(aBegin.y);
    int x1 = static_cast<int>(aEnd.x);
    int y1 = static_cast<int>(aEnd.y);

    // Calculating differences and signs for the slope of the line
    const int dx = std::abs(x1 - x0);
    const int dy = -std::abs(y1 - y0);
    // Incrementing Sign of x and y
    const int sx = x0 < x1 ? 1 : -1;
    const int sy = y0 < y1 ? 1 : -1;

    int error = dx + dy;  // Error value e_xy

    while (true)
    {
        // Check if the current pixel is within the bounds of the surface
        if (static_cast<Surface::Index>(x0) < aSurface.get_width() &&
            static_cast<Surface::Index>(y0) < aSurface.get_height() &&
            x0 >= 0 && y0 >= 0) {
            aSurface.set_pixel_srgb(static_cast<Surface::Index>(x0), static_cast<Surface::Index>(y0), aColor);
        }

        // Checking if the end point is reached
        if (x0 == x1 && y0 == y1)
            break;

        // Updating x coordinate if error is greater than or equal to dy
        const int e2 = 2 * error;
        if (e2 >= dy)
        {
            error += dy;
            x0 += sx;
        }

        // Updating y coordinate if error is less than or equal to dx
        if (e2 <= dx)
        {
            error += dx;
            y0 += sy;
        }
    }
}

// Using DDA
void draw_line_solid_DDA(Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor) {
    int x0 = static_cast<int>(aBegin.x);
    int y0 = static_cast<int>(aBegin.y);
    int x1 = static_cast<int>(aEnd.x);
    int y1 = static_cast<int>(aEnd.y);

    float dx = x1 - x0;
    float dy = y1 - y0;
    float steps = std::max(std::abs(dx), std::abs(dy)); // Determine the number of steps based on the longer axis

    float xIncrement = dx / steps; // Calculate the increment value for x
    float yIncrement = dy / steps; // Calculate the increment value for y

    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; ++i) {
        // Check if the current pixel is within the bounds of the surface
        if (static_cast<Surface::Index>(x0) < aSurface.get_width() &&
            static_cast<Surface::Index>(y0) < aSurface.get_height() &&
            x0 >= 0 && y0 >= 0) {
            aSurface.set_pixel_srgb(static_cast<Surface::Index>(x0), static_cast<Surface::Index>(y0), aColor);
        }

        x += xIncrement; // Increment x
        y += yIncrement; // Increment y
    }
}


void draw_triangle_wireframe( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aP0;   // is properly implemented.
	(void)aP1;
	(void)aP2;
	(void)aColor;
}

void draw_triangle_solid( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor) {
    // Sorting the vertices by their y-coordinates
    if (aP0.y > aP1.y) std::swap(aP0, aP1);
    if (aP0.y > aP2.y) std::swap(aP0, aP2);
    if (aP1.y > aP2.y) std::swap(aP1, aP2);

    if (aP0.y == aP2.y) {
        // Handling the case of a degenerate collinear triangle
        int left = static_cast<int>(aP0.x);
        int right = static_cast<int>(aP2.x);

        for (int x = left; x <= right; x++) {
            if (x >= 0 && static_cast<Surface::Index>(x) < aSurface.get_width() &&
                aP0.y >= 0 && static_cast<Surface::Index>(aP0.y) < aSurface.get_height()) {
                aSurface.set_pixel_srgb(static_cast<Surface::Index>(x), static_cast<Surface::Index>(aP0.y), aColor);
            }
        }

        return;
    }

    const float totalHeight = aP2.y - aP0.y;

// Iterating over the upper part of the triangle (from aP0.y to aP1.y)
    for (float y = aP0.y; y <= aP1.y; y += 1.0f) {
        // Between vertices A and B along the scanline
        const float alpha = (y - aP0.y) / totalHeight;
        const float beta = (y - aP0.y) / (aP1.y - aP0.y);
        Vec2f A = aP0 + (aP2 - aP0) * alpha;
        Vec2f B = aP0 + (aP1 - aP0) * beta;
        if (A.x > B.x) std::swap(A, B);

        // Drawing pixels along the scanline
        for (float x = A.x; x <= B.x; x += 1.0f) {
            if (x >= 0 && x < aSurface.get_width() && y >= 0 && y < aSurface.get_height()) {
                aSurface.set_pixel_srgb(static_cast<Surface::Index>(x), static_cast<Surface::Index>(y), aColor);
            }
        }
    }

// Iterating over the lower part of the triangle (from aP1.y to aP2.y)
    for (float y = aP1.y; y <= aP2.y; y += 1.0f) {
        // Between vertices A and B along the scanline
        const float alpha = (y - aP0.y) / totalHeight;
        const float beta = (y - aP1.y) / (aP2.y - aP1.y);
        Vec2f A = aP0 + (aP2 - aP0) * alpha;
        Vec2f B = aP1 + (aP2 - aP1) * beta;
        if (A.x > B.x) std::swap(A, B);

        // Drawing pixels along the scanline
        for (float x = A.x; x <= B.x; x += 1.0f) {
            if (x >= 0 && x < aSurface.get_width() && y >= 0 && y < aSurface.get_height()) {
                aSurface.set_pixel_srgb(static_cast<Surface::Index>(x), static_cast<Surface::Index>(y), aColor);
            }
        }
    }
}

void draw_triangle_interp( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2) {
    // Sorting the vertices by their y-coordinates
    if (aP0.y > aP1.y) {
        std::swap(aP0, aP1);
        std::swap(aC0, aC1);
    }
    if (aP0.y > aP2.y) {
        std::swap(aP0, aP2);
        std::swap(aC0, aC2);
    }
    if (aP1.y > aP2.y) {
        std::swap(aP1, aP2);
        std::swap(aC1, aC2);
    }

    if (aP0.y == aP2.y) {
        // For degenerate collinear triangle
        int left = static_cast<int>(aP0.x);
        int right = static_cast<int>(aP2.x);

        for (int x = left; x <= right; x++) {
            // Drawing a horizontal line for the degenerate triangle
            ColorF interpolatedColor = aC0;
            if (x >= 0 && static_cast<Surface::Index>(x) < aSurface.get_width() &&
                aP0.y >= 0 && static_cast<Surface::Index>(aP0.y) < aSurface.get_height()) {
                // Converting the interpolated ColorF to sRGB and set the pixel
                aSurface.set_pixel_srgb(static_cast<Surface::Index>(x), static_cast<Surface::Index>(aP0.y), linear_to_srgb(interpolatedColor));
            }
        }

        return;
    }

    const float totalHeight = aP2.y - aP0.y;

    // Iterating over the upper part of the triangle (from aP0.y to aP1.y)
    for (float y = aP0.y; y <= aP1.y; y += 1.0f) {
        const float alpha = (y - aP0.y) / totalHeight;
        const float beta = (y - aP0.y) / (aP1.y - aP0.y);

        // Interpolate each color channel separately
        ColorF colorA;
        colorA.r = aC0.r + (aC2.r - aC0.r) * alpha;
        colorA.g = aC0.g + (aC2.g - aC0.g) * alpha;
        colorA.b = aC0.b + (aC2.b - aC0.b) * alpha;

        ColorF colorB;
        colorB.r = aC0.r + (aC1.r - aC0.r) * beta;
        colorB.g = aC0.g + (aC1.g - aC0.g) * beta;
        colorB.b = aC0.b + (aC1.b - aC0.b) * beta;

        Vec2f A = aP0 + (aP2 - aP0) * alpha;
        Vec2f B = aP0 + (aP1 - aP0) * beta;
        if (A.x > B.x) std::swap(A, B);

        // Drawing Pixels along the scanline
        for (float x = A.x; x <= B.x; x += 1.0f) {
            if (x >= 0 && x < aSurface.get_width() && y >= 0 && y < aSurface.get_height()) {
                // Constructing a ColorF from the interpolated color channels
                ColorF interpolatedColor;
                interpolatedColor.r = colorA.r + (colorB.r - colorA.r) * ((x - A.x) / (B.x - A.x));
                interpolatedColor.g = colorA.g + (colorB.g - colorA.g) * ((x - A.x) / (B.x - A.x));
                interpolatedColor.b = colorA.b + (colorB.b - colorA.b) * ((x - A.x) / (B.x - A.x));

                // Convert the interpolated ColorF to sRGB and set the pixel
                aSurface.set_pixel_srgb(static_cast<Surface::Index>(x), static_cast<Surface::Index>(y), linear_to_srgb(interpolatedColor));
            }
        }
    }

    // Iterating over the lower part of the triangle (from aP1.y to aP2.y)
    for (float y = aP1.y; y <= aP2.y; y += 1.0f) {
        const float alpha = (y - aP0.y) / totalHeight;
        const float beta = (y - aP1.y) / (aP2.y - aP1.y);

        // Interpolating each color channel separately
        ColorF colorA;
        colorA.r = aC0.r + (aC2.r - aC0.r) * alpha;
        colorA.g = aC0.g + (aC2.g - aC0.g) * alpha;
        colorA.b = aC0.b + (aC2.b - aC0.b) * alpha;

        ColorF colorB;
        colorB.r = aC1.r + (aC2.r - aC1.r) * beta;
        colorB.g = aC1.g + (aC2.g - aC1.g) * beta;
        colorB.b = aC1.b + (aC2.b - aC1.b) * beta;

        Vec2f A = aP0 + (aP2 - aP0) * alpha;
        Vec2f B = aP1 + (aP2 - aP1) * beta;
        if (A.x > B.x) std::swap(A, B);

        // Drawing Pixels along the scanline
        for (float x = A.x; x <= B.x; x += 1.0f) {
            if (x >= 0 && x < aSurface.get_width() && y >= 0 && y < aSurface.get_height()) {
                // Constructing a ColorF from the interpolated color channels
                ColorF interpolatedColor;
                interpolatedColor.r = colorA.r + (colorB.r - colorA.r) * ((x - A.x) / (B.x - A.x));
                interpolatedColor.g = colorA.g + (colorB.g - colorA.g) * ((x - A.x) / (B.x - A.x));
                interpolatedColor.b = colorA.b + (colorB.b - colorA.b) * ((x - A.x) / (B.x - A.x));

                // Converting the interpolated ColorF to sRGB and set the pixel
                aSurface.set_pixel_srgb(static_cast<Surface::Index>(x), static_cast<Surface::Index>(y), linear_to_srgb(interpolatedColor));
            }
        }
    }
}

void draw_rectangle_solid( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aMinCorner;   // is properly implemented.
	(void)aMaxCorner;
	(void)aColor;
}

void draw_rectangle_outline( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments
	(void)aMinCorner;
	(void)aMaxCorner;
	(void)aColor;
}
