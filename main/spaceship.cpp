#include "spaceship.hpp"

#include <cstdio>

#include "../draw2d/shape.hpp"

/* Instructions - CUSTOM SPACESHIP DESIGNS
 *
 *  0. If you are OK with your space ship design being included in future
 *     computer graphics exercises and/or courseworks, please indicate this by
 *     placing a 'X' in the space between the [ ] on the following line:
 *     [ X ] I give permission for my space ship shape to be used in future
 *         computer graphics exercises and/or courseworks.
 *
 *     If you do not wish for your shape to be used, leave the line as is.
 *     Your decision will not affect the marking of Task 2.7 in CW1.
 *
 *     If you wish to be credited (name + year when you took the computer
 *     graphics mdoule) in a CREDITS.txt or similar file with future exercises
 *     and/or courseworks, please indicate this by ticking the following box
 *     [X] I wish to have my name + year listed with assignments that use my
 *         space ship shape.
 *
 *     If you do not wish to be credited, leave the [ ] empty.
 *
 *     Many thanks if you do permit the use of your cool space ship designs! It
 *     will help us to make future computer graphics exercises and courseworks
 *     more interesting.
 *
 *  1. Change the line
 *     #	define SPACESHIP SPACESHIP_DEFAULT
 *     to
 *     #	define SPACESHIP SPACESHIP_CUSTOM
 *
 *  2. Define your custom space ship design in the now active code section.
 *     (Look for the line that says '// TODO: YOUR DESIGN GOES HERE')
 */

#define SPACESHIP_DEFAULT 1
#define SPACESHIP_CUSTOM 2

#ifndef SPACESHIP
#	define SPACESHIP SPACESHIP_DEFAULT
//#	define SPACESHIP SPACESHIP_CUSTOM
#endif

LineStrip make_spaceship_shape()
{
#	if SPACESHIP == SPACESHIP_DEFAULT
	static constexpr float xs[] = { 250.f, 200.f, 150.f, 100.f, 000.f, 040.f, -50.f, -140.f, -170.f };
	static constexpr float ys[] = { 190.f, 180.f, 70.f, 50.f, 30.f, 20.f };

	LineStrip spaceship{ { 
		{ 0.2f * xs[0], 0.2f * +ys[5] }, // upper half. starts at front, goes towards the back
		{ 0.2f * xs[1], 0.2f * +ys[3] },
		{ 0.2f * xs[2], 0.2f * +ys[3] },
		{ 0.2f * xs[3], 0.2f * +ys[4] }, 
		{ 0.2f * xs[4], 0.2f * +ys[4] },
		{ 0.2f * xs[4], 0.2f * +ys[2] },
		{ 0.2f * xs[5], 0.2f * +ys[1] },
		{ 0.2f * xs[6], 0.2f * +ys[0] },
		{ 0.2f * xs[8], 0.2f * +ys[2] },
		{ 0.2f * xs[7], 0.2f * +ys[3] },

		{ 0.2f * xs[7], 0.2f * -ys[3] }, // lower half, starts at the back and goes towards the front
		{ 0.2f * xs[8], 0.2f * -ys[2] }, // this is essentially the same as the upper half, except in reverse.
		{ 0.2f * xs[6], 0.2f * -ys[0] },
		{ 0.2f * xs[5], 0.2f * -ys[1] },
		{ 0.2f * xs[4], 0.2f * -ys[2] },
		{ 0.2f * xs[4], 0.2f * -ys[4] },
		{ 0.2f * xs[3], 0.2f * -ys[4] }, 
		{ 0.2f * xs[2], 0.2f * -ys[3] },
		{ 0.2f * xs[1], 0.2f * -ys[3] },
		{ 0.2f * xs[0], 0.2f * -ys[5] }, 

		{ 0.2f * xs[0], 0.2f * +ys[5] } // link back to beginning (connects both sides at the "front")
	} };
#	elif SPACESHIP == SPACESHIP_CUSTOM
LineStrip spaceship{ {
    // right side
    { 100.f, 0.f },      // (rocket tip) 
    { 96.f, -10.f },    
    { 90.f, -20.f },     
    { 85.f, -25.f },     // (rocket head)
    { 60.f, -30.f },   
    { 40.f, -60.f },     // (rocket wing - top left)
    { 35.f, -45.f },     // (smooth transition)
    { 5.f, -15.f },    
    { -10.f, -20.f },    // (inside of the wing)
    { -10.f, -30.f },    // (inside of the wing)
    { -30.f, -30.f },    // (rocket tail - bottom)
    { -30.f, -20.f },    // (rocket tail - bottom)
    { -40.f, -20.f },    // (extend tail)
    { -75.f, 0.f },      // (extend tail)
	// left side - mirrored
    { -40.f, 20.f },     // (extend tail)
    { -30.f, 20.f },     // (rocket tail - bottom)
    { -30.f, 30.f },     // (rocket tail - bottom)
    { -10.f, 30.f },     // (inside of the wing)
    { -10.f, 20.f },     // (inside of the wing)
    { 5.f, 15.f },    
    { 35.f, 45.f },      // (smooth transition)
    { 40.f, 60.f },      // (rocket wing - top left)
	{ 60.f, 30.f }, 
    { 85.f, 25.f },      // (rocket head)
    { 90.f, 20.f }, 
	{ 96.f, 10.f },  
    { 100.f, 0.f },      // attaching to tip
} };



#	endif

	if( spaceship.vertex_count() > 32 )
	{
		std::fprintf( stderr, "WARNING: you must use at most 32 points for your custom spaceship design. You are currently using %zu\n", spaceship.vertex_count() );
	}

	return spaceship;
}
