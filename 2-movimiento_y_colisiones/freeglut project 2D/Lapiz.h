/**
@author Lin M. Dotor
*/

#ifndef __LAPIZ_H
#define __LAPIZ_H

#include <GL/freeglut.h>

#include "PV2D.h"

const GLdouble PI = 3.141592653589793;

/**
 Clase Lapiz, que almacena un puntero a un punto y una direcci�n.

 Operaciones: 
	- moveTo: Lapiz, PV2D*, Bool -> 
	- turnTo: Lapiz, GLdouble -> 
	- turn: Lapiz, GLdouble -> 
	- forward: Lapiz, GLdouble, Bool -> 

@author Lin M. Dotor
*/
class Lapiz {

private:
	// Posici�n
	PV2D _pos;

	//Direcci�n (en GRADOS) [360� = 2PiRad]
	GLdouble _dir;

public:
	/** Constructores */
	Lapiz() : _pos(PV2D()), _dir(0.0) {}
	Lapiz(PV2D p, GLdouble dir) : _pos(PV2D(p.get_x(), p.get_y())), _dir(dir) {}
	Lapiz(const Lapiz &l) : _pos(PV2D(l._pos)), _dir(l._dir) {}

	/** Destructor */
	~Lapiz() {
	}

	/**	setters y getters */
	void moveTo(PV2D p, bool draw) {
		if (draw)
		{
			glBegin ( GL_LINES ) ;
				glVertex2d( _pos.get_x(), _pos.get_y() );
				glVertex2d( p.get_x(), p.get_y() );
			glEnd () ;
		}

		_pos = PV2D(p);
	}

	void turnTo(GLdouble a) {
		_dir = a;
	}
	
	PV2D get_pos() {
		return _pos;
	}

	GLdouble get_dir() {
		return _dir;
	}
	
	/**
	 Gira la direcci�n hacia la izquierda (sentido contrahorario)
	*/
	void turn(GLdouble a) {
		_dir += a;
	}

	/**
	 Avanza la posici�n del l�piz siguiendo su direcci�n.
	 El par�metro draw indica si se dibuja el segmento.
	*/
	void forward(GLdouble dist, bool draw) {
		PV2D p = PV2D(_pos.get_x() + dist*cos(_dir/180*PI),
						_pos.get_y() + dist*sin(_dir/180*PI));
		moveTo(p, draw);
	}

	/**
	 Cambia la direcci�n del l�piz, que ahora apunta al punto referenciado.
	*/
	void lookAt(PV2D p) {
		GLdouble cateto_op = p.get_y() - _pos.get_y();
		GLdouble cateto_cont = p.get_x() - _pos.get_x();
		_dir = atan2(cateto_op, cateto_cont)*180/PI;
	}

}; //Lapiz

#endif // __LAPIZ_H