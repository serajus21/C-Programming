#include <stdio.h>
#include "prototype.h"

int main()
{
    int x = 0;
    int y = 0;

    printf("Enter two integers: ");
    scanf("%d %d", &x, &y);

    printf("Addition: %d\n", add(x, y));
    printf("Subtraction: %d\n", subtract(x, y));
    printf("Multiplication: %d\n", multiply(x, y));
    printf("Division: %d\n", divide(x, y));

    // ----------------------------Area calculations------------------------------
    // area of circle
    printf("--------------------Area of Circle---------------------\n");

    float radius = 0.0;
    printf("Enter the radius of the circle: ");
    scanf("%f", &radius);
    printf("Area of the circle: %f\n", area_of_circle(radius));

    // area of rectangle
    printf("--------------------Area of Rectangle---------------------\n");

    float length = 0.0;
    float width = 0.0;
    printf("Enter the length and width of the rectangle: ");
    scanf("%f %f", &length, &width);
    printf("Area of the rectangle: %f\n", area_of_rectangle(length, width));

    // area of triangle
    printf("--------------------Area of Triangle---------------------\n");

    float base = 0.0;
    float height = 0.0;
    printf("Enter the base and height of the triangle: ");
    scanf("%f %f", &base, &height);
    printf("Area of the triangle: %f\n", area_of_triangle(base, height));

    return 0;
}