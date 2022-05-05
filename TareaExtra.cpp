/*
 *Ejercicio Extra
 *Daniel Hernandez Toledo
 *Daniel Alejandro Osornio Lopez
*/

#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>

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

void menuAdmin();

typedef vector<Producto> Productos;

struct Persona {
public:
    double dinero;
    Productos productosAComprar;
};

Productos cargarProductos(const string & archivo);

void guardarTodo(Productos &productos, const string & archivo);

void imprimirTodos(vector<Producto> &productos);

void agregarDatos(vector<Producto> &productos);

void eliminarProductos(Productos &productos, Productos &productosEnTienda, const string & archivo);

void agregarProductoACarro(Productos &productosEnCarro, Productos &productos, string & producto, int cantidad);

void eliminarArchivo(Productos &productos, Productos &productosEnTienda, const string & archivo);

void menu();

int buscarProducto(Productos &productosEnTienda, const string &buscar);

int main()
{
    double dinero;
    Productos productosEnTienda = cargarProductos("Products.txt");
    Persona persona = { 0, cargarProductos("Usuario.txt") };
    int option = 0, lazy;

    do
    {
        guardarTodo(productosEnTienda, string("Products.txt"));
        guardarTodo(persona.productosAComprar, string("Usuario.txt"));
        menuAdmin();
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (option == 1)
        {
            do
            {
                guardarTodo(productosEnTienda, string("Products.txt"));
                guardarTodo(persona.productosAComprar, string("Usuario.txt"));
                menu();
                cout << "Ingrese la option: ";
                cin >> option;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (option) {
                    case 1:
                    {
                        // Método agregar n productos al carrito
                        string nombre;
                        int num;

                        cout << "Ingresa el nombre del producto a agregar al carrito: ";
                        getline(cin, nombre);

                        cout << "Ingrese la cantidad que desea agregar al carrito: ";
                        cin >> num;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        agregarProductoACarro(persona.productosAComprar, productosEnTienda, nombre, num);

                        break;

                    }
                    case 2:
                    {
                        // Método para buscar producto
                        string buscar;
                        cout << "Ingrese un Producto a buscar: ";
                        cin >> buscar;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        int i = buscarProducto(productosEnTienda, buscar);
                        if (i > 0)
                        {
                            cout << "El producto existe:" << endl;
                            printf("%5d | ", i);
                            productosEnTienda[i].printProducts();
                        }
                        else
                        {
                            cout << "El producto no existe en la tienda" << endl;
                        }

                    }

                        break;

                    case 3:
                    {
                        eliminarProductos(persona.productosAComprar, productosEnTienda, string("Usuario.txt"));
                        guardarTodo(productosEnTienda, string("Products.txt"));
                        guardarTodo(persona.productosAComprar, string("Usuario.txt"));
                        break;
                    }
                    case 4:
                    {
                        double total =0 ;
                        double cantidadPorducto = 0;
                        cout<<"Ingresar el dinero: ";
                        cin>>persona.dinero;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        for (Producto producto : persona.productosAComprar)
                        {
                            total += producto.price;
                            cantidadPorducto = producto.cantidad;

                        }

                        total = total*cantidadPorducto;
                        if (persona.dinero >= total)
                        {
                            total = persona.dinero- total;
                            cout<<"Compra exitosa!! "<<endl;
                            eliminarArchivo(persona.productosAComprar, productosEnTienda, string("Usuario.txt"));
                            guardarTodo(persona.productosAComprar, string("Usuario.txt"));

                            if (total == 0)
                            {
                                cout<<"No sobra dinero"<<endl;
                            }
                            else
                            {
                                cout<<"El cambio es: "<<total<<endl;
                            }
                        } else{cout<<"No se puede realizar la compra"<<endl;}


                        break;

                    }
                    case 5: {
                        imprimirTodos(persona.productosAComprar);
                    }
                    break;
                    case 6: {
                        imprimirTodos(productosEnTienda);
                    }
                    default:
                        break;
                }

            } while (option != 7);
        }
        else if (option == 2)
        {
            //metodo admin para agregar productos
            int num;
            cout << "Ingrese la cantidad de productos que desea agregar: ";
            cin >> num;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for (int i = 0; i < num; i++)
                agregarDatos(productosEnTienda);



        } else {
            break;
        }

        guardarTodo(productosEnTienda, string("Products.txt"));
        guardarTodo(persona.productosAComprar, string("Usuario.txt"));


    }while (option != 3);
}
void eliminarArchivo(Productos &productos, Productos &productosEnTienda, const string & archivo)
{
    for (const Producto& pro : productos)
    {
        int j = buscarProducto(productosEnTienda, pro.productName);
        productosEnTienda[j].cantidad -= pro.cantidad;
    }

}
int buscarProducto(Productos &productos, const string &buscar) {
    for (int i=0; i<productos.size(); i++) {
        if (buscar == productos[i].productName) {
            return i;
        }
    }

    return -1;
}

void menu() {
    cout << "MENU DEL SUPER" << endl;
    cout << "1. Agregar producto al carrito " << endl;
    cout << "2. Consulta (Busqueda)" << endl;
    cout << "3. Eliminar productos del carrito" << endl;
    cout << "4. Comprar" << endl;
    cout << "5. Mostrar carrito" << endl;
    cout << "6. Mostrar productos en tienda" << endl;
    cout << "7. Salir" << endl;
}

void eliminarProductos(Productos &productos, Productos &productosEnTienda, const string & archivo)
{
    ofstream f;
    f.open(archivo);
    if (!f)
    {
        cout << "Algo salio mal al guardar los datos" << endl;
    }

    for (const Producto& pro : productos) {
       int j = buscarProducto(productosEnTienda, pro.productName);
       productosEnTienda[j].cantidad += pro.cantidad;
    }

    productos.erase(productos.cbegin(), productos.cend());
    guardarTodo(productos, "Usuario.txt");

}
void guardarTodo(Productos &productos, const string&  archivo) {
    ofstream f;
    f.open(archivo);

    if (!f)
    {
        cout << "Algo salio mal al guardar los datos" << endl;
    }

    for (auto & producto : productos)
    {
        producto.saveProductsToFile(f);
    }
}


void imprimirTodos(Productos &productos) {
    if (productos.empty())
    {
        cout << "No hay elementos en la lista" << endl;
        return;
    }

    printf("%5s | %-25s | %-8s | %-8s\n", "Index", "Producto", "Precio", "Cantidad");

    for (int i = 0; i < productos.size(); i++) {
        printf("%5d | ", i);
        productos[i].printProducts();
    }
}

void agregarProductoACarro(Productos &productosEnCarro, Productos &productos, string & producto, int cantidad)
{
    int i = buscarProducto(productosEnCarro, producto);
    int j = buscarProducto(productos, producto);

    if (productos[j].cantidad < cantidad) {
        cout << "Error: No hay suficientes unidades en stock ( Hay " << productos[j].cantidad << " y se solicitaron " << cantidad << " )" << endl;
        return;
    }

    if (i > 0 && j > 0) {
        productosEnCarro[i].cantidad += cantidad;
        productos[j].cantidad -= cantidad;
    } else {
        if (j > 0) {
            Producto nuevo = {
                    producto,
                    productos[j].price,
                    cantidad
            };

            productosEnCarro.push_back(nuevo);
            productos[j].cantidad -= cantidad;
        } else {
            cout << "El producto deseado no esta disponible en la tienda" << endl;
        }
    }
}

void agregarDatos(Productos &productos)
{
    Producto valor;
    string NameProduct;
    double prices;
    int cantidad;

    cout << "Ingrese el nombre del producto: ";
    getline(cin, NameProduct);

    cout << "Ingrese el precio: ";
    cin >> prices;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Ingrese la cantidad en stock: ";
        cin >> cantidad;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (cantidad < 0);

    valor = {
            NameProduct,
            prices,
            cantidad
    };

    productos.push_back(valor);
}


void Producto::printProducts() const
{
    printf("%-25s | %-7.2lf | %-10d\n", productName.c_str(), price, cantidad);
}

void Producto::saveProductsToFile(ofstream &f) const
{
    f << productName << "|";
    f << price << "|";
    f << cantidad << endl;
}

bool Producto::hayEnExistencia() const
{
    return cantidad > 0;
}

Productos cargarProductos(const string & archivo) {
    Productos productos = Productos();
    ifstream f;
    string linea;

    f.open(archivo);

    while (getline(f, linea)) {
        stringstream g(linea);

        string nombre, cantidads, precios;
        int cantidad;
        double precio;

        getline(g, nombre, '|');

        getline(g, precios, '|');

        getline(g, cantidads, '|');

        stringstream cantidadss(cantidads);
        stringstream precioss(precios);

        cantidadss >> cantidad;
        precioss >> precio;

        Producto producto = {
                nombre,
                precio,
                cantidad
        };

        productos.push_back(producto);

    }

    return productos;
}
void menuAdmin()
{
    cout << "Menu Principal!!" << endl;
    cout << "1. Menu usuarios Normales" << endl;
    cout << "2. Menu Administrador" << endl;
    cout << "3. Salir" << endl;
    cout << "Ingrese la option: ";
}