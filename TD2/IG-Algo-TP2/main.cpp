# ifdef __APPLE__
# include <GLUT/glut.h>
# else
# include <GL/glut.h>
# endif
# include <math.h>
# include "window.hpp"
# include "object.hpp"
# include <vector>

Window window;
void display();
void reshape(int, int);
void keyboard_down(unsigned char, int, int);

mat4 transformation_matrix(double, double, double, vec3);
mat4x3 projection_matrix(double);
void load_box(Object &);
void load_sphere(Object &);

Object myobject;
double angle = 0;
vec4 light(0.5773, 0.5773, -0.5773, 0);

int main(int argc, char** argv)
{
	load_box(myobject);
	load_sphere(myobject);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
	glutInitWindowSize(window.get_width(), window.get_height());
	glutCreateWindow("IG");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard_down);

	glutMainLoop();
}

void reshape(int width, int height)
{
	window.reshape(width, height);
}

void keyboard_down(unsigned char key, int x, int y)
{
	switch( key )
	{
		case 'q' :
		case 'Q' :
		case 27 :
			exit( EXIT_SUCCESS );
			break;
		default :
			break;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//*** TP02 ***
	myobject.draw_method = DRAW_WIRE;

	/*** TP03 ***
	myobject.draw_method = DRAW_FILL;
	*/
	/*** TP04 ***
	myobject.draw_method = DRAW_LAMBERT;
	myobject.draw_method = DRAW_GOURAUD;
	*/
	//***Code to uncomment after TP01 ***
	vec3 trans(0.0f, 0.0f, -800.0f);
	mat4 trans_matrix = transformation_matrix(angle, angle, angle, trans);
	mat4x3 proj_matrix = projection_matrix(1000.0f);
	angle += 0.25;

	myobject.update_transformation(trans_matrix);
	myobject.update_projection(proj_matrix);

	/*** TP03 ***
	myobject.backface_culling(trans_matrix);
	*/

	//*** To uncomment after TP01 ***
	myobject.draw(window, light);


    /***Don't change anything from here***/
	window.antialiasing();

	glDrawPixels(window.get_width(), window.get_height(), GL_RGB, GL_UNSIGNED_BYTE, window.get_pixels());
	glutSwapBuffers();
	glutPostRedisplay();
	window.clear();
}

/* TD2, Exercice 1
 * transformation_matrix :
 * Parametres : - pitch : double : angle de rotation x, en degres (=teta(x))
 *              - yaw : double : angle de rotation y
 *              - roll : double : angle de rotation z
 *              - translation : vec3 : translation dans la transformation
 * Retour : mat4 : matrice combinant les rotations et les translations
 */
mat4 transformation_matrix(double pitch, double yaw, double roll, vec3 translation)
{
	/*1. multiplier par la matrice de transformation pour le positionner
	* 2. calculer la matrice de rotation : truc avec les cos et sin
	// rot_x_matrix[colonne][ligne] = ...
	*/

	/*mat4 m_translation;
    m_translation[0][0] = translation.x;
    m_translation[0][1] = translation.y;
    m_translation[0][2] = translation.z;
    m_translation[0][3] = 1;
    */

	double rad_pitch = pitch * (M_PI / 180);
	double rad_yaw = yaw * (M_PI / 180);
	double rad_roll = roll * (M_PI / 180);

    mat4 r_x;
    mat4 r_y;
    mat4 r_z;

    r_x[1 ][1] = cos(rad_pitch);
    r_x[2][1] = -sin(rad_pitch);
    r_x[1][2] = sin(rad_pitch);
    r_x[2][2] = cos(rad_pitch);

    r_y[0][0] = cos(rad_yaw);
    r_y[2][0] = sin(rad_yaw);
    r_y[0][2] = -sin(rad_yaw);
    r_y[2][2] = cos(rad_yaw);

    r_z[0][0] = cos(rad_roll);
    r_z[1][0] = -sin(rad_roll);
    r_z[0][1] = sin(rad_roll);
    r_z[1][1] = cos(rad_roll);


    /*
    mat4 m_rotation_x = mat4(1.0, 0.0, 0.0, 0.0,
                            0.0, cos(rad_pitch), -sin(rad_pitch), 0.0,
                            0.0, sin(rad_pitch), cos(rad_pitch), 0.0,
                            0.0, 0.0, 0.0, 1.0)
                    * mat4(cos(rad_pitch), 0.0, sin(rad_pitch), 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            -sin(rad_pitch), 0.0, cos(rad_pitch), 0.0,
                            0.0, 0.0, 0.0, 1.0)
                    * mat4(cos(rad_pitch), -sin(rad_pitch), 0.0, 0.0,
                            sin(rad_pitch), cos(rad_pitch), 0.0, 0.0,
                            0.0, 0.0, 0.0, 1.0,
                            0.0, 0.0, 0.0, 1.0);

    mat4 m_rotation_y = mat4(1.0, 0.0, 0.0, 0.0,
                            0.0, cos(rad_yaw), -sin(rad_yaw), 0.0,
                            0.0, sin(rad_yaw), cos(rad_yaw), 0.0,
                            0.0, 0.0, 0.0, 1.0)
                    * mat4(cos(rad_yaw), 0.0, sin(rad_yaw), 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            -sin(rad_yaw), 0.0, cos(rad_yaw), 0.0,
                            0.0, 0.0, 0.0, 1.0)
                    * mat4(cos(rad_yaw), -sin(rad_yaw), 0.0, 0.0,
                            sin(rad_yaw), cos(rad_yaw), 0.0, 0.0,
                            0.0, 0.0, 0.0, 1.0,
                            0.0, 0.0, 0.0, 1.0);

    mat4 m_rotation_z = mat4(1.0, 0.0, 0.0, 0.0,
                            0.0, cos(rad_roll), -sin(rad_roll), 0.0,
                            0.0, sin(rad_roll), cos(rad_roll), 0.0,
                            0.0, 0.0, 0.0, 1.0)
                    * mat4(cos(rad_roll), 0.0, sin(rad_roll), 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            -sin(rad_roll), 0.0, cos(rad_roll), 0.0,
                            0.0, 0.0, 0.0, 1.0)
                    * mat4(cos(rad_roll), -sin(rad_roll), 0.0, 0.0,
                            sin(rad_roll), cos(rad_roll), 0.0, 0.0,
                            0.0, 0.0, 0.0, 1.0,
                            0.0, 0.0, 0.0, 1.0);
    */



    mat4 m_rotation = r_x * r_y * r_z;

    m_rotation[3][0]= translation.x;
    m_rotation[3][1]= translation.y;
    m_rotation[3][2]= translation.z;

	return m_rotation;
}

/* TD2, Exercice 2
 * Parametre : focal : double : focale de la matrice de projection
 * Retour : mat4 : matrice permettant la projection des sommets
 */
mat4x3 projection_matrix(double focal)
{
	mat4x3 m_projection;
	m_projection[0][0] = focal;
	m_projection[2][0] = window.get_width()*window.get_sample() / 2;
	m_projection[1][1] = focal;
	m_projection[2][1] = window.get_height()*window.get_sample() / 2;


	return m_projection;
}

void load_box(Object & o)
{
	////Vertex defintion//////////////////////////
	float dim = 100;

	o.vertices.push_back(vec4(-dim, -dim, -dim, 1));
	o.vertices.push_back(vec4( dim, -dim, -dim, 1));
	o.vertices.push_back(vec4( dim,  dim, -dim, 1));
	o.vertices.push_back(vec4(-dim,  dim, -dim, 1));

	o.vertices.push_back(vec4( dim, -dim, dim, 1));
	o.vertices.push_back(vec4(-dim, -dim, dim, 1));
	o.vertices.push_back(vec4(-dim,  dim, dim, 1));
	o.vertices.push_back(vec4( dim,  dim, dim, 1));

	float n = 0.577350269;
	o.normals.push_back(vec4(-n, -n, -n, 0));
	o.normals.push_back(vec4( n, -n, -n, 0));
	o.normals.push_back(vec4( n,  n, -n, 0));
	o.normals.push_back(vec4(-n,  n, -n, 0));

	o.normals.push_back(vec4( n, -n, n, 0));
	o.normals.push_back(vec4(-n, -n, n, 0));
	o.normals.push_back(vec4(-n,  n, n, 0));
	o.normals.push_back(vec4( n,  n, n, 0));

	Face f;

	/////face 1///////////////////////////////////
	f.vertex_index[0] = 0;
	f.vertex_index[1] = 1;
	f.vertex_index[2] = 2;
	f.vertex_index[3] = 3;
	f.normal = vec4(0, 0, -1, 0);
	f.color = vec3(0,0,1);
	o.faces.push_back(f);

	/////face 2/////////////////////////////////////////
	f.vertex_index[0] = 4;
	f.vertex_index[1] = 5;
	f.vertex_index[2] = 6;
	f.vertex_index[3] = 7;
	f.normal = vec4(0, 0, 1, 0);
	f.color = vec3(0,1,0);
	o.faces.push_back(f);

	////face 3//////////////////////////////////////////
	f.vertex_index[0] = 1;
	f.vertex_index[1] = 2;
	f.vertex_index[2] = 7;
	f.vertex_index[3] = 4;
	f.normal = vec4(1, 0, 0, 0);
	f.color = vec3(0,1,1);
	o.faces.push_back(f);

	////face 4//////////////////////////////////////////
	f.vertex_index[0] = 0;
	f.vertex_index[1] = 3;
	f.vertex_index[2] = 6;
	f.vertex_index[3] = 5;
	f.normal = vec4(-1, 0, 0, 0);
	f.color = vec3(1,0,0);
	o.faces.push_back(f);

	////face 5//////////////////////////////////////////
	f.vertex_index[0] = 5;
	f.vertex_index[1] = 0;
	f.vertex_index[2] = 1;
	f.vertex_index[3] = 4;
	f.normal = vec4(0, -1, 0, 0);
	f.color = vec3(1,0,1);
	o.faces.push_back(f);

	////face 6///////////////////////////////////////////
	f.vertex_index[0] = 2;
	f.vertex_index[1] = 3;
	f.vertex_index[2] = 6;
	f.vertex_index[3] = 7;
	f.normal = vec4(0, 1, 0, 0);
	f.color = vec3(1,1,0);
	o.faces.push_back(f);
}

void load_sphere(Object & o)
{
	int i, j;
	int slice = 40, stack = 20;
	float radius = 100;
	for(i=0; i<=stack; i++)
	{
		float phi = i * M_PI / (float)stack;
		for(j=0; j<slice; j++)
		{
			float theta = j * 2.0f * M_PI / (float)slice;
			float x = cos(theta) * sin(phi);
			float y = sin(theta) * sin(phi);
			float z = cos(phi);
			o.vertices.push_back(vec4(radius * x, radius * y, radius * z, 1));
			o.normals.push_back(vec4(x, y, z, 0));
		}
	}

	for(i=0; i<slice; i++)
	{
		float theta = (i+0.5) * 2.0f * M_PI / (float)slice;
		for(j=0; j<stack; j++)
		{
			float phi = (j+0.5) * M_PI / (float)stack;
			Face f;

			f.vertex_index[0] = i + slice*j;
			f.vertex_index[1] = (i+1)%slice + slice*j;
			f.vertex_index[2] = (i+1)%slice + slice*(j+1);
			f.vertex_index[3] = i + slice*(j+1);

			f.normal.x = cos(theta) * sin(phi);
			f.normal.y = sin(theta) * sin(phi);
			f.normal.z = cos(phi);

			f.color = vec3(1,1,1);

			o.faces.push_back(f);
		}
	}
}
