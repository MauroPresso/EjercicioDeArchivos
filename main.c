
/**
 * @file main.c
 * @brief Programa que lee datos de distintos tipos (int, float, double y struct Complex) desde un archivo binario.
 * 
 * Este programa lee un archivo binario con números de diferentes tipos y los agrupa en vectores. 
 * Además, muestra en consola la cantidad de números de cada tipo y los imprime.
 * 
 * El archivo binario debe contener un prefijo que indica el tipo de los datos:
 * - 'i' para int
 * - 'f' para float
 * - 'd' para double
 * - 'z' para struct Complex
 * 
 * Se utilizan vectores dinámicos para almacenar los números de cada tipo.
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>


/**
 * @struct Complex
 * @brief Estructura para representar números complejos.
 * 
 * Esta estructura almacena las partes real e imaginaria de un número complejo.
 * 
 * @var Complex::re
 * Parte real del número complejo.
 * 
 * @var Complex::im
 * Parte imaginaria del número complejo.
 */

struct Complex
{
    double re;
    double im;
};


/**
 * @brief Función principal que lee un archivo binario y agrupa los datos por tipo.
 * 
 * La función realiza lo siguiente:
 * 1. Abre un archivo binario para leer los datos.
 * 2. Cuenta la cantidad de cada tipo de dato en el archivo.
 * 3. Carga los datos en vectores dinámicos según su tipo.
 * 4. Imprime los datos y las cantidades de cada tipo en consola.
 * 
 * @return 0 si el programa se ejecuta correctamente, 1 en caso de error.
 */

int main()
{
    
	/**
 	* @brief Puntero al archivo binario a leer.
 	* 
 	* Este puntero se utiliza para abrir el archivo `number_mixed.dat` en modo lectura binaria.
 	*/
	
	FILE *pf;
    pf = fopen("C:\\Users\\MAURO\\Documents\\FileExample\\number_mixed.dat","rb");
    if (pf == NULL)
    {
        printf("\nError 404: Not Found\n");
        return 0;
    }
    else
    {
        printf("\nFile opening was OK. Continue with the procedure\n");
    }
    
	/**
 	* @brief Contadores de cantidades por tipo de dato.
 	* 
 	* Estas variables almacenan la cantidad de números de cada tipo en el archivo.
 	*/
    int cant_intigers;
    int cant_float;
    int cant_double;
    int cant_complex;
    
	// Cantidades TOTALES.
	int cant_TOTAL_intigers = 0;
    int cant_TOTAL_float = 0;
    int cant_TOTAL_double = 0;
    int cant_TOTAL_complex = 0;

    /**
 	* @brief Vectores dinámicos para almacenar los datos leídos.
 	* 
 	* Estos vectores almacenan los datos por tipo (int, float, double, Complex).
 	*/
    int *intigers_vector;
    float *float_vector;
    double *double_vector;
    struct Complex *complex_vector;
    
	/**
	* @brief Última posición ocupada en cada vector.
	* 
	* Estas variables se usan para hacer un seguimiento de la última posición ocupada en cada vector, 
 	* asegurando que los datos se almacenen en el orden correcto.
 	*/
	int ult_pos_i;
	int ult_pos_f;
	int ult_pos_d;
	int ult_pos_z;

	/**
	* @brief Variable que indica el tipo de dato que se está leyendo del archivo.
	* 
	* Este carácter se lee desde el archivo y determina si el siguiente bloque de datos es de tipo 'i', 
	* 'f', 'd' o 'z'.
	*/
	char tipo;
	tipo = '\0';

	/**
 	* @brief Lee el archivo y cuenta la cantidad de elementos por tipo de dato.
 	* 
 	* Este bucle lee el archivo binario y, dependiendo del tipo de dato ('i', 'f', 'd', 'z'), 
 	* actualiza los contadores correspondientes y avanza a la siguiente sección del archivo.
 	*/
	while(fread(&tipo, sizeof(char), 1, pf) != 0) // Si yo le pido a la funcion fread() que lea 'tanto', se corre 'tanto'.
	{
		// Acá ya detectó el primer tipo
		if(tipo == 'i')
		{
			fread(&cant_intigers, sizeof(int), 1, pf);
			cant_TOTAL_intigers = cant_TOTAL_intigers + cant_intigers;
			fseek(pf, (sizeof(int)*cant_intigers), SEEK_CUR);
		}
		if(tipo == 'f')
		{
			fread(&cant_float, sizeof(int), 1, pf);
			cant_TOTAL_float = cant_TOTAL_float + cant_float;
			fseek(pf, (sizeof(float)*cant_float), SEEK_CUR);
		}
		if(tipo == 'd')
		{
			fread(&cant_double, sizeof(int), 1, pf);
			cant_TOTAL_double = cant_TOTAL_double + cant_double;
			fseek(pf, (sizeof(double)*cant_double), SEEK_CUR);
		}
		if(tipo == 'z')
		{
			fread(&cant_complex, sizeof(int), 1, pf);
			cant_TOTAL_complex = cant_TOTAL_complex + cant_complex;
			fseek(pf, (sizeof(struct Complex)*cant_complex), SEEK_CUR);
		}
		
    } 
	
	printf("\n");
	// Printing the total of intiger values.
	printf("Hay %u numeros enteros\n" , cant_TOTAL_intigers);	
	
	// Printing the total of float values.
	printf("Hay %u numeros float\n" , cant_TOTAL_float);
	
	// Printing the total of double values.
	printf("Hay %u  numeros double\n" , cant_TOTAL_double);
	

	// Printing the total of complex values.
	printf("Hay %u numeros complejos\n" , cant_TOTAL_complex);
	

	// Inicializo los vectores dinamicos luego de saber la cantidad de valores que tiene cada uno.
	// intigers_vector
	intigers_vector = (int*)malloc(cant_TOTAL_intigers*sizeof(int));
	ult_pos_i = 0;
	
	// float_vector
	float_vector = (float*)malloc(cant_TOTAL_float*sizeof(float));
	ult_pos_f = 0;

	// double_vector
	double_vector = (double*)malloc(cant_TOTAL_double*sizeof(double));
	ult_pos_d = 0;

	// complex_vector
	complex_vector = (struct Complex*)malloc(cant_TOTAL_complex*sizeof(struct Complex));
	ult_pos_z = 0;
	
	rewind(pf); // Me lo pone al principio del archivo.
	
	/**
	* @brief Lee el archivo y carga los datos en los vectores correspondientes.
	* 
	* Este bucle lee el archivo binario nuevamente, pero ahora carga los datos en los vectores dinámicos 
	* correspondientes según el tipo de dato. La variable `tipo` determina el tipo de dato que se está 
	* leyendo y almacenando.
	*/
	while(fread(&tipo, sizeof(char), 1, pf) != 0) // Si yo le pido a la funcion fread() que lea 'tanto', se corre 'tanto'.
	{
		// Aca ya detecto el tipo
		if(tipo == 'i')
		{
			int k;
			fread(&cant_intigers, sizeof(int), 1, pf);
			for(k = ult_pos_i ; k < (ult_pos_i + cant_intigers) ; k++)
			{
				fread(&intigers_vector[k], sizeof(int), 1, pf);
			}
			ult_pos_i = k;	
		}
		if(tipo == 'f')
		{
			int k;
			fread(&cant_float, sizeof(int), 1, pf);
			for(k = ult_pos_f ; k < (ult_pos_f + cant_float) ; k++)
			{
				fread(&float_vector[k], sizeof(float), 1, pf);
			}
			ult_pos_f = k;
		}
		if(tipo == 'd')
		{
			int k;
			fread(&cant_double, sizeof(int), 1, pf);
			for(k = ult_pos_d ; k < (ult_pos_d + cant_double) ; k++)
			{
				fread(&double_vector[k], sizeof(double), 1, pf);
			}
			ult_pos_d = k;
		}
		if(tipo == 'z')
		{
			int k;
			fread(&cant_complex, sizeof(int), 1, pf);
			for(k = ult_pos_z ; k < (ult_pos_z + cant_complex) ; k++)
			{
				fread(&complex_vector[k], sizeof(struct Complex), 1, pf);
			}
			ult_pos_z = k;
		}
		
    } 
	
	printf("\n");
	/**
 	* @brief Imprime los resultados de los vectores.
 	* 
 	* Esta sección del código imprime los contenidos de los vectores dinámicos 
 	* en consola, mostrando los valores de los números enteros, flotantes, doubles y complejos.
 	*/
	printf("\nVector de numeros enteros:\n");
	for(int j = 0 ; j < cant_TOTAL_intigers ; j++)
	{
		printf("int[%d] = %d\n", j, intigers_vector[j]);
	}
	printf("\n");
	
	printf("\nVector de numeros float:\n");
	for(int j = 0 ; j < cant_TOTAL_float ; j++)
	{
		printf("float[%d] = %0.3f\n", j, float_vector[j]);
	}
	printf("\n");
	
	printf("\nVector de numeros double:\n");
	for(int j = 0 ; j < cant_TOTAL_double ; j++)
	{
		printf("double[%d] = %lf\n", j, double_vector[j]);
	}
	printf("\n");
	
	printf("\nVector de numeros complejos:\n");
	for(int j = 0 ; j < cant_TOTAL_complex ; j++)
	{
		printf("Complex[%d] = %lf + (%lf)j\n", j, complex_vector[j].re, complex_vector[j].im);
	}
	printf("\n");
	
	fclose(pf);
    
	/**
 	* @brief Libera la memoria asignada dinámicamente.
 	* 
 	* Esta sección libera la memoria asignada para los vectores dinámicos 
 	* y asegura que no queden punteros residuales.
 	*/
    free(intigers_vector);
    free(float_vector);
    free(double_vector);
    free(complex_vector);
	
	// Asegurar que no quede ningun puntero residual.
    intigers_vector = NULL;
    float_vector = NULL;
    double_vector = NULL;
    complex_vector = NULL;
	
	printf("\nFin del programa :D");
    return 0;
}