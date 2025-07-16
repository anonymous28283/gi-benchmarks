





















namespace spirograph {

template <std::size_t N>
void spirograph(std::array<std::pair<double, double>, N> *points, double l,
                double k, double rot) {
    double dt = rot * 2.f * M_PI / N;
    double R = 1.f;
    const double k1 = 1.f - k;
    int32_t step = 0;




    for (step = 0; step < N; step++) {
        double t = dt * step;
        double first = R * (k1 * std::cos(t) + l * k * std::cos(k1 * t / k));
        double second = R * (k1 * std::sin(t) - l * k * std::sin(k1 * t / k));
        points[0][step].first = first;
        points[0][step].second = second;
    }
}


void test() {
    const size_t N = 500;
    double l = 0.3, k = 0.75, rot = 10.;
    std::stringstream fname;
    fname << std::setw(3) << "spirograph_" << l << "_" << k << "_" << rot
          << ".csv";
    std::ofstream fp(fname.str());
    if (!fp.is_open()) {
        perror(fname.str().c_str());
        exit(EXIT_FAILURE);
    }

    std::array<std::pair<double, double>, N> points;

    spirograph(&points, l, k, rot);

    for (size_t i = 0; i < N; i++) {
        fp << points[i].first << "," << points[i].first;
        if (i < N - 1) {
            fp << '\n';
        }
    }

    fp.close();
}


static bool paused = 0;
static const int animation_speed = 25;

static const double step = 0.01;
static double l_ratio = step * 10;
static double k_ratio = step;
static const double num_rot = 20.;


static inline void glutBitmapString(void *font, char *message) {
    for (char *ch = message; *ch != '\0'; ch++) glutBitmapCharacter(font, *ch);
}


template <size_t N>
void display_graph(const std::array<std::pair<double, double>, N> &points,
                   double l, double k) {
    glClearColor(1.0f, 1.0f, 1.0f,
                 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    glColor3f(0.f, 0.f, 1.f);
    glPointSize(2.f);

    for (size_t i = 1; i < N; i++) {
        glVertex2f(points[i - 1].first, points[i - 1].second);
        glVertex2f(points[i].first, points[i].second);
    }
    glEnd();

    glColor3f(0.f, 0.f, 0.f);
    std::stringstream buffer;
    buffer << std::setw(3) << "l = " << l;
    glRasterPos2f(-.85, .85);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,
                     const_cast<char *>(buffer.str().c_str()));
    buffer.str("");
    buffer.clear();
    buffer << std::setw(3) << "k = " << k;
    glRasterPos2f(-.85, .70);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,
                     const_cast<char *>(buffer.str().c_str()));

    glutSwapBuffers();
}


void test2() {
    const size_t N = 5000;

    static bool direction1 = true;
    static bool direction2 = true;

    std::array<std::pair<double, double>, N> points;

    spirograph(&points, l_ratio, k_ratio, num_rot);
    display_graph(points, l_ratio, k_ratio);

    if (paused)

        return;

    if (direction1) {
        if (k_ratio >= (1.f - step))
            direction1 = false;
        else
            k_ratio += step;
    } else {
        if (k_ratio <= step) {
            direction1 = true;

            if (direction2) {
                if (l_ratio >= (1.f - step))
                    direction2 = false;
                else
                    l_ratio += step;
            } else {
                if (l_ratio <= step)
                    direction2 = true;
                else
                    l_ratio -= step;
            }
        } else {
            k_ratio -= step;
        }
    }
}


void timer_cb(int t) {
    glutTimerFunc(animation_speed, timer_cb, 0);
    glutPostRedisplay();
}


void keyboard_cb(unsigned char key, int x, int y) {
    switch (key) {
        case ' ':
            paused = !paused;
            break;
        case GLUT_KEY_UP:
        case '+':
            k_ratio += step;
            break;
        case GLUT_KEY_DOWN:
        case '_':
            k_ratio -= step;
            break;
        case GLUT_KEY_RIGHT:
        case '=':
            l_ratio += step;
            break;
        case GLUT_KEY_LEFT:
        case '-':
            l_ratio -= step;
            break;
        case 0x1B:
            exit(EXIT_SUCCESS);
        default:
            return;
    }
}

}


int main(int argc, char **argv) {
    spirograph::test();


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Spirograph");
    glutInitWindowSize(400, 400);

    glutTimerFunc(spirograph::animation_speed, spirograph::timer_cb, 0);
    glutKeyboardFunc(spirograph::keyboard_cb);
    glutDisplayFunc(spirograph::test2);
    glutMainLoop();


    return 0;
}
