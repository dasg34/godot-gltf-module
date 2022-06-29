/*************************************************************************/
/*  web_request.cpp                                                      */
/*************************************************************************/
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "web_request.h"

#include <OS.hpp>

#ifndef ERR_FAIL_COND_V_MSG
#define ERR_FAIL_COND_V_MSG(cond, ret, msg) if (cond) { ERR_PRINT((msg)); return (ret); }
#endif

namespace godot {
	template <class T>
	String itos(const T &arg) {
		return String("{0}").format(Array::make(Variant(arg)));
	}
	template <class T>
	String rtos(const T &arg) {
		return String("{0}").format(Array::make(Variant(arg)));
	}

	int get_slice_count(String base, String p_splitter) {
		if (base.empty()) {
			return 0;
		}
		if (p_splitter.empty()) {
			return 0;
		}

		int pos = 0;
		int slices = 1;

		while ((pos = base.find(p_splitter, pos)) >= 0) {
			slices++;
			pos += p_splitter.length();
		}

		return slices;
	}

	Error parse_url(String base, String &r_scheme, String &r_host, int &r_port, String &r_path) {
		// Splits the URL into scheme, host, port, path. Strip credentials when present.
		r_scheme = "";
		r_host = "";
		r_port = 0;
		r_path = "";
		int pos = base.find("://");
		// Scheme
		if (pos != -1) {
			r_scheme = base.substr(0, pos + 3).to_lower();
			base = base.substr(pos + 3, base.length() - pos - 3);
		}
		pos = base.find("/");
		// Path
		if (pos != -1) {
			r_path = base.substr(pos, base.length() - pos);
			base = base.substr(0, pos);
		}
		// Host
		pos = base.find("@");
		if (pos != -1) {
			// Strip credentials
			base = base.substr(pos + 1, base.length() - pos - 1);
		}
		String s1("[");
		if (base.begins_with(s1)) {
			// Literal IPv6
			pos = base.rfind("]");
			if (pos == -1) {
				return Error::ERR_INVALID_PARAMETER;
			}
			r_host = base.substr(1, pos - 1);
			base = base.substr(pos + 1, base.length() - pos - 1);
		} else {
			// Anything else
			if (get_slice_count(base, ":") > 2) {
				return Error::ERR_INVALID_PARAMETER;
			}
			pos = base.rfind(":");
			if (pos == -1) {
				r_host = base;
				base = "";
			} else {
				r_host = base.substr(0, pos);
				base = base.substr(pos, base.length() - pos);
			}
		}
		if (r_host.empty()) {
			return Error::ERR_INVALID_PARAMETER;
		}
		r_host = r_host.to_lower();
		// Port
		String s2(":");
		if (base.begins_with(s2)) {
			base = base.substr(1, base.length() - 1);
			if (!base.is_valid_integer()) {
				return Error::ERR_INVALID_PARAMETER;
			}
			r_port = base.to_int();
			if (r_port < 1 || r_port > 65535) {
				return Error::ERR_INVALID_PARAMETER;
			}
		}
		return Error::OK;
	}
}

WebRequest *WebRequest::_singleton = nullptr;

void WebRequest::_register_methods() {
	register_method("_init", &WebRequest::_init);
}

const PoolByteArray WebRequest::load_bytes(String url)
{
	PoolByteArray ret;
	Ref<HTTPClient> client;

	client.instance();
	String host;
	String path;
	String scheme;
	int port = 0;
	Error err = parse_url(url, scheme, host, port, path);
	ERR_FAIL_COND_V_MSG(err != Error::OK, ret, "Invalid URL: " + url);

	err = client->connect_to_host(host, port);
	ERR_FAIL_COND_V_MSG(err != Error::OK, ret, "Failed to connect to host: " + url);

	while (client->get_status() == HTTPClient::STATUS_CONNECTING || client->get_status() == HTTPClient::STATUS_RESOLVING)
	{
		client->poll();
	}
	ERR_FAIL_COND_V_MSG(client->get_status() != HTTPClient::STATUS_CONNECTED, ret, "Failed to connect to host: " + url);


	PoolStringArray headers;
	err = client->request(HTTPClient::METHOD_GET, "/" + path.substr(1, path.length() - 1).percent_encode(), headers);
	ERR_FAIL_COND_V_MSG(err != Error::OK, ret, "Failed to connect to host: " + url);

	while (client->get_status() == HTTPClient::STATUS_REQUESTING)
	{
		client->poll();
	}

	ERR_FAIL_COND_V_MSG(client->get_status() != HTTPClient::STATUS_BODY && client->get_status() != HTTPClient::STATUS_CONNECTED,
		ret, "Failed to sends a request to the connected host: " + url);

	if (client->has_response())
	{
		while (client->get_status() == HTTPClient::STATUS_BODY)
		{
			client->poll();
			PoolByteArray chunk = client->read_response_body_chunk();
			if (chunk.size() != 0)
			{
				ret.append_array(chunk);
			}
		}
	}
	client->close();

	return ret;
}
