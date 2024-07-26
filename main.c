#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

struct Complex
{
    double re;
    double im;
};

int main()
{
    FILE *pf;
    pf = fopen("C:\\Users\\MAURO\\Documents\\EjercicioDeArchivos\\number_mixed.dat","rb");
    if (pf == NULL)
    {
        printf("\nError 404: Not Found\n");
        return 0;
    }
    else
    {
        printf("\nFile opening was OK. Continue with the procedure\n");
    }
    
	// Cantidades.
    int cant_intigers;
    int cant_float;
    int cant_double;
    int cant_complex;
    
	// Cantidades TOTALES.
	int cant_TOTAL_intigers = 0;
    int cant_TOTAL_float = 0;
    int cant_TOTAL_double = 0;
    int cant_TOTAL_complex = 0;

    // Creando vectores dinamicos para juntar los datos.
    int *intigers_vector;
    float *float_vector;
    double *double_vector;
    struct Complex *complex_vector;
    
	char tipo;
	tipo = '\0';
	
	// Creo estas variables para guardar la ultima posicion cargada de cada vector.
	int ult_pos_i;
	int ult_pos_f;
	int ult_pos_d;
	int ult_pos_z;

	// Hago este bucle para saber cuanta cantidad hay de cada tipo de dato.
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
	
	// Hago este bucle para cargar los valores en cada vector.
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
	// Imprimiendo los vectores.
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
    
	// Liberar memoria
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