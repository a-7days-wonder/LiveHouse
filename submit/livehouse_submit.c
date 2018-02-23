//
//  livehouse.c
//  CGexB
//
//  Created by 永田駿平 on 2017/11/14.
//  Copyright © 2017年 SyunpeiNagata. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "GLMetaseq.h"

///////////////テクスチャ用///////////////
#define TEXWIDTH1 256 //テクスチャの幅
#define TEXHEIGHT1 256 //テクスチャの高さ
static const char texture1[] = "Texture/flooring.data";
GLuint texid_1;

#define TEXWIDTH2 256
#define TEXHEIGHT2 150
static const char texture2[] = "Texture/wall.data";
GLuint texid_2;

#define TEXWIDTH3 256
#define TEXHEIGHT3 256
static const char texture3[] = "Texture/ceiling.data";
GLuint texid_3;

#define TEXWIDTH4 75
#define TEXHEIGHT4 256
static const char texture4[] = "Texture/bass.data";
GLuint texid_4;

#define TEXWIDTH5 86
#define TEXHEIGHT5 256
static const char texture5[] = "Texture/guitar.data";
GLuint texid_5;
///////////////テクスチャ用ここまで////////////////

MQO_MODEL light;
MQO_MODEL fence;
MQO_MODEL bamp;
MQO_MODEL gamp;
MQO_MODEL mic;
MQO_MODEL drum;
MQO_MODEL mainsp;
MQO_MODEL sub;
MQO_MODEL monitor;

int isRon, isGon, isBon; //灯体が点灯しているか否か

GLdouble CameraAngle[2] = {0.0, 0.0}; //カメラの向き
GLdouble CameraPosition[3] = {0.0, 0.7, 10.0}; //カメラの位置
GLint WindowSize[2] = {0.0, 0.0}; //ウインドウサイズ


static GLfloat red[] = {0.8, 0.2, 0.2, 1.0};
static GLfloat green[] = { 0.2, 0.8, 0.2, 1.0 };
static GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };

static GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
static GLfloat gray[] = {0.2, 0.2, 0.2, 1.0};
static GLfloat stagecolor[] = {0.1, 0.1, 0.1, 1.0};

void hako() {
    //glCullFace(GL_FRONT)のために全て裏(視点から見て右回り)に描く
    glEnable(GL_TEXTURE_2D); //テクスチャマッピングの有効化
    //床
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
    glBindTexture(GL_TEXTURE_2D, texid_1);
    glBegin(GL_QUADS);
    glNormal3d(0.0, 1.0, 0.0);
    glTexCoord2d(0.0, 0.0); glVertex3d(-4.0, -0.5, -7.0);
    glTexCoord2d(0.0, 1.0); glVertex3d(4.0, -0.5, -7.0);
    glTexCoord2d(1.0, 1.0); glVertex3d(4.0, -0.5, 7.0);
    glTexCoord2d(1.0, 0.0); glVertex3d(-4.0, -0.5, 7.0);
    glEnd();
    //glBindTexture(GL_TEXTURE_2D, 0);
    
    //壁1
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
    glBindTexture(GL_TEXTURE_2D, texid_2);
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, 1.0);
    glTexCoord2d(0.0, 0.0); glVertex3d(-4.0, -0.5, -7.0);
    glTexCoord2d(0.0, 1.0); glVertex3d(-4.0, 3.0, -7.0);
    glTexCoord2d(1.0, 1.0); glVertex3d(4.0, 3.0, -7.0);
    glTexCoord2d(1.0, 0.0); glVertex3d(4.0, -0.5, -7.0);
    glEnd();
    
    //壁2
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
    glBegin(GL_QUADS);
    glNormal3d(-1.0, 0.0, 0.0);
    glTexCoord2d(0.0, 0.0); glVertex3d(4.0, -0.5, -7.0);
    glTexCoord2d(0.0, 1.0); glVertex3d(4.0, 3.0, -7.0);
    glTexCoord2d(1.0, 1.0); glVertex3d(4.0, 3.0, 7.0);
    glTexCoord2d(1.0, 0.0); glVertex3d(4.0, -0.5, 7.0);
    glEnd();
    
    //壁3
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, -1.0);
    glTexCoord2d(0.0, 0.0); glVertex3d(4.0, -0.5, 7.0);
    glTexCoord2d(0.0, 1.0); glVertex3d(4.0, 3.0, 7.0);
    glTexCoord2d(1.0, 1.0); glVertex3d(-4.0, 3.0, 7.0);
    glTexCoord2d(1.0, 0.0); glVertex3d(-4.0, -0.5, 7.0);
    glEnd();
    
    //壁4
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
    glBegin(GL_QUADS);
    glNormal3d(1.0, 0.0, 0.0);
    glTexCoord2d(0.0, 0.0); glVertex3d(-4.0, -0.5, 7.0);
    glTexCoord2d(0.0, 1.0); glVertex3d(-4.0, 3, 7.0);
    glTexCoord2d(1.0, 1.0); glVertex3d(-4.0, 3.0, -7.0);
    glTexCoord2d(1.0, 0.0); glVertex3d(-4.0, -0.5, -7.0);
    glEnd();
    //glBindTexture(GL_TEXTURE_2D, 0);
    
    //天井
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
    glBindTexture(GL_TEXTURE_2D, texid_3);
    glBegin(GL_QUADS);
    glNormal3d(0.0, -1.0, 0.0);
    glTexCoord2d(0.0, 0.0); glVertex3d(-4.0, 3.0, 7.0);
    glTexCoord2d(0.0, 1.0); glVertex3d(4.0, 3.0, 7.0);
    glTexCoord2d(1.0, 1.0); glVertex3d(4.0, 3.0, -7.0);
    glTexCoord2d(1.0, 0.0); glVertex3d(-4.0, 3.0, -7.0);
    glEnd();
    glTexCoord2d(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D); //テクスチャマッピングの無効化
}
void stage() {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, stagecolor);
    glBegin(GL_QUADS);
    //床
    glNormal3d(0.0, 1.0, 0.0);
    glVertex3d(-4.0, 0.2, -7.0); glVertex3d(4.0, 0.2, -7.0);
    glVertex3d(4.0, 0.2, -3.0); glVertex3d(-4.0, 0.2, -3.0);
    
    //観客側壁
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3d(-4.0, 0.2, -3.0); glVertex3d(4.0, 0.2, -3.0);
    glVertex3d(4.0, -0.5, -3.0); glVertex3d(-4.0, -0.5, -3.0);
    glEnd();
    
    //機材
    glPushMatrix();
    glTranslated(-2.0, 0.7, -5.0);
    glTranslated(0.0, 0.24, 0.0);
    mqoCallModel(bamp);
    glTranslated(0.0, -0.24, 0.0);
    glTranslated(2.0, -0.14, 0.0);
    mqoCallModel(drum);
    glTranslated(0.0, 0.14, 1.5);
    mqoCallModel(mic);
    glTranslated(2.0, -0.24, -1.5);
    mqoCallModel(gamp);
    glPopMatrix();
    
    //メイン、サブ
    glPushMatrix();
    glTranslated(-3.5, 0.45, -3.5);
    glRotated(30.0, 0.0, 1.0, 0.0);
    mqoCallModel(sub);
    glTranslated(0.0, 0.75, 0.0);
    mqoCallModel(mainsp);
    glPopMatrix();
    glPushMatrix();
    glTranslated(3.5, 0.45, -3.5);
    glRotated(-30.0, 0.0, 1.0, 0.0);
    mqoCallModel(sub);
    glTranslated(0.0, 0.75, 0.0);
    mqoCallModel(mainsp);
    glPopMatrix();
    
    //返し
    glPushMatrix();
    glTranslated(-2.0, 0.5, -3.5);
    mqoCallModel(monitor);
    glTranslated(4.0, 0.0, 0.0);
    mqoCallModel(monitor);
    glTranslated(-2.5, 0.0, 0.0);
    glRotated(-55.0, 0.0, 1.0, 0.0);
    mqoCallModel(monitor);
    glRotated(55.0, 0.0, 1.0, 0.0);
    glTranslated(1.0, 0.0, 0.0);
    glRotated(55.0, 0.0, 1.0, 0.0);
    mqoCallModel(monitor);
    glRotated(-55.0, 0.0, 1.0, 0.0);
    glTranslated(1.0, 0.0, -2.5);
    glRotated(90.0, 0.0, 1.0, 0.0);
    mqoCallModel(monitor);
    glPopMatrix();
    
    glPushMatrix();
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);
    //ベース
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
    glBindTexture(GL_TEXTURE_2D, texid_4);
    glTranslated(-2.5, 0.2, -4.5);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex3d(-0.175, 1.5, 0.0);
    glTexCoord2d(1, 0); glVertex3d(0.175, 1.5, 0.0);
    glTexCoord2d(1, 1); glVertex3d(0.175, 0.0, 0.0);
    glTexCoord2d(0, 1); glVertex3d(-0.175, 0.0, 0.0);
    glEnd();
    //ギター
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
    glBindTexture(GL_TEXTURE_2D, texid_5);
    glTranslated(5.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex3d(-0.22, 1.3, 0.0);
    glTexCoord2d(1, 0); glVertex3d(0.22, 1.3, 0.0);
    glTexCoord2d(1, 1); glVertex3d(0.22, 0.0, 0.0);
    glTexCoord2d(0, 1); glVertex3d(-0.22, 0.0, 0.0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void setLights() {
    glPushMatrix();
    
    //灯体1
    glTranslated(-3.0, 2.5, -6.5);
    glRotated(25.0, 0.0, 1.0, 0.0);
    glRotated(21.0, 1.0, 0.0, 0.0);
    mqoCallModel(light);
    glRotated(-21.0, 1.0, 0.0, 0.0);
    glRotated(-25.0, 0.0, 1.0, 0.0);
    
    //灯体2
    glTranslated(2.0, 0.0, 0.0);
    glRotated(-26.5, 0.0, 1.0, 0.0);
    glRotated(32.0, 1.0, 0.0, 0.0);
    mqoCallModel(light);
    glRotated(-32.0, 1.0, 0.0, 0.0);
    glRotated(26.5, 0.0, 1.0, 0.0);
    
    //灯体3
    glTranslated(2.0, 0.0, 0.0);
    glRotated(32.0, 1.0, 0.0, 0.0);
    glRotated(26.5, 0.0, 1.0, 0.0);
    mqoCallModel(light);
    glRotated(-26.5, 0.0, 1.0, 0.0);
    glRotated(-32.0, 1.0, 0.0, 0.0);
    
    //灯体4
    glTranslated(2.0, 0.0, 0.0);
    glRotated(21.0, 1.0, 0.0, 0.0);
    glRotated(-25.0, 0.0, 1.0, 0.0);
    mqoCallModel(light);
    glRotated(25.0, 0.0, 1.0, 0.0);
    glRotated(-21.0, 1.0, 0.0, 0.0);
    
    //灯体5
    glTranslated(-6.0, -0.7, 0.0);
    glRotated(39.0, 0.0, 1.0, 0.0);
    glRotated(20.0, 1.0, 0.0, 0.0);
    mqoCallModel(light);
    glRotated(-20.0, 1.0, 0.0, 0.0);
    glRotated(-39.0, 0.0, 1.0, 0.0);
    
    //灯体6
    glTranslated(6.0, 0.0, 0.0);
    glRotated(-39.0, 0.0, 1.0, 0.0);
    glRotated(20.0, 1.0, 0.0, 0.0);
    mqoCallModel(light);
    glRotated(-20.0, 1.0, 0.0, 0.0);
    glRotated(39.0, 0.0, 1.0, 0.0);
    
    glPopMatrix();
}

void setFence() {
    int i;
    glPushMatrix();
    glTranslated(-3.0, 0.0, -2.5);
    for(i=0; i<4; i++) {
        mqoCallModel(fence);
        glTranslated(2.0, 0.0, 0.0);
    }
    glPopMatrix();
}

void display(void) {
    static GLfloat light0pos[] = {0.0, 3.0, 0.0, 1.0};
    static GLfloat light1pos[] = {-3.0, 2.5, -6.5, 1.0};
    static GLfloat light2pos[] = {-1.0, 2.5, -6.5, 1.0};
    static GLfloat light3pos[] = {1.0, 2.5, -6.5, 1.0};
    static GLfloat light4pos[] = {3.0, 2.5, -6.5, 1.0};
    static GLfloat light5pos[] = {-3.0, 1.8, -6.5, 1.0};
    static GLfloat light6pos[] = {3.0, 1.8, -6.5, 1.0};
    
    static GLfloat light14dir[] = {0.0, 0.0, 0.0};
    static GLfloat light2dir[] = {-3.0, 0.0, -2.5};
    static GLfloat light3dir[] = {3.0, 0.0, -2.5};
    static GLfloat light5dir[] = {1.0, 0.0, -1.5};
    static GLfloat light6dir[] = {-1.0, 0.0, -1.5};
    
    //ウィンドウの塗りつぶし
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    
    glRotatef(-CameraAngle[1] / M_PI * 180, 1.0, 0.0, 0.0);
    glRotatef(CameraAngle[0] / M_PI * 180, 0.0, 1.0, 0.0);
    glTranslatef(-CameraPosition[0], -CameraPosition[1], -CameraPosition[2]);

    //光源の位置を設定
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    
    //灯体1
    glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
    //glLightfv(GL_LIGHT1, GL_AMBIENT, red);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red);
    glLightfv(GL_LIGHT1, GL_SPECULAR, red);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light14dir);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0);
    
    //灯体2
    glLightfv(GL_LIGHT2, GL_POSITION, light2pos);
    //glLightfv(GL_LIGHT2, GL_AMBIENT, green);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, green);
    glLightfv(GL_LIGHT2, GL_SPECULAR, green);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2dir);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60.0);
    
    //灯体3
    glLightfv(GL_LIGHT3, GL_POSITION, light3pos);
    //glLightfv(GL_LIGHT3, GL_AMBIENT, green);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, green);
    glLightfv(GL_LIGHT3, GL_SPECULAR, green);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3dir);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 60.0);
    
    //灯体4
    glLightfv(GL_LIGHT4, GL_POSITION, light4pos);
    //glLightfv(GL_LIGHT4, GL_AMBIENT, red);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, red);
    glLightfv(GL_LIGHT4, GL_SPECULAR, red);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, light14dir);
    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 60.0);
    
    //灯体5
    glLightfv(GL_LIGHT5, GL_POSITION, light5pos);
    //glLightfv(GL_LIGHT5, GL_AMBIENT, blue);
    glLightfv(GL_LIGHT5, GL_DIFFUSE, blue);
    glLightfv(GL_LIGHT5, GL_SPECULAR, blue);
    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, light5dir);
    glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 60.0);
    
    //灯体6
    glLightfv(GL_LIGHT6, GL_POSITION, light6pos);
    //glLightfv(GL_LIGHT6, GL_AMBIENT, blue);
    glLightfv(GL_LIGHT6, GL_DIFFUSE, blue);
    glLightfv(GL_LIGHT6, GL_SPECULAR, blue);
    glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, light6dir);
    glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 60.0);
    
    //図形の描画
    glPushMatrix();
    hako();
    stage();
    setLights();
    setFence();
    glPopMatrix();
    
    glutSwapBuffers();
}

void resize(int w, int h)
{
    /* ウィンドウ全体をビューポートにする */
    glViewport(0, 0, w, h);
    
    WindowSize[0] = w;
    WindowSize[1] = h;
    
    /* 透視変換行列の指定 */
    glMatrixMode(GL_PROJECTION);
    
    /* 透視変換行列の初期化 */
    glLoadIdentity();
    gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
    
    /* モデルビュー変換行列の指定 */
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q':
    case 'Q':
    case '\033': //'\033'はESCのASCIIコード
        exit(0);
        break;
    default:
        break;
    }
    const double vel = 0.1;
    
    //キーボード入力RGBによる照明点灯・消灯
    switch (key) {
        case 'r':
            if(isRon==1) {
                glDisable(GL_LIGHT1);
                glDisable(GL_LIGHT4);
                isRon = 0;
                printf("R is disabled.\n");
            } else {
                glEnable(GL_LIGHT1);
                glEnable(GL_LIGHT4);
                isRon = 1;
                printf("R is enabled.\n");
            }
            break;
        case 'g':
            if(isGon==1) {
                glDisable(GL_LIGHT2);
                glDisable(GL_LIGHT3);
                isGon = 0;
                printf("G is disabled.\n");
            } else {
                glEnable(GL_LIGHT2);
                glEnable(GL_LIGHT3);
                isGon = 1;
                printf("G is enabled.\n");
            }
            break;
        case 'b':
            if(isBon==1) {
                glDisable(GL_LIGHT5);
                glDisable(GL_LIGHT6);
                isBon = 0;
                printf("B is disabled.\n");
            } else {
                glEnable(GL_LIGHT5);
                glEnable(GL_LIGHT6);
                isBon = 1;
                printf("B is enabled.\n");
            }
            break;
        default:
            break;
    }
    
    /* キーボード入力WASDによる移動処理 */
    switch (key) {
        case 'w':
            //前進 z+
            CameraPosition[0] += vel * cos(CameraAngle[0] - M_PI/2.0);
            CameraPosition[2] += vel * sin(CameraAngle[0] - M_PI/2.0);
            break;
        case 's':
            //後退 z-
            CameraPosition[0] += vel * cos(CameraAngle[0] + M_PI/2.0);
            CameraPosition[2] += vel * sin(CameraAngle[0] + M_PI/2.0);
            break;
        case 'a':
            //左に平行移動 x-
            CameraPosition[0] += vel * cos(CameraAngle[0] + M_PI);
            CameraPosition[2] += vel * sin(CameraAngle[0] + M_PI);
            break;
        case 'd':
            //右に平行移動 x+
            CameraPosition[0] += vel * cos(CameraAngle[0]);
            CameraPosition[2] += vel * sin(CameraAngle[0]);
            break;
        case ' ':
        default:
            break;
    }
    glutPostRedisplay();
}

void motion(int x, int y)
{
    //カメラの向きを変更する
    CameraAngle[0] = (GLdouble)x / WindowSize[0] * M_PI * 2 - M_PI;
    CameraAngle[1] = (GLdouble)y / -WindowSize[1] * M_PI + M_PI / 2.0;
}

void init(void) {
    //テクスチャ
    FILE *fp;
    GLubyte texture_buf1[TEXHEIGHT1][TEXWIDTH1][4];
    GLubyte texture_buf2[TEXHEIGHT2][TEXWIDTH2][4];
    GLubyte texture_buf3[TEXHEIGHT3][TEXWIDTH3][4];
    GLubyte texture_buf4[TEXHEIGHT4][TEXWIDTH4][4];
    GLubyte texture_buf5[TEXHEIGHT5][TEXWIDTH5][4];
    
    if((fp = fopen(texture1, "rb")) != NULL) {
        fread(texture_buf1, sizeof(texture_buf1), 1, fp);
        fclose(fp);
    } else {
        perror(texture1);
    }
    
    if((fp = fopen(texture2, "rb")) != NULL) {
        fread(texture_buf2, sizeof(texture_buf2), 1, fp);
        fclose(fp);
    } else {
        perror(texture2);
    }
    
    if((fp = fopen(texture3, "rb")) != NULL) {
        fread(texture_buf3, sizeof(texture_buf3), 1, fp);
        fclose(fp);
    } else {
        perror(texture3);
    }
    
    if ((fp = fopen(texture4, "rb")) != NULL) {
        fread(texture_buf4, sizeof texture_buf4, 1, fp);
        fclose(fp);
    } else {
        perror(texture4);
    }
    
    if ((fp = fopen(texture5, "rb")) != NULL) {
        fread(texture_buf5, sizeof texture_buf5, 1, fp);
        fclose(fp);
    } else {
        perror(texture5);
    }
    
    ////////// 1枚目のテクスチャの読み込み ////////////
    glGenTextures(1, &texid_1);
    glBindTexture(GL_TEXTURE_2D, texid_1);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TEXWIDTH1, TEXHEIGHT1,
                      GL_RGBA, GL_UNSIGNED_BYTE, texture_buf1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    ////////// 2枚目のテクスチャの読み込み ////////////
    glGenTextures(1, &texid_2);
    glBindTexture(GL_TEXTURE_2D, texid_2);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TEXWIDTH2, TEXHEIGHT2,
                      GL_RGBA, GL_UNSIGNED_BYTE, texture_buf2);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    ////////// 3枚目のテクスチャの読み込み ////////////
    glGenTextures(1, &texid_3);
    glBindTexture(GL_TEXTURE_2D, texid_3);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TEXWIDTH3, TEXHEIGHT3,
                      GL_RGBA, GL_UNSIGNED_BYTE, texture_buf3);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    ////////// 4枚目のテクスチャの読み込み ////////////
    glGenTextures(1, &texid_4);
    glBindTexture(GL_TEXTURE_2D, texid_4);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TEXWIDTH4, TEXHEIGHT4,
                      GL_RGBA, GL_UNSIGNED_BYTE, texture_buf4);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    ////////// 5枚目のテクスチャの読み込み ////////////
    glGenTextures(1, &texid_5);
    glBindTexture(GL_TEXTURE_2D, texid_5);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TEXWIDTH5, TEXHEIGHT5,
                      GL_RGBA, GL_UNSIGNED_BYTE, texture_buf5);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    ////////////////////////////////////////////////////
    
    //ウィンドウを塗りつぶす色の設定
    glClearColor(1.0, 1.0, 0.8, 1.0);
    glEnable(GL_DEPTH_TEST);
    glAlphaFunc(GL_GREATER, 0.5);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    
    glEnable(GL_LIGHTING);
    //光源の設定
    glEnable(GL_LIGHT0); //環境光
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    
    glEnable(GL_LIGHT1); //灯体
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_LIGHT5);
    glEnable(GL_LIGHT6);
    
    isRon = 1;
    isGon = 1;
    isBon = 1;
}
void idle(void) {
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 400);
    glutCreateWindow(argv[0]);
    
    //メタセコイア読み込み
    mqoInit();
    light = mqoCreateModel("mqofiles/light.mqo", 0.0018);
    fence = mqoCreateModel("mqofiles/fence.mqo", 0.005);
    bamp = mqoCreateModel("mqofiles/bamp.mqo", 0.006);
    gamp = mqoCreateModel("mqofiles/gamp.mqo", 0.006);
    mic = mqoCreateModel("mqofiles/mic.mqo", 0.005);
    drum = mqoCreateModel("mqofiles/drum.mqo", 0.007);
    mainsp = mqoCreateModel("mqofiles/mainsp.mqo", 0.005);
    sub = mqoCreateModel("mqofiles/sub.mqo", 0.005);
    monitor = mqoCreateModel("mqofiles/monitor.mqo", 0.005);
    
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    
    init();
    glutMainLoop();
    return 0;
}


