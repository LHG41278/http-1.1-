#pragma once
#include <netinet/in.h>
#ifndef _SESSION_H
#define _SESSION_H 1

#include <sys/socket.h>

struct session {
  int socket;
  struct sockaddr_in addr;
  socklen_t addr_len;
};

int session_main(int tcp_socket);

#endif // _SEESION_H
