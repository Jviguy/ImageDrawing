#include <stdio.h>
#include <Windows.h>
#include <WinUser.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <direct.h>

using namespace cv;

int main(int argc, char* argv[]) {
    if (!(argc > 1)) {
        std::cout << "ERROR: invalid usage please provide a proper filepath!" << std::endl;
        return 1;
    }
    HWND console = ::GetConsoleWindow();
    HDC chdc = GetDC(console);
    Mat img = imread(argv[1]);
    char buff[FILENAME_MAX]; //create string buffer to hold path
    if (img.empty()) {
        _getcwd(buff, FILENAME_MAX);
        std::string str(buff);
        str += "/"; str += argv[1];
        img = imread(str);
        if (img.empty()) {
            std::cout << "ERROR: invalid usage please provide a proper filepath!" << std::endl;
            return 1;
        }
    }
    //DISPLAY image
    for (int x = 0; x < img.size().width; x++) for (auto y = 0; y < img.size().height; y++) {
        Vec3b& color = img.at<Vec3b>(y, x);
        ::SetPixel(chdc, x, y, RGB(color[0], color[1], color[3]));
    }
    getchar();
    return 0;
}