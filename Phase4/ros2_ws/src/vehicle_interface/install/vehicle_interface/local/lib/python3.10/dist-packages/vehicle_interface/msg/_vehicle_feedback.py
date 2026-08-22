# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vehicle_interface:msg/VehicleFeedback.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_VehicleFeedback(type):
    """Metaclass of message 'VehicleFeedback'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('vehicle_interface')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vehicle_interface.msg.VehicleFeedback')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__vehicle_feedback
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__vehicle_feedback
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__vehicle_feedback
            cls._TYPE_SUPPORT = module.type_support_msg__msg__vehicle_feedback
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__vehicle_feedback

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class VehicleFeedback(metaclass=Metaclass_VehicleFeedback):
    """Message class 'VehicleFeedback'."""

    __slots__ = [
        '_telemetry_seq',
        '_last_cmd_seq',
        '_stm32_timestamp_ms',
        '_erpm',
        '_motor_current_x10',
        '_duty_x1000',
    ]

    _fields_and_field_types = {
        'telemetry_seq': 'uint16',
        'last_cmd_seq': 'uint16',
        'stm32_timestamp_ms': 'uint32',
        'erpm': 'int32',
        'motor_current_x10': 'int16',
        'duty_x1000': 'int16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.telemetry_seq = kwargs.get('telemetry_seq', int())
        self.last_cmd_seq = kwargs.get('last_cmd_seq', int())
        self.stm32_timestamp_ms = kwargs.get('stm32_timestamp_ms', int())
        self.erpm = kwargs.get('erpm', int())
        self.motor_current_x10 = kwargs.get('motor_current_x10', int())
        self.duty_x1000 = kwargs.get('duty_x1000', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.telemetry_seq != other.telemetry_seq:
            return False
        if self.last_cmd_seq != other.last_cmd_seq:
            return False
        if self.stm32_timestamp_ms != other.stm32_timestamp_ms:
            return False
        if self.erpm != other.erpm:
            return False
        if self.motor_current_x10 != other.motor_current_x10:
            return False
        if self.duty_x1000 != other.duty_x1000:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def telemetry_seq(self):
        """Message field 'telemetry_seq'."""
        return self._telemetry_seq

    @telemetry_seq.setter
    def telemetry_seq(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'telemetry_seq' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'telemetry_seq' field must be an unsigned integer in [0, 65535]"
        self._telemetry_seq = value

    @builtins.property
    def last_cmd_seq(self):
        """Message field 'last_cmd_seq'."""
        return self._last_cmd_seq

    @last_cmd_seq.setter
    def last_cmd_seq(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'last_cmd_seq' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'last_cmd_seq' field must be an unsigned integer in [0, 65535]"
        self._last_cmd_seq = value

    @builtins.property
    def stm32_timestamp_ms(self):
        """Message field 'stm32_timestamp_ms'."""
        return self._stm32_timestamp_ms

    @stm32_timestamp_ms.setter
    def stm32_timestamp_ms(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'stm32_timestamp_ms' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'stm32_timestamp_ms' field must be an unsigned integer in [0, 4294967295]"
        self._stm32_timestamp_ms = value

    @builtins.property
    def erpm(self):
        """Message field 'erpm'."""
        return self._erpm

    @erpm.setter
    def erpm(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'erpm' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'erpm' field must be an integer in [-2147483648, 2147483647]"
        self._erpm = value

    @builtins.property
    def motor_current_x10(self):
        """Message field 'motor_current_x10'."""
        return self._motor_current_x10

    @motor_current_x10.setter
    def motor_current_x10(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'motor_current_x10' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'motor_current_x10' field must be an integer in [-32768, 32767]"
        self._motor_current_x10 = value

    @builtins.property
    def duty_x1000(self):
        """Message field 'duty_x1000'."""
        return self._duty_x1000

    @duty_x1000.setter
    def duty_x1000(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'duty_x1000' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'duty_x1000' field must be an integer in [-32768, 32767]"
        self._duty_x1000 = value
