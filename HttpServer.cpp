#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#ifndef S_ISDIR
#define S_ISDIR(x) (((x) & S_IFMT) == S_IFDIR)
#endif
#else
#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#endif

#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/keyvalq_struct.h>

#include "HttpServer.h"
#include "Macroes.h"
#include "Exception.h"

char uri_root[512];

/* Try to guess a good content-type for 'path' */
static const char *guessContentType(const char *path)
{
	const char *last_period, *extension;
	const struct table_entry *ent;
	last_period = strrchr(path, '.');
	if (!last_period || strchr(last_period, '/'))
		goto not_found; /* no exension */
	extension = last_period + 1;
	for (ent = &content_type_table[0]; ent->extension; ++ent) 
	{
		if (!evutil_ascii_strcasecmp(ent->extension, extension))
		{
			return ent->content_type;
		}
	}

not_found:
	return "application/misc";
}

/* Callback used for the /dump URI, and for every non-GET request:
* dumps all information to stdout and gives back a trivial 200 ok */
static void dumpRequestCb(struct evhttp_request *req, void *arg)
{
	const char *cmdtype;
	struct evkeyvalq *headers;
	struct evkeyval *header;
	struct evbuffer *buf;

	switch (evhttp_request_get_command(req))
	{
	case EVHTTP_REQ_GET:
		cmdtype = "GET";
		break;
	case EVHTTP_REQ_POST:
		cmdtype = "POST";
		break;
	case EVHTTP_REQ_HEAD:
		cmdtype = "HEAD";
		break;
	case EVHTTP_REQ_PUT:
		cmdtype = "PUT";
		break;
	case EVHTTP_REQ_DELETE:
		cmdtype = "DELETE";
		break;
	case EVHTTP_REQ_OPTIONS:
		cmdtype = "OPTIONS";
		break;
	case EVHTTP_REQ_TRACE:
		cmdtype = "TRACE";
		break;
	case EVHTTP_REQ_CONNECT:
		cmdtype = "CONNECT";
		break;
	case EVHTTP_REQ_PATCH:
		cmdtype = "PATCH";
		break;
	default:
		cmdtype = "unknown";
		break;
	}

	DEBUG("Received a %s request for %s\nHeaders:\n",
		cmdtype, evhttp_request_get_uri(req));

	headers = evhttp_request_get_input_headers(req);
	for (header = headers->tqh_first; header; header = header->next.tqe_next) 
	{
		DEBUG("  %s: %s", header->key, header->value);
	}

	buf = evhttp_request_get_input_buffer(req);
	puts("Input data: <<<");
	while (evbuffer_get_length(buf))
	{
		int n;
		char cbuf[128];
		n = evbuffer_remove(buf, cbuf, sizeof(cbuf));
		if (n > 0) 
		{
			(void)fwrite(cbuf, 1, n, stdout);
		}
	}
	puts(">>>");
	evhttp_send_reply(req, 200, "OK", NULL);
}

/* This callback gets invoked when we get any http request that doesn't match
* any other callback.  Like any evhttp server callback, it has a simple job:
* it must eventually call evhttp_send_error() or evhttp_send_reply().
*/
//需要使用真正的逻辑处理函数替换这两个回调函数
static void sendDocumentCb(struct evhttp_request *req, void *arg)
{
	struct evbuffer *evb = NULL;
	const char *docroot = (char*)arg;
	const char *uri = evhttp_request_get_uri(req); //获取请求的URI
	struct evhttp_uri *decoded = NULL;
	const char *path;
	char *decoded_path;
	char *whole_path = NULL;
	size_t len;
	int fd = -1;
	struct stat st;

	if (evhttp_request_get_command(req) != EVHTTP_REQ_GET) 
	{
		//处理非GET请求
		dumpRequestCb(req, arg);
		return;
	}

	printf("Got a GET request for <%s>\n", uri);

	/* Decode the URI */
	decoded = evhttp_uri_parse(uri);
	if (!decoded)
	{
		printf("It's not a good URI. Sending BADREQUEST\n");
		evhttp_send_error(req, HTTP_BADREQUEST, 0);
		return;
	}

	/* Let's see what path the user asked for. */
	path = evhttp_uri_get_path(decoded);
	if (!path)
	{
		path = "/";
	}

	/* We need to decode it, to see what path the user really wanted. */
	decoded_path = evhttp_uridecode(path, 0, NULL);
	if (decoded_path == NULL)
		goto err;
	/* Don't allow any ".."s in the path, to avoid exposing stuff outside
	* of the docroot.  This test is both overzealous and underzealous:
	* it forbids aceptable paths like "/this/one..here", but it doesn't
	* do anything to prevent symlink following." */
	if (strstr(decoded_path, ".."))
		goto err;

	len = strlen(decoded_path) + strlen(docroot) + 2;
	if (!(whole_path = (char *)malloc(len)))
	{
		perror("malloc");
		goto err;
	}
	evutil_snprintf(whole_path, len, "%s/%s", docroot, decoded_path);

	if (stat(whole_path, &st)<0)
	{
		goto err;
	}

	/* This holds the content we're sending. */
	evb = evbuffer_new();

	if (S_ISDIR(st.st_mode))
	{
		/* If it's a directory, read the comments and make a little
		* index page */
#ifdef WIN32
		HANDLE d;
		WIN32_FIND_DATAA ent;
		char *pattern;
		size_t dirlen;
#else
		DIR *d;
		struct dirent *ent;
#endif
		const char *trailing_slash = "";

		if (!strlen(path) || path[strlen(path) - 1] != '/')
			trailing_slash = "/";

#ifdef WIN32
		dirlen = strlen(whole_path);
		pattern = (char *)malloc(dirlen + 3);
		memcpy(pattern, whole_path, dirlen);
		pattern[dirlen] = '\\';
		pattern[dirlen + 1] = '*';
		pattern[dirlen + 2] = '\0';
		d = FindFirstFileA(pattern, &ent);
		free(pattern);
		if (d == INVALID_HANDLE_VALUE)
			goto err;
#else
		if (!(d = opendir(whole_path)))
			goto err;
#endif

		evbuffer_add_printf(evb, "<html>\n <head>\n"
			"  <title>%s</title>\n"
			"  <base href='%s%s%s'>\n"
			" </head>\n"
			" <body>\n"
			"  <h1>%s</h1>\n"
			"  <ul>\n",
			decoded_path, /* XXX html-escape this. */
			uri_root, path, /* XXX html-escape this? */
			trailing_slash,
			decoded_path /* XXX html-escape this */);
#ifdef WIN32
		do {
			const char *name = ent.cFileName;
#else
		while ((ent = readdir(d))) {
			const char *name = ent->d_name;
#endif
			evbuffer_add_printf(evb,
				"    <li><a href=\"%s\">%s</a>\n",
				name, name);/* XXX escape this */
#ifdef WIN32
		} while (FindNextFileA(d, &ent));
#else
		}
#endif
		evbuffer_add_printf(evb, "</ul></body></html>\n");
#ifdef WIN32
		FindClose(d);
#else
		closedir(d);
#endif
		evhttp_add_header(evhttp_request_get_output_headers(req),
			"Content-Type", "text/html");
	}
	else
	{
		/* Otherwise it's a file; add it to the buffer to get
		* sent via sendfile */
		const char *type = guessContentType(decoded_path);
		if ((fd = _open(whole_path, O_RDONLY)) < 0)
		{
			perror("open");
			goto err;
		}

		if (fstat(fd, &st)<0)
		{
			/* Make sure the length still matches, now that we
			* opened the file :/ */
			perror("fstat");
			goto err;
		}
		evhttp_add_header(evhttp_request_get_output_headers(req),
			"Content-Type", type);
		evbuffer_add_file(evb, fd, 0, st.st_size);
	}

	evhttp_send_reply(req, 200, "OK", evb);
	goto done;
err:
	evhttp_send_error(req, 404, "Document was not found");
	if (fd >= 0)
		_close(fd);
done:
	if (decoded)
	{
		evhttp_uri_free(decoded);
	}
	if (decoded_path)
	{
		free(decoded_path);
	}
	if (whole_path)
	{
		free(whole_path);
	}
	if (evb)
	{
		evbuffer_free(evb);
	}
}

CHttpServer::CHttpServer(const int port):_iPort(port), _strIp(""), _pEventBaseHandle(NULL), _pEvHttpHandle(NULL)
{
	DEBUG("CHttpServer Ctor now");
	//C++构造函数不能调用基类的虚函数，会导致静态调用
}

CHttpServer:: ~CHttpServer() 
{
	if (_pEventBaseHandle != NULL)
	{
		event_base_free(_pEventBaseHandle);
		_pEventBaseHandle = NULL;
	}
	
	if (_pEvHttpHandle != NULL) 
	{
		evhttp_free(_pEvHttpHandle);
		_pEvHttpHandle = NULL;
	}
}

/*初始化函数，完成句柄的创建，socket的监听*/
void CHttpServer::init()
{
	//创建event句柄
	_pEventBaseHandle = createEventBase();
	//创建http句柄
	_pEvHttpHandle = createEvHttp(_pEventBaseHandle);
	setHttpcb(0);
	setHttpcb(1);	
	//绑定socket 端口
	eventSocketBind();
}

/*进行事件处理*/
void CHttpServer::run() 
{
	//进行事件处理
	eventDispatch();
}

void CHttpServer::decordRequest(const std::string& strRequst)
{

}

struct event_base* CHttpServer::createEventBase()
{
	struct event_base* pEventBase = event_base_new(); //创建eventbase
	if (!pEventBase)
	{
		DEBUG("Couldn't create an event_base: exiting");
		throw CException(1001,"Couldn't create an event_base");
	}
	return pEventBase;
}

struct evhttp* CHttpServer::createEvHttp(struct event_base* pEventBase)
{
	struct evhttp *pEvhttp = evhttp_new(pEventBase); //创建http handle
	if (!pEvhttp)
	{
		DEBUG("couldn't create evhttp. Exiting");
		throw CException(1002, "couldn't create evhttp");
	}
	return pEvhttp;
}

void CHttpServer::eventDispatch()
{
	int iret = event_base_dispatch(_pEventBaseHandle);
	if (iret < 0) 
	{
		DEBUG("couldn't dispatch event. Exiting");
		throw CException(1003, "couldn't dispatch event");
	}
}

void CHttpServer::eventSocketBind()
{
	int iret = evhttp_bind_socket(_pEvHttpHandle, _strIp.c_str(), _iPort);
	if (iret < 0 ) 
	{
		DEBUG("couldn't bind socket. Exiting");
		throw CException(1004, "couldn't bind socket");
	}
}

//传入参数过于简单，封装没意义
void CHttpServer::setHttpcb(int itype)
{
	//0设置为通用处理回调函数
	if (itype == 0) 
	{ 
		evhttp_set_gencb(_pEvHttpHandle, sendDocumentCb, NULL);
	}
	else if(itype == 1)//1设置为专用处理回调函数
	{ 
		evhttp_set_cb(_pEvHttpHandle, "/dump", dumpRequestCb, NULL);
	}
}



