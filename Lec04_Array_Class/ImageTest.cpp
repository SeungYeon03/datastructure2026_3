#define	HEIGHT	8
#define	WIDTH	8

int image[HEIGHT][WIDTH] = {
  {  10,  30,  55,  80, 120, 160, 200, 230},
  {  20,  45,  70, 100, 140, 180, 220, 210},
  {  35,  60,  90, 130, 170, 210, 240, 190},
  {  50,  80, 115, 150, 190, 230, 255, 170},
  {  40,  65, 100, 140, 175, 215, 235, 150},
  {  25,  50,  80, 115, 155, 195, 210, 130},
  {  15,  35,  60,  90, 130, 165, 185, 110},
  {    5,  20,  40,  70, 105, 140, 160,  90},
};

#include <cstdio>

int findMaxPixel(int img[][WIDTH], int h, int w) {
    int max = img[0][0];

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (img[i][j] > max)
                max = img[i][j];
        }
    }
    return max;
}

int main() {
    printf("Max Brightness = %d\n", findMaxPixel(image, HEIGHT, WIDTH));

    return 0;
}