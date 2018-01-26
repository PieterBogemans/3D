#include "imaging/ppm-format.h"
#include <bitset>

using namespace imaging;

namespace
{
	struct RGBColor
	{
		uint8_t r, g, b;

		RGBColor(const Color& c)
		{
			Color clamped = c.clamped();

			r = uint8_t(clamped.r * 255);
			g = uint8_t(clamped.g * 255);
			b = uint8_t(clamped.b * 255);
		}
	};
}

namespace imaging
{
	void write_text_ppm(const Bitmap& bitmap, std::ostream& out)
	{
		uint32_t width = bitmap.width();
		uint32_t height = bitmap.height();

		out << "P3\n"	<< width << " " << height << "\n" 	<< "255\n";

		for (unsigned i = 0; i != height; i++)
		{
			for (unsigned j = 0; j != width; j++)
			{
				Color color(bitmap[Position2D(j, i)]);
				RGBColor rgb(color);
				out << rgb.r << " " << rgb.g << " " << rgb.b << "	";
			}
			out << "\n";
		}
	}
}