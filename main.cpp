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
  string contraseña;

public:
  Usuario(string _nombre, string _telefono, int _edad, string _contraseña)
      : nombre(_nombre), telefono(_telefono), edad(_edad),
        contraseña(_contraseña) {}

  virtual bool login(string _nombre, string _contraseña) {
    return (nombre == _nombre && contraseña == _contraseña);
  }

  virtual void logout() { cout << "Sesión cerrada." << endl; }

  void cambiarPwd(string viejaContraseña, string nuevaContraseña) {
    if (contraseña == viejaContraseña) {
      contraseña = nuevaContraseña;
      cout << "Contraseña cambiada exitosamente." << endl;
    } else {
      cout << "La contraseña anterior es incorrecta." << endl;
    }
  }
};

class Cliente : public Usuario {
public:
  Cliente(string _nombre, string _telefono, int _edad, string _contraseña)
      : Usuario(_nombre, _telefono, _edad, _contraseña) {}

  void comprar() { cout << "Compra realizada." << endl; }

  void reclamar() { cout << "Reclamo realizado." << endl; }

  void devolucion() { cout << "Devolución realizada." << endl; }
};

class Vendedor : public Usuario {
public:
  Vendedor(string _nombre, string _telefono, int _edad, string _contraseña)
      : Usuario(_nombre, _telefono, _edad, _contraseña) {}

  void vender() { cout << "Venta realizada." << endl; }

  void actualizarInventario() { cout << "Inventario actualizado." << endl; }
};

int main() {
  string opcion;
  cout << "¿Eres cliente o vendedor? (cliente/vendedor): ";
  cin >> opcion;

  Usuario *usuario = nullptr;

  if (opcion == "cliente") {
    usuario = new Cliente("Juan", "123456789", 30, "contraseña123");
  } else if (opcion == "vendedor") {
    usuario = new Vendedor("Maria", "987654321", 25, "contraseña456");
  } else {
    cout << "Opción no válida." << endl;
    return 1;
  }

  string nombreUsuario, contraseña;
  cout << "Ingresa tu nombre de usuario: ";
  cin >> nombreUsuario;
  cout << "Ingresa tu contraseña: ";
  cin >> contraseña;

  if (usuario->login(nombreUsuario, contraseña)) {
    cout << "Inicio de sesión exitoso como " << opcion << "." << endl;
    usuario->cambiarPwd(contraseña, "nuevaContraseña");

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
    cout << "Inicio de sesión fallido." << endl;
  }

  return 0;
}
