/* Test glGenProgramsNV(), glIsProgramNV(), glLoadProgramNV() */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <glad/glad.h>
#include "glut_wrap.h"


#define CI_OFFSET_1 16
#define CI_OFFSET_2 32


GLenum doubleBuffer;

static void Init(void)
{
   GLint errnum;
   GLuint prognum;
   
   static const char *prog1 =
      "!!ARBvp1.0\n"
      "OPTION ARB_position_invariant ;"
      "MOV  result.color, vertex.color;\n"
      "END\n";


   glGenProgramsARB(1, &prognum);

   glBindProgramARB(GL_VERTEX_PROGRAM_ARB, prognum);
   glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,
		      strlen(prog1), (const GLubyte *) prog1);

   errnum = glGetError();
   printf("glGetError = %d\n", errnum);
   if (errnum != GL_NO_ERROR)
   {
      GLint errorpos;

      glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &errorpos);
      printf("errorpos: %d\n", errorpos);
      printf("%s\n", (char *)glGetString(GL_PROGRAM_ERROR_STRING_ARB));
   }

   fprintf(stderr, "GL_RENDERER   = %s\n", (char *) glGetString(GL_RENDERER));
   fprintf(stderr, "GL_VERSION    = %s\n", (char *) glGetString(GL_VERSION));
   fprintf(stderr, "GL_VENDOR     = %s\n", (char *) glGetString(GL_VENDOR));
   fflush(stderr);

    glClearColor(0.0, 0.0, 1.0, 0.0);
}

static void Reshape(int width, int height)
{

    glViewport(0, 0, (GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
/*     glOrtho(-1.0, 1.0, -1.0, 1.0, -0.5, 1000.0); */
    glMatrixMode(GL_MODELVIEW);
}

static void Key(unsigned char key, int x, int y)
{

    switch (key) {
      case 27:
	exit(1);
      default:
	break;
    }

    glutPostRedisplay();
}

static void Draw(void)
{
   glClear(GL_COLOR_BUFFER_BIT); 

   glEnable(GL_VERTEX_PROGRAM_ARB);

   glBegin(GL_TRIANGLES);
   glColor3f(0,0,.7); 
   glVertex3f( 0.9, -0.9, -0.0);
   glColor3f(.8,0,0); 
   glVertex3f( 0.9,  0.9, -0.0);
   glColor3f(0,.9,0); 
   glVertex3f(-0.9,  0.0, -0.0);
   glEnd();

   glFlush();

   if (doubleBuffer) {
      glutSwapBuffers();
   }
}

static GLenum Args(int argc, char **argv)
{
    GLint i;

    doubleBuffer = GL_FALSE;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-sb") == 0) {
	    doubleBuffer = GL_FALSE;
	} else if (strcmp(argv[i], "-db") == 0) {
	    doubleBuffer = GL_TRUE;
	} else {
	    fprintf(stderr, "%s (Bad option).\n", argv[i]);
	    return GL_FALSE;
	}
    }
    return GL_TRUE;
}

int main(int argc, char **argv)
{
    GLenum type;

    glutInit(&argc, argv);

    if (Args(argc, argv) == GL_FALSE) {
	exit(1);
    }

    glutInitWindowPosition(0, 0); glutInitWindowSize( 250, 250);

    type = GLUT_RGB | GLUT_ALPHA;
    type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
    glutInitDisplayMode(type);

    if (glutCreateWindow(*argv) == GL_FALSE) {
	exit(1);
    }

    gladLoadGL();
    Init();

    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Key);
    glutDisplayFunc(Draw);
    glutMainLoop();
	return 0;
}
