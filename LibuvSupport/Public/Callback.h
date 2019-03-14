#pragma once
#ifndef LIBUV_CALLBACK_H
#define LIBUV_CALLBACK_H
#include "uv.h"

void defaultReadCallback(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);

void defaultAllocBufferCallback(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);

void defaultConnectionCallback(uv_connect_t* req, int status);

#endif // !LIBUV_CALLBACK_H
