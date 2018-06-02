/*
 * César Ezequiel Herrera 97429
 * Numero de grupo: 4
 *
 * Make:
 * gcc -o CT04 CT04.c -lm -std=c11 -Wall -pedantic -pedantic-errors -I.
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define TRUE 0
#define FALSE 1

void imprimirEnunciado (char enunciado) {

	switch (enunciado) {
		case 1:
			printf ("\n1) Indicar el número de padrón a utilizar y calcular los datos particulares del grupo.\n\n");
			break;
		case 2:
			printf ("\n2) Expresar la fuerza elástica como función de la coordenada vertical “y”\n");
			printf ("   (tener en cuenta que la cuerda no tiene resistencia a la compresión).\n");
			printf ("   Plantear la ecuación de movimiento correspondiente.\n\n");
			break;
		case 3:
			printf ("\n3) Para el caso particular k2=1, encontrar el punto más bajo de la trayectoria por\n");
			printf ("   consideraciones energéticas o por algún método conocido de otras materias.\n\n");
			break;
		case 4:
			printf ("\n4) Resolver el problema del ítem 3) por el Método de Euler.\n");
			printf ("   Encontrar el paso h necesario para que el error en el punto más bajo sea del 0.1%%.\n");
			printf ("   Comprobar experimentalmente el orden del método.\n\n");
			break;
		case 5:
			printf ("\n5) Resolver el problema del ítem 3) por el Método de Runge Kutta de orden 4.\n");
			printf ("   Encontrar el paso h necesario para que el que error en el punto más bajo sea del 0.1%%.\n");
			printf ("   Comprobar experimentalmente el orden del método.\n\n");
			break;
		case 7:
			printf ("\n7) Dimensionar los parámetros de la cuerda k1 y k2 para que el recorrido en la primera caída supere el 90%%\n");
			printf ("   de H (y no supere el 100%%), y a la vez, la aceleración en el punto más bajo no supere las 2.5g (24.52m/s2).\n");
			printf ("   Aparte, para evitar cualquier brusquedad en el momento que se tensa la cuerda, el valor de k2 deberá ser mayor a 1, indefectiblemente.\n\n");
			break;
		case 8:
			printf ("\n8) Resolver nuevamente el ítem 7 pero incluyendo el efecto de la resistencia del aire\n\n");
			break;
	}

}

/*
 * Manejo de lista
 * https://github.com/fiuba-7541/elemental ?
 */

/*
 * Movimientos que va a manejar la estructura. Son de conocimiento público,
 * pero sólo deberían usarse para el manejo puntual de esta estructura.
 */
typedef enum TMovimiento_Ls {

	L_Primero,
	L_Siguiente,
	L_Anterior

} TMovimiento_Ls;

/*
 * Estructura auxiliar de la lista simple. Es privada y no debe usarse bajo
 * ningún concepto en la aplicación.
 */
typedef struct TNodoListaSimple {

	void * Elem;
	struct TNodoListaSimple * Siguiente, * Anterior;

} TNodoListaSimple;

/*
 * Estructura cabecera, este es el tipo que se deberá instanciar, aunque
 * nunca acceder a sus campos.
 */
typedef struct TListaSimple {

	TNodoListaSimple * Primero, * Corriente;
	int TamanioDato;

} TListaSimple;

/*
 * L_CREAR
 * Pre: Ls no fue creada.
 * Post: Ls creada y vacia
 */
void L_Crear (TListaSimple * pLs, int TamanioDato) {

	pLs->Corriente = NULL;
	pLs->Primero = NULL;
	pLs->TamanioDato = TamanioDato;

}

/*
 * L_VACIAR
 * Pre: Ls creada.
 * Post: Ls vacia.
 */
void L_Vaciar (TListaSimple * pLs) {

	TNodoListaSimple * pNodo, * Siguiente;

	for (pNodo = pLs->Primero; pNodo; pNodo = Siguiente) {
		Siguiente = pNodo->Siguiente;
		free (pNodo->Elem);
		free (pNodo);
	}

	pLs->Primero = pLs->Corriente = NULL;

}

/*
 * L_VACIA
 * Pre: Ls creada.
 * Post: Si Ls tiene elementos devuelve FALSE sino TRUE.
 */
int L_Vacia (TListaSimple Ls) {

	if (Ls.Primero == NULL)
		return TRUE;

	return FALSE;

}

/*
 * L_ELEM_CTE
 * Pre: Ls creada y no vacia.
 * Post: Se devuelve en E el elemento Corriente de la lista.
 */
void L_Elem_Cte (TListaSimple Ls, void * pE) {

	memcpy (pE, Ls.Corriente->Elem, Ls.TamanioDato);

}

/*
 * L_MOVER_CTE
 * Pre: Ls creada
 * Post: Si Ls esta vacia, devuelve FALSE. Sino:
 * Si M = L_Primero, el nuevo elemento Corriente es el Primero. Devuelve TRUE
 * Si M = L_Siguiente, el nuevo elemento Corriente es el Siguiente al
 * Corriente. Si estaba en el ultimo elemento, devuelve FALSE, sino TRUE.
 * Si M = L_Anterior, el nuevo elemento Corriente es el Anterior al
 * Corriente. Si estaba en el primer elemento, devuelve FALSE, sino TRUE.
 */
int L_Mover_Cte (TListaSimple * pLs, TMovimiento_Ls M) {

	if (L_Vacia (* pLs) == TRUE)
		return FALSE;

	switch (M) {
		case L_Primero:
			pLs->Corriente = pLs->Primero;
			break;
		case L_Siguiente:
			if (pLs->Corriente->Siguiente == NULL)
				return FALSE;
			else
				pLs->Corriente = pLs->Corriente->Siguiente;
			break;
		case L_Anterior:
			if (pLs->Corriente->Anterior == NULL)
				return FALSE;
			else
				pLs->Corriente = pLs->Corriente->Anterior;
			break;
	}

	return TRUE;

}

/*
 * L_BORRAR_CTE
 * Pre: Ls creada y no vacia.
 * Post: Se elimino el elemento Corriente, el nuevo elemento es el Siguiente o
 * el Anterior si el Corriente era el ultimo elemento.
 */
void L_Borrar_Cte (TListaSimple * pLs) {

	TNodoListaSimple * pNodo = pLs->Corriente;

	if (pLs->Corriente == pLs->Primero) {
		pLs->Primero = pLs->Primero->Siguiente;
		pLs->Corriente = pLs->Primero;
		if (pLs->Corriente != NULL)
			pLs->Corriente->Anterior = NULL;
	} else {
		if (pLs->Corriente->Siguiente) {
			pNodo = pLs->Corriente->Siguiente;
			memcpy (pLs->Corriente->Elem, pNodo->Elem, pLs->TamanioDato);
			pLs->Corriente->Siguiente = pNodo->Siguiente;
			if (pLs->Corriente->Siguiente != NULL)
				pLs->Corriente->Siguiente->Anterior = pLs->Corriente;
		} else {
			/* Si es el último queda en el Anterior al borrado */
			pLs->Corriente->Anterior->Siguiente = NULL;
			pLs->Corriente = pLs->Corriente->Anterior;
		}
	}

	free (pNodo->Elem);
	free (pNodo);

}

/*
 * L_INSERTAR_CTE
 * Pre: Ls creada.
 * Post: E se agrego a la lista y es el actual elemento Corriente.
 * Si M=L_Primero: se inserto como Primero de la lista.
 * Si M=L_Siguiente: se inserto despues del elemento Corriente.
 * Si M=L_Anterior: se inserto antes del elemento Corriente.
 * Si pudo insertar el elemento devuelve TRUE, sino FALSE.
 */
int L_Insertar_Cte (TListaSimple * pLs, TMovimiento_Ls M, void * pE) {

	TNodoListaSimple * pNodo = malloc (sizeof (TNodoListaSimple));

	if (!pNodo)
		return FALSE; // No hay memoria disponible

	pNodo->Elem = malloc (pLs->TamanioDato);

	if (!pNodo->Elem) {
		free (pNodo);
		return FALSE;
	}

	memcpy (pNodo->Elem, pE, pLs->TamanioDato);

	if ((pLs->Primero == NULL) || (M == L_Primero) || ((M == L_Anterior) && (pLs->Primero == pLs->Corriente))) {
		/*Si está vacía o hay que insertar en el Primero o
		hay que insertar en el Anterior y el actual es el Primero */
		pNodo->Siguiente = pLs->Primero;
		if (pLs->Primero != NULL)
			pLs->Primero->Anterior = pNodo;
		pLs->Primero = pLs->Corriente = pNodo;
	} else {
		// Siempre inserto como siguiente, el nodo nuevo, porque es más fácil
		pNodo->Siguiente = pLs->Corriente->Siguiente;
		pNodo->Anterior = pLs->Corriente;
		if (pLs->Corriente->Siguiente != NULL)
			pLs->Corriente->Siguiente->Anterior = pNodo;
		pLs->Corriente->Siguiente = pNodo;

		if (M == L_Anterior) {
			// Pero cuando el movimiento es Anterior, entonces swapeo los elementos
			void * tmp = pNodo->Elem;
			pNodo->Elem = pLs->Corriente->Elem;
			pLs->Corriente->Elem = tmp;
		}
	}

	pLs->Corriente = pNodo;
	return TRUE;

}

struct TVectorDatos {

	int numeroDePadron;
	int altura;
	float longitudCuerda;
	float masa;
	float k1;
	float k2;
	float c1;
	float c2;

};

struct TVectorDatos cargarVectorDatos () {

	struct TVectorDatos aux;

	aux.numeroDePadron = 97429;
	aux.altura = 150;
	aux.longitudCuerda = aux.altura * (0.25 + 0.1 * ((float) aux.numeroDePadron - 90000) / 10000);
	aux.masa = 50 + 40 * ((float) aux.numeroDePadron - 90000) / 10000;
	aux.k1   = 40 + 10 * ((float) aux.numeroDePadron - 90000) / 10000;
	aux.k2   =  1;
	aux.c1   =  3 +  2 * ((float) aux.numeroDePadron - 90000) / 10000;
	aux.c2   =  1.5;

	printf ("NP = %d\n", aux.numeroDePadron);
	printf (" H = %d\n", aux.altura);
	printf ("L0 = %d*(0.25+0.1*(%d-90000)/10000) = %f\n", aux.altura, aux.numeroDePadron, aux.longitudCuerda);
	printf (" m = 50+40*(%d-90000)/10000 = %f\n", aux.numeroDePadron, aux.masa);
	printf ("k1 = 40+10*(%d-90000)/10000 = %f\n", aux.numeroDePadron, aux.k1);
	printf ("k2 = 1\n");
	printf ("c1 =   3+2*(%d-90000)/10000 = %f\n", aux.numeroDePadron, aux.c1);
	printf ("c2 = 1.5\n");

	return aux;

}

int proceso () {

	struct TVectorDatos datos;

	imprimirEnunciado (1);
	datos = cargarVectorDatos ();

	/*
	imprimirEnunciado (2);
	imprimirEnunciado (3);
	imprimirEnunciado (4);
	imprimirEnunciado (5);
	imprimirEnunciado (7);
	imprimirEnunciado (8);
	*/

	return TRUE;

}

int main () {

	printf ("\nCesar Ezequiel Herrera 97429\n");

	return proceso ();

}
