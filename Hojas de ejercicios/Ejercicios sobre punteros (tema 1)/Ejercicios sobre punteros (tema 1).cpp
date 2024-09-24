// Carmen Gómez Becerra
#include <iostream>

#pragma region EJERCICIO 4
struct Registro {
    std::string nombre;
    double sueldo;
    int edad;
};

void func(Registro* reg, double* irpf, int* edad) { // Hay que reemplazar los & por *. Tienen CASI el mismo efecto
    const double TIPO = 0.18;
    (*reg).edad++;
    *irpf = (*reg).sueldo * TIPO;
    *edad = (*reg).edad;
}

void funcC(const Registro* reg, double* irpf, int* edad) {
    const double TIPO = 0.18;
    //*reg.edad++; // Error de compilación
    *irpf = (*reg).sueldo * TIPO;
    *edad = (*reg).edad;
}
#pragma endregion

#pragma region EJERCICIO 5
void crearNuevoReg(Registro*& preg) {
    preg = new Registro; // el registro *preg toma valor
}
#pragma endregion


int main()
{
    // EJERCICIO 1: ¿Qué muestra el siguiente código?
    /*
    int x = 5, y = 12, z; // variables.
    int* p1, * p2, * p3; // punteros.

    // obtiene el valor, no la dirección.
    p1 = &x;
    p2 = &y;

    // 5 * 12.
    z = *p1 * *p2;
    p3 = &z; // le da a p3 el valor de z.

    // 60 + 1.
    (*p3)++;

    // Copiamos el valor de p3 en p1.
    p1 = p3;

    // Saldrá "61 12 61".
    std::cout << *p1 << " " << *p2 << " " << *p3;
    */

    // EJERCICIO 2: ¿Qué problema hay en el siguiente código?
    /*
    int dato = 5; // variables.
    int *p1, *p2; // punteros. Nota: el asterisco va con el puntero, no con el tipo.

    // p1 apunta al valor de dato.
    p1 = &dato;

    // Copiamos el valor de p1 en p2.
    p2 = p1;

    // La consola mostrará "5".
    std::cout << *p2;
    */

    // EJERCICIO 3: ¿Qué problema hay en el siguiente código?
    /*
    double d = 5.4, e = 1.2, f = 0.9; //variables.
    double* p1, * p2, * p3; // punteros.
    p1 = &d; // p1 = 5.4
    (*p1) = (*p1) + 3; // p1 = 5.4 + 3
    p2 = &e; // p2 = 1.2
    p3 = &f; // hacemos que p3 apunte a un lugar cualquiera (daría igual si fuese a d, e o f.
    (*p3) = (*p1) + (*p2); // No estaba p3 inicializado y daba error.

    // Va a salir "8.4 1.2 9.6".
    std::cout << *p1 << " " << *p2 << " " << *p3;
    */

    // EJERCICIO 4: Dado el siguiente tipo, 
    // la siguiente función (los dos últimos parámetros son de salida y el primero de entrada/salida),
    // y el siguiente bloque de código. 
    // Reescribe la función para que implemente el paso de parámetros con punteros, en lugar de las referencias que
    // usa ahora(modifica el prototipo y la implementación convenientemente).Finalmente reescribe el bloque de
    // código para adaptarlo a la nueva función.
    /*
    Registro r1;
    Registro* pr = new Registro;
    // los registros r1 y *pr toman valor
    double cotiza; int años;
    func(&r1, &cotiza, &años);
    func(pr, &cotiza, &años);

    // NOTA: el asterisco pasa del puntero al tipo y el & al revés.
    // El & te da la dir de mem.
    */

    // EJERCICIO 5. Las funciones, por supuesto, también pueden devolver punteros, tanto por medio de parámetros, 
    // como por medio de la instrucción return.Dada la siguiente función : Completa el siguiente subprograma para que las 
    // variables r1 y pr tomen valor mediante la función crearNuevoReg antes de usarla.
    /*
    Registro r1;
    Registro* pr = nullptr;
    // los registros r1 y *pr toman valor
    r1 = *crearNuevoReg();
    pr = crearNuevoReg();
        double cotiza; int años;
    func(&r1, &cotiza, &años);
    func(pr, &cotiza, &años);
    

    // EJERCICIO 5.1. Reescribe la función crearNuevoReg para que devuelva el puntero por parámetro y adapta el subprograma.
    Registro r1;
    Registro* pr = nullptr;
    // los registros r1 y *pr toman valor
    crearNuevoReg(r1);
    crearNuevoReg(*pr);
    double cotiza; int años;
    func(&r1, &cotiza, &años);
    func(pr, &cotiza, &años);
    */

    // EJERCICIO 6. Como podemos tener punteros que apunten a cualquier tipo de datos, también podemos tener punteros que apunten a punteros.
    // int x = 5;
    // int* p = &x; // Puntero a entero
    // int** pp = &p; // Puntero a puntero a entero
    // Para acceder a x a través de p escribimos* p.Para acceder a x a través de pp escribimos** pp, o* (*pp). Con* pp accedemos a p, 
    // el otro puntero. Indica qué es lo que muestra el siguiente código :
    /*
    int x = 5, y = 8;
    int* px = &x, * py = &y, * p; // px = 5, py = 8, p = nada.
    int** ppx = &px, ** ppy = &py, ** pp; // ppx = 5, ppy = 8, pp = nada.
    p = px; // p = 5.
    px = py; // px = 8.
    py = p; // py = 5.
    pp = ppx; // pp = 5.
    ppx = ppy; // ppx = 8.
    ppy = pp; // ppy = 5.
    std::cout << **ppx << " " << **ppy; // El resultado es "8 5". No sé por qué sale "5 8".
    */

    // EJERCICIO 7. Los siguientes fragmentos de código emplean memoria dinámica, pero su funcionamiento no es evidente.Indica, 
    // para cada fragmento, cuál es el resultado de la ejecución y si el código tiene algún problema o defecto.
    // Indica también en qué zona de la memoria se guarda cada uno de los datos.
    // A:
    /*
    int* p;
    p = new int;
    *p = 100;
    std::cout << *p; // p = 100.
    p = new int;
    *p = 32; // p = basura por no borrar el new de antes.
    std::cout << *p;
    */
    
    // B: 
    /*
    int* p, *q; // p es puntero pero q no.
    p = new int;
    q = new int; // no has reservado espacio en memoria para q.
    
    *p = 42; 
    q = p; // has puesto la asignacion del valor antes de la inicializacion.
    std::cout << *p; // 42
    std:: cout << *q; // 42
    delete p, q; // hay que borrarlos al terminar de usarlos.

    // Me da error si hago delete p; delete q; , pero si hago delete p, q; no. No lo entiendo.
    */

    // C: No se hacerlo, me sale un error y no sé solucionarlo.
    /*
    int n = 12; // n = 12.

    int* p, *q; // p era puntero pero q no.
    p = new int;
    q = new int;

    int** pp, **qq; // pp era puntero de puntero pero qq no.

    // ¿declaracion de puntero de puntero?
    pp = new int*;
    *pp = new int;

    qq = new int*;
    *qq = new int;
    
    // Esta parte estaba desordenada.
    **pp = 42;
    qq = pp;
    q = *qq;
    p = q;
    p = &n;

    std::cout << **qq;
    delete p, pp, q, qq;
    */

    // EJERCICIO 8. Escribe las instrucciones necesarias para borrar la memoria dinámica creada por cada uno de los siguientes bloques de código.
    // Si alguna de las instrucciones debe ir intercalada en el código indícalo expresamente.
    // A:
    int* p1; int* p2;
    int n = 5;
    p1 = &n;
    p2 = p1
    

    
    


}
