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

// Función para encontrar un ticket por número
int encontrarTicketPorNumero(const string& numeroTicket) {
    for (int i = 0; i < listaTickets.size(); ++i) {
        if (listaTickets[i].numeroTicket == numeroTicket) {
            return i;  // Devolver la posición del ticket en el vector
        }
    }
    return -1;  // Devolver -1 si no se encuentra el ticket
}

void altaOrden() {
    Ticket nuevoTicket;

    // Ingresar información para el nuevo ticket
    printf("Número de Ticket: ");
    scanf("%s", &nuevoTicket.numeroTicket[0]);

    // Validar si el número de ticket ya existe
    for (const Ticket& ticket : listaTickets) {
        if (ticket.numeroTicket == nuevoTicket.numeroTicket) {
            printf("Error: El número de ticket ya existe.\n");
            return;
        }
    }

    printf("Bienvenido al sistema de ventas de Nieves 'Copo de nieve'\n");
    printf("Nombre del Vendedor: ");
    scanf("%s", &nuevoTicket.nombreVendedor[0]);

    printf("Fecha: ");
    scanf("%s", &nuevoTicket.fecha[0]);

    int numArticulos;
    printf("Número de Artículos: ");
    scanf("%d", &numArticulos);

    // Ingresar información para cada artículo
    for (int i = 0; i < numArticulos; ++i) {
        Articulo nuevoArticulo;
        printf("Artículo %d:\n", i + 1);
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

    // Añadir el nuevo ticket a la lista
    nuevoTicket.cancelado = false;
    listaTickets.push_back(nuevoTicket);

    printf("Ticket agregado correctamente.\n");
}

void modificarOrden() {
    string numeroTicketModificar;
    printf("Ingrese el número de ticket que desea modificar: ");
    scanf("%s", &numeroTicketModificar[0]);

    int indiceTicket = encontrarTicketPorNumero(numeroTicketModificar);

    if (indiceTicket != -1) {
        // Mostrar la información actual del ticket
        Ticket& ticketModificar = listaTickets[indiceTicket];

        printf("\nInformación actual del ticket:\n");
        printf("Número de Ticket: %s\n", ticketModificar.numeroTicket.c_str());
        printf("Nombre del Vendedor: %s\n", ticketModificar.nombreVendedor.c_str());
        printf("Fecha: %s\n", ticketModificar.fecha.c_str());

        printf("\nArtículos:\n");
        for (const Articulo& articulo : ticketModificar.listaArticulos) {
            printf("- %s: %d x $%.2f\n", articulo.nombre.c_str(), articulo.cantidad, articulo.precioUnitario);
        }

        printf("Descuento: %.2f%%\n", ticketModificar.descuento);
        printf("Propina: %.2f%%\n", ticketModificar.propina);
        printf("Impuesto: %.2f%%\n", ticketModificar.impuesto);
        printf("Total: $%.2f\n", ticketModificar.total);

        // Permitir la modificación de la información
        printf("\nModificación de la orden:\n");
        printf("1. Modificar Nombre del Vendedor\n");
        printf("2. Modificar Fecha\n");
        printf("3. Modificar Artículos\n");
        printf("4. Modificar Descuento\n");
        printf("5. Modificar Propina\n");
        printf("6. Modificar Impuesto\n");
        printf("7. Volver al Menú Principal\n");

        int opcionModificar;
        printf("Seleccione la opción: ");
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
                printf("Ingrese el número del artículo que desea modificar: ");
                scanf("%d", &numArticulo);

                if (numArticulo >= 1 && numArticulo <= ticketModificar.listaArticulos.size()) {
                    Articulo& articuloModificar = ticketModificar.listaArticulos[numArticulo - 1];

                    printf("Ingrese el nuevo nombre del artículo: ");
                    scanf("%s", &articuloModificar.nombre[0]);

                    printf("Ingrese la nueva cantidad: ");
                    scanf("%d", &articuloModificar.cantidad);

                    printf("Ingrese el nuevo precio unitario: ");
                    scanf("%f", &articuloModificar.precioUnitario);

                    printf("Artículo modificado correctamente.\n");
                } else {
                    printf("Número de artículo no válido.\n");
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
                // Volver al menú principal
                break;
            default:
                printf("Opción no válida.\n");
        }
    } else {
        printf("No se encontró un ticket con ese número.\n");
    }
}

void eliminarOrden() {
    string numeroTicketEliminar;
    printf("Ingrese el número de ticket que desea eliminar: ");
    scanf("%s", &numeroTicketEliminar[0]);

    eliminarTicket(numeroTicketEliminar);
}

void cancelarOrden() {
    string numeroTicketCancelar;
    printf("Ingrese el número de ticket que desea cancelar: ");
    scanf("%s", &numeroTicketCancelar[0]);

    int indiceTicket = encontrarTicketPorNumero(numeroTicketCancelar);

    if (indiceTicket != -1) {
        // Cancelar la orden (marcar como cancelado)
        listaTickets[indiceTicket].cancelado = true;
        printf("La orden con número de ticket %s ha sido cancelada.\n", numeroTicketCancelar.c_str());

        // Eliminar completamente el ticket si se cancela
        if (listaTickets[indiceTicket].cancelado) {
            eliminarTicket(numeroTicketCancelar);
        }
    } else {
        printf("No se encontró un ticket con ese número.\n");
    }
}

void listaOrdenes() {
    printf("LISTA DE ORDENES\n");

    // Mostrar la información de todos los tickets
    for (const Ticket& ticket : listaTickets) {
        printf("--------------------------------------\n");
        printf("Número de Ticket: %s\n", ticket.numeroTicket.c_str());
        printf("Nombre del Vendedor: %s\n", ticket.nombreVendedor.c_str());
        printf("Fecha: %s\n", ticket.fecha.c_str());

        // Mostrar información de artículos
        printf("Artículos:\n");
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
        // Guardar información de tickets activos
        for (const Ticket& ticket : listaTickets) {
            if (!ticket.cancelado) {
                archivo << "Número de Ticket: " << ticket.numeroTicket << endl;
                archivo << "Nombre del Vendedor: " << ticket.nombreVendedor << endl;
                archivo << "Fecha: " << ticket.fecha << endl;

                // Guardar información de artículos
                archivo << "Artículos:" << endl;
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
        printf("MENÚ DE OPCIONES\n");
        printf("1. Alta de Ordenes\n");
        printf("2. Modificar Orden\n");
        printf("3. Eliminar o Cancelar Orden\n");
        printf("4. Lista de Ordenes\n");
        printf("5. Limpiar pantalla\n");
        printf("6. Guardar Archivo\n");
        printf("7. Salir\n");

        printf("Ingrese su opción: ");
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
                printf("Opción no válida.\n");
        }
    } while (opcion != 7);

    return 0;
}