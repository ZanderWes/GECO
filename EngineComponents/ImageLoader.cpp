


#include "ImageLoader.h"



void ImageLoader::loadImage(const char* filename, int size)
{
	std::ifstream infile(filename, std::ios::in | std::ios::binary);

	if (!infile)
	{
		std::cerr << "error loading image: " << filename << std::endl;
        
        //return -1;
	}

	if (size > 0)
		imageData = new unsigned char[size * size];

    if (imageData == NULL)
        std::cerr << "error loading image: " << filename << std::endl;
		//return false;

	infile.seekg(0, std::ios::end);
	int length = infile.tellg();

	infile.seekg(0, std::ios::beg);
	infile.read(reinterpret_cast<char*>(imageData), length);
	infile.close();

	//textureID = imageData;

	//return true;
}

int ImageLoader::getSize()
{
	return size;
}



/*

struct RGB_t
{
    unsigned char red, green, blue;
    unsigned char& operator [] (const int& index)
    {
        switch (index)
        {
        case 0: return red;
        case 1: return green;
        case 2: return blue;
        }
        throw 0;
    }
    RGB_t() :
        red(0), green(0), blue(0)
    { }
    RGB_t(unsigned char red, unsigned char green, unsigned char blue) :
        red(red), green(green), blue(blue)
    { }
    RGB_t(const unsigned char* rgb) :
        red(rgb[0]), green(rgb[1]), blue(rgb[2])
    { }
};


class ImageLoader
{
private:
    // The image data is shared among all instances of the image.
    struct ImageData
    {
        unsigned width;
        unsigned height;
        RGB_t* data;
        unsigned ref_count;
        ImageData(unsigned width, unsigned height, RGB_t* data, unsigned ref_count) :
            width(width),
            height(height),
            data(data),
            ref_count(ref_count)
        { }
    };
    ImageData* f_data;

    void f_free()
    {
        if (f_data != NULL)
            if (--(f_data->ref_count) == 0)
            {
                delete[] f_data->data;
                delete    f_data;
            }
        f_data = NULL;
    }

    ImageData* f_getdata()
    {
        if (f_data == NULL) throw 0;
        return f_data;
    }

public:
    // Defaultly constructed images can only be assigned to
    ImageLoader() :
        f_data(NULL)
    { }

    // Create a new image of (width, height) colors
    ImageLoader(unsigned width, unsigned height) :
        f_data(new ImageData(width, height, new RGB_t[width * height], 1))
    { }

    // Destroy image data only if we are the last referent
    ~ImageLoader()
    {
        f_free();
    }

    // Copy constructors
    ImageLoader(const ImageLoader& image2d)
    {
        *this = const_cast<ImageLoader&>(image2d);
    }

    ImageLoader(ImageLoader& image2d)
    {
        *this = image2d;
    }

    // Assignment operators
    ImageLoader& operator = (const ImageLoader& image2d)
    {
        return *this = const_cast<ImageLoader&>(image2d);
    }

    ImageLoader& operator = (ImageLoader& image2d)
    {
        if (&image2d != this)
        {
            f_free();
            f_data = image2d.f_data;
            f_getdata()->ref_count++;
        }
        return *this;
    }

    // Make a deep copy
    ImageLoader copy()
    {
        ImageLoader result(f_getdata()->width, f_getdata()->height);
        result.f_data->width = f_data->width;
        result.f_data->height = f_data->height;
        result.f_data->ref_count = f_data->ref_count;
        std::copy(
            f_data->data,
            f_data->data + (f_data->width * f_data->height),
            result.f_data->data
        );
        return result;
    }

    // Access the data directly
    // It is stored in row-major format (height rows of width colors).
    RGB_t* data() { return f_getdata()->data; }
    //const RGB_t* data() const { return f_getdata()->data; }

    // Index an individual color
    RGB_t& index(unsigned x, unsigned y)
    {
        if ((x >= f_getdata()->width) or (y >= f_getdata()->height)) throw 0;
        return f_data->data[(y * f_data->height) + x];
    }
    /*const RGB_t& index(unsigned x, unsigned y) const
    {

        if ((x >= f_getdata()->width) or (y >= f_getdata()->height)) throw 0;
        return f_data->data[(y * f_data->height) + x];
    }

    // Information about the image
    unsigned width()  const { return (f_data == NULL) ? 0 : f_data->width; }
    unsigned height() const { return (f_data == NULL) ? 0 : f_data->height; }
    unsigned size()   { return f_getdata()->width * f_getdata()->height; }

    // Play with the [] operators
    struct curry
    {
        ImageLoader* image2d;
        unsigned x;
        curry(ImageLoader* image2d, unsigned x) :
            image2d(image2d),
            x(x)
        { }
        RGB_t& operator [] (unsigned y)
        {
            return image2d->index(x, y);
        }
        const RGB_t& operator [] (unsigned y) const
        {
            return image2d->index(x, y);
        }
    };

    curry operator [] (unsigned x)
    {
        return curry(this, x);
    }
    const curry operator [] (unsigned x) const
    {
        return curry(const_cast<ImageLoader*>(this), x);
    }
};*/

