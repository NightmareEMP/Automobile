// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vehicle_interface:msg/VehicleFeedback.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "vehicle_interface/msg/detail/vehicle_feedback__struct.h"
#include "vehicle_interface/msg/detail/vehicle_feedback__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool vehicle_interface__msg__vehicle_feedback__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[56];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("vehicle_interface.msg._vehicle_feedback.VehicleFeedback", full_classname_dest, 55) == 0);
  }
  vehicle_interface__msg__VehicleFeedback * ros_message = _ros_message;
  {  // telemetry_seq
    PyObject * field = PyObject_GetAttrString(_pymsg, "telemetry_seq");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->telemetry_seq = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // last_cmd_seq
    PyObject * field = PyObject_GetAttrString(_pymsg, "last_cmd_seq");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->last_cmd_seq = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // stm32_timestamp_ms
    PyObject * field = PyObject_GetAttrString(_pymsg, "stm32_timestamp_ms");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->stm32_timestamp_ms = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // erpm
    PyObject * field = PyObject_GetAttrString(_pymsg, "erpm");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->erpm = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // motor_current_x10
    PyObject * field = PyObject_GetAttrString(_pymsg, "motor_current_x10");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->motor_current_x10 = (int16_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // duty_x1000
    PyObject * field = PyObject_GetAttrString(_pymsg, "duty_x1000");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->duty_x1000 = (int16_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vehicle_interface__msg__vehicle_feedback__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of VehicleFeedback */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vehicle_interface.msg._vehicle_feedback");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "VehicleFeedback");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vehicle_interface__msg__VehicleFeedback * ros_message = (vehicle_interface__msg__VehicleFeedback *)raw_ros_message;
  {  // telemetry_seq
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->telemetry_seq);
    {
      int rc = PyObject_SetAttrString(_pymessage, "telemetry_seq", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // last_cmd_seq
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->last_cmd_seq);
    {
      int rc = PyObject_SetAttrString(_pymessage, "last_cmd_seq", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // stm32_timestamp_ms
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->stm32_timestamp_ms);
    {
      int rc = PyObject_SetAttrString(_pymessage, "stm32_timestamp_ms", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // erpm
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->erpm);
    {
      int rc = PyObject_SetAttrString(_pymessage, "erpm", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // motor_current_x10
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->motor_current_x10);
    {
      int rc = PyObject_SetAttrString(_pymessage, "motor_current_x10", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // duty_x1000
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->duty_x1000);
    {
      int rc = PyObject_SetAttrString(_pymessage, "duty_x1000", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
