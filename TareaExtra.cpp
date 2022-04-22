/*
 *Ejercicio Extra
 *Daniel Hernandez Toledo
 *Daniel Alejandro Osornio Lopez
*/

#include <iostream>
#include <limits>
#include <vector>
#include <fstream>

using namespace std;

struct Producto {
public:
    string productName;
    double price{};
    int cantidad{};

    void printProducts() const;

    bool hayEnExistencia() const;

    void saveProductsToFile(ofstream &f) const;
};

void guardarTodo(vector<Producto> &arreglo);

void imprimirTodos(vector<Producto> &arreglo);

void agregarDatos(vector<Producto> &arreglo);

void menu();

int main() {
    fstream f;
    vector<Producto> productos;
    int option = 0, lazy;
    do {
        guardarTodo(productos);
        menu();
        cout << "Ingrese la option: ";
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        imprimirTodos(productos);
        switch (option) {
            case 1: {
                int num;
                cout << "Ingrese la cantidad de Producto a agregar: ";
                cin >> num;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                for (int i = 0; i < num; i++)
                    agregarDatos(productos);
                break;

            }
            case 2: {
                string buscar;
                cout << "Ingrese un Producto a buscar: ";
                cin >> buscar;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                for (auto &producto: productos) {
                    if (buscar == producto.productName) {
                        cout << "El Producto ah sido encontrado exitosamente: " << producto.productName << endl;
                        producto.printProducts();

                    } else {
                        cout << "Libro no encontrado" << endl;
                    }

                }
            }

                break;

            case 3: {

                do {

                    cout << "Ingresa el index (0-" << productos.size()-1 << ") del producto a devolver: ";
                    cin >> lazy;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                } while (lazy < 0 || lazy > productos.size() - 1);
                productos[lazy].stock = true;
                break;
            }
            case 4: {
                do {
                    cout << "Ingresa el index (0-" << productos.size()-1 << ") del producto a devolver: ";
                    cin >> lazy;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                } while (lazy < 0 || lazy > productos.size() - 1);

                productos[lazy].stock = true;

                break;
            }

            default:
                break;
        }

    } while (option != 5);

}

void menu() {
    cout << "MENU DEL SUPER" << endl;
    cout << "1. Agregar producto " << endl;
    cout << "2. Eliminar Producto " << endl;
    cout << "3. Modificar" << endl;
    cout << "4. Consulta" << endl;
    cout << "5. Comprar" << endl;
    cout << "6. Devolución" << endl;
}

void guardarTodo(vector<Producto> &arreglo) {
    ofstream f;
    f.open("products.txt");

    if (!f) {
        cout << "Algo salio mal al guardar los datos" << endl;
    }

    f << "Index | Producto | Precio" << endl;

    for (int i = 0; i < arreglo.size(); i++) {
        f << i << "|";
        arreglo[i].saveProductsToFile(f);
    }

}


void imprimirTodos(vector<Producto> &arreglo) {
    if (arreglo.empty()) {
        cout << "No hay elementos en la lista" << endl;
        return;
    }

    printf("%5s | %-25s | %-9s\n", "Index", "Producto", "Precio");

    for (int i = 0; i < arreglo.size(); i++) {
        printf("%5d | ", i);
        arreglo[i].printProducts();
    }
}

void agregarDatos(vector<Producto> &arreglo) {
    Producto valor;
    string NameProduct;
    double prices;
    bool disponibilidad;

    cout << "Ingrese NameProduct: ";
    getline(cin, NameProduct);

    cout << "Ingrese price: ";
    cin >> prices;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    disponibilidad = true;

    valor = {
            NameProduct,
            prices,
            disponibilidad
    };

    arreglo.push_back(valor);
}


void Producto::printProducts() const {
    printf("%-25s | %-7.2lf\n", productName.c_str(), price);
}

void Producto::saveProductsToFile(ofstream &f) const {
    f << productName << "|";
    f << price << endl;
}

bool Producto::hayEnExistencia() const {
    return cantidad > 0;
}