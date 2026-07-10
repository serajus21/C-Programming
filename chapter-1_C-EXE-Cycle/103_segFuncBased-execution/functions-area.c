// functions-area.c
// area functions to use in main.c

float area_of_circle(float radius) // function to calculate area of a circle
{
    return 3.14159 * radius * radius;
}

float area_of_rectangle(float length, float width) // function to calculate area of a rectangle
{
    return length * width;
}

float area_of_triangle(float base, float height) // function to calculate area of a triangle
{
    return 0.5 * base * height;
}