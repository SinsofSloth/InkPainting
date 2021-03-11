#include "InkPainting.h"

void split_image(std::string const input, std::string const output)
{
    std::vector<unsigned char> image;
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, input);
    if (error)
    {
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        exit(0);
    }

    std::vector<unsigned char> layer_FF, layer_EE, layer_88, layer_66;
    for (size_t i = 0; i < image.size(); i+= 4)
    {
        if (image[i + 3] == 0xFF)
        {
            if (layer_FF.empty())
                layer_FF.resize(image.size());
            layer_FF[i] = image[i];
            layer_FF[i + 1] = image[i + 1];
            layer_FF[i + 2] = image[i + 2];
            layer_FF[i + 3] = 0xFF;
        }
        else if (image[i + 3] == 0xEE)
        {
            if (layer_EE.empty())
                layer_EE.resize(image.size());
            layer_EE[i] = image[i];
            layer_EE[i + 1] = image[i + 1];
            layer_EE[i + 2] = image[i + 2];
            layer_EE[i + 3] = 0xFF;
        }
        else if (image[i + 3] == 0x88)
        {
          if (layer_88.empty())
                layer_88.resize(image.size());
            layer_88[i] = image[i];
            layer_88[i + 1] = image[i + 1];
            layer_88[i + 2] = image[i + 2];
            layer_88[i + 3] = 0xFF;
        }
        else if (image[i + 3] == 0x66)
        {
            if (layer_66.empty())
                layer_66.resize(image.size());
            layer_66[i] = image[i];
            layer_66[i + 1] = image[i + 1];
            layer_66[i + 2] = image[i + 2];
            layer_66[i + 3] = 0xFF;
        }
    }
    if (!layer_FF.empty())
    {
        std::vector<unsigned char> encoded;
        lodepng::encode(encoded, layer_FF, width, height);
        lodepng::save_file(encoded, output + "_0xFF.png");
    }

    if (!layer_EE.empty())
    {
        std::vector<unsigned char> encoded;
        lodepng::encode(encoded, layer_EE, width, height);
        lodepng::save_file(encoded, output + "_0xEE.png");
    }

    if (!layer_88.empty())
    {
        std::vector<unsigned char> encoded;
        lodepng::encode(encoded, layer_88, width, height);
        lodepng::save_file(encoded, output + "_0x88.png");
    }

    if (!layer_66.empty())
    {
        std::vector<unsigned char> encoded;
        lodepng::encode(encoded, layer_66, width, height);
        lodepng::save_file(encoded, output + "_0x66.png");
    }
}

void merge(std::string const input_FF, std::string const input_EE, std::string const input_88, std::string const input_66, std::string const output)
{
    std::vector<unsigned char> image_FF, image_EE, image_88, image_66, image;
    unsigned int width_FF = 0, width_EE = 0, width_88 = 0, width_66 = 0, width = 0;
    unsigned int height_FF = 0, height_EE = 0, height_88 = 0, height_66 = 0, height = 0;

    if (!input_FF.empty())
    {            
        lodepng::decode(image_FF, width_FF, height_FF, input_FF);
        if (width == 0 && height == 0 && image.empty())
        {
            width = width_FF;
            height = height_FF;
            image.resize(image_FF.size());
        }
        for (size_t i = 0; i < image.size(); i+= 4)
        {
            if (image_FF[i + 3] > 0)
            {
                image[i] = image_FF[i];
                image[i + 1] = image_FF[i + 1];
                image[i + 2] = image_FF[i + 2];
                image[i + 3] = 0xFF;
            }
        }
    }
    if (!input_88.empty())
    {
        lodepng::decode(image_88, width_88, height_88, input_88);
        if (width == 0 && height == 0 && image.empty())
        {
            width = width_88;
            height = height_88;
            image.resize(image_88.size());
        }
        for (size_t i = 0; i < image_88.size(); i+= 4)
        {
            if (image_88[i + 3] > 0 && 0x88 > image[i + 3])
            {  
                image[i] = image_88[i];
                image[i + 1] = image_88[i + 1];
                image[i + 2] = image_88[i + 2];
                image[i + 3] = 0x88;
            }
        }
    }
    if (!input_66.empty())
    {
        lodepng::decode(image_66, width_66, height_66, input_66);
        if (width == 0 && height == 0 && image.empty())
        {
            width = width_66;
            height = height_66;
            image.resize(image_66.size());
        }
        for (size_t i = 0; i < image_66.size(); i+= 4)
        {
            if (image_66[i + 3] > 0 && 0x66 > image[i + 3])
            {  
                image[i] = image_EE[i];
                image[i + 1] = image_EE[i + 1];
                image[i + 2] = image_EE[i + 2];
                image[i + 3] = 0x66;
            }
        }
    }
    if (!input_EE.empty())
    {
        lodepng::decode(image_EE, width_EE, height_EE, input_EE);
        if (width == 0 && height == 0 && image.empty())
        {
            width = width_EE;
            height = height_EE;
            image.resize(image_FF.size());
        }
        for (size_t i = 0; i < image.size(); i+= 4)
        {
            if (image_EE[i + 3] > 0 && 0xEE > image[i + 3])
            {  
                image[i] = image_EE[i];
                image[i + 1] = image_EE[i + 1];
                image[i + 2] = image_EE[i + 2];
                image[i + 3] = 0xEE;
            }
        }
    }
    std::vector<unsigned char> encoded;
    lodepng::encode(encoded, image, width, height);
    lodepng::save_file(encoded, output + ".png");
}

void parse(int argc, char* argv[])
{
    try
    {
        cxxopts::Options options(argv[0], " - example command line options");
        options
            .positional_help("[optional args]")
            .show_positional_help()
            .allow_unrecognised_options()
            .add_options()
            ("output", "Output filename. Required for all top-level options.", cxxopts::value<std::string>(), "[output]")
            ("split", "Split raster image into layers.", cxxopts::value<std::string>(), "[input]")
            ("merge", "Merge layers into one raster image.");

        options
            .add_options("Merge")
            ("0xFF", "A layer with an alpha layer of 0xFF.", cxxopts::value<std::string>(), "[input]")
            ("0xEE", "A layer with an alpha layer of 0xEE. This layer will always be the first drawn in the game.", cxxopts::value<std::string>(), "[input]")
            ("0x88", "A layer with an alpha layer of 0x88.", cxxopts::value<std::string>(), "[input]")
            ("0x66", "A layer with an alpha layer of 0x66.", cxxopts::value<std::string>(), "[input]");

        auto result = options.parse(argc, argv);

        if (result.count("split") && !result["split"].as<std::string>().empty())
        {
            if (!result.count("output"))
            {
                std::cout << options.help() << std::endl;
                exit(0);
            }
            else {
                split_image(result["split"].as<std::string>(), result["output"].as<std::string>());
            }
        }
        else if (result.count("merge")) 
        {
            if (!result.count("output"))
            {
                std::cout << options.help() << std::endl;
                exit(0);
            }
            else
            {
                std::string layer_FF, layer_EE, layer_88, layer_66;
                if (result.count("0xFF") && !result["0xFF"].as<std::string>().empty())
                {
                    layer_FF = result["0xFF"].as<std::string>();
                }
                if (result.count("0xEE") && !result["0xEE"].as<std::string>().empty())
                {
                    layer_EE = result["0xEE"].as<std::string>();
                }
                if (result.count("0x88") && !result["0x88"].as<std::string>().empty())
                {
                    layer_88 = result["0x88"].as<std::string>();
                }
                if (result.count("0x66") && !result["0x66"].as<std::string>().empty())
                {
                    layer_66 = result["0x66"].as<std::string>();
                }
                merge(layer_FF, layer_EE, layer_88, layer_66, result["output"].as<std::string>());
            }
        }
        else
        {
            std::cout << options.help() << std::endl;
            exit(0);
        }
    }
    catch (const cxxopts::OptionException& e)
    {
        std::cout << "error parsing options: " << e.what() << std::endl;
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    parse(argc, argv);
}