//
//  main.cpp
//  CG Project
//
//  Created by Mohammed Fayez on 13/05/2023.
#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
#include<iostream>
#include<cmath>
#include<windows.h>
#include<GLUT/GLUT.h>// دي طريقة الانكلود للماك لو انت ويندوز عدلها
#include"stb_image.h"
#include<time.h>

int levels = 3, x, y, ch = -1, win, count, aspect, px = 9, py = 0, endx = 8, endy = 20, n = 15, m = 21, co[3][4] = { { 9, 0, 0, 12 } ,{ 9, 0, 8, 20 }, { 9, 0, 14, 9 } }, current_level = 0;
unsigned char* data = NULL;
int width, height, nrChannels;

clock_t start, endd;

char t[2];
unsigned int texture;

void check (unsigned char *data);
void load ( int imgnum );

// كمال
// كمال ومريم
// هنا رسمنا المتاهه بتاعتنا والابعاد بتاعتها وهي عباره عن 3 مستويات
int maze[3][15][21] = {

    // ماتريكس اول جيم
{ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 },
{ 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
{ 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1 },
{ 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } },

// ماتريكس تاني جيم
{ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 },
{ 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1 },
{ 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } } ,

// ماتريكس تالت جيم
{ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 },
{ 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
{ 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1 },
{ 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } }

};

// مريم
// كمال ومريم
// الفانكشن ده بندخلها مكان المكعب علي المستوي الافقي والعمودي ومنها بنعرف هو فين وبنشوف لو قدامه
// في اي حاجه سعتها بيقف ومش بيتحرك طب لو مش قدامه حاجه يبقي عادي يقدر يتحرك في المكان الفاضي ده
// وده مستخدمينها جوي الفانكشن بتاعت سبيشال كيي المسئوله عن تحريك المكعب
bool valid(int x, int y) {
    return x >= 0 && x < n&& y >= 0 && y < m;
}


// مريم
// كمال ومريم
// ده فانكشن المسئوله عن رسم المكعب بتاعنا لي يبتحرك
// بنرسم جوي الالوان بتاعت كل اتجاه فيه
// وبنعين حجمه ومكانه لي هيبدا منه وكدا
void currentPoint()
{
    int sz = 5, addx = -180 + 15 * co[current_level][1], addy = 100 - co[current_level][0] * 15;
    std::cout << " Y = " << co[current_level][0] << "   -----   " << " X = " << co[current_level][1] << " ch = " << ch << "\n";


    glBegin(GL_QUADS);

    //top
    glColor3f(.3, .3, .3);
    glVertex3f(sz + addx, sz + addy, -sz);
    glVertex3f(-sz + addx, sz + addy, -sz);
    glVertex3f(-sz + addx, sz + addy, sz);
    glVertex3f(sz + addx, sz + addy, sz);

    //botton
    glColor3f(1, .3, .3);
    glVertex3f(sz + addx, -sz + addy, -sz);
    glVertex3f(-sz + addx, -sz + addy, -sz);
    glVertex3f(-sz + addx, -sz + addy, sz);
    glVertex3f(sz + addx, -sz + addy, sz);

    //right
    glColor3f(1, .3, .3);
    glVertex3f(sz + addx, sz + addy, -sz);
    glVertex3f(sz + addx, -sz + addy, -sz);
    glVertex3f(sz + addx, -sz + addy, sz);
    glVertex3f(sz + addx, sz + addy, sz);

    //left
    glColor3f(1, .5, .5);
    glVertex3f(-sz + addx, sz + addy, -sz);
    glVertex3f(-sz + addx, -sz + addy, -sz);
    glVertex3f(-sz + addx, -sz + addy, sz);
    glVertex3f(-sz + addx, sz + addy, sz);

    //back
    glColor3f(1, .9, .9);
    glVertex3f(sz + addx, sz + addy, -sz);
    glVertex3f(-sz + addx, sz + addy, -sz);
    glVertex3f(-sz + addx, -sz + addy, -sz);
    glVertex3f(sz + addx, -sz + addy, -sz);

    //front
    glColor3f(1, .9, .9);
    glVertex3f(sz + addx, sz + addy, sz);
    glVertex3f(-sz + addx, sz + addy, sz);
    glVertex3f(-sz + addx, -sz + addy, sz);
    glVertex3f(sz + addx, -sz + addy, sz);
    glEnd();
}

// كمال
// كمال ومريم
// ده فانكشن المسئوله عن رسم المتاهه نفسها
// بنرسم جوي الالوان بتاعت كل اتجاه فيها
// وبنعين حجمه ومكانه لي هيبدا منه وكدا
void wallPoint(float x, float y)
{
    int sz = 7, addx = x, addy = y;
    glBegin(GL_QUADS);

    //top
    glColor3f(.3, .3, .3);
    glVertex3f(sz + addx, sz + addy, -sz);
    glVertex3f(-sz + addx, sz + addy, -sz);
    glVertex3f(-sz + addx, sz + addy, sz);
    glVertex3f(sz + addx, sz + addy, sz);

    //bottom
    glColor3f(.3, .3, .3);
    glVertex3f(sz + addx, -sz + addy, -sz);
    glVertex3f(-sz + addx, -sz + addy, -sz);
    glVertex3f(-sz + addx, -sz + addy, sz);
    glVertex3f(sz + addx, -sz + addy, sz);

    //right
    glColor3f(.5, .5, .5);
    glVertex3f(sz + addx, sz + addy, -sz);
    glVertex3f(sz + addx, -sz + addy, -sz);
    glVertex3f(sz + addx, -sz + addy, sz);
    glVertex3f(sz + addx, sz + addy, sz);

    //left
    glColor3f(.5, .5, .5);
    glVertex3f(-sz + addx, sz + addy, -sz);
    glVertex3f(-sz + addx, -sz + addy, -sz);
    glVertex3f(-sz + addx, -sz + addy, sz);
    glVertex3f(-sz + addx, sz + addy, sz);

    //back
    glColor3f(.9, .9, .9);
    glVertex3f(sz + addx, sz + addy, -sz);
    glVertex3f(-sz + addx, sz + addy, -sz);
    glVertex3f(-sz + addx, -sz + addy, -sz);
    glVertex3f(sz + addx, -sz + addy, -sz);

    //front
    glColor3f(.9, .9, .9);
    glVertex3f(sz + addx, sz + addy, sz);
    glVertex3f(-sz + addx, sz + addy, sz);
    glVertex3f(-sz + addx, -sz + addy, sz);
    glVertex3f(sz + addx, -sz + addy, sz);
    glEnd();

}
// شاكر
// شاكر وفتحي
// الفانكشن المسئوله عن الكتابه لاي جمله في الشاشات
// بناخد المكان الطولي والافقي للجمله في الشاشه
// بناخد حرف حرف في الكلمه وناخد طولها ونرسمه كجمله كمله
// بناخد الفونت لي هيتحط بيه الجمله
void writeStr(int x, int y, const char* str, void* font)
{
    
    int len = strlen(str);
    glRasterPos2f(x, y);
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// شاكر
// شاكر وشروق
// بنشوف بيها هل الصوره موجوده ولا لا
// لو موجوده هباخدها ويعديها علي الميثود بتاع التيكستر ويعملها تو دي
// ويحطلها الطول والعرض والالوان بتوعها ولو لا هيجيب في الكونسول ان الصوره متحملتش
void check (unsigned char *data){
    if (data != NULL)
        {
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
    stbi_image_free(data);
}

// شروق
// شروق وشاكر
// فانكشن ببعتلها رقم بقولها اندهيلي بيه علي صوره رقم كذا
// ولما اندهه بيجيب الصوره سعتها باسمها
void load ( int imgnum ){
    if( imgnum == 1){
        
        data= stbi_load("wall.bmp", &width, &height, &nrChannels, 0);
        check(data);
    }
    else if( imgnum == 2){
        
        data= stbi_load("maze.jpg", &width, &height, &nrChannels, 0);
        check(data);
    }
}

// شاكر وفتحي
// فتحي
// الفانكشن المسئوله عن التنقل بين الشاشات
// بنعين الزراير لي هنستخدمها للتنقل
// لو واحد يبدء اللعبه من المستوي رقم زيرو ويشغل التايمر
// لو 4 يروح لتاني ليفيل
// لو 2 يقفل اللعبه
// لو 3 يرجع للصفحه الرئيسيه
void keyboard(unsigned char key, int x, int y) {
    if (key == '1')
    {
        ch = 1;
        current_level = 0;
        co[current_level][0] = 9;
        co[current_level][1] = 0;
        start = clock();
    }
    else if (key == '4')
    {
        ch = 1;
        start = clock();
    }
    else if (key == '2')exit(0);
    else if (key == '3')ch = -1;
}
//----------------------------------------------------------------------------------------------------------------------------------------
// شروق وروان
// روان
//  الشاشه لي فيها المتاهه
// بنحط الالوان والابعاد بتاعت الشاشه
// بنحط الجمله لي بتظهر باقي قد ايه وقت
// وجمل اضافيه لو عايز يرجع او يعيد اللعبه
void map() {   //that is responsible for rendering a game map using OpenGL
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clears the color and depth buffers to prepare for rendering.
    glLoadIdentity();//Resets the current transformation matrix to the identity matrix.
    glTranslatef(0, 0, -80.0f);//Translates the coordinate system by (0, 0, -80.0) units along the z-axis. This effectively moves the scene closer to the viewer.
    
    
    glColor3f(0.9490196078431373, 0.9490196078431373, 0.9490196078431373);// light gray color
    writeStr(-50, 130, "TIME REMAINING : ", GLUT_BITMAP_HELVETICA_18);//to draw a text string indicating the remaining time at position (-50, 130) using a specific font (GLUT_BITMAP_HELVETICA_18).
   
    glColor3f(0.9529411764705882, 0.1411764705882353, 0.1411764705882353);// dark red color
    writeStr(-187, 170, "Press 3 To Go To Main Menu ", GLUT_BITMAP_HELVETICA_18);//to draw two additional text strings indicating different game options
    writeStr(-180, 140, "Press 1 To Restart The Game From Level 0", GLUT_BITMAP_HELVETICA_18);
    
    int num = 20 - count;//يحسب الوقت المتبقي عن طريق طرح عدد متغير من 20 ويخزنه في الرقم المتغير.
    t[0] = '0' + num / 10;//بيحول الرقم الي 2characters و one digits
    t[1] = '0' + num % 10;
    glColor3f(0.9490196078431373, 0.9490196078431373, 0.9490196078431373);
    writeStr(50, 142, t, GLUT_BITMAP_HELVETICA_18); //بيرسم ال 2 characters الي ف ال t
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maze[current_level][i][j]) {
                wallPoint(-180 + j * 15, 100 - i * 15);
            }
        }
    }
    currentPoint(); //to draw the current point in the game.
    glFlush();//to ensure they are executed.
    glutSwapBuffers();//to update the displayed image with the newly rendered content.
}
//----------------------------------------------------------------------------------------------------------------------------------------
// فانكشن بنرسم بيها اللون في الخلفيه
// شروق وروان
// شروق
void background() {
    
    glClearColor(0.2274509803921569, 0.2196078431372549, 0.2705882352941176, 1);
    load(1);
    glColor3f(0.2274509803921569, 0.2196078431372549, 0.2705882352941176);
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1);
    glVertex2f(-120, -70);
    glTexCoord2f(1, 1);
    glVertex2f(180, -70);
    glTexCoord2f(1, 0);
    glVertex2f(180, 200);
    glTexCoord2f(0, 0);
    glVertex2f(-120, 200);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}
//----------------------------------------------------------------------------------------------------------------------------------------
// شاشه البدايه بتاعت اللعبه بنحط الخلفيه والكلام لي هنعرضه والوانه وكدا
// شروق وروان
// روان
void cover() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -100.0f);
    background();
    glColor3f(0.67, 0.4, 0.8);
    glColor3f(0.7764705882352941, 0.607843137254902, 0.4823529411764706);
    writeStr(-50, 50, "\"THE MAZE\"", GLUT_BITMAP_TIMES_ROMAN_24);

    glColor3f(0.7764705882352941, 0.607843137254902, 0.4823529411764706);
    writeStr(-50, -20, "If you want to start the game press 1", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(-50, -40, "If you want to close the game press 2", GLUT_BITMAP_TIMES_ROMAN_24);
    glutSwapBuffers();


}

// شاشة الفوز بتاعت اللعبه بنحط الخلفيه والكلام لي هنعرضه سعتها وكدا
// شروق وروان
// روان
void winScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -50);
    glColor3f(0, 1, 0);
    writeStr(-25, 40, "WILL DONE", GLUT_BITMAP_TIMES_ROMAN_24);

    glColor3f(0.7764705882352941, 0.607843137254902, 0.4823529411764706);
    writeStr(-50, -20, "If you want to end the game ,press 3 ", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(-50, -60, "If you want to next level ,press 4 ", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(-50, -40, "If you want to play again , press 1", GLUT_BITMAP_TIMES_ROMAN_24);
    glutSwapBuffers();
}
//----------------------------------------------------------------------------------------------------------------------------------------

// شاشة الخساره بنحط فيها الخلفيه واللون والكلام لي هنعرضه سعتها وكدا
//كمال ومريم
// كمال
void loseScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -50.0f);
    glColor3f(0.7764705882352941, 0.607843137254902, 0.4823529411764706);
    writeStr(-50, 20, "TIME OUT ", GLUT_BITMAP_TIMES_ROMAN_24);
    background();


    glColor3f(0.7764705882352941, 0.607843137254902, 0.4823529411764706);
    writeStr(-50, -20, "If you want to end the game ,press 3", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(-50, -40, "If you want to play again, press 1", GLUT_BITMAP_TIMES_ROMAN_24);
    glutSwapBuffers();
}

// كمال ومريم
// مريم
// شاشه لي بتظهر لما نخلص كل المستويات وبنحط فيها اللون والكلام لي بنعرضه وخلافه سيم
void FinshScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -50);
    glColor3f(0, 1, 0);
    writeStr(-50, 50, "CONGRATULATIONS!", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(-50, 30, "You have Finshed the maze", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1.0, 1.0, 1.0);
    writeStr(-50, 10, "Press 1 to restart the game ", GLUT_BITMAP_TIMES_ROMAN_24);
    writeStr(-50, 0, "Press 3 to go to main menu", GLUT_BITMAP_TIMES_ROMAN_24);
    glutSwapBuffers();
}


// شاكر وفتحي
// فتحي
// فانكشن بتشوف هنعرض انهي شاشه وده مربوطه باكثر من فانكشن تانيه
// مثلا لما دوسنا علي 1 فوق قولناله خلي فاريابل سي اش ده ب 1 فيروح لصفحه اللعبه
// في فانكشن تانيه لما التايمر يخلص بنقوله سعتها خلي السي اش ب 2 وسعتها بيروح لشاشه الخساره وهكذا
void display() {
    if (ch == -1)cover();
    else if (ch == 1) {
        map();
    }
    else if (ch == 2) {
        loseScreen();
    }
    if (co[current_level][0] == co[current_level][2] && co[current_level][1] == co[current_level][3]) {

        if (current_level == levels - 1) {
            current_level = 0;
            FinshScreen();
        }
        else
        {
            co[current_level][0] = 9;
            co[current_level][1] = 0;
            current_level++;
            winScreen();
        }

        ch = 3;
    }

    if (ch != 1) {
        co[current_level][0] = 9;
        co[current_level][1] = 0;
    }

}
// شاكر وفتحي
// شاكر
// الفانكشن المسئوله عن تحريك المكعب وده بنديها الاسكي كود بتاع الحرف
// و الخط الافقي والعمودي وبنقوله شوف لو احنا دوسنا علي لي فوق وفي مكان فاضي ومفيش تصادم اتحرك عادي
// وهكذا لباقي الاتجاهات
void SpecialKey(int key, int x, int y) {
    switch (key)
    {
    case GLUT_KEY_UP:
        if (valid(co[current_level][0] - 1, co[current_level][1]) && !maze[current_level][co[current_level][0] - 1][co[current_level][1]])
            co[current_level][0]--;
        break;
    case GLUT_KEY_DOWN:
        if (valid(co[current_level][0] + 1, co[current_level][1]) && !maze[current_level][co[current_level][0] + 1][co[current_level][1]])
            co[current_level][0]++;
        break;
    case GLUT_KEY_LEFT:
        if (valid(co[current_level][0], co[current_level][1] - 1) && !maze[current_level][co[current_level][0]][co[current_level][1] - 1])
            co[current_level][1]--;
        break;
    case GLUT_KEY_RIGHT:
        if (valid(co[current_level][0], co[current_level][1] + 1) && !maze[current_level][co[current_level][0]][co[current_level][1] + 1])
            co[current_level][1]++;
        break;
    }
    display();
}
// شروق وروان
// شروق
// هنا فانكشن الكاميرا بنستخدمها عشان نشوف زاويه عرض المتاهه وشكلها وعايزين تبقي ظاهره ازاي في اللعبه وكدا
void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, aspect, 0.7f, 200.0f);
    gluLookAt(0, -60, 50, 20, 0, -180, 0, 10, 1);
    glMatrixMode(GL_MODELVIEW);

}

// شاكر وفتحي
// فتحي
// ده مسئوله عن الاكشن بتاع شاشه البدايه اول ما التطبيق يفتح والزراير لي جواه
// بتقوله لو دوست واحد اعمل كذا ولو اتنين اعمل كذا
// ولو مسحتها هتلاقي لما بتدوس علي اي زرار مش بيعمل حاجه والاكشن مش شغال
void idle()
{
    if (ch == 1)
    {
        endd = clock();
        count = (endd - start) / CLOCKS_PER_SEC;
        if (count == 20) {
            ch = 2;
        }
    }
    glutPostRedisplay();
}

int main(int agrc, char** agrv) {
    glutInit(&agrc, agrv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutCreateWindow("Solve The Maze");
    glEnable(GL_DEPTH_TEST);
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(SpecialKey);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    system("pause");
    return 0;
}
