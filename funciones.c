#include <stdio.h>
#include <string.h>
#include "funciones.h"
float validarfloat (float a, float b){
    float num;
    int val=0;
    do{
        val=scanf("%f", &num);
        while((getchar())!='\n');
        if (val!=1 || num<a || num>b ){
            printf("Ingreso invalido. Intente nuevamente: ");
        }
    }while(  val!=1 || num<a || num>b);
    return num;
}
float validarcantidad(float a){
    float num;
    int val=0;
     do{
        val=scanf("%f", &num);
        while((getchar())!='\n');
        if ( val!=1 || num<=a ){
            printf("Ingreso invalido. Intente nuevamente: ");
        }
    }while(val!=1 || num<=a);
    return num;
}
void leercadena(char arr[], int n){
    fgets(arr, n, stdin);
    arr[strcspn(arr, "\n")]='\0';
}
void ingresoing(Ingredientes *ing, int *cont){
    int op;
    do
    {
        if (*cont >= 20)
        {
            printf("Limite de ingredientes alcanzado.\n");
            return;
        }
        printf("---Registro de Ingredientes/Inventario---\n");
        printf("Ingrediente %d\n", *cont + 1);
        ing[*cont].id = *cont + 1;
        printf("Nombre: ");
        leercadena(ing[*cont].nombre, 50);
        printf("Cantidad: ");
        ing[*cont].cantidad = validarcantidad(0);
        printf("Unidad (Unidades, Kg, Litros): ");
        leercadena(ing[*cont].unidad, 15);
        printf("Costo: $");
        ing[*cont].costo = validarcantidad(0);
        (*cont)++;

        printf("Desea ingresar otro ingrediente? 1.Si / 2.No\n");
        printf(">> ");
        op = validarfloat(1, 2);
    } while (op == 1);
}
void mostrarinventario(Ingredientes *ing, int cont){
    if (cont == 0)
    {
        printf("No hay ingredientes registrados.\n");
        return;
    }
    printf("Inventario de Ingredientes: \n");
    printf("%-10s %-50s %-15s %-15s %-15s\n", "ID", "Nombre", "Cantidad", "Unidad", "Costo");
    for (int i = 0; i < cont; i++)
    {
         printf("%-10d %-50s %-15.2f %-15s %-15.2f\n", ing[i].id, ing[i].nombre, ing[i].cantidad, ing[i].unidad, ing[i].costo);
    }
}
void receta(Productos *prod, int pos, Ingredientes *ing, int conting){
    for (int i = 0; i < 20; i++)
    {
        prod[pos].receta[i] = 0;
    }
    printf("Ingredientes disponibles: \n");
    printf("%-10s %-50s %-15s\n", "ID", "Nombre", "Cantidad");
    for (int i = 0; i < conting; i++)
    {
        printf("%-10d %-50s %-15.2f\n", ing[i].id, ing[i].nombre, ing[i].cantidad);
    }
    printf("Cantidad de ingredientes: ");
    int num = validarfloat(0, conting);
    for (int i = 0; i < num; i++)
    {
        printf("Ingrediente %d\n", i + 1);
        printf("Seleccione el ID: ");
        int id = validarfloat(1, conting);
        printf("Cantidad necesaria por hamburguesa: ");
        float cantidad = validarcantidad(0);
        prod[pos].receta[id - 1] = cantidad;
    }
}
void ingresoprod(Productos *prod, int *cont, Ingredientes *ing, int conting){
    int op;
    if (conting == 0)
    {
        printf("Primero debe registrar ingredientes.\n");
        return;
    }
    do{
        if (*cont >= 20)
        {
            printf("Limite de productos alcanzado.\n");
            return;
        }
        printf("---Registro de Productos---\n");
        printf("ID: %d\n", *cont + 1);
        prod[*cont].id = *cont + 1;
        printf("Nombre: ");
        leercadena(prod[*cont].nombre, 100);
        receta(prod, *cont, ing, conting);
        printf("Precio: $");
        prod[*cont].precio = validarcantidad(0);
        printf("Tiempo de preparacion (min): ");
        prod[*cont].tiempo = validarcantidad(0);
        (*cont)++;
        printf("Desea registrar otro producto? 1.Si / 2.No\n");
        printf(">> ");
        op = validarfloat(1, 2);
    } while (op == 1);
}
void mostrarproductos(Productos *prod, int cont,  Ingredientes *ing, int conting){
    if (cont == 0)
    {
        printf("No hay productos registrados.\n");
        return;
    }
    printf("---Menu Disponible---\n");
    printf("%-10s %-50s %-15s %-20s\n", "ID", "Nombre", "Precio", "Tiempo (Min)");
    for (int i = 0; i < cont; i++)
    {
         printf("%-10d %-50s %-15.2f %-20.2f\n", prod[i].id, prod[i].nombre, prod[i].precio, prod[i].tiempo);
         printf("Ingredientes: \n");
         for (int n = 0; n < conting; n++)
         {
            if (prod[i].receta[n]>0){
                 printf("- %s: %.2f %s\n", ing[n].nombre, prod[i].receta[n], ing[n].unidad);
            }
         }
    }
}
void editreceta(Productos *prod, int pos, Ingredientes *ing, int conting)
{
    int op, id, posing;
    do {
        printf("\n--- EDITAR RECETA ---\n");
        printf("Producto: %s\n", prod[pos].nombre);

        printf("\nIngredientes actuales:\n");
        for (int i = 0; i < conting; i++)
        {
            if (prod[pos].receta[i] > 0)
            {
                printf("ID: %d | %s | %.2f %s\n",
                       ing[i].id,
                       ing[i].nombre,
                       prod[pos].receta[i],
                       ing[i].unidad);
            }
        }
        printf("\n1. Agregar ingrediente\n");
        printf("2. Modificar cantidad\n");
        printf("3. Quitar ingrediente\n");
        printf("4. Cancelar\n");
        printf(">> ");
        op = validarfloat(1, 4);
        if (op == 4)
            break;
        mostrarinventario(ing, conting);
        printf("Ingrese el ID del ingrediente: ");
        id = validarfloat(1, 20);
        posing = -1;
        for (int i = 0; i < conting; i++)
        {
            if (id == ing[i].id)
            {
                posing = i;
                break;
            }
        }
        if (posing == -1)
        {
            printf("Ingrediente no encontrado.\n");
            return;
        }
        switch (op)
        {
            case 1:
                if (prod[pos].receta[posing] > 0)
                {
                    printf("El ingrediente ya pertenece a la receta.\n");
                    break;
                }
                printf("Cantidad necesaria por hamburguesa: ");
                prod[pos].receta[posing] = validarcantidad(0);

                printf("Ingrediente agregado correctamente.\n");
                break;
            case 2:
                if (prod[pos].receta[posing] == 0)
                {
                    printf("Este ingrediente no pertenece a la receta.\n");
                    break;
                }
                printf("Nueva cantidad por hamburguesa: ");
                prod[pos].receta[posing] = validarcantidad(0);

                printf("Cantidad modificada correctamente.\n");
                break;
            case 3:
                if (prod[pos].receta[posing] == 0)
                {
                    printf("Este ingrediente no pertenece a la receta.\n");
                    break;
                }

                prod[pos].receta[posing] = 0;

                printf("Ingrediente quitado de la receta.\n");
                break;
        }
    } while (op != 4);
}
void editarprod(Productos *prod, int cont, Ingredientes *ing, int conting)
{
    if (cont == 0)
    {
        printf("No hay productos registrados para editar.\n");
        return;
    }
    int id, pos = -1;
    printf("Ingrese el ID del producto (1-%d): ", cont);
    id = validarfloat(1, cont);
    for (int i = 0; i < cont; i++)
    {
        if (id == prod[i].id)
        {
            pos = i;
            break;
        }
    }
    if (pos == -1)
    {
        printf("Producto no encontrado o no existente\n");
        return;
    }
    printf("Producto seleccionado: %s\n", prod[pos].nombre);
    printf("Que desea editar?\n");
    printf("1. Nombre\n");
    printf("2. Precio\n");
    printf("3. Tiempo de preparacion\n");
    printf("4. Receta (Ingredientes)\n");
    printf("5. Todo\n");
    printf("6. Cancelar\n");
    printf(">> ");
    int op = validarfloat(1, 6);
    switch (op)
    {
    case 1:
        printf("---Editar nombre---\n");
        printf("Nuevo nombre: ");
        leercadena(prod[pos].nombre, 100);
        printf("Cambio de nombre exitoso!\n");
        break;
    case 2:
        printf("---Editar precio---\n");
        printf("Nuevo precio: ");
        prod[pos].precio = validarcantidad(0);
        printf("Cambio de precio exitoso!\n");
        break;
    case 3:
        printf("---Editar tiempo de preparacion---\n");
        printf("Nuevo tiempo: ");
        prod[pos].tiempo = validarcantidad(0);
        printf("Cambio de tiempo exitoso!\n");
        break;
    case 4:
        editreceta(prod, pos, ing, conting);
        break;
    case 5:
        printf("---Editar todo---\n");
        printf("Nuevo nombre: ");
        leercadena(prod[pos].nombre, 100);
        printf("Nuevo precio: ");
        prod[pos].precio = validarcantidad(0);
        printf("Nuevo tiempo: ");
        prod[pos].tiempo = validarcantidad(0);
        editreceta(prod, pos, ing, conting);
        break;
    case 6:
        return;
    default:
        break;
    }
}
void eliminar(Productos *prod, int *cont)
{
    if (*cont == 0)
    {
        printf("No hay productos registrados para eliminar.\n");
        return;
    }
    int id, pos = -1;
    printf("Ingrese el ID del producto a eliminar (1-%d): ", *cont);
    id = validarfloat(1, *cont);
    for (int i = 0; i < *cont; i++)
    {
        if (prod[i].id == id)
        {
            pos = i;
            break;
        }
    }
    if (pos == -1)
    {
        printf("Producto no encontrado.\n");
        return;
    }
    printf("Esta seguro de eliminar este producto? 1.Si / 2.No\n");
    int opc = validarfloat(1, 2);
    if (opc == 1)
    {
        for (int i = pos; i < *cont - 1; i++)
        {
            prod[i] = prod[i + 1];
        }
        (*cont)--;
        printf("Producto eliminado correctamente\n");
        for (int i = 0; i < *cont; i++)
        {
            prod[i].id = i + 1;
        }
    }
}
void evaluarpedido(Productos *prod, int cont, Ingredientes *ing, int conting){
    if (cont == 0 || conting == 0)
    {
        printf("No hay productos o ingredientes registrados.\n");
        return;
    }
    float necesarios[20] = {0};
    float tiempotot = 0, pretot= 0;
    float tiempodis;
    int cantidad, id, pos, op, viable = 1;
    do
    {
        printf("\n---Evaluar viabilidad del pedido---\n");
        printf("%-10s %-30s %-10s\n", "ID", "Producto", "Precio");
        for (int i = 0; i < cont; i++)
        {
            printf("%-10d %-30s $%-10.2f\n",
                   prod[i].id, prod[i].nombre, prod[i].precio);
        }
        printf("\nIngrese el ID del producto: ");
        id = validarfloat(1, cont);
        pos = -1;
        for (int i = 0; i < cont; i++)
        {
            if (prod[i].id == id)
            {
                pos = i;
                break;
            }
        }
        if (pos == -1)
        {
            printf("Producto no encontrado.\n");
            return;
        }
        printf("Cantidad de hamburguesas: ");
        cantidad = validarcantidad(0);
        for (int i = 0; i < conting; i++)
        {
            necesarios[i] += prod[pos].receta[i] * cantidad;
        }
        tiempotot+= prod[pos].tiempo * cantidad;
        pretot+= prod[pos].precio * cantidad;
        printf("Desea agregar otro tipo de hamburguesa? 1.Si / 2.No\n");
        op = validarfloat(1, 2);
    } while (op == 1);
    printf("\nTiempo disponible (minutos): ");
    tiempodis=validarcantidad(0);
    printf("\n--- RESUMEN DEL PEDIDO ---\n");
    printf("Precio total: $%.2f\n", pretot);
    printf("Tiempo estimado: %.2f minutos\n", tiempotot);
    printf("\n--- EVALUACION DE INGREDIENTES ---\n");
    for (int i = 0; i < conting; i++)
    {
        if (necesarios[i] > 0)
        {
            printf("%s: Necesario %.2f %s / Disponible %.2f %s\n",
                   ing[i].nombre,
                   necesarios[i], ing[i].unidad,
                   ing[i].cantidad, ing[i].unidad);

            if (necesarios[i] > ing[i].cantidad)
            {
                printf("Ingrediente insuficiente.\n");
                viable = 0;
            }
        }
    }
    if (tiempotot>tiempodis)
    {
        printf("\nTiempo insuficiente para preparar el pedido.\n");
        viable = 0;
    }
    if (viable)
    {
        printf("\nPEDIDO VIABLE: Ingredientes y tiempo suficientes.\n");
    }
    else
    {
        printf("\nPEDIDO NO VIABLE: Recursos o tiempo insuficientes.\n");
    }
}
void actualiv(Ingredientes *ing, int *conting, Productos *prod, int contprod){
    int pos=-1, id;
    float cant;
    if (*conting==0){
        printf("Inventario vacio.\n");
        return;
    }
    printf("---Actualizar inventario---\n");
    printf("1. Reabastecer ingrediente\n");
    printf("2. Registrar consumo o perdida\n");
    printf("3. Agregar nuevo ingrediente\n");
    printf("4. Salir\n");
    printf(">> ");
    int opc=validarfloat(1,4);
    switch (opc)
    {
    case 1:
        mostrarinventario(ing, *conting);
        printf("---Reabastecer ingrediente---\n");
        printf("Ingrese el ID del ingrediete: ");
        id =validarcantidad(0);
        for (int i = 0; i < *conting; i++)
        {
            if(ing[i].id==id){
                pos=i;
                break;
            }
        }
        if(pos==-1){
        printf("Ingrediente no encontrado o no existente\n");
        break;
        }
        printf("Cantidad a reabastecer: ");
        cant=validarcantidad(0);
        ing[pos].cantidad+=cant;
        printf("Reabastecimiento exitoso\n");
        break;
    case 2:
        mostrarinventario(ing, *conting);
        printf("---Registrar consumo o perdida---\n");
        printf("Ingrese el ID del ingrediete: ");
        id = validarcantidad(0);
        for (int i = 0; i < *conting; i++)
        {
            if (ing[i].id == id)
            {
                pos = i;
                break;
            }
        }
        if (pos == -1)
        {
            printf("Ingrediente no encontrado o no existente\n");
            break;
        }
        printf("Cantidad descontar: ");
        cant=validarcantidad(0);
        if (cant > ing[pos].cantidad)
        {
            printf("Stock insuficiente.\n");
            break;
        }
        ing[pos].cantidad-=cant;
        printf("Stock restante de %s: %.2f %s\n",
               ing[pos].nombre,
               ing[pos].cantidad,
               ing[pos].unidad);
        break;
    case 3:
        int anterior = *conting;
        ingresoing(ing, conting);
        if (*conting > anterior){
            for (int i = 0; i < contprod; i++){
                for (int j = anterior; j < *conting; j++){
                    prod[i].receta[j] = 0;
                }
            }
        }
        break;
    }
}
void existencias(Ingredientes *ing, int conting){
    int id, pos=-1;
    if(conting==0){
        printf("Inventario vacio.\n");
        return;
    }
    printf("---Consultar existencias del inventario---\n");
    printf("1. Mostrar todo el inventario\n");
    printf("2. Consultar por ID del ingrediente\n");
    printf("3. Salir\n");
    printf(">> ");
    int op=validarfloat(1,3);
    switch (op)
    {
    case 1:
        mostrarinventario(ing, conting);
        break;
    case 2:
    printf("Ingrese el ID del ingrediente (1-%d): ", conting);
    id=validarfloat(1, conting);
    for (int i = 0; i < conting; i++)
    {
        if(ing[i].id==id){
            pos=i;
            break;
        }
    }
    if(pos==-1){
        printf("Ingrediente no encontrado o inexistente\n");
        return;
    }
    printf("Ingrediente: %s\n", ing[pos].nombre);
    printf("Cantidad disponible: %.2f %s", ing[pos].cantidad, ing[pos].unidad);
    break;
    case 3:
    return;
    default:
        break;
    }
}