#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

bool eixos = true,
     wire = !true;

float rotX = 0.0,
      rotY = 0.0,
      rotX_ini, rotY_ini;

float obsX = 10.0,
      obsY = 50.0,
      obsZ = 150.0,
      obsX_ini, obsY_ini, obsZ_ini;

int x_ini, y_ini, bot;
float anguloMartelo =45 ;
int clique=-1;
int passo = 10;
int passo2 = 25;
bool flagBatida = false, ldifusa=false,ambiente=false;
GLfloat fAspect;
GLUquadricObj *cepo;

//-----------------------------------------------------------------------
void desenha_circulo(float r){ //desenha centro na origem
    int NUM_LINHAS = 360;
    glBegin(GL_POLYGON);
        for(int i = 0; i < NUM_LINHAS; i++){
            float ang = i * M_PI / 180.0;
            glVertex3f(r * cos(ang), r * sin(ang), 0.0);
        }
    glEnd();
}
void desenha_cilindro(float raio, float altura, float angulo){
    //desenha o cilindro com o raio especifico e o centro geometrico localizado em:
    //altura/2.0  na direção positiva do eixo Z
    glPushMatrix();
        glRotatef(angulo, 1, 0,0);
        //glScalef(t.ex, t.ey, t.ez);
        gluCylinder(cepo,raio, raio, altura, 32, 32);
        //"tampa" inferior
        desenha_circulo(raio);
        //"Tampa" superior
        glPushMatrix();
            glTranslatef(0.0, 0.0, 0);
            desenha_circulo(raio);
        glPopMatrix();
    glPopMatrix();
}
//------------------------------------------------------------------------------

void desenhaCenarioSolid()
{
   //cepo de madeira
    glPushMatrix();
    	glColor3f( 0.5, 0.2, 0.13 );
        glTranslatef( 0.0, -10.0, 0.0 );
        glScalef( 0.30, 0.2, 0.10 );
       // glutSolidCube(50);
        //glRotatef(90, 1,0 , 0);
        //gluCylinder(cepo, 80, 80, 50, 42, 42);
        desenha_cilindro(50, 50, 90);
    glPopMatrix();
    //prego
    glPushMatrix();
        glColor3f( 0.3, 0.35, 0.5 );
        glTranslatef( 0.0, -5.0, 0.0 );
        glScalef( 0.10, 1.6, 0.10 );
        glutSolidCube(10);
        //glRotatef(90, 1,0 , 0);
        //gluCylinder(cepo, 80, 80, 50, 42, 42);
    glPopMatrix();
    //corpo
      /* glPushMatrix();
            glColor3f( 0.5, 0.5, 0.5 );
            glRotatef(140,0,0,1);
            glTranslatef( -30.0, -63.0, 0.10 );
            glScalef( 0.1, 0.85, 0.1 );
            glutSolidCube(50);
        glPopMatrix();*/
    //martelo
    glPushMatrix();
    	glTranslatef(40,24,0.1);
	    glRotatef(anguloMartelo,0,0,1);
	    glTranslatef(0,15,0);

        glPushMatrix();
            glColor3f( 1.0,0.98, 0.80 );
            glTranslatef( 0.0, 0.0, 0.10 );
            glScalef( 0.10, 1.8, 0.1 );
            glutSolidCube(50);
        glPopMatrix();
	    glPushMatrix();
	    	glColor3f( 1.0, 0.0, 0.0 );
	        glTranslatef( 0.0, 24.0, 0.10 );
	        glScalef( 0.80, 0.5, 0.5 );
	        glutSolidCube(50);
           // glRotatef(-45, 0, -1, 0);
            //gluCylinder(cepo, 20, 20, 50, 42, 42);
	    glPopMatrix();

	    
    glPopMatrix();

    
}
//------------------------------------------------------------------------------
void display(void)
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //if( eixos ) desenhaEixos();

    desenhaCenarioSolid();

	glutSwapBuffers();
}

//------------------------------------------------------------------------------
void projecao(void)
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluPerspective( 60, fAspect, 0.1, 1000 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	gluLookAt( obsX,obsY,obsZ, 10,50,0, 0,1,0 );
}

//------------------------------------------------------------------------------
void reshape( GLsizei w, GLsizei h )
{
	if ( h == 0 ) h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w/(GLfloat)h;

	projecao();
}

//------------------------------------------------------------------------------
void keyboard( unsigned char key, int x, int y )
{
    switch( key )
    {
        case 27: exit(0); break;

        case 'q':
        case 'Q':
            if(ldifusa==0){
                glEnable(GL_LIGHT0);
                GLfloat difusa[] = {1.0, 1.0, 1.0, 1.0};
                glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
                ldifusa = !ldifusa;
            }else{
                 glDisable(GL_LIGHT0);
                 ldifusa = !ldifusa;
             }

        break;

        case 'w':
        case 'W':
            if(ambiente==0){
                glEnable(GL_LIGHT1);
                GLfloat ambient[] = {0.5, 0.5, 0.5, 1.0};
                glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
                ambiente =!ambiente;
            }else{ 
                glDisable(GL_LIGHT1);
                ambiente =!ambiente;
            }
        break;
    }
    glutPostRedisplay();
}

//------------------------------------------------------------------------------

void Inicializa (void)
{   

    printf("\n Para acender a luz difusa aperte Q \n");
    printf("\n Para acender a luz ambiente aperte W \n");
    cepo = gluNewQuadric();
    GLfloat posicao[]={0.0,50.0,0.0,0.0};
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glLightfv(GL_LIGHT0,GL_POSITION,posicao);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
	glEnable( GL_DEPTH_TEST );
}
//-----------------------------------------------------------------------
#define SENS_ROT 5.0
#define SENS_OBS 20.0
#define SENS_TRANSL 30.0

void motion( int x, int y )
{	
	
    if( bot == GLUT_RIGHT_BUTTON )
    {
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        rotY = rotY_ini - deltax/SENS_ROT;
        rotX = rotX_ini - deltay/SENS_ROT;

    }
    else if( bot == GLUT_MIDDLE_BUTTON )
    {
        int deltaz = y_ini - y;
        obsZ = obsZ_ini + deltaz/SENS_OBS;
    }
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glTranslatef( -obsX, -obsY, -obsZ );
    glRotatef( rotX, 1, 0, 0 );
    glRotatef( rotY, 0, 1, 0 );

    glutPostRedisplay();
}
//-----------------------------------------------------------------------
void mouse( int button, int state, int x, int y )
{	
	if( bot == GLUT_LEFT_BUTTON )
    {	
    	if(anguloMartelo == 45) clique = 0;
    	if(anguloMartelo == 90) clique = 1;
    	/*
    	if(clique==0){
    		anguloMartelo=90;
    		clique=1;
    	}else if(clique==1){
    		anguloMartelo=45;
    		clique=0;
    	}
    	*/
    	glutPostRedisplay();
    	
    }
    if( state == GLUT_DOWN )
    {
        x_ini = x;
        y_ini = y;

        obsX_ini = obsX;
        obsY_ini = obsY;
        obsZ_ini = obsZ;

        rotX_ini = rotX;
        rotY_ini = rotY;

        bot = button;
    } else {
        bot = -1;
    }
}
//------------------------------------------------------------------------------
void Timer(int value){

	if (value == 0){
		if(clique == 0){
			anguloMartelo-=passo;
			if(anguloMartelo <= 10){
				anguloMartelo = 10;
				flagBatida = true;	
			}
			if(flagBatida == true){ 
				if(anguloMartelo>=10  && anguloMartelo <90){
					anguloMartelo+=passo2;
					passo2+=passo;
				}
				if(anguloMartelo > 90) anguloMartelo = 90;
			}
		}
		else if(clique == 1){

			if(anguloMartelo <= 90) anguloMartelo-=passo;
			if(anguloMartelo < 45) anguloMartelo = 45;
			flagBatida = false;
			passo2 = 25;

		}

	glutTimerFunc(100,Timer, 0);
	}

	glutPostRedisplay();
}
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize( 450, 450 );
	glutCreateWindow("Trabalho Final(Minecraft)");

	glutDisplayFunc( display );
	glutMouseFunc( mouse );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
    glutMouseFunc( mouse );
    glutMotionFunc( motion );
    glutTimerFunc(100,Timer,0);

	Inicializa();

	glutMainLoop();
	return 0;
}
//------------------------------------------------------------------------------

