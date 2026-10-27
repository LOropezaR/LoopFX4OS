/**
 * @file serial.cpp
 * @author Diego Abarca Robles (dabarcar2200@alumno.ipn.mx)
 * @brief Programa de prueba del primer prototipo de Master FX4OS donde se
 * prueba la comunicacion serial entre el arduino y la computadora para cambiar
 * los bancos.
 * @version 0.1
 * @date 2026-10-09
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

int main() {
  int serialPort =
      open("/dev/ttyACM0",
           O_RDWR); // cambiar esta cosa por el puerto q estemos trabajando

  if (serialPort < 0) {
    std::cerr << "Error al abrir el puerto serial" << std::endl;
    return 1;
  }

  struct termios tty;
  tcgetattr(serialPort, &tty);
  cfsetospeed(&tty, B9600);
  cfsetispeed(&tty, B9600);

  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag |= CS8;

  tcsetattr(serialPort, TCSANOW, &tty);

  char buffer[256];
  while (true) {
    int bytesRead = read(serialPort, buffer, sizeof(buffer) - 1);
    if (bytesRead > 0) {
      buffer[bytesRead] = '\0';
      std::cout << "Voltaje: " << buffer << std::endl;
    }
    usleep(500000);
  }

  close(serialPort);
  return 0;
}
