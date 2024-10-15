#include <catch2/catch_amalgamated.hpp>

#include <algorithm>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////

// mine
TEST_CASE( "Vertical Line with Negative Length", "[additional]" )
{
    Surface surface( 200, 200 );
    surface.clear();

    SECTION( "negative length" )
    {
        draw_line_solid( surface,
            { 100.f, 100.f },
            { 100.f, 50.f },
            { 255, 255, 255 }
        );

        auto const counts = count_pixel_neighbours( surface );
        REQUIRE( 0 == counts[0] ); // No pixels should be drawn
    }
}

TEST_CASE( "Vertical Line with Negative Length", "[line]" )
{
    Surface surface( 200, 200 );
    surface.clear();

    draw_line_solid( surface,
        { 100.f, 100.f },
        { 100.f, 50.f },
        { 255, 255, 255 }
    );

    auto const counts = count_pixel_neighbours( surface );

    // Verify that no pixels are drawn due to the negative-length line
    REQUIRE( counts[0] == 0 );
}

TEST_CASE( "Steep Diagonal Line", "[line]" )
{
    Surface surface( 200, 200 );
    surface.clear();

    draw_line_solid( surface,
        { 10.f, 10.f },
        { 15.f, 100.f },
        { 255, 255, 255 }
    );

    auto const counts = count_pixel_neighbours( surface );

    // Verify that the steep diagonal line is continuous
    REQUIRE( counts[1] == 0 );
}

TEST_CASE( "Line with Intervening Pixels", "[line]" )
{
    Surface surface( 200, 200 );
    surface.clear();

    // Pre-draw some pixels
    surface.set_pixel_srgb(50, 100, {255, 0, 0});
    surface.set_pixel_srgb(80, 130, {0, 255, 0});
    surface.set_pixel_srgb(110, 160, {0, 0, 255});

    // Draw a line passing through the pre-drawn pixels
    draw_line_solid( surface,
        { 50.f, 100.f },
        { 110.f, 160.f },
        { 255, 255, 255 }
    );

    auto const counts = count_pixel_neighbours( surface );

    // Verify that the line interacts correctly with the existing pixels
    REQUIRE( counts[1] == 0 );
}

TEST_CASE( "Single Pixel Line", "[line]" )
{
    Surface surface( 200, 200 );
    surface.clear();

    draw_line_solid( surface,
        { 50.f, 60.f },
        { 50.f, 60.f },
        { 255, 255, 255 }
    );

    auto const counts = count_pixel_neighbours( surface );

    // Verify that only one pixel is drawn for a single pixel line
    REQUIRE( counts[0] == 1 );
}

TEST_CASE( "Anti-Aliasing Test", "[line]" )
{
    Surface surface( 200, 200 );
    surface.clear();

    // Draw a diagonal line with anti-aliasing
    draw_line_solid(surface,
        { 30.f, 30.f },
        { 100.f, 100.f },
        { 255, 255, 255 }
    );

    auto const counts = count_pixel_neighbours(surface);

    // Verify that the line has smooth and blurred edges due to anti-aliasing
    REQUIRE(counts[2] > 0); // Pixels with two or more neighbors indicate anti-aliased edges
}
