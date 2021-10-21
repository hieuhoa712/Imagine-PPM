#include "ImageMaker.h"
#include <cmath>

//Default constructor
ImageMaker::ImageMaker() {
    image[0][0][3];
    pen_blue = 0;
    pen_green = 0;
    pen_red = 0;
    width = 0;
    height = 0;
    for(int i = 0; i < MAX_WIDTH;i++){
        for(int j = 0; j< MAX_HEIGHT;j++ ){
            image[j][i][RED] = 255;
            image[j][i][GREEN] = 255;
            image[j][i][BLUE] = 255;
        }
    }


}

//Default constructor when chosen a file
ImageMaker::ImageMaker(string filename) {
    ImageMaker files;
    files.LoadImage(filename);
    height = files.GetHeight();
    width = files.GetWidth();
    for(int i = 0; i < height;i++){
        for(int j = 0; j< width;j++ ){
            int red = files.GetPenRed();
            int green = files.GetPenGreen();
            int blue = files.GetPenBlue();
            image[j][i][RED] = red;
            image[j][i][GREEN] = green;
            image[j][i][BLUE] = blue;
        }
    }

}

// Opens image with filename and stores information into
void ImageMaker::LoadImage(string filename) {
    ifstream file;
    int loadColor, loadWidth, loadHeight, pixelR, pixelG, pixelB;
    string magicNumber = "P3";
    //Open file
    file.open (filename);
    //Check if file can be opened
    if(file.is_open()){
        //Retrieving value from file
        file >> magic >> loadWidth >> loadHeight >> loadColor;
        SetWidth(loadWidth);
        SetHeight(loadHeight);
        //Check if magic number is not correct
        if(magic.find(magicNumber) == string::npos){
            throw "Bad magic number";
        }
        //Check if color range is > 255
        if(loadColor > 255){
            throw "Max color range not 255";
        }

        //Pasting the value
        for(int i = 0; i < loadHeight;i++){
            for(int j = 0; j< loadWidth;j++ ){
                file >> pixelR >> pixelG >> pixelB;
                if(pixelR > 255 || pixelG > 255 || pixelB > 255){
                    throw "Color value invalid";
                }
                SetPenBlue(pixelB);
                SetPenGreen(pixelG);
                SetPenRed(pixelR);
                image[j][i][RED] = pixelR;
                image[j][i][GREEN] = pixelG;
                image[j][i][BLUE] = pixelB;
            }
        }
    }
    //File cannot be opened
    else{
        throw "File failed to open";
    }
    //Close file
    file.close();
}

//Save the imagine to the chosen filename
void ImageMaker::SaveImage(string filename) {
    ofstream ofs;
    //Open file
    ofs.open(filename);
    ofs << "P3\n" << GetWidth() << " " << GetHeight() << "\n" << MAX_COLOR << endl;
    //Check if we are saving an invalid file
    if (GetWidth() == 0 || GetHeight() == 0) {
        throw "Image must have non-zero dimensions";
    }
    //Pasting the value
    for(int i = 0; i < height;i++){
        for(int j = 0; j< width;j++ ){
            ofs << image[j][i][RED] << " ";
            ofs << image[j][i][GREEN] << " ";
            ofs << image[j][i][BLUE] << "  ";
        }
        ofs << "\n";
    }
    //Close file
    ofs.close();

}

//Retrieve the width value
int ImageMaker::GetWidth()   {
    return width;
}

//Retrieve the height value
int ImageMaker::GetHeight()  {
    return height;
}

//Set the value of the width of the ppm file
void ImageMaker::SetWidth(int newWidth) {
    if (newWidth < 0 || newWidth > MAX_WIDTH) {
        throw "Width out of bounds";
    }
    width = newWidth;
}

//Set the value of the height of the ppm file
void ImageMaker::SetHeight(int newHeight) {
    if (newHeight < 0 || newHeight > MAX_HEIGHT) {
        throw "Height out of bounds";
    }
    height = newHeight;
}

//Get the value of pen_red
int ImageMaker::GetPenRed() {
    return pen_red;
}

//Get the value of pen_green
int ImageMaker::GetPenGreen() {
    return pen_green;
}

//Get the value of pen_blue
int ImageMaker::GetPenBlue() {
    return pen_blue;
}

//Set the color value of pen_red
void ImageMaker::SetPenRed(int newR) {
    if (newR < 0 || newR > MAX_COLOR) {
        throw "Color value invalid";
    }
    pen_red = newR;
}

//Set the color value of pen_green
void ImageMaker::SetPenGreen(int newG) {
    if (newG < 0 || newG > MAX_COLOR) {
        throw "Color value invalid";
    }
    pen_green = newG;
}

//Set the color value of pen_blue
void ImageMaker::SetPenBlue(int newB) {
    if (newB < 0 || newB > MAX_COLOR) {
        throw "Color value invalid";
    }
    pen_blue = newB;
}

//Draw a single pixel
void ImageMaker::DrawPixel(int x, int y) {
    //Exception Check
    if (x < 0 || y < 0 || x >= GetWidth() || y >= GetHeight()) {
        throw "Point out of bounds";
    }

    //RGB Element
    image[x][y][RED] = pen_red;
    image[x][y][BLUE] = pen_blue;
    image[x][y][GREEN] = pen_green;
}

//Draw a Rectangle
void ImageMaker::DrawRectangle(int x1, int y1, int x2, int y2) {
    DrawLine(x1, y1, x1, y2); //Vertical 1 (Left side)
    DrawLine(x1, y1, x2, y1); //Horizontal 1 (Top)
    DrawLine(x2, y2, x2, y1); //Vertical 2 (Right side)
    DrawLine(x2, y2, x1, y2); //Horizontal 2 (Bottom)

}

//Draw a line
void ImageMaker::DrawLine(int x1, int y1, int x2, int y2) {
    //Condition Check
    if (x1 < 0 || y1 < 0 || x1 >= GetWidth() || y1 >= GetHeight()) {
        throw "Point out of bounds";
    }
    else if (x2 < 0 || y2 < 0 || x2 >= GetWidth() || y2 >= GetHeight()) {
        throw "Point out of bounds";
    }
    //Draw a Dot
    if (x1 == x2 && y1 == y2){
        DrawPixel(x1, y1);
        return;
    }
    //Draw Vertical
    if (x1 == x2){
        //Draw Forward
        for (int j = y1; j <= y2;j++){
            DrawPixel(x1, j);
        }
        //Draw Backward
        for (int j = y2; j <= y1;j++){
            DrawPixel(x1, j);
        }
        return;
    }
    //Draw Horizontal
    if (y1 == y2){
        //Draw Forward
        for (int k = x1; k <= x2;k++){
            DrawPixel(k, y1);
        }
        //Draw Backward
        for (int k = x2; k <= x1;k++){
            DrawPixel(k, y1);
        }
        return;
    }
    //Draw diagonal line
    double slope = double(y2 - y1)/ (x2 - x1);
    double bValue = y1 - slope*(x1);
    //Draw Forward
    for (int i = x1; i <= x2;i++){
        double point = (slope * i) + bValue;
        int roundedPoint = round(point);
        DrawPixel(i, roundedPoint);
    }
    //Draw Backward
    for (int i = x2; i <= x1;i++){
        double point = (slope * i) + bValue;
        int roundedPoint = round(point);
        DrawPixel(i, roundedPoint);
    }
}

bool ImageMaker::PointInBounds(int x, int y) {
    return false;
}
