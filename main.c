#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <netinet/tcp.h>

#include "main.h"
#include "session.h"

int main() {
  int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (tcp_socket < 0) {
    log("Socket_Creation_Error:%s", strerror(errno));
    goto mainfail;
  }

  struct sockaddr_in sock_addr = {AF_INET,
                                  htons(3080),
                                  {
                                      INADDR_ANY,
                                  }
                                  };

  int ret_val =
      bind(tcp_socket, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
  if (ret_val < 0) {
    log("Socket_Bind_Error:%s", strerror(errno));
    goto mainfail;
  }

  ret_val = listen(tcp_socket, QUEUE_LENGTH);
  if (ret_val < 0) {
    log("Socket_Listen_Error:%s", strerror(errno));
    goto mainfail;
  }

  while (1) {
    if (session_main(tcp_socket) < 0) {
      goto mainfail;
    }
  }

// exception handle
mainfail:
  shutdown(tcp_socket, SHUT_RDWR);
  close(tcp_socket);
  return -1;
}

void real_log(const char *message, ...) {
  va_list va;
  va_start(va, message);
  vprintf(message, va);

  return;
}