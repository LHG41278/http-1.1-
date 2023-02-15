#pragma once
#ifndef _MAIN_H
#define _MAIN_H 1

#define QUEUE_LENGTH 16
#define BUF_SIZE (1UL << 12)

void real_log(const char *, ...);
#define log(v, ...)                                                            \
  real_log(" %s:%d %s::" v "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#endif // _MAIN_H