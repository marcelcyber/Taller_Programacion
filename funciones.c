#include <stdio.h>
#include "funciones.h"
#include <string.h>

void buscarPorTamano(int *numHabitacion,char habitaciones[][3][40],double precios[]){
    char tipo[40];
    printf("Ingrese el tamano de habitacion que desea buscar: ");
    scanf("%s",tipo);
    printf("#\t\tTamano\t\tHotel\t\tPrecio\n");
    for (int i = 0; i < 9; i++)
    {
        if (strcmp(habitaciones[i][1],tipo)==0)
        {
            printf("%s\t\t%s\t\t%s\t\t%lf\n",habitaciones[i][0],habitaciones[i][1],habitaciones[i][2],precios[i]);
        }
    }
    printf("Elija la habitacion que desea reservar: ");
    scanf("%d",numHabitacion); 
}

void buscarHotel(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    char hotel[40];
    printf("Ingrese el nombre del hotel:\n>>");
    scanf("%s", hotel);

    printf("#\t\tTamano\t\tHotel\t\tPrecio\n");
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][2], hotel) == 0) {
            printf("%s\t\t%s\t\t%s\t\t%.2lf\n", habitaciones[i][0], habitaciones[i][1], habitaciones[i][2], precios[i]);
        }
    }
    printf("Elija la habitacion que desea reservar: ");
    scanf("%d", numHabitacion);
}

void realizarReserva(int numHabitacion, char habitaciones[][3][40], char clientes[][2][40], int reservas[][4]) {
    char cedula[40];
    printf("Ingrese su cedula:\n>>");
    scanf("%s", cedula);

    // Buscar cliente
    int clienteIndex = -1;
    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], cedula) == 0) {
            clienteIndex = i;
            break;
        }
    }

    // Si no se encuentra, se agrega
    if (clienteIndex == -1) {
        for (int i = 0; i < 5; i++) {
            if (strcmp(clientes[i][1], "") == 0) {
                clienteIndex = i;
                printf("Ingrese su nombre:\n>>");
                scanf("%s", clientes[i][0]);
                strcpy(clientes[i][1], cedula);
                break;
            }
        }
    }

    // Realizar reserva
    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] == -1) {
            reservas[i][0] = clienteIndex;
            reservas[i][1] = numHabitacion - 1;
            reservas[i][2] = 0;  // No pagada
            reservas[i][3] = 1;  // Reservada
            printf("Reserva realizada exitosamente!\n");
            return;
        }
    }
    printf("No hay espacio para mas reservas.\n");
}

void buscarReservaPorCedula(int *numReserva, char clientes[][2][40], int reservas[][4]) {
    char cedula[40];
    printf("Ingrese su cedula:\n>>");
    scanf("%s", cedula);

    // Buscar cliente
    int clienteIndex = -1;
    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], cedula) == 0) {
            clienteIndex = i;
            break;
        }
    }

    // Buscar reserva
    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] == clienteIndex && reservas[i][3] == 1) {
            *numReserva = i;
            return;
        }
    }
    *numReserva = -1;
}

void imprimirReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double precios[]) {
    if (numReserva == -1) {
        printf("No se encontro ninguna reserva.\n");
        return;
    }

    int habitacionIndex = reservas[numReserva][1];
    printf("Reserva #%d\n", numReserva + 1);
    printf("Habitacion: %s\n", habitaciones[habitacionIndex][0]);
    printf("Tipo: %s\n", habitaciones[habitacionIndex][1]);
    printf("Hotel: %s\n", habitaciones[habitacionIndex][2]);
    printf("Precio: $%.2f\n", precios[habitacionIndex]);
}

void pagarReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double precios[]) {
    if (numReserva == -1) {
        printf("No se encontro ninguna reserva.\n");
        return;
    }

    int habitacionIndex = reservas[numReserva][1];
    printf("El total a pagar es: $%.2f\n", precios[habitacionIndex]);
    printf("Ingrese el monto a pagar:\n>>");
    double monto;
    scanf("%lf", &monto);

    if (monto >= precios[habitacionIndex]) {
        printf("Pago realizado exitosamente!\n");
        reservas[numReserva][2] = 1; // Indica que está pagada
        reservas[numReserva][3] = 0; // Libera la reserva
    } else {
        printf("Monto insuficiente. Pago no realizado.\n");
    }
}
