typedef struct
{
    int id;
    char nombre[50];
    float cantidad;
    char unidad[15];
    float costo;
} Ingredientes;
typedef struct
{
    int id;
    char nombre[100];
    float precio;
    float tiempo;
    float receta[20];
} Productos;
float validarfloat (float a, float b);
float validarcantidad(float a);
void leercadena(char arr[], int n);
void ingresoing (Ingredientes *ing, int *cont);
void receta(Productos *prod, int pos, Ingredientes *ing, int conting);
void ingresoprod(Productos *prod, int *cont, Ingredientes *ing, int conting);
void mostrarproductos(Productos *prod, int cont,  Ingredientes *ing, int conting);
void editreceta(Productos *prod, int pos, Ingredientes *ing, int conting);
void editarprod(Productos *prod, int cont, Ingredientes *ing, int conting);
void eliminar(Productos *prod, int *cont);
void evaluarpedido(Productos *prod, int cont, Ingredientes *ing, int conting);
void actualiv(Ingredientes *ing, int *conting, Productos *prod, int contprod);
void existencias(Ingredientes *ing, int conting);