#include <catch2/catch_amalgamated.hpp>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"
#include "../draw2d/color.hpp"


TEST_CASE( "sRGB conversion", "[interp][sRGB]" )
{
#	if DRAW2D_CFG_SRGB_MODE != DRAW2D_CFG_SRGB_EXACT
#		error "These tests require SRGB_MODE == SRGB_EXACT"
#	endif
	
	Surface surface( 16, 16 );
	surface.clear();

	SECTION( "linear midpoint" )
	{
		draw_triangle_interp( surface,
			{ 1.f, 15.f }, { 1.f, 1.f }, { 15.f, 1.f },
			{ 0.5f, 0.5f, 0.5f },
			{ 0.5f, 0.5f, 0.5f },
			{ 0.5f, 0.5f, 0.5f }
		);

		// I use the "find_most_red_pixel" to avoid making any assumptions on
		// how triangle drawing is implemented. In your own tests, you could
		// read back a single pre-determined pixel instead.
		auto const col = find_most_red_pixel( surface );
		REQUIRE( 188 == int(col.r) );
		REQUIRE( 188 == int(col.g) );
		REQUIRE( 188 == int(col.b) );
	}

	SECTION( "channels" )
	{
		draw_triangle_interp( surface,
			{ 1.f, 15.f }, { 1.f, 1.f }, { 15.f, 1.f },
			{ 0.212f, 0.051f, 0.527f },
			{ 0.212f, 0.051f, 0.527f },
			{ 0.212f, 0.051f, 0.527f }
		);

		auto const col = find_most_red_pixel( surface );
		REQUIRE( 127 == int(col.r) );
		REQUIRE( 64 == int(col.g) );
		REQUIRE( 192 == int(col.b) );
	}
}




/////////////////////////////////////////////////////////////////////////////////////////////////

//mine

// Test Case: Degenerate Collinear Triangle
// Purpose: Ensure that a degenerate collinear triangle, where all vertices are on the same line, is correctly handled.
TEST_CASE( "Degenerate Collinear Triangle", "[special]" )
{
    // Create a surface and clear it
    Surface surface(320, 240);
    surface.clear();

    // Draw a degenerate collinear triangle with all vertices on the same line
    draw_triangle_solid(surface,
        {50.f, 50.f},
        {100.f, 50.f},
        {150.f, 50.f},
        {255, 0, 0}
    );

    // Check if the entire triangle is filled in the specified color
    auto const col = find_most_red_pixel(surface);
    REQUIRE(255 == int(col.r));
    REQUIRE(0 == int(col.g));
    REQUIRE(0 == int(col.b));
}

// Test Case: Filled Triangle with Three Vertices Not on the Same Line
// Purpose: Ensure that a filled triangle with three vertices not on the same line is correctly filled with the specified color.
TEST_CASE("Filled Triangle with Three Vertices Not on the Same Line", "[solid_triangle]")
{
    // Create a surface and clear it
    Surface surface(320, 240);
    surface.clear();

    // Draw a filled triangle with three vertices not on the same line
    draw_triangle_solid(surface,
        {50.f, 50.f},
        {100.f, 100.f},
        {150.f, 50.f},
        {255, 0, 0}
    );

    // Check if the entire triangle is filled in the specified color
    auto const col = find_most_red_pixel(surface);
    REQUIRE(255 == int(col.r));
    REQUIRE(0 == int(col.g));
    REQUIRE(0 == int(col.b));
}

// Test Case: Filled Triangle with Collinear Vertices
// Purpose: Ensure that a filled triangle with collinear vertices is correctly filled with the specified color.
TEST_CASE("Filled Triangle with Collinear Vertices", "[solid_triangle]")
{
    // Create a surface and clear it
    Surface surface(320, 240);
    surface.clear();

    // Draw a filled triangle with collinear vertices
    draw_triangle_solid(surface,
        {50.f, 50.f},
        {100.f, 50.f},
        {150.f, 50.f},
        {255, 0, 0}
    );

    // Check if the entire triangle is filled in the specified color
    auto const col = find_most_red_pixel(surface);
    REQUIRE(255 == int(col.r));
    REQUIRE(0 == int(col.g));
    REQUIRE(0 == int(col.b));
}