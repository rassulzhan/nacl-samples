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

#include "custom_events.h"
#include "myinstance.h"

// Convert a pepper inputevent modifier value into a
// custom event modifier.
unsigned int ConvertEventModifier(uint32_t pp_modifier) {
  unsigned int custom_modifier = 0;
  if (pp_modifier & PP_INPUTEVENT_MODIFIER_SHIFTKEY) {
    custom_modifier |= kShiftKeyModifier;
  }
  if (pp_modifier & PP_INPUTEVENT_MODIFIER_CONTROLKEY) {
    custom_modifier |= kControlKeyModifier;
  }
  if (pp_modifier & PP_INPUTEVENT_MODIFIER_ALTKEY) {
    custom_modifier |= kAltKeyModifier;
  }
  if (pp_modifier & PP_INPUTEVENT_MODIFIER_METAKEY) {
    custom_modifier |= kMetaKeyModifer;
  }
  if (pp_modifier & PP_INPUTEVENT_MODIFIER_ISKEYPAD) {
    custom_modifier |= kKeyPadModifier;
  }
  if (pp_modifier & PP_INPUTEVENT_MODIFIER_ISAUTOREPEAT) {
    custom_modifier |= kAutoRepeatModifier;
  }
  if (pp_modifier & PP_INPUTEVENT_MODIFIER_LEFTBUTTONDOWN) {
    custom_modifier |= kLeftButtonModifier;
  }
  if (pp_modifier & PP_INPUTEVENT_MODIFIER_MIDDLEBUTTONDOWN) {
    custom_modifier |= kMiddleButtonModifier;
  }
  if (pp_modifier & PP_INPUTEVENT_MODIFIER_RIGHTBUTTONDOWN) {
    custom_modifier |= kRightButtonModifier;
  }
  if (pp_modifier & PP_INPUTEVENT_MODIFIER_CAPSLOCKKEY) {
    custom_modifier |= kCapsLockModifier;
  }
  if (pp_modifier & PP_INPUTEVENT_MODIFIER_NUMLOCKKEY) {
    custom_modifier |= kNumLockModifier;
  }
  return custom_modifier;
}


MyInstance::MyInstance(PP_Instance instance, const char *args[])
    : PPAPIInstance(instance, args)
      {
//  glInitializePPAPI(pp::Module::Get()->get_browser_interface());
}

bool MyInstance::HandleInputEvent(const pp::InputEvent& event)
{
	Event* event_ptr = NULL;
	bool ret = false;
	ret = PPAPIInstance::HandleInputEvent(event);
	pp::KeyboardInputEvent key_event(event);

	fprintf(stderr,"HandelInputEvent");
	fflush(stderr);
	event_ptr = new KeyEvent(
              ConvertEventModifier(key_event.GetModifiers()),
              key_event.GetKeyCode(), key_event.GetTimeStamp(),
              key_event.GetCharacterText().DebugString());
	event_queue_.Push(event_ptr);
	return ret;
}


Event* MyInstance::AcquireEvent(bool* was_queue_cancelled)
{
    Event* event = NULL;
    QueueGetResult result = event_queue_.GetItem(&event, kWait);
    if (result == kQueueWasCancelled) {
      *was_queue_cancelled = true;
      return NULL;
    }
    *was_queue_cancelled = false;
    return event;
}

Event* Event_Acquire(bool* was_queue_cancelled)
{
    return static_cast<MyInstance*>(PPAPI_GetInstanceObject())->AcquireEvent(was_queue_cancelled);
}
