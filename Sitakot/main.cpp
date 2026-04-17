#include <windows.h>
#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <utility>
#include <windows.h> // Include Windows header for sound functions

const int WIDTH = 1000;
const int HEIGHT = 600;
bool isDay = true;
bool moveClouds = false;
bool moveBirds = false;
bool showIntro = true;
bool isRaining = false;
bool isThundering = false;
bool isSoundPlaying = false; // Track sound state
float cloudOffset = 0.0f;
float birdOffset = 0.0f;

// Vector to store star positions
std::vector<std::pair<float, float>> stars;

// Vector to store raindrop positions
std::vector<std::pair<float, float>> raindrops;

void initializeAudio() {
    // Initialize sound for birds
    if (isDay && !isSoundPlaying) {
        PlaySound(TEXT("bird.wav"), NULL, SND_ASYNC | SND_LOOP);
        isSoundPlaying = true;
    }
}

void init() {
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    srand(time(0));

    // Generate star positions
    for (int i = 0; i < 100; ++i) {
        float x = rand() % WIDTH;
        float y = 500 + rand() % 100;
        stars.emplace_back(x, y);
    }
}

void drawIntro() {
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    void *font = GLUT_BITMAP_HELVETICA_18;

    auto drawText = [&](float x, float y, const char* text) {
        glRasterPos2f(x, y);
        while (*text) glutBitmapCharacter(font, *text++);
    };

    drawText(300, 450, "SITAKOT PROJECT");
    drawText(280, 400, "'N/n' = NIGHT MODE");
    drawText(280, 370, "'D/d' = DAY MODE");
    drawText(280, 340, "'M/m' = MOVE CLOUDS AND BIRDS");
    drawText(280, 310, "'R/r' = RAIN");
    drawText(280, 280, "'T/t' = THUNDER");
    drawText(280, 250, "NAME: ARMAN HOSSAIN FOEJ       ID:22-49440-3");
    drawText(280, 220, "[ PRESS ENTER TO START ]");
    glFlush();
}

void drawBrickWalls() {
    if (isDay) {
        glColor3f(0.55f, 0.27f, 0.07f);
    } else {
        glColor3f(0.35f, 0.17f, 0.07f);
    }
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(0, 300);
    glVertex2f(500, 450);
    glVertex2f(500, 450);
    glVertex2f(1000, 300);
    glVertex2f(0, 350);
    glVertex2f(500, 500);
    glVertex2f(500, 500);
    glVertex2f(1000, 350);
    glVertex2f(0, 300);
    glVertex2f(400, 200);
    glVertex2f(400, 200);
    glVertex2f(0, 100);
    glVertex2f(0, 250);
    glVertex2f(240, 200);
    glVertex2f(240, 200);
    glVertex2f(0, 150);
    glVertex2f(0, 100);
    glVertex2f(200, 0);
    glVertex2f(200, 0);
    glVertex2f(1000, 300);
    glVertex2f(324, 0);
    glVertex2f(1000, 201);
    glVertex2f(765, 130);
    glVertex2f(1000, 50);
    glVertex2f(690, 110);
    glVertex2f(1000, 0);
    glVertex2f(50, 288);
    glVertex2f(500, 426);
    glVertex2f(102, 275);
    glVertex2f(500, 400);
    glVertex2f(500, 426);
    glVertex2f(957, 284);
    glVertex2f(500, 400);
    glVertex2f(914, 270);
    glVertex2f(1000, 285);
    glVertex2f(655, 160);
    glVertex2f(690, 120);
    glVertex2f(1000, 215);
    glVertex2f(655, 160);
    glVertex2f(690, 120);
    glEnd();
}

void drawGrassArea() {
    if (isDay) {
        glColor3f(0.4f, 0.8f, 0.4f);
    } else {
        glColor3f(0.1f, 0.4f, 0.1f);
    }
    glBegin(GL_POLYGON);
    glVertex2f(0, 300);
    glVertex2f(500, 450);
    glVertex2f(1000, 300);
    glVertex2f(200, 0);
    glVertex2f(0, 100);
    glVertex2f(400, 200);
    glVertex2f(0, 300);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(324, 0);
    glVertex2f(1000, 0);
    glVertex2f(640, 122);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(1000, 201);
    glVertex2f(716, 152);
    glVertex2f(1000, 50);
    glEnd();
}

void drawBricksArea() {
    if (isDay) {
        glColor3f(0.8f, 0.5f, 0.3f);
    } else {
        glColor3f(0.6f, 0.3f, 0.1f);
    }
    glBegin(GL_POLYGON);
    glVertex2f(0, 300);
    glVertex2f(0, 250);
    glVertex2f(240, 200);
    glVertex2f(400, 200);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0, 150);
    glVertex2f(0, 100);
    glVertex2f(400, 200);
    glVertex2f(240, 200);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 100);
    glVertex2f(200, 0);
    glVertex2f(0, 0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(200, 0);
    glVertex2f(1000, 300);
    glVertex2f(324, 0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(1000, 300);
    glVertex2f(324, 0);
    glVertex2f(1000, 201);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(1000, 50);
    glVertex2f(716, 152);
    glVertex2f(640, 122);
    glVertex2f(1000, 0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(1000, 300);
    glVertex2f(1000, 350);
    glVertex2f(500, 500);
    glVertex2f(500, 450);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0, 350);
    glVertex2f(0, 300);
    glVertex2f(500, 450);
    glVertex2f(500, 500);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(50, 288);
    glVertex2f(102, 275);
    glVertex2f(500, 400);
    glVertex2f(500, 426);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(500, 426);
    glVertex2f(500, 400);
    glVertex2f(914, 270);
    glVertex2f(957, 284);
    glEnd();
    glColor3f(0.631f, 0.529f, 0.467f);
    glBegin(GL_POLYGON);
    glVertex2f(50, 288);
    glVertex2f(500, 426);
    glVertex2f(500, 449);
    glVertex2f(2, 300);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(500, 450);
    glVertex2f(500, 426);
    glVertex2f(957, 284);
    glVertex2f(1000, 300);
    glEnd();
}

void drawTree() {
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(40, 360);
    glVertex2f(60, 365);
    glVertex2f(60, 400);
    glVertex2f(40, 400);
    glEnd();
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(20, 400);
    glVertex2f(50, 430);
    glVertex2f(80, 400);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(30, 420);
    glVertex2f(50, 450);
    glVertex2f(70, 420);
    glEnd();
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(140, 390);
    glVertex2f(160, 395);
    glVertex2f(160, 430);
    glVertex2f(140, 430);
    glEnd();
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(120, 430);
    glVertex2f(150, 460);
    glVertex2f(180, 430);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(130, 450);
    glVertex2f(150, 480);
    glVertex2f(170, 450);
    glEnd();
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(240, 420);
    glVertex2f(260, 425);
    glVertex2f(260, 460);
    glVertex2f(240, 460);
    glEnd();
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(220, 460);
    glVertex2f(250, 490);
    glVertex2f(280, 460);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(230, 480);
    glVertex2f(250, 510);
    glVertex2f(270, 480);
    glEnd();
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(340, 450);
    glVertex2f(360, 455);
    glVertex2f(360, 490);
    glVertex2f(340, 490);
    glEnd();
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(320, 490);
    glVertex2f(350, 520);
    glVertex2f(380, 490);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(330, 510);
    glVertex2f(350, 540);
    glVertex2f(370, 510);
    glEnd();
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(440, 480);
    glVertex2f(460, 485);
    glVertex2f(460, 520);
    glVertex2f(440, 520);
    glEnd();
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(420, 520);
    glVertex2f(450, 550);
    glVertex2f(480, 520);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(430, 540);
    glVertex2f(450, 570);
    glVertex2f(470, 540);
    glEnd();
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(540, 485);
    glVertex2f(560, 480);
    glVertex2f(560, 520);
    glVertex2f(540, 520);
    glEnd();
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(520, 520);
    glVertex2f(550, 550);
    glVertex2f(580, 520);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(530, 540);
    glVertex2f(550, 570);
    glVertex2f(570, 540);
    glEnd();
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(640, 455);
    glVertex2f(660, 450);
    glVertex2f(660, 490);
    glVertex2f(640, 490);
    glEnd();
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(620, 490);
    glVertex2f(650, 520);
    glVertex2f(680, 490);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(630, 510);
    glVertex2f(650, 540);
    glVertex2f(670, 510);
    glEnd();
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(740, 425);
    glVertex2f(760, 420);
    glVertex2f(760, 460);
    glVertex2f(740, 460);
    glEnd();
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(720, 460);
    glVertex2f(750, 490);
    glVertex2f(780, 460);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(730, 480);
    glVertex2f(750, 510);
    glVertex2f(770, 480);
    glEnd();
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(840, 395);
    glVertex2f(860, 390);
    glVertex2f(860, 430);
    glVertex2f(840, 430);
    glEnd();
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(820, 430);
    glVertex2f(850, 460);
    glVertex2f(880, 430);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(830, 450);
    glVertex2f(850, 480);
    glVertex2f(870, 450);
    glEnd();
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(940, 365);
    glVertex2f(960, 360);
    glVertex2f(960, 400);
    glVertex2f(940, 400);
    glEnd();
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(920, 400);
    glVertex2f(950, 430);
    glVertex2f(980, 400);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(930, 420);
    glVertex2f(950, 450);
    glVertex2f(970, 420);
    glEnd();
}


void drawstairs() {
    glColor3f(0.75f, 0.45f, 0.20f);
    glBegin(GL_QUADS);
    glVertex2f(350, 362);
    glVertex2f(401, 380);
    glVertex2f(414, 371);
    glVertex2f(362, 352);
    glVertex2f(362, 352);
    glVertex2f(414, 371);
    glVertex2f(430, 365);
    glVertex2f(380, 342);
    glVertex2f(380, 342);
    glVertex2f(430, 365);
    glVertex2f(443, 358);
    glVertex2f(395, 330);
    glVertex2f(395, 330);
    glVertex2f(443, 358);
    glVertex2f(457, 350);
    glVertex2f(403, 321);
    glEnd();
    if (isDay) {
        glColor3f(0.55f, 0.27f, 0.07f);
    } else {
        glColor3f(0.35f, 0.17f, 0.07f);
    }
    glLineWidth(3.0f);
    glBegin(GL_QUADS);
    glVertex2f(350, 352);
    glVertex2f(401, 370);
    glVertex2f(401, 380);
    glVertex2f(350, 362);
    glVertex2f(362, 342);
    glVertex2f(414, 361);
    glVertex2f(414, 371);
    glVertex2f(362, 352);
    glVertex2f(380, 332);
    glVertex2f(430, 355);
    glVertex2f(430, 365);
    glVertex2f(380, 342);
    glVertex2f(395, 320);
    glVertex2f(443, 348);
    glVertex2f(443, 358);
    glVertex2f(395, 330);
    glVertex2f(403, 311);
    glVertex2f(457, 340);
    glVertex2f(457, 350);
    glVertex2f(403, 321);
    glEnd();
}

void drawCloud() {
    if (isDay) {
        glColor3f(1.0f, 1.0f, 1.0f);
        for (int i = -1; i <= 1; ++i) {
            glPushMatrix();
            glTranslatef(cloudOffset + i * WIDTH, 0.0f, 0.0f);
             glBegin(GL_POLYGON);
            glVertex2f(150, 570);
            glVertex2f(160, 580);
            glVertex2f(170, 585);
            glVertex2f(180, 580);
            glVertex2f(190, 570);
            glVertex2f(180, 560);
            glVertex2f(160, 560);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(165, 580);
            glVertex2f(175, 590);
            glVertex2f(185, 595);
            glVertex2f(195, 590);
            glVertex2f(185, 580);
            glVertex2f(170, 575);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(180, 570);
            glVertex2f(190, 580);
            glVertex2f(200, 585);
            glVertex2f(210, 580);
            glVertex2f(220, 570);
            glVertex2f(210, 560);
            glVertex2f(190, 560);
            glEnd();
            // Draw second set of clouds
            glBegin(GL_POLYGON);
            glVertex2f(450, 580);
            glVertex2f(460, 590);
            glVertex2f(470, 595);
            glVertex2f(480, 590);
            glVertex2f(490, 580);
            glVertex2f(480, 570);
            glVertex2f(460, 570);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(470, 590);
            glVertex2f(480, 600);
            glVertex2f(490, 605);
            glVertex2f(500, 600);
            glVertex2f(490, 590);
            glVertex2f(475, 585);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(490, 580);
            glVertex2f(500, 590);
            glVertex2f(510, 595);
            glVertex2f(520, 590);
            glVertex2f(530, 580);
            glVertex2f(520, 570);
            glVertex2f(500, 570);
            glEnd();
            // Draw third set of clouds
            glBegin(GL_POLYGON);
            glVertex2f(750, 570);
            glVertex2f(760, 580);
            glVertex2f(770, 585);
            glVertex2f(780, 580);
            glVertex2f(790, 570);
            glVertex2f(780, 560);
            glVertex2f(760, 560);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(770, 580);
            glVertex2f(780, 590);
            glVertex2f(790, 595);
            glVertex2f(800, 590);
            glVertex2f(790, 580);
            glVertex2f(775, 575);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(790, 570);
            glVertex2f(800, 580);
            glVertex2f(810, 585);
            glVertex2f(820, 580);
            glVertex2f(830, 570);
            glVertex2f(820, 560);
            glVertex2f(800, 560);
            glEnd();

            glPopMatrix();
        }
    }
}

void drawBirds() {
    if (isDay && moveBirds) {
        glColor3f(0.0f, 0.0f, 0.0f);
        for (int i = 0; i < 3; ++i) {
            glPushMatrix();
            glTranslatef(birdOffset + i * 300, 0.0f, 0.0f);
            glBegin(GL_TRIANGLES);
            glVertex2f(200, 550);
            glVertex2f(210, 560);
            glVertex2f(220, 550);
            glEnd();
            glBegin(GL_LINES);
            glVertex2f(220, 550);
            glVertex2f(230, 540);
            glEnd();
            glPopMatrix();
        }
    }
}

void drawStars() {
    if (!isDay) {
        glColor3f(isRaining ? 0.3f : 1.0f, isRaining ? 0.3f : 1.0f, isRaining ? 0.3f : 1.0f);
        glPointSize(2.0f);
        glBegin(GL_POINTS);
        for (const auto& star : stars) {
            glVertex2f(star.first, star.second);
        }
        glEnd();
    }
}

void drawRain() {
    if (isRaining) {
        glColor3f(0.5f, 0.5f, 1.0f);
        glPointSize(2.0f);
        glBegin(GL_LINES);
        for (const auto& drop : raindrops) {
            glVertex2f(drop.first, drop.second);
            glVertex2f(drop.first, drop.second - 10);
        }
        glEnd();
    }
}

void drawThunder() {
    if (isThundering) {
        glColor3f(1.0f, 1.0f, 0.8f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex2f(200, 500);
        glVertex2f(250, 450);
        glVertex2f(250, 450);
        glVertex2f(300, 500);
        glVertex2f(300, 500);
        glVertex2f(350, 450);
        glVertex2f(350, 450);
        glVertex2f(400, 400);
        glEnd();
    }
}

void drawSunOrMoon() {
    if (isDay) {
        glColor3f(isRaining ? 0.7f : 1.0f, isRaining ? 0.7f : 1.0f, isRaining ? 0.0f : 0.0f);
        float sun_center_x = 892;
        float sun_center_y = 540;
        float sun_radius = 30;
        int triangleAmount = 100;
        float twicePi = 2.0f * 3.1415926f;
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(sun_center_x, sun_center_y);
        for (int i = 0; i <= triangleAmount; i++) {
            glVertex2f(
                sun_center_x + (sun_radius * cos(i * twicePi / triangleAmount)),
                sun_center_y + (sun_radius * sin(i * twicePi / triangleAmount))
            );
        }
        glEnd();
        glColor3f(1.0f, 0.8f, 0.0f);
        for (int i = 0; i < 8; i++) {
            float angle = i * (twicePi / 8);
            float x1 = sun_center_x + sun_radius * cos(angle);
            float y1 = sun_center_y + sun_radius * sin(angle);
            float x2 = sun_center_x + (sun_radius + 15) * cos(angle);
            float y2 = sun_center_y + (sun_radius + 15) * sin(angle);
            glBegin(GL_LINES);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glEnd();
        }
    } else {
        glColor3f(isRaining ? 0.5f : 1.0f, isRaining ? 0.5f : 1.0f, isRaining ? 0.5f : 1.0f);
        float moon_center_x = 892;
        float moon_center_y = 540;
        float moon_radius = 25;
        int triangleAmount = 100;
        float twicePi = 2.0f * 3.1415926f;
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(moon_center_x, moon_center_y);
        for (int i = 0; i <= triangleAmount; i++) {
            glVertex2f(
                moon_center_x + (moon_radius * cos(i * twicePi / triangleAmount)),
                moon_center_y + (moon_radius * sin(i * twicePi / triangleAmount))
            );
        }
        glEnd();
    }
}

void drawDoor() {
     glColor3f(0.36f, 0.25f, 0.20f);
    glBegin(GL_POLYGON);
    glVertex2f(20, 305);
    glVertex2f(37, 310);
    glVertex2f(32, 330);
    glVertex2f(15, 325);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(70, 320);
    glVertex2f(87, 325);
    glVertex2f(82, 345);
    glVertex2f(65, 340);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(120, 335);
    glVertex2f(137, 340);
    glVertex2f(132, 360);
    glVertex2f(115, 355);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(170, 350);
    glVertex2f(187, 355);
    glVertex2f(182, 375);
    glVertex2f(165, 370);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(220, 365);
    glVertex2f(237, 370);
    glVertex2f(232, 390);
    glVertex2f(215, 385);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(270, 380);
    glVertex2f(287, 385);
    glVertex2f(282, 405);
    glVertex2f(265, 400);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(320, 395);
    glVertex2f(337, 400);
    glVertex2f(332, 420);
    glVertex2f(315, 415);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(370, 410);
    glVertex2f(387, 415);
    glVertex2f(382, 435);
    glVertex2f(365, 430);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(420, 425);
    glVertex2f(437, 430);
    glVertex2f(432, 450);
    glVertex2f(415, 445);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(470, 440);
    glVertex2f(487, 445);
    glVertex2f(482, 465);
    glVertex2f(465, 460);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(520, 445);
    glVertex2f(537, 440);
    glVertex2f(532, 460);
    glVertex2f(515, 465);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(570, 430);
    glVertex2f(587, 425);
    glVertex2f(582, 445);
    glVertex2f(565, 450);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(620, 415);
    glVertex2f(637, 410);
    glVertex2f(632, 430);
    glVertex2f(615, 435);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(670, 400);
    glVertex2f(687, 395);
    glVertex2f(682, 415);
    glVertex2f(665, 420);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(720, 385);
    glVertex2f(737, 380);
    glVertex2f(732, 400);
    glVertex2f(715, 405);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(770, 370);
    glVertex2f(787, 365);
    glVertex2f(782, 385);
    glVertex2f(765, 390);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(820, 355);
    glVertex2f(837, 350);
    glVertex2f(832, 370);
    glVertex2f(815, 375);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(870, 340);
    glVertex2f(887, 335);
    glVertex2f(882, 355);
    glVertex2f(865, 360);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(920, 325);
    glVertex2f(937, 320);
    glVertex2f(932, 340);
    glVertex2f(915, 345);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(970, 310);
    glVertex2f(987, 305);
    glVertex2f(982, 325);
    glVertex2f(965, 330);
    glEnd();

}

void display() {
    if (showIntro) {
        drawIntro();
    } else {
        glClear(GL_COLOR_BUFFER_BIT);
        if (isDay) {
            glClearColor(isRaining ? 0.3f : 0.7f, isRaining ? 0.3f : 0.9f, isRaining ? 0.4f : 1.0f, 1.0f);
        } else {
            glClearColor(isRaining ? 0.1f : 0.0f, isRaining ? 0.1f : 0.0f, isRaining ? 0.3f : 0.2f, 1.0f);
        }
        drawGrassArea();
        drawBricksArea();
        drawBrickWalls();
        drawCloud();
        drawBirds();
        drawStars();
        drawTree();
        drawstairs();
        drawSunOrMoon();
        drawDoor();
        drawRain();
        drawThunder();
    }
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (showIntro) {
        if (key == 13) { // ASCII code for Enter key
            showIntro = false;
            glutPostRedisplay();
        }
    } else {
        switch (key) {
            case 'd':
            case 'D':
                isDay = true;
                isSoundPlaying = false;
                glutPostRedisplay();
                break;
            case 'n':
            case 'N':
                isDay = false;
                isSoundPlaying = false;
                glutPostRedisplay();
                break;
            case 'm':
            case 'M':
                moveClouds = !moveClouds;
                moveBirds = !moveBirds;
                if (moveClouds && isDay) {
                    PlaySound(TEXT("bird.wav"), NULL, SND_ASYNC | SND_LOOP);
                    isSoundPlaying = true;
                } else {
                    PlaySound(NULL, NULL, SND_ASYNC);
                    isSoundPlaying = false;
                }
                break;
            case 'r':
            case 'R':
                isRaining = !isRaining;
                if (isRaining) {
                    raindrops.clear();
                    for (int i = 0; i < 200; ++i) {
                        float x = rand() % WIDTH;
                        float y = rand() % HEIGHT;
                        raindrops.emplace_back(x, y);
                    }
                    PlaySound(TEXT("rain.wav"), NULL, SND_ASYNC | SND_LOOP);
                } else {
                    PlaySound(NULL, NULL, SND_ASYNC);
                }
                break;
            case 't':
            case 'T':
                isThundering = !isThundering;
                if (isThundering) {
                    PlaySound(TEXT("thunder.wav"), NULL, SND_ASYNC);
                }
                break;
        }
    }
}

void update(int value) {
    if (moveClouds && isDay) {
        cloudOffset += 1.0f;
        if (cloudOffset > WIDTH) {
            cloudOffset = 0.0f;
        }
    }
    if (moveBirds && isDay) {
        birdOffset += 2.0f;
        if (birdOffset > WIDTH) {
            birdOffset = -200.0f;
        }
    }
    if (isRaining) {
        for (auto& drop : raindrops) {
            drop.second -= 5.0f;
            if (drop.second < 0) {
                drop.second = HEIGHT;
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sitakot Bihar");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
