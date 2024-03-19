#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

int emojiX = 400;
int emojiY = 30;

void scanLineFillRectangle(int x1, int y1, int x2, int y2, int fill_color);
void rotatePoint(int *x, int *y, int cx, int cy, double theta);
void drawEmojiWithRotationAndTranslation(int x, int y, double rotationAngle, int xTranslation, int yTranslation);
void reflectEmoji(int *x, int *y, int centerX, int centerY, char axis);

void scanLineFillRectangle(int x1, int y1, int x2, int y2, int fill_color) {
    int x, y;
    for (x = x1 + 1; x < x2; x++) {
        for (y = y1 + 1; y < y2; y++) {
            if (!getpixel(x, y)) {
                putpixel(x, y, fill_color);
            }
        }
    }
}

void rotatePoint(int *x, int *y, int cx, int cy, double theta) {
    double cosTheta = cos(theta * (PI / 180.0));  // Convert degrees to radians
    double sinTheta = sin(theta * (PI / 180.0));  // Convert degrees to radians
    int tempX = *x - cx;
    int tempY = *y - cy;
    *x = (int)(tempX * cosTheta - tempY * sinTheta) + cx;
    *y = (int)(tempX * sinTheta + tempY * cosTheta) + cy;
}

void drawEmojiWithRotationAndTranslation(int x, int y, double rotationAngle, int xTranslation, int yTranslation) {
    int cx, cy;
    int leftEyeX, leftEyeY;
    int rightEyeX, rightEyeY;
    int mouthX, mouthY;
    int rectLeft, rectTop, rectRight, rectBottom;
    cx = x + 100;
    cy = y + 90;

    // Rotate the features around the center of the circle
    leftEyeX = x + 55;
    leftEyeY = y + 55;
    rotatePoint(&leftEyeX, &leftEyeY, cx, cy, rotationAngle);

    rightEyeX = x + 125;
    rightEyeY = y + 55;
    rotatePoint(&rightEyeX, &rightEyeY, cx, cy, rotationAngle);

    // Calculate the mouth's position relative to the center
    mouthX = cx; // Mouth should be at the center of the circle
    mouthY = cy + 30; // Mouth should be above the center of the circle by 50 pixels
    rotatePoint(&mouthX, &mouthY, cx, cy, rotationAngle);

    // Draw the circle
    circle(cx, cy, 80);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(cx, cy, WHITE);

    // Draw the eyes
    line(leftEyeX, leftEyeY, leftEyeX + 20, leftEyeY + 25);
    line(leftEyeX + 40, leftEyeY, leftEyeX + 20, leftEyeY + 25);
    arc(leftEyeX + 10, leftEyeY, 0, 180, 10);
    arc(leftEyeX + 30, leftEyeY, 0, 180, 10);
    setfillstyle(SOLID_FILL, RED);
    floodfill(leftEyeX + 20, leftEyeY + 5, WHITE);

    line(rightEyeX, rightEyeY, rightEyeX + 20, rightEyeY + 25);
    line(rightEyeX + 40, rightEyeY, rightEyeX + 20, rightEyeY + 25);
    arc(rightEyeX + 10, rightEyeY, 0, 180, 10);
    arc(rightEyeX + 30, rightEyeY, 0, 180, 10);
    floodfill(rightEyeX + 20, rightEyeY + 5, WHITE);

    // Draw the mouth
    arc(mouthX, mouthY, 200, 340, 38);
    arc(mouthX, mouthY - 88, 250, 290, 108);
    setfillstyle(SOLID_FILL, BROWN);
    floodfill(mouthX, mouthY + 20, WHITE);

    // Draw the rectangle around the emoji
    rectLeft = x;
    rectTop = y;
    rectRight = x + 200;
    rectBottom = y + 180;
    rectangle(rectLeft, rectTop, rectRight, rectBottom);
    scanLineFillRectangle(rectLeft, rectTop, rectRight, rectBottom, BLUE);
}

void reflectEmoji(int *x, int *y, int centerX, int centerY, char axis) {
    // Reflect the features (eyes and mouth) across the specified axis
    if (axis == 'x') {
        *x = 2 * centerX - *x;
    } else if (axis == 'y') {
        *y = 2 * centerY - *y;
    } else if (axis == 'd') { // Diagonal reflection
        int temp = *x;
        *x = *y;
        *y = temp;
    }
}

int main() {
    int gd = DETECT, gm;
    int choice;
    double rotationAngle = 0;
    int xTranslation = 0, yTranslation = 0;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);

    do {
        printf("Menu:\n");
        printf("1. Translate the emoji\n");
        printf("2. Rotate the emoji\n");
        printf("3. Reflect the emoji with respect to X-axis\n");
        printf("4. Reflect the emoji with respect to Y-axis\n");
        printf("5. Reflect the emoji with respect to the diagonal\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter translation coordinates (x y): ");
                scanf("%d %d", &xTranslation, &yTranslation);
                cleardevice();
                line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
                line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
                drawEmojiWithRotationAndTranslation(emojiX + xTranslation, emojiY + yTranslation, rotationAngle, 0, 0);
                break;
            case 2:
                printf("Enter rotation angle in degrees: ");
                scanf("%lf", &rotationAngle);
                cleardevice();
                line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
                line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
                drawEmojiWithRotationAndTranslation(emojiX, emojiY, rotationAngle, 0, 0);
                break;
            case 3:
                cleardevice();
                line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
                line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
                reflectEmoji(&emojiX, &emojiY, getmaxx() / 2, getmaxy() / 2, 'x');
                drawEmojiWithRotationAndTranslation(emojiX, emojiY, rotationAngle, 0, 0);
                break;
            case 4:
                cleardevice();
                line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
                line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
                reflectEmoji(&emojiX, &emojiY, getmaxx() / 2, getmaxy() / 2, 'y');
                drawEmojiWithRotationAndTranslation(emojiX, emojiY, rotationAngle, 0, 0);
                break;
            case 5:
                cleardevice();
                line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
                line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
                reflectEmoji(&emojiX, &emojiY, getmaxx() / 2, getmaxy() / 2, 'd');
                drawEmojiWithRotationAndTranslation(emojiX, emojiY, rotationAngle, 0, 0);
                break;
            case 6:
                closegraph();
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 6);

    getch();
    closegraph();
    return 0;
}
