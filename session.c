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

#include <arpa/inet.h>

#include "main.h"
#include "session.h"

int session_main(const int tcp_socket) {
  struct session peerbuf;
  struct session *peer = &peerbuf;
  memset(peer, 0, sizeof(struct session));

  char *buf = calloc(BUF_SIZE, 1);

  if (buf == NULL) {
    log("Receving_Buf_Allocation_Error:%s", strerror(errno));
    goto localfail;
  }

  peer->socket = accept(tcp_socket, (struct sockaddr *)&peer->addr,
                &peer->addr_len);
  if (peer->socket < 0) {
    log("Accept_Socket_Error:%s", strerror(errno));
    goto localfail;
  }
  char address_buf[INET_ADDRSTRLEN] = {0};
  log("Accepted:%s %d",  inet_ntop(AF_INET, &(peer->addr.sin_addr), address_buf, sizeof(address_buf)) 
  ,(int)ntohs(peer->addr.sin_port));

  ssize_t received_length = recv(peer->socket, buf, BUF_SIZE, 0);
  if (received_length < 0) {
    log("Received_Error:%s", strerror(errno));
    goto localfail;
  }

  if (received_length == BUF_SIZE) {
    log("Receving_Buffer_Overflow:%s", strerror(errno));
    goto localfail;
  }

localfail:
  if (buf != NULL) {
    free(buf);
  }
  shutdown(peer->socket, SHUT_RDWR);
  close(peer->socket);
  return -1;
}