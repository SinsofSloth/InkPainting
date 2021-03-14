# InkPainting
A command-line tool for FE14-15 sprites.
## Supported Files
- PNG
## Usage
Arguments can be passed like so:
```
--long
--long=argument
--long argument
-a
-ab
-abc argument
```
``InkPainting --split=tmp.png --output=output_file``

Splits raster image into layers based on the alpha of the pixel.

``InkPainting --merge --0xFF=input_file_0xFF.png --0xEE=input_file_0xEE.png --0x88=input_file_0x88.png --0x66=input_file_0x66.png --output=output_file``

Merges raster images into one image based on the alpha of the pixel. 

Note: Order of arguments does not matter, so be wary of the layer order when working with your image editor:

(Firstmost to most last layer) 0xEE > 0x66 > 0x88 > 0xFF

## Building
### Dependencies
- cmake
- C++ compiler with C++11 support
### Compiling
1. Clone the repository either on Github by clicking ``Code`` and clicking ``Download Zip`` on the dropdown and unzipping the download, or with ``git clone https://github.com/SinsofSloth/InkPainting``, if you have git installed.
2. In the root of the downloaded directory:
```
mkdir build
cd build
cmake ../
cmake --build . --config Release
```
## External Libraries
- [lodepng](https://github.com/lvandeve/lodepng)
- [cxxopts](https://github.com/jarro2783/cxxopts)
## License
Distributed under the MIT License. See ``LICENSE`` for more information.
