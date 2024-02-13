/*
    collaborators :
        Metsehafe Eyasu     ETS0852/13
        MICHAEL ENGIDA      ETS0859/13
        MOHAMMED MEHAD      ETS0907/13
        MOHAMMED RESTEM     ETS0911/13
        MOHAMMED SHEMIM     ETS0912/13
    Group: G1
    Subject: Computer Graphics
    University: Addis Ababa Science and Technology University
*/

#include<bits/stdc++.h>
#include<conio.h>
#include<GL/glut.h>
using namespace std;

int x_coord, y_coord, dir, state, score, level = 0;
int time_interval, flag = 0, option;
static int menu_id, submenu_id;

class Node
{
    public:
    int j, k, p, q;
    Node *next;
};

void create_new_prey();

class Snake
{
    public:
    Node *head, *tail;

    Snake()
    {
        head = new Node;
        tail = new Node;

        head->p = head->j = 60;
        head->q = head->k = 40;

        tail->p = tail->j = 60;
        tail->p = tail->k = 20;

        head->next = tail;
        tail->next = NULL;
    }

    void erase_position(int m, int n)
    {
        glColor3f(0.0, 0.1, 0.0);
        glBegin(GL_QUADS);
        glVertex2i(m - 10, n + 10);
        glVertex2i(m - 10, n - 10);
        glVertex2i(m + 10, n - 10);
        glVertex2i(m + 10, n + 10);
        glEnd();
    }

    void redraw_position(int m, int n)
    {
        glBegin(GL_QUADS);
        glVertex2i(m - 10, n + 10);
        glVertex2i(m - 10, n - 10);
        glVertex2i(m + 10, n - 10);
        glVertex2i(m + 10, n + 10);
        glEnd();
    }

    bool check_strangled(int x, int y)
    {
        int p[3];
        glReadPixels(
            x, y,
            1, 1,
            GL_RGB, GL_INT,
            &p[0]
        );

        p[0] = p[0] / 2147483647;
        p[1] = p[1] / 2147483647;
        p[2] = p[2] / 2147483647;

        if (p[0] == 0 && p[1] == 1 && p[2] == 1)
            return true;

        return false;
    }

    void move_snake()
    {
        Node* temp;
        bool b;
        int i = 1, f = 0;
        temp = head;

        while (temp != NULL && level != 0)
        {
            if (temp->next != NULL)
            {
                temp->next->p = temp->j;
                temp->next->q = temp->k;
            }

            if (temp->next == NULL)
                erase_position(temp->j, temp->k);

            if (temp == head)
            {
                if (state == 1)
                    temp->q += 20;
                else if (state == 2)
                    temp->q -= 20;
                else if (state == 3)
                    temp->p -= 20;
                else if (state == 4)
                    temp->p += 20;
            }

            if (temp == head)
            {
                if (temp->j > 250 && temp->k > 590 && temp->j < 330)
                    temp->q = 20;
                else if (temp->j > 250 && temp->k < 10 && temp->j < 330)
                    temp->q = 580;

                else if (temp->j < 10 || temp->j > 590 || temp->k < 10 || temp->k > 590)
                {
                    cout << "\n Crashed with wall \n!!!  Game Over !!!\n";
                    if (level == 1)
                        cout << "\n\tIn EASY Difficulty, Your Score : " << score * 10 << '\n';
                    if (level == 2)
                        cout << "\n\tIn HARD Difficulty, Your Score : " << score * 10 << '\n';
                    flag = 1;
                    option = 1;
                }
                else if (temp->j > 150 && temp->j < 450 && temp->k > 290 && temp->k < 330 && level == 2)
                {
                    cout << "\n Crashed with wall \n!!!  Game Over !!!\n";
                    flag = 1;
                    option = 1;
                    if (level == 1)
                        cout << "\n\tIn EASY Difficulty, Your Score : " << score * 10 << '\n';
                    if (level == 2)
                        cout << "\n\tIn HARD Difficulty, Your Score : " << score * 10 << '\n';
                }
                else if (temp->j > 270 && temp->j < 310 && temp->k > 150 && temp->k < 450 && level == 2)
                {
                    cout << "\n Crashed with wall \n!!!  Game Over !!!\n";
                    if (level == 1)
                        cout << "\n\tIn EASY Difficulty, Your Score : " << score * 10 << '\n';
                    if (level == 2)
                        cout << "\n\tIn HARD Difficulty, Your Score : " << score * 10 << '\n';
                    flag = 1;
                    option = 1;
                }
            }

            if (temp == head)
            {
                b = check_strangled(temp->p, temp->q);
                if (b)
                {
                    cout << "\n\tStrangled\n !!!  Game Over !!!\n";
                    if (level == 1)
                        cout << "\n\tIn EASY Difficulty, Your Score : " << score * 10 << '\n';
                    if (level == 2)
                        cout << "\n\tIn HARD Difficulty, Your Score : " << score * 10 << '\n';
                    flag = 1;
                    option = 1;
                }
            }
            glColor3f(0.0, 1.0, 1.0);
            if (temp == head)
                glColor3f(1.0, 1.0, 1.0);

            redraw_position(temp->p, temp->q);

            temp->j = temp->p;
            temp->k = temp->q;

            if (temp->p == (x_coord + 10) && temp->q == y_coord - 10)
            {
                ++score;
                create_new_prey();
                time_interval = time_interval - 5;
                if (time_interval < 20)
                {
                    if (level == 1)
                        cout << "Congrats! You have completed EASY version of the challenge\n"
                             << "\tScore : " << score * 10;
                    if (level == 2)
                        cout << "Congrats! You have completed HARD version of the challenge\n"
                             << "\tScore : " << score * 10;

                    cout << "\n\n##################################\n";
                    cout << "##### YOU WON THIS CHALLENGE #####";
                    cout << "\n##################################\n";
                    flag = 1;
                }
                f = 1;
            }

            glFlush();
            temp = temp->next;
        }

        if (f == 1)
        {
            Node* temp1 = new Node;
            temp1->j = tail->j;
            temp1->k = tail->k;
            temp1->p = tail->p;
            temp1->q = tail->q;
            temp1->next = NULL;
            tail->next = temp1;
            tail = temp1;
        }
        f = 0;
    }
};

void display_text(string text, int x, int y, int font)
{
    void *p = NULL;
    if (font < 8 && font > 1)
        p = ((void *)font);
    else
        p = ((void *)5);

    glColor3f(1, 0, 0);
    glRasterPos2f(x, y);
    size_t len = text.length();
    for (int i = 0; i < len; i++)
        glutBitmapCharacter(p, (int)text[i]);

    glColor3f(1, 0, 0);
}

Snake saap;
void timer(int value)
{
    saap.move_snake();
    if (!flag)
        glutTimerFunc(time_interval, timer, 0);
    else
    {
        if (option == 1)
            display_text("!!!  Game Over !!!", 220, 320, 5);
        else
            display_text("Congrats!! You Won", 220, 320, 5);
        glFlush();
    }
}

void draw_boundary()
{
    if (level == 1)
    {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        //leftWall
        glColor3f(0.8, 0.5, 0.5);
        glVertex2f(0.0, 0.0);
        glVertex2f(10.0, 0.0);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(10.0, 600.0);
        glVertex2f(0.0, 600.0);
        //downWall
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 10.0);
        glColor3f(0.8, 0.5, 0.5);
        glVertex2f(250.0, 10.0);
        glVertex2f(250.0, 0.0);

        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(330.0, 0.0);
        glVertex2f(330.0, 10.0);
        glColor3f(0.8, 0.5, 0.5);
        glVertex2f(600.0, 10.0);
        glVertex2f(600.0, 0.0);

        //rightWall
        glColor3f(0.8, 0.5, 0.5);
        glVertex2f(590.0, 0.0);
        glVertex2f(600.0, 0.0);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(600.0, 600.0);
        glVertex2f(590.0, 600.0);
        //topWall
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(600.0, 600.0);
        glVertex2f(600.0, 590.0);
        glColor3f(0.8, 0.5, 0.5);
        glVertex2f(330.0, 590.0);
        glVertex2f(330.0, 600.0);

        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(250.0, 600.0);
        glVertex2f(250.0, 590.0);
        glColor3f(0.8, 0.5, 0.5);
        glVertex2f(0.0, 590.0);
        glVertex2f(0.0, 600.0);

        glEnd();
        glFlush();
    }

    if (level == 2)
    {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        //leftWall
        glColor3f(0.8, 0.5, 0.5);
        glVertex2f(0.0, 0.0);
        glVertex2f(10.0, 0.0);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(10.0, 600.0);
        glVertex2f(0.0, 600.0);
        //downWall
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 10.0);
        glColor3f(0.8, 0.5, 0.5);
        glVertex2f(250.0, 10.0);
        glVertex2f(250.0, 0.0);

        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(330.0, 0.0);
        glVertex2f(330.0, 10.0);
        glColor3f(0.8, 0.5, 0.5);
        glVertex2f(600.0, 10.0);
        glVertex2f(600.0, 0.0);

        //rightWall
        glColor3f(0.8, 0.5, 0.5);
        glVertex2f(590.0, 0.0);
        glVertex2f(600.0, 0.0);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(600.0, 600.0);
        glVertex2f(590.0, 600.0);
        //topWall
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(600.0, 600.0);
        glVertex2f(600.0, 590.0);
        glColor3f(0.8, 0.5, 0.5);
        glVertex2f(330.0, 590.0);
        glVertex2f(330.0, 600.0);

        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(250.0, 600.0);
        glVertex2f(250.0, 590.0);
        glColor3f(0.8, 0.5, 0.5);
        glVertex2f(0.0, 590.0);
        glVertex2f(0.0, 600.0);

        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(270, 150);
        glVertex2f(310, 150);
        glColor3f(0.8, 0.5, 0.5);
        glVertex2f(310, 450);
        glVertex2f(270, 450);

        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(150, 290);
        glVertex2f(150, 330);
        glColor3f(0.8, 0.5, 0.5);
        glVertex2f(450, 330);
        glVertex2f(450, 290);

        glEnd();
        glFlush();
    }
}

void create_new_prey()
{
    int i = 1;
    bool b = true;

    x_coord = rand() % 590 + 10;
    y_coord = rand() % 590 + 10;

    if (x_coord >= 590 || x_coord <= 10)
        x_coord = 40;
    if (y_coord <= 10 || y_coord >= 590)
        y_coord = 40;

    do
    {
        b = saap.check_strangled(x_coord, y_coord);
        if (b)
        {
            create_new_prey();
            return;
        }
    } while (b);

    x_coord = x_coord - ((x_coord - 10) % 20);
    y_coord = y_coord + ((590 - y_coord) % 20);

    if (level == 2)
    {
        if (x_coord > 130 && x_coord < 450)
            if (y_coord > 290 && y_coord < 350)
                y_coord += 40;

        if (y_coord > 150 && y_coord < 490)
            if (x_coord > 250 && x_coord < 310)
                x_coord += 40;
    }

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2i(x_coord, y_coord);
    glVertex2i(x_coord + 20, y_coord);
    glColor3f(0.2, 0.5, 0.2);
    glVertex2i(x_coord + 20, y_coord - 20);
    glVertex2i(x_coord, y_coord - 20);
    glEnd();
    glFlush();
}

void my_display()
{
}
void my_reshape(GLsizei x, GLsizei y)
{
    glutReshapeWindow(600, 600);
}
void my_keyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        state = 1;
        break;
    case GLUT_KEY_DOWN:
        state = 2;
        break;
    case GLUT_KEY_LEFT:
        state = 3;
        break;
    case GLUT_KEY_RIGHT:
        state = 4;
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

void select_level(int num)
{
    level = num;
    draw_boundary();
    create_new_prey();
    time_interval = 140;
    state = 1;

    glutTimerFunc(0, timer, 0);
    glutPostRedisplay();
    glFlush();
}

void create_menu()
{
    submenu_id = glutCreateMenu(select_level);
    glutAddMenuEntry("EASY", 1);
    glutAddMenuEntry("HARD", 2);
    menu_id = glutCreateMenu(select_level);
    glutAddSubMenu("Select Difficulty", submenu_id);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void initialize()
{
    srand(time(NULL));
    glClearColor(0.0, 0.1, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
}

int main(int argc, char** argv)
{
    cout << "OBJECTIVE : --->\n\t* Hunt down all 25 preys scattered on the field \n\n\t* But avoid hitting walls and crossing your own body \n\n";
    cout << "Controls : --->\n\t* Use arrow keys to change direction \n\n";
    cout << "LEGEND : --->\n\t* Cyan dot : Prey \n\t* White dot : Snake \n\t* Red boundary : Boundary \n\n";
    cout << "Scoring : --->\n\t* 10 points per prey \n\n";

    cout << "Authors : --->\n\t*  Metsehafe Eyasu   ETS0852/13 \n\t*  MICHAEL ENGIDA    ETS0859/13 \n\t*  MOHAMMED MEHAD    ETS0907/13 \n\t*  MOHAMMED RESTEM   ETS0911/13 \n\t*  MOHAMMED SHEMIM   ETS0912/13 \n\n";

    cout << "Group : G1 \n\n";

    cout << "*****  PRESS ENTER TO START  *****";
    getch();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("SNAKE GAME");
    initialize();
    create_menu();
    glutSpecialFunc(my_keyboard);
    glutDisplayFunc(my_display);
    glutReshapeFunc(my_reshape);
    glutMainLoop();

    return 0;
}
