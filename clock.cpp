#include <stdio.h>
#include <cstdlib>
#include <GL/glut.h>
#include <math.h>

#define PI 3.142857

struct Point {
    GLint x;
    GLint y;
};

Point centerPoint = { 200, 200 };
GLint clockRadius = 150;

double hourHandAngle = 90;
double minuteHandAngle = 30;
double secondHandAngle = 10;

int hourHandLength = 85;
int minuteHandLength = 120;
int secondHandLength = 140;

void drawLine(Point start, Point end, GLfloat red, GLfloat green, GLfloat blue) {
    glColor3f(red, green, blue);
    glBegin(GL_LINES);
    glVertex2i(start.x, start.y);
    glVertex2i(end.x, end.y);
    glEnd();
}

void drawClockCircle(Point center, GLfloat radius, GLfloat red, GLfloat green, GLfloat blue) {
    glColor3f(red, green, blue);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float theta = i * PI / 180.0;
        float x = center.x + radius * cos(theta);
        float y = center.y + radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void displayClock() {
    Point hourHandTip, minuteHandTip, secondHandTip;

    hourHandTip.y = centerPoint.y + (hourHandLength * sin(hourHandAngle));
    hourHandTip.x = centerPoint.x + (hourHandLength * cos(hourHandAngle));

    minuteHandTip.y = centerPoint.y + (minuteHandLength * sin(minuteHandAngle));
    minuteHandTip.x = centerPoint.x + (minuteHandLength * cos(minuteHandAngle));

    secondHandTip.y = centerPoint.y + (secondHandLength * sin(secondHandAngle));
    secondHandTip.x = centerPoint.x + (secondHandLength * cos(secondHandAngle));

    glClear(GL_COLOR_BUFFER_BIT);

    drawClockCircle(centerPoint, clockRadius, 0.7, 0.7, 0.7); // Gray clock face

    drawLine(centerPoint, hourHandTip, 0.0, 0.0, 0.0); // Black hour hand
    drawLine(centerPoint, minuteHandTip, 0.0, 0.0, 0.0); // Black minute hand
    drawLine(centerPoint, secondHandTip, 1.0, 0.0, 0.0); // Red second hand

    // Display numbers at their respective positions
    glColor3f(0.0, 0.0, 0.0); // Black color for numbers
    for (int i = 1; i <= 12; i++) {
        double angle = -(i * 30) * (PI / 180);
        int number_x = centerPoint.x + (clockRadius - 20) * cos(angle);
        int number_y = centerPoint.y + (clockRadius - 20) * sin(angle);

        int num_offset = (i >= 10) ? 10 : 0;
        glRasterPos2i(number_x - num_offset, number_y - 5);
        if (i + 3 <= 12) {
            if (i + 3 > 9) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ((i + 3) % 10) + '0');
            }
            else {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (i + 3) + '0');
            }
        }
        else {
            int k = i - 10;
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, k + '1');
        }
    }

    glFlush();

    minuteHandAngle -= 0.001333333;
    secondHandAngle -= 0.08;
    hourHandAngle -= 0.0002733333;
}

void updateTimer(int value) {
    glutTimerFunc(1000, updateTimer, 1);
    glutPostRedisplay();
}

void initializeGraphics() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glPointSize(1.0f);
    gluOrtho2D(0.0f, 400.0f, 0.0f, 400.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Customized Analog Clock");
    glutDisplayFunc(displayClock);
    initializeGraphics();
    updateTimer(0);
    glutMainLoop();

    return 0;
}