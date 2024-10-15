/* Inline functions need to have a definition that is visible to the compiler
 * whenever the function is used. THey could be define in the header that
 * declares the function. However, to keep the definitions and declarations
 * somewhat apart, it is a common practice to move them to an "inline" file
 * such as this one (*.inl extension). This file is then #include:ed at the end
 * of the header, to ensure that whoever includes the header also automatically
 * includes the inline file.
 *
 * Inlining allows us to avoid any overheads related to call (when building in
 * "release mode" / with optimizations enabled). This makes functions like
 * set_pixel_srgb() zero overhead abstractions.
 *
 */

inline
void Surface::set_pixel_srgb( Index aX, Index aY, ColorU8_sRGB const& aColor )
{
    assert(aX < mWidth && aY < mHeight); // IMPORTANT! This line must remain the first line in this function!

    // Calculate the linear index for the given pixel
    Index index = get_linear_index(aX, aY);

    // Each pixel consists of 4 bytes (RGBA), so we need to calculate the starting position in the surface array
    std::size_t startPos = index * 4;

    // Set the color components in the array
    mSurface[startPos + 0] = aColor.r;
    mSurface[startPos + 1] = aColor.g;
    mSurface[startPos + 2] = aColor.b;
    mSurface[startPos + 3] = 0; // The "x" component is set to 0
}

inline 
auto Surface::get_width() const noexcept -> Index
{
	return mWidth;
}
inline
auto Surface::get_height() const noexcept -> Index
{
	return mHeight;
}

inline
Surface::Index Surface::get_linear_index( Index aX, Index aY ) const noexcept
{
    // Row-major order
    return aY * mWidth + aX;
}