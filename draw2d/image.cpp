#include "image.hpp"

#include <memory>
#include <algorithm>

#include <cstdio>
#include <cstring>
#include <cassert>

#include <stb_image.h>

#include "surface.hpp"

#include "../support/error.hpp"

namespace
{
	struct STBImageRGBA_ : public ImageRGBA
	{
		STBImageRGBA_( Index, Index, std::uint8_t* );
		virtual ~STBImageRGBA_();
	};
}

ImageRGBA::ImageRGBA()
	: mWidth( 0 )
	, mHeight( 0 )
	, mData( nullptr )
{}

ImageRGBA::~ImageRGBA() = default;


std::unique_ptr<ImageRGBA> load_image( char const* aPath )
{
	assert( aPath );

	stbi_set_flip_vertically_on_load( true );

	int w, h, channels;
	stbi_uc* ptr = stbi_load( aPath, &w, &h, &channels, 4 );
	if( !ptr )
		throw Error( "Unable to load image \"%s\"", aPath );

	return std::make_unique<STBImageRGBA_>(
		ImageRGBA::Index(w),
		ImageRGBA::Index(h),
		ptr
	);
}

// // Blit with Alpha masking
// void blit_masked( Surface& aSurface, ImageRGBA const& aImage, Vec2f aPosition )
// {
// 	// Getting the dimensions of the input image
//     ImageRGBA::Index width = aImage.get_width();
//     ImageRGBA::Index height = aImage.get_height();

//     // Iterating through each pixel in the input image
//     for (ImageRGBA::Index y = 0; y < height; ++y)
//     {
//         for (ImageRGBA::Index x = 0; x < width; ++x)
//         {
//             // Getting the pixel color from the image
//             ColorU8_sRGB_Alpha pixelColor = aImage.get_pixel(x, y);

//             // Discarding the alpha channel and convert to ColorU8_sRGB
//             ColorU8_sRGB pixelColorSrgb{
//                 static_cast<std::uint8_t>(pixelColor.r),
//                 static_cast<std::uint8_t>(pixelColor.g),
//                 static_cast<std::uint8_t>(pixelColor.b)
//             };

//             // Calculating the destination position
//             Vec2f destinationPosition{ aPosition.x + static_cast<float>(x), aPosition.y + static_cast<float>(y) };

//             // Checking the destination position is within bounds
//             if (destinationPosition.x >= 0 && destinationPosition.x < aSurface.get_width() &&
//                 destinationPosition.y >= 0 && destinationPosition.y < aSurface.get_height())
//             {
//                 aSurface.set_pixel_srgb(
//                     static_cast<Surface::Index>(destinationPosition.x),
//                     static_cast<Surface::Index>(destinationPosition.y),
//                     pixelColorSrgb
//                 );
//             }
//         }
//     }
// }



// Blit without Alpha masking blit_without_alpha_masking
void blit_masked( Surface& aSurface, ImageRGBA const& aImage, Vec2f aPosition )
{
    // Getting the dimensions of the input image
    ImageRGBA::Index width = aImage.get_width();
    ImageRGBA::Index height = aImage.get_height();

    // Iterating through each pixel in the input image
    for (ImageRGBA::Index y = 0; y < height; ++y)
    {
        for (ImageRGBA::Index x = 0; x < width; ++x)
        {
            // Getting the pixel color from the image
            ColorU8_sRGB_Alpha pixelColor = aImage.get_pixel(x, y);

            // Convert to ColorU8_sRGB
            ColorU8_sRGB pixelColorSrgb{
                static_cast<std::uint8_t>(pixelColor.r),
                static_cast<std::uint8_t>(pixelColor.g),
                static_cast<std::uint8_t>(pixelColor.b)
            };

            // Calculating the destination position
            Vec2f destinationPosition{ aPosition.x + static_cast<float>(x), aPosition.y + static_cast<float>(y) };

            // Checking the destination position is within bounds
            if (destinationPosition.x >= 0 && destinationPosition.x < aSurface.get_width() &&
                destinationPosition.y >= 0 && destinationPosition.y < aSurface.get_height())
            {
                aSurface.set_pixel_srgb(
                    static_cast<Surface::Index>(destinationPosition.x),
                    static_cast<Surface::Index>(destinationPosition.y),
                    pixelColorSrgb
                );
            }
        }
    }
}



// Blit without Alpha maksing - using multiple calls to std::memcpy - one for each line
void blit_masked_stdmemcpy(Surface& aSurface, ImageRGBA const& aImage, Vec2f aPosition)
{
    // Getting the dimensions of the input image
    ImageRGBA::Index width = aImage.get_width();
    ImageRGBA::Index height = aImage.get_height();

    // Iterating through each line in the input image
    for (ImageRGBA::Index y = 0; y < height; ++y)
    {
        // Calculate the destination position for the entire line
        Vec2f destinationPosition{aPosition.x, aPosition.y + static_cast<float>(y)};

        // Checking if the entire line is within bounds
        if (destinationPosition.y >= 0 && destinationPosition.y < aSurface.get_height())
        {
            // Iterate through each pixel in the line
            for (ImageRGBA::Index x = 0; x < width; ++x)
            {
                // Getting the pixel color from the image
                ColorU8_sRGB_Alpha pixelColor = aImage.get_pixel(x, y);

                // Discarding the alpha channel and convert to ColorU8_sRGB
                ColorU8_sRGB pixelColorSrgb{
                    static_cast<std::uint8_t>(pixelColor.r),
                    static_cast<std::uint8_t>(pixelColor.g),
                    static_cast<std::uint8_t>(pixelColor.b)
                };

                // Calculating the destination position for the current pixel
                Vec2f currentPixelPosition{destinationPosition.x + static_cast<float>(x), destinationPosition.y};

                // Checking the current pixel position is within bounds
                if (currentPixelPosition.x >= 0 && currentPixelPosition.x < aSurface.get_width())
                {
                    aSurface.set_pixel_srgb(
                        static_cast<Surface::Index>(currentPixelPosition.x),
                        static_cast<Surface::Index>(currentPixelPosition.y),
                        pixelColorSrgb
                    );
                }
            }
        }
    }
}



namespace
{
	STBImageRGBA_::STBImageRGBA_( Index aWidth, Index aHeight, std::uint8_t* aPtr )
	{
		mWidth = aWidth;
		mHeight = aHeight;
		mData = aPtr;
	}

	STBImageRGBA_::~STBImageRGBA_()
	{
		if( mData )
			stbi_image_free( mData );
	}
}
