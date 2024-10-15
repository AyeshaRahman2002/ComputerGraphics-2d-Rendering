#include <catch2/catch_amalgamated.hpp>

#include <algorithm>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"


TEST_CASE( "1px wide lines", "[thin]" )
{
	// Note: this code is run before each of the SECTION()s below run! This
	// gives each of the SECTION()s a fresh+cleared Surface to work with.
	Surface surface( 128, 128 );
	surface.clear();

	SECTION( "horizontal" )
	{
		draw_line_solid( surface,
			{ 10.f, 47.f },
			{ 110.f, 47.f },
			{ 255, 255, 255 }
		);

		REQUIRE( max_row_pixel_count( surface ) > 1 );
		REQUIRE( 1 == max_col_pixel_count( surface ) );
	}
	SECTION( "vertical" )
	{
		draw_line_solid( surface,
			{ 64.f, 28.f },
			{ 64.f, 100.f },
			{ 255, 255, 255 }
		);

		REQUIRE( 1 == max_row_pixel_count( surface ) );
		REQUIRE( max_col_pixel_count( surface ) > 1 );
	}

	SECTION( "x-major" )
	{
		draw_line_solid( surface,
			{ 1.f, 20.f },
			{ 127.f, 60.f },
			{ 255, 255, 255 }
		);

		REQUIRE( max_row_pixel_count( surface ) > 1 );
		REQUIRE( 1 == max_col_pixel_count( surface ) );
	}
	SECTION( "y-major" )
	{
		draw_line_solid( surface,
			{ 79.f, 28.f },
			{ 70.f, 100.f },
			{ 255, 255, 255 }
		);

		REQUIRE( 1 == max_row_pixel_count( surface ) );
		REQUIRE( max_col_pixel_count( surface ) > 1 );
	}

	SECTION( "diagonal" )
	{
		draw_line_solid( surface,
			{ 10.f, 10.f },
			{ 100.f, 100.f },
			{ 255, 255, 255 }
		);

		REQUIRE( 1 == max_row_pixel_count( surface ) );
		REQUIRE( 1 == max_col_pixel_count( surface ) );
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////

// mine

// Test Case: Vertical Line with Negative Length
// Purpose: Ensure that drawing a vertical line with negative length does not draw any pixels.
TEST_CASE( "Vertical Line with Negative Length", "[line]" )
{
	// Create a surface and clear it
    Surface surface( 200, 200 );
    surface.clear();

    // Draw a vertical line with negative length
    draw_line_solid( surface,
        { 100.f, 100.f },
        { 100.f, 50.f },
        { 255, 255, 255 }
    );

    // Count the pixel neighbors on the surface
    auto const counts = count_pixel_neighbours( surface );

    // Verify that no pixels are drawn due to the negative-length line
    REQUIRE( counts[0] == 0 );
}

// Test Case: Single Pixel Line
// Purpose: Ensure that drawing a single pixel line results in only one pixel being drawn.
TEST_CASE( "Single Pixel Line", "[line]" )
{
    // Create a surface and clear it
    Surface surface( 200, 200 );
    surface.clear();

    // Draw a single pixel line
    draw_line_solid( surface,
        { 50.f, 60.f },
        { 50.f, 60.f },
        { 255, 255, 255 }
    );

    // Count the pixel neighbors on the surface
    auto const counts = count_pixel_neighbours( surface );

    // Verify that only one pixel is drawn for a single pixel line
    REQUIRE( counts[0] == 1 );
}

// Test Case: Anti-Aliasing Test
// Purpose: Ensure that drawing a diagonal line with anti-aliasing results in smooth and blurred edges.
TEST_CASE( "Anti-Aliasing Test", "[line]" )
{
    // Create a surface and clear it
    Surface surface( 200, 200 );
    surface.clear();

    // Draw a diagonal line with anti-aliasing
    draw_line_solid(surface,
        { 30.f, 30.f },
        { 100.f, 100.f },
        { 255, 255, 255 }
    );

    // Count the pixel neighbors on the surface
    auto const counts = count_pixel_neighbours(surface);

    // Verify that the line has smooth and blurred edges due to anti-aliasing
    REQUIRE(counts[2] > 0); // Pixels with two or more neighbors indicate anti-aliased edges
}

// Test Case: Two Lines with No Gap
// Purpose: Ensure that drawing two lines with no gap between them results in a continuous line.
TEST_CASE( "Two Lines with No Gap", "[line]" )
{
    // Create a surface and clear it
    Surface surface(200, 200);
    surface.clear();

    // Draw two lines with no gap between them
    draw_line_solid(surface,
        {50.f, 50.f},
        {100.f, 100.f},
        {255, 0, 0}
    );

    draw_line_solid(surface,
        {100.f, 100.f},
        {150.f, 150.f},
        {0, 0, 255}
    );

    // Count the pixel neighbors on the surface
    auto const counts = count_pixel_neighbours(surface);

    // Verify that there is no gap between the two lines
    REQUIRE(counts[0] == 0);
}

// Test Case: Horizontal Line with Negative Length
// Purpose: Ensure that drawing a horizontal line with negative length does not draw any pixels.
TEST_CASE( "Horizontal Line with Negative Length", "[line]" )
{
    // Create a surface and clear it
    Surface surface(200, 200);
    surface.clear();

    // Draw a horizontal line with negative length
    draw_line_solid(surface,
        {100.f, 100.f},
        {50.f, 100.f},
        {255, 255, 255}
    );

    // Count the pixel neighbors on the surface
    auto const counts = count_pixel_neighbours(surface);

    // Verify that no pixels are drawn due to the negative-length line
    REQUIRE(counts[0] == 0);
}