#pragma once

// Include CBT
#include "Core/General/cbtLibrary.h"
#include "cbtTexture.h"

// Include STD
#include <unordered_map>
#include <array>

NS_CBT_BEGIN

class cbtTextureBuilder
{
protected:
    /**
        \brief Flip the image data vertically.

        \param _image The image data to flip.
        \param _width The horizontal resolution of the image data.
        \param _height The vertical resolution of the image data.
        \param _bytesPerPixel How many bytes per pixel.

        \warning This function assumes that the image data is row major.
    */
    static void FlipImageVertically(cbtU8* _image, cbtS32 _width, cbtS32 _height, size_t _bytesPerPixel)
    {
        cbtS32 bytesPerRow = _width * (cbtS32)_bytesPerPixel;

        // Create temporary buffers to copy the image data into.
        cbtU8* topRow = new cbtU8[bytesPerRow];
        cbtU8* bottomRow = new cbtU8[bytesPerRow];

        // Since the data is stored in a row-major format, we can swap the data row by row rather then pixel by pixel.
        for (cbtS32 r = 0; r < (_height >> 1); ++r)
        {
            // Get the pixel data for the current rows and copy it into our temporary buffer.
            // Convert it to an unsigned char so that we can iterate byte by byte.
            std::memcpy(topRow, &_image[r * bytesPerRow], bytesPerRow);
            std::memcpy(bottomRow, &_image[(_height - r - 1) * bytesPerRow], bytesPerRow);

            // Copy the data from our temporary buffer back into the image.
            std::memcpy(&_image[r * bytesPerRow], bottomRow, bytesPerRow);
            std::memcpy(&_image[(_height - r - 1) * bytesPerRow], topRow, bytesPerRow);
        }

        delete[] topRow;
        delete[] bottomRow;
    }

    /**
        \brief Flip the image data horizontally.

        \param _image The image data to flip.
        \param _width The horizontal resolution of the image data.
        \param _height The vertical resolution of the image data.
        \param _bytesPerPixel How many bytes per pixel.

        \warning This function assumes that the image data is row major.
    */
    static void FlipImageHorizontally(cbtU8* _image, cbtS32 _width, cbtS32 _height, size_t _bytesPerPixel)
    {
        cbtS32 bytesPerRow = _width * (cbtS32)_bytesPerPixel;

        // Create temporary buffers to copy the image data into.
        cbtU8* leftPixel = new cbtU8[_bytesPerPixel];
        cbtU8* rightPixel = new cbtU8[_bytesPerPixel];

        // For every row, we need to flip the first and last pixel.
        for (cbtS32 r = 0; r < _height; ++r)
        {
            // Get the pixel data for the current row.
            // Convert it to an unsigned char so that we can iterate byte by byte.
            cbtU8* row = (cbtU8*)_image + (r * bytesPerRow);

            // Swap the first and last pixel, then the second and second last pixel, then the third and third last pixel...
            for (cbtS32 c = 0; c < (_width >> 1); ++c)
            {
                // Get the pixel data for the current pixel and copy it into our temporary buffer.
                // Convert it to an unsigned char so that we can iterate byte by byte.
                memcpy(leftPixel, &row[c * _bytesPerPixel], _bytesPerPixel); // Front Pixel (1st Pixel, 2nd Pixel, 3rd Pixel etc...)
                memcpy(rightPixel, &row[(_width - c - 1) * _bytesPerPixel], _bytesPerPixel); // Back Pixel (Last Pixel, 2nd Last Pixel, 3rd Last Pixel etc...)

                // Copy the data from our temporary buffer back into the image.
                memcpy(&row[c * _bytesPerPixel], rightPixel, _bytesPerPixel);
                memcpy(&row[(_width - c - 1) * _bytesPerPixel], leftPixel, _bytesPerPixel);
            }
        }

        delete[] leftPixel;
        delete[] rightPixel;
    }

    /**
        \brief Private Constructor. All functions should be static. No objects of this class should be created.
    */
    cbtTextureBuilder() {}
    /**
        \brief Private Destructor. All functions should be static. No objects of this class should be created.
    */
    ~cbtTextureBuilder() {}

public:
    static cbtTexture* Create2DTexture(const cbtStr& _name, const cbtStr& _filePath, cbtBool _flipVertical = true, cbtBool _flipHorizontal = false);
    static cbtTexture* CreateCubeMap(const cbtStr& _name, std::array<cbtStr, CBT_CUBEMAP_MAX_SIDES> _filePath, cbtBool _flipVertical = false , cbtBool _flipHorizontal = true);
};

NS_CBT_END