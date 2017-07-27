/* Copyright 2017-present Samsung Electronics Co., Ltd. and other contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "iotjs_module_websocket.h"
#include "iotjs_objectwrap.h"
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include "iotjs_def.h"

IOTJS_DEFINE_NATIVE_HANDLE_INFO_THIS_MODULE(websocket);


#define logf3(f,k,v) \
    printf("%s:%d: " f , __FILE__, __LINE__, k, v)

#define LOGfp(a) \
    logf3("log: %s=%p\n", (#a), a)

#define LOGfs(a) \
    logf3("log: %s=%s\n", (#a), a)

#define LOGfd(a) \
    logf3("log: %s=%d\n", (#a), a)

static unsigned int opts = 0;

static void iotjs_websocket_destroy(iotjs_websocket_t* websocket) {
    //IOTJS_VALIDATED_STRUCT_DESTRUCTOR(iotjs_websocket_t, websocket);
  //IOTJS_RELEASE(websocket);
}

// Call any property of ClientRequest._Incoming
bool iotjs_websocket_jcallback(iotjs_websocket_t* websocket_data, const char* property,
                           const iotjs_jargs_t* jargs, bool resultvalue)
{
  printf("#{ %s\n", __PRETTY_FUNCTION__);
  LOGfp(websocket_data);
  bool retval = true;

  IOTJS_VALIDATED_STRUCT_METHOD(iotjs_websocket_t, websocket_data);
  LOGfp(_this);

#if 0
  iotjs_jval_t jprop = iotjs_jval_get_property(_this, property);
  LOGfp(jprop);
  IOTJS_ASSERT(iotjs_jval_is_function(&jprop));
  //iotjs_jargs_t const * jargs = iotjs_jargs_get_empty();
  iotjs_make_callback(&jprop, _this, jargs);
#endif 
  printf("#} %s\n", __PRETTY_FUNCTION__);

  return retval;
}

static int
callback_dumb_increment(struct lws *wsi, enum lws_callback_reasons reason,
			void *user, void *in, size_t len)
{
  //printf("#{ %s\n", __PRETTY_FUNCTION__);
  //LOGfd(reason);
  switch (reason) {
     case LWS_CALLBACK_GET_THREAD_ID:
      //LOGfd(LWS_CALLBACK_GET_THREAD_ID);
      break;
    case LWS_CALLBACK_WS_PEER_INITIATED_CLOSE:
      LOGfd(LWS_CALLBACK_WS_PEER_INITIATED_CLOSE);
      break;
    case LWS_CALLBACK_CLIENT_ESTABLISHED:
      lwsl_info("dumb: LWS_CALLBACK_CLIENT_ESTABLISHED\n");

      void* user = lws_get_protocol(wsi)->user;
      LOGfp(user);
      const iotjs_jval_t* jthis = (iotjs_jval_t*) user;
      
      LOGfp(jthis);
      iotjs_jargs_t const * jargs = iotjs_jargs_get_empty();
      LOGfp(jargs);
      iotjs_jval_t jprop = iotjs_jval_get_property(jthis, "onopen");
      LOGfp(jprop);
      iotjs_make_callback(&jprop, jthis, jargs);
      lws_callback_on_writable(wsi);

      break;
    case LWS_CALLBACK_CLOSED:
      lwsl_notice("dumb: LWS_CALLBACK_CLOSED\n");
      wsi = NULL;
      break;
    case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
      break;
    case LWS_CALLBACK_RECEIVE_CLIENT_HTTP:
      break;
    case LWS_CALLBACK_COMPLETED_CLIENT_HTTP:
      wsi = NULL;
      break;
    case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER:
      LOGfd(LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER);
      //libwebsocket_callback_on_writable(this, wsi);
      break;
    case LWS_CALLBACK_CLIENT_WRITEABLE:
      LOGfd(LWS_CALLBACK_CLIENT_WRITEABLE);
      break;

    default:
      break;
  }
  
  return 0;
}

static struct lws_protocols protocols[] = {
	{
		"dumb-increment-protocol,fake-nonexistant-protocol",
		callback_dumb_increment,
		0,
		20,
                0,
                0
	},
	{ NULL, NULL, 0, 0, 0, 0 } /* end */
};


JHANDLER_FUNCTION(W3cWebsocket)
{
    printf("#{ %s (constructor)\n", __PRETTY_FUNCTION__);
    printf("#. %s %d\n", __PRETTY_FUNCTION__, __LINE__);
    JHANDLER_CHECK_THIS(object);

    const iotjs_jval_t* jwebsocket = JHANDLER_GET_THIS(object);
    LOGfp(jwebsocket);
   
    iotjs_websocket_t* websocket_data = IOTJS_ALLOC(iotjs_websocket_t);
    IOTJS_VALIDATED_STRUCT_CONSTRUCTOR(iotjs_websocket_t, websocket_data);
    iotjs_jobjectwrap_initialize(&_this->jobjectwrap, jwebsocket, &this_module_native_info);

    //iotjs_websocket_t* websocket = iotjs_websocket_create(jwebsocket);

    JHANDLER_CHECK_ARGS(2, object, string);
    const iotjs_jval_t* jthis = JHANDLER_GET_ARG(0, object);
    LOGfp(jthis);
    iotjs_string_t arg1 = JHANDLER_GET_ARG(1, string);
    const char* url = iotjs_string_data(&arg1);
    LOGfs(url);
    //_this->URL = url;

    struct lws_context_creation_info info;
    memset(&info, 0, sizeof info);
    info.port = CONTEXT_PORT_NO_LISTEN;
    info.iface = NULL;
    info.ssl_cert_filepath = NULL;
    info.ssl_private_key_filepath = NULL;
    info.gid = -1;
    info.uid = -1;
    info.options = 0;
    info.user = (void*) jthis;
    info.protocols = protocols;

    LOGfp(&info);
    _this->context = lws_create_context(&info);

    if (_this->context == NULL) {
        return ;
    }
    //protocol.owning_server = _this->context;
    
    //char* hostname = "echo.websockets.org";
    //char* host = "echo.websockets.org:80";
    //int port = 80;
    int port = 1337;
    char* hostname = "localhost";
    char* host = "localhost:1337";
    {
        struct lws_client_connect_info i;
        memset(&i, 0, sizeof(i));
        i.context = _this->context;
        i.address = hostname;
        i.port = port;
        i.path = "/";
	i.host = host;
	i.origin = host;
	i.client_exts = NULL;
        i.ssl_connection = 0;
        i.ietf_version_or_minus_one = -1;
        i.protocol = protocols[0].name;
        protocols[0].user = _this; //TODO
        _this->wsi = lws_client_connect_via_info(&i);

    }
    LOGfp(_this);
    LOGfp(_this->context);
    LOGfp(_this->wsi);
  
    iotjs_string_destroy(&arg1);
    printf("#} %s\n", __PRETTY_FUNCTION__);
}

JHANDLER_FUNCTION(W3cwebsocketClose)
{
    printf("#{ %s\n", __PRETTY_FUNCTION__);
    DJHANDLER_CHECK_THIS(object);
    const iotjs_jval_t* jthis = JHANDLER_GET_THIS(object);
    LOGfp(jthis);
        
    JHANDLER_DECLARE_THIS_PTR(websocket, websocket_data);
    IOTJS_VALIDATED_STRUCT_METHOD(iotjs_websocket_t, websocket_data);
    LOGfp(_this);
    lws_context_destroy(_this->context);
    _this->context = NULL;

    //iotjs_websocket_jcallback( websocket_data, "onclose",
    //                         iotjs_jargs_get_empty(), false);
    iotjs_jargs_t const * jargs = iotjs_jargs_get_empty();
    iotjs_jval_t jprop = iotjs_jval_get_property(jthis, "onclose");
    iotjs_make_callback(&jprop, jthis, jargs);

    printf("#} %s\n", __PRETTY_FUNCTION__);
}

JHANDLER_FUNCTION(W3cwebsocketIdle_)
{
    //printf("#{ %s\n", __PRETTY_FUNCTION__);
    JHANDLER_DECLARE_THIS_PTR(websocket, websocket_data);
    IOTJS_VALIDATED_STRUCT_METHOD(iotjs_websocket_t, websocket_data);
    //LOGfp(_this->context);
    if (_this->context) {
        lws_service( _this->context, 500);
    }
    //printf("#} %s\n", __PRETTY_FUNCTION__);
}

/**
 * websocket_write_back: write the string data to the destination wsi.
 */
int w3cwebsocket_send(struct lws *wsi, char const *str) 
{
    printf("#{ %s\n", __PRETTY_FUNCTION__);
    printf("# wsi=%p\n", wsi);
    if (str == NULL || wsi == NULL)
        return -1;

    size_t l = strlen(str);
    char buffer[LWS_PRE + l];
    sprintf(&buffer[LWS_PRE], "%s", str);

    int n = lws_write(wsi, (unsigned char*) &buffer[LWS_PRE], l, opts | LWS_WRITE_TEXT);

    printf("#} %s\n", __PRETTY_FUNCTION__);
    return n;
}

JHANDLER_FUNCTION(W3cwebsocketSend)
{
  printf("#{ %s\n", __PRETTY_FUNCTION__);
  const iotjs_jval_t* jthis = JHANDLER_GET_THIS(object);
  LOGfp(jthis);
  JHANDLER_DECLARE_THIS_PTR(websocket, websocket_data);
  LOGfp(websocket_data);
  IOTJS_VALIDATED_STRUCT_METHOD(iotjs_websocket_t, websocket_data);
  LOGfp(_this->wsi);
  iotjs_string_t msg = JHANDLER_GET_ARG(0, string);
  const char* str = iotjs_string_data(&msg);
  printf("# {%s @ module}\n", str);
  w3cwebsocket_send(_this->wsi, str);
  //lws_callback_on_writable(wsi);
  //libwebsocket_callback_on_writable(_this->context, _this->wsi);
  iotjs_string_destroy(&msg);
  printf("#} %s\n", __PRETTY_FUNCTION__);
}

iotjs_jval_t InitWebsocket() {
  printf("#{ %s\n", __PRETTY_FUNCTION__);
  iotjs_jval_t constructor =
  iotjs_jval_create_function_with_dispatch(W3cWebsocket);
  LOGfp(constructor);
  iotjs_jval_t prototype = iotjs_jval_create_object();
  iotjs_jval_set_method(&prototype, "send", W3cwebsocketSend);
  iotjs_jval_set_method(&prototype, "close", W3cwebsocketClose);
  iotjs_jval_set_method(&prototype, "idle_", W3cwebsocketIdle_);
  iotjs_jval_set_property_jval(&constructor, IOTJS_MAGIC_STRING_PROTOTYPE,
                                 &prototype);
  printf("#} %s\n", __PRETTY_FUNCTION__);
  return constructor;
}
