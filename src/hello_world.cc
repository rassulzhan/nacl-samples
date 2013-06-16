/* Copyright (c) 2012 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/** @file hello_world_gles.cc
 * This example demonstrates loading and running a simple 3D openGL ES 2.0
 * application.
 */

//---------------------------------------------------------------------------
// The spinning Cube
//---------------------------------------------------------------------------

#define _USE_MATH_DEFINES 1
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "nacl_io/nacl_io.h"

#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_errors.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_module.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_var.h"
#include "ppapi/c/ppb.h"
#include "ppapi/c/ppb_opengles2.h"
#include "ppapi/c/ppb_var.h"
#include "ppapi/c/ppp.h"
#include "ppapi/c/ppp_graphics_3d.h"
#include "ppapi/c/ppp_instance.h"

#include "ppapi/lib/gl/gles2/gl2ext_ppapi.h"

#include "ppapi_main/ppapi_event.h"
#include "ppapi_main/ppapi_instance3d.h"
#include "ppapi_main/ppapi_main.h"

#include "myinstance.h"

const char *g_TextureData = NULL;
const char *g_VShaderData = NULL;
const char *g_FShaderData = NULL;

bool g_Loaded = false;
bool g_Ready = false;

void* PPAPI_CreateMyInstance(PP_Instance inst, const char *args[]) {
  return static_cast<void*>(new MyInstance(inst, args));
}

void ProcessEvent(PPAPIEvent* event) {
  fprintf(stderr,"processEvent");
  if (event->event_type == PP_INPUTEVENT_TYPE_KEYUP) {
    PPAPIKeyEvent* key = (PPAPIKeyEvent*) event;

  fprintf(stderr,"key:%d\n", key->key_code);
    if (key->key_code == 13) {

    }
  }
}

/*
void PPAPIRender(uint32_t width, uint32_t height) {
  if (!g_Ready) {
    if (g_Loaded) {
      InitProgram();
      g_Ready = true;
    } else {
      return;
    }
  }

  PPAPIEvent* event;
  while (PPAPIEvent* event = PPAPI_AcquireEvent()) {
    ProcessEvent(event);
    PPAPI_ReleaseEvent(event);
  }
*/


void EventHandler()
{
	
  Event* event = NULL;

  fprintf(stderr,"Loaded3");
  fflush(stderr);

  bool cancel = true;
  while (1)
  {
        event = Event_Acquire(&cancel);
  	fprintf(stderr,"Loaded3-1");
  	fflush(stderr);
	if (event != NULL)
	{
		break;
	}
  }
}


const char *LoadData(const char *url) {
  char *buf;
  struct stat stat_buf;

  int fp = open(url, O_RDONLY);
  fstat(fp, &stat_buf);

  int len = static_cast<int>(stat_buf.st_size);
  buf = new char[len + 1];
  int read_size  = read(fp, buf, len);
  buf[len] = 0;
  return buf;
}


PPAPI_MAIN_USE(PPAPI_CreateMyInstance, PPAPI_MAIN_DEFAULT_ARGS)
int ppapi_main(int argc, const char *argv[]) {
  printf("Started main.\n");

  // Mount URL loads to /http
  mount("", "/http", "httpfs", 0, "");

  g_TextureData = LoadData("/http/hello.raw");

  fprintf(stderr,"Loaded2\n");
  g_Loaded = true;
  EventHandler();

