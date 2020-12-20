
#include <GL/glut.h>
#include <iostream>
#include "math.h"

const float sizeOneCross = 0.01f;
//const float sizeOneCross = 0.0175f;

struct Point {
public:
    float x;
    float y;

    Point(float x, float y) {
        this->x = x;
        this->y = y;
    }
};

void drawSquare(float x1, float x2, float y1, float y2, bool drawLine = true) {

    glBegin(GL_POLYGON);
    glVertex2d(x1, y1);
    glVertex2d(x1, y2);
    glVertex2d(x2, y2);
    glVertex2d(x2, y1);
    glEnd();

    if (!drawLine) {
        return;
    }

    glLineWidth(2.5);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x1, y2);

    glVertex2d(x1, y2);
    glVertex2d(x2, y2);

    glVertex2d(x2, y2);
    glVertex2d(x2, y1);

    glVertex2d(x2, y1);
    glVertex2d(x1, y1);
    glEnd();
}

void drawCycle(float x, float y, float radius, GLubyte r, GLubyte g, GLubyte b, bool drawBorder = true) {
    float x1 = x;
    float y1 = y;
    if (drawBorder) {
        for (double i = 0; i <= 360;) {
            glBegin(GL_TRIANGLES);
            x = x1 + radius * cos(i);
            y = y1 + radius * sin(i);
            glVertex2d(x, y);
            i = i + .5;
            x = x1 + radius * cos(i);
            y = y1 + radius * sin(i);
            glVertex2d(x, y);
            glVertex2d(x1, y1);
            glEnd();
            i = i + .5;
        }
        glEnd();
    }

    radius -= 0.003f;
    glColor3ub(r, g, b);
    for (double i = 0; i <= 360;) {
        glBegin(GL_TRIANGLES);
        x = x1 + radius * cos(i);
        y = y1 + radius * sin(i);
        glVertex2d(x, y);
        i = i + .5;
        x = x1 + radius * cos(i);
        y = y1 + radius * sin(i);
        glVertex2d(x, y);
        glVertex2d(x1, y1);
        glEnd();
        i = i + .5;
    }
    glEnd();
}

void drawFigure(Point *points, int length, float x, float y, GLbyte r, GLbyte g, GLbyte b, bool drawlines = true) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < length; i++) {
        auto el = points[i];
        glVertex2f(el.x - x, el.y + y);
    }
    glEnd();

    if (!drawlines) {
        return;
    }

    glColor3ub(r, g, b);

    glLineWidth(1);
    glBegin(GL_LINES);
    for (int i1 = 0; i1 < length - 1; i1++) {
        auto el1 = points[i1];
        auto el2 = points[i1 + 1];
        glVertex2f(el1.x - x, el1.y + y);
        glVertex2f(el2.x - x, el2.y + y);
    }

    glVertex2f(points[length - 1].x - x, points[length - 1].y + y);
    glVertex2f(points[0].x - x, points[0].y + y);
    glEnd();
}

void pointUpdate(Point *points, int length) {
    for (int i = 0; i < length; i++) {
        points[i].x *= sizeOneCross;
        points[i].y *= sizeOneCross;
    }
}


void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(45, 15, 4);
    drawSquare(0.8f, -0.8f, 0.8f, -0.8f);

    glColor3ub(45, 15, 4);
    drawSquare(0.7f, -0.7f, 0.7f, -0.7f);

    //Рисуем поле
    for (int i = 0; i < 8; i++) {
        float
                y1 = 0.7f - 0.175 * i,
                y2 = 0.7f - 0.175 * i - 0.175;

        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                glColor3ub(215, 169, 109);
            } else {
                glColor3ub(140, 70, 10);
            }
            float
                    x1 = 0.7f - 0.175 * j,
                    x2 = 0.7f - 0.175 * j - 0.175;

            drawSquare(x1, x2, y1, y2);
        }
    }

    // Рисуем пешки

    float lenghtPoints = 10;
    auto *points = new Point[10]{
            *new Point(8, 8),
            *new Point(6, 4),
            *new Point(7, 3),
            *new Point(11, 3),
            *new Point(12, 4),
            *new Point(10, 8),
            *new Point(11, 8),
            *new Point(11, 9),
            *new Point(7, 9),
            *new Point(7, 8)
    };

    pointUpdate(points, lenghtPoints);

    float y1 = 0.7f - 0.175f * 2;
    float y2 = 0.7f - 0.175f * 7;
    float x = 0.7f;
    for (int i = 0; i < 8; i++) {
        glColor3ub(00, 00, 00);
        drawFigure(points, lenghtPoints, x, y1, 255, 255, 255);
        glColor3ub(255, 255, 255);
        drawCycle(x - 8.5 * sizeOneCross, y1 + 11 * sizeOneCross, 0.02f, 0, 0, 0);


        glColor3ub(255, 255, 255);
        drawFigure(points, lenghtPoints, x, y2, 0, 0, 0);
        glColor3ub(0, 0, 0);
        drawCycle(x - 8.5 * sizeOneCross, y2 + 11 * sizeOneCross, 0.02f, 255, 255, 255);

        x -= 0.175f;
    }

    // рисукем Слонов

    lenghtPoints = 20;
    points = new Point[20]{
            *new Point(6, 9),
            *new Point(6, 5),
            *new Point(4, 3),
            *new Point(5, 2),
            *new Point(9, 2),
            *new Point(10, 3),
            *new Point(8, 5),
            *new Point(8, 9),
            *new Point(8.5, 9),
            *new Point(8.5, 10),
            *new Point(9, 10),
            *new Point(9, 11),
            *new Point(7.5, 11),
            *new Point(7.5, 10),
            *new Point(6.5, 10),
            *new Point(6.5, 11),
            *new Point(5, 11),
            *new Point(5, 10),
            *new Point(5.5, 10),
            *new Point(5.5, 9),
    };

    int sizeElement = 6;
    const int sizeSquare = 4;

    pointUpdate(points, lenghtPoints);

    Point **figures = new Point *[6]{
            new Point[sizeSquare]{
                    points[2],
                    points[3],
                    points[4],
                    points[5],
            },
            new Point[sizeSquare]{
                    points[2],
                    points[5],
                    points[6],
                    points[1]
            },
            new Point[sizeSquare]{
                    points[1],
                    points[6],
                    points[7],
                    points[0]
            },
            new Point[sizeSquare]{
                    points[19],
                    points[18],
                    points[9],
                    points[8]
            },
            new Point[sizeSquare]{
                    points[10],
                    points[11],
                    points[12],
                    points[13]
            },
            new Point[sizeSquare]{
                    points[14],
                    points[15],
                    points[16],
                    points[17]
            }
    };

    const float leftUpAngle = 0.7f;
    const float sizeOneFigureCross = 0.175f;

    auto pointFerz = new Point[4]{
            *new Point(leftUpAngle, leftUpAngle - sizeOneFigureCross),
            *new Point(leftUpAngle, leftUpAngle - sizeOneFigureCross * 8),
            *new Point(leftUpAngle - sizeOneFigureCross * 7, leftUpAngle - sizeOneFigureCross),
            *new Point(leftUpAngle - sizeOneFigureCross * 7, leftUpAngle - sizeOneFigureCross * 8)
    };

    for (int j = 0; j < 4; j++) {
        auto color = j % 2 == 0 ? 0 : 255;
        auto pointfer = pointFerz[j];
        glColor3ub(color, color, color);
        for (int i = 0; i < sizeElement; i++) {
            glColor3ub(color, color, color);
            auto borderColor = color == 0 ? 255 : 0;
            drawFigure(figures[i], sizeSquare, pointfer.x, pointfer.y, borderColor, borderColor, borderColor);
        }
    }

    /**
     * Рисуем коняшек
     */


    lenghtPoints = 12;
    points = new Point[12]{
            *new Point(8, 4),
            *new Point(10, 2),
            *new Point(13, 2),
            *new Point(15, 4),
            *new Point(13.5, 11),
            *new Point(13, 13),
            *new Point(12.5, 14),
            *new Point(12, 13),
            *new Point(10, 13),
            *new Point(7, 11),
            *new Point(8, 9),
            *new Point(10, 11),
    };

    sizeElement = 5;
    pointUpdate(points, lenghtPoints);
    figures = new Point *[5]{
            new Point[sizeSquare]{
                    points[0],
                    points[1],
                    points[2],
                    points[3],
            },
            new Point[sizeSquare]{
                    points[11],
                    points[0],
                    points[3],
                    points[4]
            },
            new Point[sizeSquare]{
                    points[4],
                    points[5],
                    points[8],
                    points[11]
            },
            new Point[sizeSquare]{
                    points[5],
                    points[6],
                    points[8],
                    points[6]
            },
            new Point[sizeSquare]{
                    points[8],
                    points[9],
                    points[10],
                    points[11]
            }
    };


    pointFerz = new Point[4]{
            *new Point(leftUpAngle - sizeOneFigureCross, leftUpAngle - sizeOneFigureCross),
            *new Point(leftUpAngle - sizeOneFigureCross, leftUpAngle - sizeOneFigureCross * 8),
            *new Point(leftUpAngle - sizeOneFigureCross * 6, leftUpAngle - sizeOneFigureCross),
            *new Point(leftUpAngle - sizeOneFigureCross * 6, leftUpAngle - sizeOneFigureCross * 8)
    };

    for (int j = 0; j < 4; j++) {
        auto color = j % 2 == 0 ? 0 : 255;
        auto pointfer = pointFerz[j];
        glColor3ub(color, color, color);
        for (int i = 0; i < sizeElement; i++) {
            glColor3ub(color, color, color);
            auto borderColor = color == 0 ? 255 : 0;
            drawFigure(figures[i], sizeSquare, pointfer.x, pointfer.y, borderColor, borderColor, borderColor);
        }
    }

    /**
     * Рисуеум Короля
     */

    lenghtPoints = 22;
    points = new Point[22]{
            *new Point(6.5, 5),
            *new Point(7, 4),
            *new Point(12, 4),
            *new Point(12.5, 5),
            *new Point(10, 9),
            *new Point(10.5, 14),
            *new Point(11, 14),
            *new Point(10.5, 15),
            *new Point(11, 16),
            *new Point(10, 16),
            *new Point(11, 17),
            *new Point(11, 18),
            *new Point(10, 19),
            *new Point(9, 19),
            *new Point(8, 18),
            *new Point(8, 17),
            *new Point(9, 16),
            *new Point(8, 16),
            *new Point(8.5, 15),
            *new Point(8, 14),
            *new Point(8.5, 14),
            *new Point(9, 9),

    };

    sizeElement = 7;
    for (int i = 0; i < lenghtPoints; i++) {
        points[i].y -= 3;
    }
    pointUpdate(points, lenghtPoints);
    figures = new Point *[7]{
            new Point[sizeSquare]{
                    points[0],
                    points[1],
                    points[2],
                    points[3],
            },
            new Point[sizeSquare]{
                    points[0],
                    points[3],
                    points[4],
                    points[21]
            },
            new Point[sizeSquare]{
                    points[4],
                    points[5],
                    points[20],
                    points[21]
            },
            new Point[sizeSquare]{
                    points[19],
                    points[6],
                    points[7],
                    points[18]
            },
            new Point[sizeSquare]{
                    points[17],
                    points[18],
                    points[7],
                    points[8]
            },
            new Point[sizeSquare]{
                    points[9],
                    points[16],
                    points[12],
                    points[13]
            },
            new Point[sizeSquare]{
                    points[10],
                    points[11],
                    points[14],
                    points[15]
            }
    };


    pointFerz = new Point[2]{
            *new Point(leftUpAngle - sizeOneFigureCross * 4, leftUpAngle - sizeOneFigureCross),
            *new Point(leftUpAngle - sizeOneFigureCross * 4, leftUpAngle - sizeOneFigureCross * 8)
    };
    for (int j = 0; j < 2; j++) {
        auto color = j % 2 == 0 ? 0 : 255;
        auto pointfer = pointFerz[j];
        glColor3ub(color, color, color);
        for (int i = 0; i < sizeElement; i++) {
            glColor3ub(color, color, color);
            auto borderColor = color == 0 ? 255 : 0;
            drawFigure(figures[i], sizeSquare, pointfer.x, pointfer.y, borderColor, borderColor, borderColor);
        }
    }

    /**
    * Рисуеум королеву
    */

    lenghtPoints = 18;
    points = new Point[18]{
            *new Point(6, 2),
            *new Point(7, 1),
            *new Point(12, 1),
            *new Point(13, 2),
            *new Point(10, 5),
            *new Point(11, 11),
            *new Point(11.5, 11),
            *new Point(11, 12),
            *new Point(11.5, 14),
            *new Point(11, 14),
            *new Point(10, 15),
            *new Point(9, 15),
            *new Point(8, 14),
            *new Point(7.5, 14),
            *new Point(8, 12),
            *new Point(7.5, 11),
            *new Point(8, 11),
            *new Point(9, 5),
    };

    sizeElement = 6;
    pointUpdate(points, lenghtPoints);
    figures = new Point *[6]{
            new Point[sizeSquare]{
                    points[0],
                    points[1],
                    points[2],
                    points[3],
            },
            new Point[sizeSquare]{
                    points[0],
                    points[3],
                    points[4],
                    points[17]
            },
            new Point[sizeSquare]{
                    points[17],
                    points[4],
                    points[5],
                    points[16]
            },
            new Point[sizeSquare]{
                    points[15],
                    points[6],
                    points[7],
                    points[14]
            },
            new Point[sizeSquare]{
                    points[7],
                    points[8],
                    points[13],
                    points[14]
            },
            new Point[sizeSquare]{
                    points[9],
                    points[10],
                    points[11],
                    points[12]
            }
    };


    pointFerz = new Point[2]{
            *new Point(leftUpAngle - sizeOneFigureCross * 3, leftUpAngle - sizeOneFigureCross),
            *new Point(leftUpAngle - sizeOneFigureCross * 3, leftUpAngle - sizeOneFigureCross * 8)
    };
    for (int j = 0; j < 2; j++) {
        auto color = j % 2 == 0 ? 0 : 255;
        auto pointfer = pointFerz[j];
        glColor3ub(color, color, color);
        for (int i = 0; i < sizeElement; i++) {
            glColor3ub(color, color, color);
            auto borderColor = color == 0 ? 255 : 0;
            drawFigure(figures[i], sizeSquare, pointfer.x, pointfer.y, borderColor, borderColor, borderColor);
        }
    }


    /**
     * Рисуеум ферзей
     */

    lenghtPoints = 15;
    points = new Point[15]{
            *new Point(8, 4),
            *new Point(9, 3),
            *new Point(12, 3),
            *new Point(13, 4),
            *new Point(11, 7),
            *new Point(11.5, 9),
            *new Point(12, 9),
            *new Point(11.5, 10),
            *new Point(10.5, 10),
            *new Point(11.5, 12),
            *new Point(10.5, 14),
            *new Point(9.5, 12),
            *new Point(9.5, 10),
            *new Point(9, 9),
            *new Point(10, 7),

    };

    sizeElement = 5;
    pointUpdate(points, lenghtPoints);
    figures = new Point *[5]{
            new Point[sizeSquare]{
                    points[0],
                    points[1],
                    points[2],
                    points[3],
            },
            new Point[sizeSquare]{
                    points[0],
                    points[3],
                    points[4],
                    points[14]
            },
            new Point[sizeSquare]{
                    points[14],
                    points[4],
                    points[6],
                    points[13]
            },
            new Point[sizeSquare]{
                    points[13],
                    points[6],
                    points[7],
                    points[12]
            },
            new Point[sizeSquare]{
                    points[8],
                    points[9],
                    points[10],
                    points[11]
            }
    };


    pointFerz = new Point[4]{
            *new Point(leftUpAngle - sizeOneFigureCross * 2, leftUpAngle - sizeOneFigureCross),
            *new Point(leftUpAngle - sizeOneFigureCross * 2, leftUpAngle - sizeOneFigureCross * 8),
            *new Point(leftUpAngle - sizeOneFigureCross * 5, leftUpAngle - sizeOneFigureCross),
            *new Point(leftUpAngle - sizeOneFigureCross * 5, leftUpAngle - sizeOneFigureCross * 8)
    };

    for (int j = 0; j < 4; j++) {
        auto color = j % 2 == 0 ? 0 : 255;
        auto pointfer = pointFerz[j];
        glColor3ub(color, color, color);
        for (int i = 0; i < sizeElement; i++) {
            glColor3ub(color, color, color);
            auto borderColor = color == 0 ? 255 : 0;
            drawFigure(figures[i], sizeSquare, pointfer.x, pointfer.y, borderColor, borderColor, borderColor);
        }
    }

    glFlush();
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Dmitriev Yury. Chess");
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glutInitWindowPosition(50, 50);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}