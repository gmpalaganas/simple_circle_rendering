#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>

#include <GL/freeglut.h>

#define MAX_FRAMES 100000000

#define WIN_HEIGHT 720
#define WIN_WIDTH 720

using namespace std;

struct Point{
    int x;
    int y;

    Point(int x_0, int y_0): x(x_0), y(y_0) {}; }; 

struct Color{
    float r;
    float g;
    float b;

    Color(float r_0, float g_0, float b_0):
        r(r_0), g(g_0), b(b_0) {};
};

typedef struct Point Point;
typedef struct Color Color;

int r = 350;
int x = 0;
int y = 0;

bool running = false;

vector<Point *> points;

Color black(0.0f, 0.0f, 0.0f);
Color red(1.0f, 0.0f, 0.0f);

// Integer Square root
int int_sqrt(int num){
    int res = 0;
    int bit = 1ul << 30;

    while (bit != 0){
        if( num >= res + bit ){
            num -= res + bit;
            res = (res >> 1) + bit;
        } else
            res >>= 1;
        bit >>= 2;
    }

    return res;
}

void clear_points(){
    for(Point *p : points)
        delete p;

    points.clear();
}

void reset_circle(){
    x = 0;
    y = 0;

    clear_points();
}

void draw_point(Point *p, Color *c){
    glBegin(GL_POINTS);
        glColor3f(c->r, c->g, c->b);
        glVertex2i(p->x, p->y);
    glEnd();
}

// Draw circle
void draw_circle(){

    int h = WIN_WIDTH/2;
    int k = WIN_HEIGHT/2;
    
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0f);

    for(Point *point : points){
        draw_point(point, &black);
    }

    if(x <= r && running){
        
        y = int_sqrt((r*r) - (x*x));

        Point *new_point = new Point(h + x, k + y);
        draw_point(new_point, &red);
        points.push_back(new_point);
        
        new_point = new Point(h + x, k - y);
        draw_point(new_point, &red);
        points.push_back(new_point);

        new_point = new Point(h - x, k + y);
        draw_point(new_point, &red);
        points.push_back(new_point);

        new_point = new Point(h - x, k - y);
        draw_point(new_point, &red);
        points.push_back(new_point);

        x++;
    }

    if( x > r)
        reset_circle();

    glutSwapBuffers();

}

void init(){

    glClearColor(1.0f,1.0f,1.0f,0.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0f, float(WIN_WIDTH), 0.0f, float(WIN_HEIGHT));

}

void mouse_action(int button, int m_state, int m_x, int m_y){
    if (button == GLUT_LEFT_BUTTON && m_state == GLUT_DOWN)
        running = !running;
    else if(button == GLUT_RIGHT_BUTTON && m_state == GLUT_DOWN)
        reset_circle();
    
}

void keyboard_action(int key, int x, int y){
    switch(key) {
        case ' ': running = !running; break;
    }
}

int main(int argc , char **argv){

    // init GLUT and Create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutInitWindowSize(WIN_WIDTH,WIN_HEIGHT); // 1280 x 720 Window size
    glutCreateWindow("Circle");
    init();

    glutMouseFunc(mouse_action);

    glutDisplayFunc(draw_circle);
    glutIdleFunc(draw_circle);

    glutMainLoop();

    cout << "Cleaning up..." << endl;

    clear_points();

    return 0;

}
