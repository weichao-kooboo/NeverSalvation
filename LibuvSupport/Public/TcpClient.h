#pragma once

#include "CoreMinimal.h"

#include <functional>
#include <string>

#include "LibuvSupport/Public/Callback.h"

using namespace std;

typedef struct {
	uv_write_t req;
	uv_buf_t buf;
} write_req_t;

class LIBUVSUPPORT_API TcpClient
{
public:
	TcpClient(const string &ip, int port);
	~TcpClient();
	void write(const string &data);
	void connect();
	void disconnect();
	void stop();
	void setConnectionCallBack(uv_connect_cb cb) {
		connectionCallback_ = std::move(cb);
	}
	void setCloseCallBack(uv_close_cb cb) {
		closeCallback_ = std::move(cb);
	}
	void setWriteCallBack(uv_write_cb cb) {
		writeCallback_ = std::move(cb);
	}
	void setReadCallBack(uv_read_cb cb) {
		readCallback_ = std::move(cb);
	}
	void setAllocCallBack(uv_alloc_cb cb) {
		allocCallback_ = std::move(cb);
	}
private:
	uv_loop_t * loop_;
	uv_connect_cb connectionCallback_;
	uv_close_cb closeCallback_;
	uv_write_cb writeCallback_;
	uv_read_cb readCallback_;
	uv_alloc_cb allocCallback_;
	struct sockaddr_in addr_;
	uv_tcp_t *socket_;
	uv_connect_t *connect_;
	write_req_t *write_;
	bool canWrite_;
};