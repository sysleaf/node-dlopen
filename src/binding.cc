#include <node_api.h>
#include "uv.h"
#include <assert.h>
#include <stdio.h>

napi_value dlopen(napi_env env, napi_callback_info info)
{
  char filename[200];
  uv_lib_t *lib = nullptr;
  size_t *argvSize = nullptr;
  size_t argc = 2;
  napi_value args[2];
  napi_valuetype argvtype1;
  napi_value retcode;
  napi_status status;
  void *data;
  size_t length;

  napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

  napi_typeof(env, args[0], &argvtype1);
  if (argvtype1 == napi_string)
  {
    status = napi_get_value_string_utf8(env, args[0], filename, 200, argvSize);
    assert(status == napi_ok);
  }
  else
  {
    napi_throw_type_error(env, nullptr, "a string filename must be passed as the first argument");
  }

  status = napi_get_buffer_info(env, args[1], &data, &length);
  assert(status == napi_ok);
  lib = (uv_lib_t *)data;
  // lib = (uv_lib_t *)malloc(sizeof(uv_lib_t));
  int err = uv_dlopen(filename, lib);

  napi_create_int32(env, err, &retcode);
  return retcode;
}

napi_value dlclose(napi_env env, napi_callback_info info)
{
  napi_value retcode;
  uv_lib_t *lib = nullptr;
  size_t argc = 1;
  napi_value args[1];
  void *data;
  size_t length;
  napi_status status;

  status = napi_get_undefined(env, &retcode);
  assert(status == napi_ok);


  status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  status = napi_get_buffer_info(env, args[0], &data, &length);
  assert(status == napi_ok);
  lib = (uv_lib_t *)data;

  uv_dlclose(lib);
  return retcode;
}

napi_value dlsym(napi_env env, napi_callback_info info)
{
  char symbname[200];
  uv_lib_t *lib = nullptr;
  size_t *argvSize = nullptr;
  size_t argc = 3;
  napi_value args[3];
  napi_valuetype argvtype1;
  napi_value retcode;
  napi_status status;
  void *data;
  void *sym;
  size_t length;

  status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  status = napi_get_buffer_info(env, args[0], &data, &length);
  assert(status == napi_ok);
  lib = (uv_lib_t *)data;

  status = napi_get_value_string_utf8(env, args[1], symbname, 200, argvSize);
  assert(status == napi_ok);

  status = napi_get_buffer_info(env, args[2], &sym, &length);
  assert(status == napi_ok);
  
  int err = uv_dlsym(lib, symbname, &sym);

  napi_create_int32(env, err, &retcode);
  return retcode;
}

napi_value Init(napi_env env, napi_value exports)
{
  napi_status status;
  napi_value sizeof_void_ptr;
  napi_value sizeof_uv_lib_t;

  napi_create_int32(env, sizeof(void *), &sizeof_void_ptr);
  napi_create_int32(env, sizeof(uv_lib_t), &sizeof_uv_lib_t);

  napi_property_descriptor descs[] = {
      {"dlopen", 0, dlopen, 0, 0, 0, napi_default, 0},
      {"dlclose", 0, dlclose, 0, 0, 0, napi_default, 0},
      {"dlsym", 0, dlsym, 0, 0, 0, napi_default, 0},
      {"sizeof_void_ptr", 0, 0, 0, 0, sizeof_void_ptr, napi_default, 0},
      {"sizeof_uv_lib_t", 0, 0, 0, 0, sizeof_uv_lib_t, napi_default, 0},
  };
  status = napi_define_properties(env, exports, sizeof(descs) / sizeof(descs[0]), descs);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)