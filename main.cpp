// Jose Angel Pacheco Cervantes
// 23310194

#include <iostream>
#include <string>

using namespace std;

class Usuario {
protected:
  string nombre;
  string telefono;
  int edad;
  string contrasenna;

public:
  Usuario(string _nombre, string _telefono, int _edad, string _contrasenna)
      : nombre(_nombre), telefono(_telefono), edad(_edad),
        contrasenna(_contrasenna) {}

  virtual bool login(string _nombre, string _contrasenna) {
    return (nombre == _nombre && contrasenna == _contrasenna);
  }

  virtual void logout() { cout << "Sesion cerrada." << endl; }

  void cambiarPwd(string viejaContrasenna, string nuevaContrasenna) {
    if (contrasenna == viejaContrasenna) {
      contrasenna = nuevaContrasenna;
      cout << "Contrasenna cambiada exitosamente." << endl;
    } else {
      cout << "La contrasenna anterior es incorrecta." << endl;
    }
  }
};

class Cliente : public Usuario {
public:
  Cliente(string _nombre, string _telefono, int _edad, string _contrasenna)
      : Usuario(_nombre, _telefono, _edad, _contrasenna) {}

  void comprar() { cout << "Compra realizada." << endl; }

  void reclamar() { cout << "Reclamo realizado." << endl; }

  void devolucion() { cout << "Devolucion realizada." << endl; }
};

class Vendedor : public Usuario {
public:
  Vendedor(string _nombre, string _telefono, int _edad, string _contrasenna)
      : Usuario(_nombre, _telefono, _edad, _contrasenna) {}

  void vender() { cout << "Venta realizada." << endl; }

  void actualizarInventario() { cout << "Inventario actualizado." << endl; }
};

int main() {
  string opcion;
  cout << "¿Eres cliente o vendedor? (cliente/vendedor): ";
  cin >> opcion;

  Usuario *usuario = nullptr;

  if (opcion == "cliente") {
    usuario = new Cliente("Juan", "123456789", 30, "contrasenna123");
  } else if (opcion == "vendedor") {
    usuario = new Vendedor("Maria", "987654321", 25, "contrasenna456");
  } else {
    cout << "Opcion no valida." << endl;
    return 1;
  }

  string nombreUsuario, contrasenna;
  cout << "Ingresa tu nombre de usuario: ";
  cin >> nombreUsuario;
  cout << "Ingresa tu contrasenna: ";
  cin >> contrasenna;

  if (usuario->login(nombreUsuario, contrasenna)) {
    cout << "Inicio de sesion exitoso como " << opcion << "." << endl;
    usuario->cambiarPwd(contrasenna, "nuevaContrasenna");

    if (opcion == "cliente") {
      Cliente *cliente = dynamic_cast<Cliente *>(usuario);
      cliente->comprar();
      cliente->reclamar();
      cliente->devolucion();
    } else if (opcion == "vendedor") {
      Vendedor *vendedor = dynamic_cast<Vendedor *>(usuario);
      vendedor->vender();
      vendedor->actualizarInventario();
    }

    usuario->logout();
  } else {
    cout << "Inicio de sesion fallido." << endl;
  }

  return 0;
}
