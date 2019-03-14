#include "LibuvSupportPrivatePCH.h"
#include "LibuvSupport/Public/TcpClient.h"

TcpClient::TcpClient(const string &ip, int port) :
	connectionCallback_(defaultConnectionCallback),
	canWrite_(false)
{
	loop_ = uv_default_loop();
	socket_ = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
	uv_tcp_init(loop_, socket_);
	uv_ip4_addr(ip.c_str(), port, &addr_);
	write_ = (write_req_t*)malloc(sizeof(write_req_t));
}

TcpClient::~TcpClient()
{
	if (connect_)
		free(connect_);
	if (socket_)
		free(socket_);
	if (write_)
		free(write_);
	uv_loop_close(loop_);
	free(loop_);
}

void TcpClient::write(const string & data)
{
	if (!canWrite_)
		return;

	write_->buf = uv_buf_init((char*)data.c_str(), data.size());
	uv_write((uv_write_t*)write_, (uv_stream_t *)socket_, &write_->buf, 1, NULL);
}

void TcpClient::connect()
{
	connect_ = (uv_connect_t*)malloc(sizeof(uv_connect_t));
	int r = uv_tcp_connect(connect_, socket_, (const struct sockaddr *)&addr_, connectionCallback_);
	if (r) {
		fprintf(stderr, "connect error %s\n", uv_strerror(r));
		return;
	}
	canWrite_ = true;
	//程序结束的时候释放资源
	FCoreDelegates::OnPreExit.AddRaw(this, &TcpClient::disconnect);

	uv_run(loop_, UV_RUN_DEFAULT);
}

void TcpClient::disconnect()
{
	FCoreDelegates::OnPreExit.RemoveAll(this);
	canWrite_ = false;
	uv_read_stop((uv_stream_t*)socket_);
	uv_close((uv_handle_t*)socket_, closeCallback_);
}

void TcpClient::stop()
{
}

void
defaultReadCallback(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
	if (nread > 0) {
		return;
	}
	if (nread < 0) {
		if (nread != UV_EOF)
			fprintf(stderr, "Read error %s\n", uv_err_name(nread));
	}
}

void
defaultAllocBufferCallback(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
	buf->base = (char*)malloc(suggested_size);
	buf->len = suggested_size;
}

void
defaultConnectionCallback(uv_connect_t* req, int status) {
	if (status < 0)
	{
		fprintf(stderr, "Connection error %s\n", uv_strerror(status));

		return;
	}
	uv_read_start((uv_stream_t*)req->handle, defaultAllocBufferCallback, defaultReadCallback);
	fprintf(stdout, "Connect ok\n");
}