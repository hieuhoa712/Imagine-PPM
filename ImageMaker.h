#ifndef IMAGEMAKER_H
#define IMAGEMAKER_H

#include <string>
#include <cmath>
#include <fstream>

const int MAX_WIDTH = 800;
const int MAX_HEIGHT = 800;
const int MAX_COLOR = 255;
enum COLOR { RED, GREEN, BLUE };

using namespace std;

class ImageMaker
{
public:
    ImageMaker();
    //Constructor
    ImageMaker(string filename);
    //Constructor that take file input



    // Opens image with filename and stores information into
    void LoadImage(string filename);
    //Pre: String of the filename has been initialized
    //Post: All the private variable has been initialized

    void SaveImage(string filename);
    //Pre: String of the filename has been initialized
    //Post: All the private variable has been saved to the file name

    // Size functions
    //Retrieve the width value
    int GetWidth();
    // Pre:  List has been initialized.
    // Post: Return the value of width

    //Retrieve the height value
    int GetHeight();
    // Pre:  List has been initialized.
    // Post: Return the value of height

    //Set the value of the width of the ppm file
    void SetWidth(int width);
    // Pre:  List has been initialized.
    //      List must not be less than 0 and not be larger than the MAX_Width value
    // Post: Function value = width

    //Set the value of the height of the ppm file
    void SetHeight(int height);
    // Pre:  List has been initialized.
    //      List must not be less than 0 and not be larger than the MAX_Height value
    // Post: Function value = height

    // Color functions
    //Get the value of pen_red
    int GetPenRed();
    // Pre:  List has been initialized.
    // Post: Return the value of red pen

    //Get the value of pen_green
    int GetPenGreen();
    // Pre:  List has been initialized.
    // Post: Return the value of green pen

    //Get the value of pen_blue
    int GetPenBlue();
    // Pre:  List has been initialized.
    // Post: Return the value of blue pen

    //Set the color value of pen_red
    void SetPenRed(int newR);
    // Pre:  List has been initialized.
    //      List must not be less than 0 and not be larger than the MAX_Color value
    // Post: Function value = pen_red

    //Get the value of pen_green
    void SetPenGreen(int newG);
    // Pre:  List has been initialized.
    //      List must not be less than 0 and not be larger than the MAX_Color value
    // Post: Function value = pen_green

    //Get the value of pen_blue
    void SetPenBlue(int newB);
    // Pre:  List has been initialized.
    //      List must not be less than 0 and not be larger than the MAX_Color value
    // Post: Function value = pen_blue

    // Drawing methods
    // These methods will use the current red, green, blue values of the pen
    void DrawPixel(int x, int y);
    // Pre:  List has been initialized.
    //      List must not be less than 0 and not be larger than the width and height value
    //Post: Return the color value at the given coordinate at the input
    void DrawRectangle(int x1, int y1, int x2, int y2);
    // Pre:  List has been initialized.
    //      List must not be less than 0 and not be larger than the width and height value
    //Post: Return the color value at the given coordinate at the input
    //      A rectangle with given color shape will be drawn
    void DrawLine(int x1, int y1, int x2, int y2);
    // Pre:  List has been initialized.
    //      List must not be less than 0 and not be larger than the width and height value
    //Post: Return the color value at the given coordinate at the input
    //      A line with given color value will be drawn

private:
    string magic;
    int width;
    int height;
    int pen_red;    // Used by draw functions
    int pen_green;  // Used by draw functions
    int pen_blue;   // Used by draw functions
    bool PointInBounds(int x, int y);  // Not a bad idea to implement

               //   x          y
    short image[MAX_WIDTH][MAX_HEIGHT][3];
};

#endif //IMAGEMAKER_H
