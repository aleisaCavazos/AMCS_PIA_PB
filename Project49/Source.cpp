#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdio>

using namespace std;

struct Articulo {
    string nombre;
    int cantidad;
    float precioUnitario;
};

struct Ticket {
    string numeroTicket;
    string nombreVendedor;
    string fecha;
    vector<Articulo> listaArticulos;
    float descuento;
    float propina;
    float impuesto;
    float total;
    bool cancelado;
};

vector<Ticket> listaTickets;  // Almacena todos los tickets activos

// Funci�n para encontrar un ticket por n�mero
int encontrarTicketPorNumero(const string& numeroTicket) {
    for (int i = 0; i < listaTickets.size(); ++i) {
        if (listaTickets[i].numeroTicket == numeroTicket) {
            return i;  // Devolver la posici�n del ticket en el vector
        }
    }
    return -1;  // Devolver -1 si no se encuentra el ticket
}

void altaOrden() {
    Ticket nuevoTicket;

    // Ingresar informaci�n para el nuevo ticket
    printf("N�mero de Ticket: ");
    scanf("%s", &nuevoTicket.numeroTicket[0]);

    // Validar si el n�mero de ticket ya existe
    for (const Ticket& ticket : listaTickets) {
        if (ticket.numeroTicket == nuevoTicket.numeroTicket) {
            printf("Error: El n�mero de ticket ya existe.\n");
            return;
        }
    }

    printf("Bienvenido al sistema de ventas de Nieves 'Copo de nieve'\n");
    printf("Nombre del Vendedor: ");
    scanf("%s", &nuevoTicket.nombreVendedor[0]);

    printf("Fecha: ");
    scanf("%s", &nuevoTicket.fecha[0]);

    int numArticulos;
    printf("N�mero de Art�culos: ");
    scanf("%d", &numArticulos);

    // Ingresar informaci�n para cada art�culo
    for (int i = 0; i < numArticulos; ++i) {
        Articulo nuevoArticulo;
        printf("Art�culo %d:\n", i + 1);
        printf("Nombre: ");
        scanf("%s", &nuevoArticulo.nombre[0]);
        printf("Cantidad: ");
        scanf("%d", &nuevoArticulo.cantidad);
        printf("Precio Unitario: ");
        scanf("%f", &nuevoArticulo.precioUnitario);
        nuevoTicket.listaArticulos.push_back(nuevoArticulo);
    }

    printf("Descuento (%%): ");
    scanf("%f", &nuevoTicket.descuento);

    printf("Propina (%%): ");
    scanf("%f", &nuevoTicket.propina);

    printf("Impuesto (%%): ");
    scanf("%f", &nuevoTicket.impuesto);

    // Calcular el total
    nuevoTicket.total = 0;
    for (const Articulo& articulo : nuevoTicket.listaArticulos) {
        nuevoTicket.total += articulo.cantidad * articulo.precioUnitario;
    }
    nuevoTicket.total *= (100 - nuevoTicket.descuento) / nuevoTicket.descuento; // Aplicar descuento
    nuevoTicket.total *= (100 + nuevoTicket.impuesto) / 16;  // Aplicar impuesto
    nuevoTicket.total *= (100 + nuevoTicket.propina) / 10;   // Aplicar propina

    // A�adir el nuevo ticket a la lista
    nuevoTicket.cancelado = false;
    listaTickets.push_back(nuevoTicket);

    printf("Ticket agregado correctamente.\n");
}

void modificarOrden() {
    string numeroTicketModificar;
    printf("Ingrese el n�mero de ticket que desea modificar: ");
    scanf("%s", &numeroTicketModificar[0]);

    int indiceTicket = encontrarTicketPorNumero(numeroTicketModificar);

    if (indiceTicket != -1) {
        // Mostrar la informaci�n actual del ticket
        Ticket& ticketModificar = listaTickets[indiceTicket];

        printf("\nInformaci�n actual del ticket:\n");
        printf("N�mero de Ticket: %s\n", ticketModificar.numeroTicket.c_str());
        printf("Nombre del Vendedor: %s\n", ticketModificar.nombreVendedor.c_str());
        printf("Fecha: %s\n", ticketModificar.fecha.c_str());

        printf("\nArt�culos:\n");
        for (const Articulo& articulo : ticketModificar.listaArticulos) {
            printf("- %s: %d x $%.2f\n", articulo.nombre.c_str(), articulo.cantidad, articulo.precioUnitario);
        }

        printf("Descuento: %.2f%%\n", ticketModificar.descuento);
        printf("Propina: %.2f%%\n", ticketModificar.propina);
        printf("Impuesto: %.2f%%\n", ticketModificar.impuesto);
        printf("Total: $%.2f\n", ticketModificar.total);

        // Permitir la modificaci�n de la informaci�n
        printf("\nModificaci�n de la orden:\n");
        printf("1. Modificar Nombre del Vendedor\n");
        printf("2. Modificar Fecha\n");
        printf("3. Modificar Art�culos\n");
        printf("4. Modificar Descuento\n");
        printf("5. Modificar Propina\n");
        printf("6. Modificar Impuesto\n");
        printf("7. Volver al Men� Principal\n");

        int opcionModificar;
        printf("Seleccione la opci�n: ");
        scanf("%d", &opcionModificar);

        switch (opcionModificar) {
            case 1:
                printf("Ingrese el nuevo nombre del vendedor: ");
                scanf("%s", &ticketModificar.nombreVendedor[0]);
                break;
            case 2:
                printf("Ingrese la nueva fecha: ");
                scanf("%s", &ticketModificar.fecha[0]);
                break;
            case 3:
                printf("Ingrese el n�mero del art�culo que desea modificar: ");
                scanf("%d", &numArticulo);

                if (numArticulo >= 1 && numArticulo <= ticketModificar.listaArticulos.size()) {
                    Articulo& articuloModificar = ticketModificar.listaArticulos[numArticulo - 1];

                    printf("Ingrese el nuevo nombre del art�culo: ");
                    scanf("%s", &articuloModificar.nombre[0]);

                    printf("Ingrese la nueva cantidad: ");
                    scanf("%d", &articuloModificar.cantidad);

                    printf("Ingrese el nuevo precio unitario: ");
                    scanf("%f", &articuloModificar.precioUnitario);

                    printf("Art�culo modificado correctamente.\n");
                } else {
                    printf("N�mero de art�culo no v�lido.\n");
                }
                break;
            case 4:
                printf("Ingrese el nuevo descuento (%%): ");
                scanf("%f", &ticketModificar.descuento);
                break;
            case 5:
                printf("Ingrese la nueva propina (%%): ");
                scanf("%f", &ticketModificar.propina);
                break;
            case 6:
                printf("Ingrese el nuevo impuesto (%%): ");
                scanf("%f", &ticketModificar.impuesto);
                break;
            case 7:
                // Volver al men� principal
                break;
            default:
                printf("Opci�n no v�lida.\n");
        }
    } else {
        printf("No se encontr� un ticket con ese n�mero.\n");
    }
}

void eliminarOrden() {
    string numeroTicketEliminar;
    printf("Ingrese el n�mero de ticket que desea eliminar: ");
    scanf("%s", &numeroTicketEliminar[0]);

    eliminarTicket(numeroTicketEliminar);
}

void cancelarOrden() {
    string numeroTicketCancelar;
    printf("Ingrese el n�mero de ticket que desea cancelar: ");
    scanf("%s", &numeroTicketCancelar[0]);

    int indiceTicket = encontrarTicketPorNumero(numeroTicketCancelar);

    if (indiceTicket != -1) {
        // Cancelar la orden (marcar como cancelado)
        listaTickets[indiceTicket].cancelado = true;
        printf("La orden con n�mero de ticket %s ha sido cancelada.\n", numeroTicketCancelar.c_str());

        // Eliminar completamente el ticket si se cancela
        if (listaTickets[indiceTicket].cancelado) {
            eliminarTicket(numeroTicketCancelar);
        }
    } else {
        printf("No se encontr� un ticket con ese n�mero.\n");
    }
}

void listaOrdenes() {
    printf("LISTA DE ORDENES\n");

    // Mostrar la informaci�n de todos los tickets
    for (const Ticket& ticket : listaTickets) {
        printf("--------------------------------------\n");
        printf("N�mero de Ticket: %s\n", ticket.numeroTicket.c_str());
        printf("Nombre del Vendedor: %s\n", ticket.nombreVendedor.c_str());
        printf("Fecha: %s\n", ticket.fecha.c_str());

        // Mostrar informaci�n de art�culos
        printf("Art�culos:\n");
        for (const Articulo& articulo : ticket.listaArticulos) {
            printf("- %s: %d x $%.2f\n", articulo.nombre.c_str(), articulo.cantidad, articulo.precioUnitario);
        }

        printf("Descuento: %.2f%%\n", ticket.descuento);
        printf("Propina: %.2f%%\n", ticket.descuento);
        printf("Impuesto: %.2f%%\n", ticket.descuento);
        printf("Total: $%.2f\n", ticket.total);

        if (ticket.cancelado) {
            printf("Estado: Cancelado\n");
        } else {
            printf("Estado: Activo\n");
        }
    }

    printf("--------------------------------------\n");
}

void limpiarPantalla() {
    system("cls"); // Limpiar pantalla
}

void guardarArchivo() {
    ofstream archivo;
    archivo.open("NombreRestaurante-Fecha.txt");

    if (archivo.is_open()) {
        // Guardar informaci�n de tickets activos
        for (const Ticket& ticket : listaTickets) {
            if (!ticket.cancelado) {
                archivo << "N�mero de Ticket: " << ticket.numeroTicket << endl;
                archivo << "Nombre del Vendedor: " << ticket.nombreVendedor << endl;
                archivo << "Fecha: " << ticket.fecha << endl;

                // Guardar informaci�n de art�culos
                archivo << "Art�culos:" << endl;
                for (const Articulo& articulo : ticket.listaArticulos) {
                    archivo << "- " << articulo.nombre << ": " << articulo.cantidad << " x $" << fixed << setprecision(2) << articulo.precioUnitario << endl;
                }

                archivo << "Descuento: " << ticket.descuento << "%" << endl;
                archivo << "Propina: " << ticket.propina << "%" << endl;
                archivo << "Impuesto: " << ticket.impuesto << "%" << endl;
                archivo << "Total: $" << fixed << setprecision(2) << ticket.total << endl;

                archivo << "--------------------------------------" << endl;
            }
        }

        archivo.close();
        printf("Archivo guardado correctamente.\n");
    } else {
        printf("Error al abrir el archivo.\n");
    }
}

int main() {
    int opcion;

    do {
        printf("MEN� DE OPCIONES\n");
        printf("1. Alta de Ordenes\n");
        printf("2. Modificar Orden\n");
        printf("3. Eliminar o Cancelar Orden\n");
        printf("4. Lista de Ordenes\n");
        printf("5. Limpiar pantalla\n");
        printf("6. Guardar Archivo\n");
        printf("7. Salir\n");

        printf("Ingrese su opci�n: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                altaOrden();
                break;
            case 2:
                modificarOrden();
                break;
            case 3:
                eliminarOrden();
                break;
            case 4:
                listaOrdenes();
                break;
            case 5:
                limpiarPantalla();
                break;
            case 6:
                guardarArchivo();
                break;
            case 7:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opci�n no v�lida.\n");
        }
    } while (opcion != 7);

    return 0;
}