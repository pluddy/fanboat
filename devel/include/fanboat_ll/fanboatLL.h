// Generated by gencpp from file fanboat_ll/fanboatLL.msg
// DO NOT EDIT!


#ifndef FANBOAT_LL_MESSAGE_FANBOATLL_H
#define FANBOAT_LL_MESSAGE_FANBOATLL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace fanboat_ll
{
template <class ContainerAllocator>
struct fanboatLL_
{
  typedef fanboatLL_<ContainerAllocator> Type;

  fanboatLL_()
    : header()
    , roll(0.0)
    , pitch(0.0)
    , yaw(0.0)
    , a0(0)
    , a1(0)
    , a2(0)
    , a3(0)
    , a6(0)
    , a7(0)
    , leftMotorSetting(0.0)
    , rightMotorSetting(0.0)  {
    }
  fanboatLL_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , roll(0.0)
    , pitch(0.0)
    , yaw(0.0)
    , a0(0)
    , a1(0)
    , a2(0)
    , a3(0)
    , a6(0)
    , a7(0)
    , leftMotorSetting(0.0)
    , rightMotorSetting(0.0)  {
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef double _roll_type;
  _roll_type roll;

   typedef double _pitch_type;
  _pitch_type pitch;

   typedef double _yaw_type;
  _yaw_type yaw;

   typedef int16_t _a0_type;
  _a0_type a0;

   typedef int16_t _a1_type;
  _a1_type a1;

   typedef int16_t _a2_type;
  _a2_type a2;

   typedef int16_t _a3_type;
  _a3_type a3;

   typedef int16_t _a6_type;
  _a6_type a6;

   typedef int16_t _a7_type;
  _a7_type a7;

   typedef double _leftMotorSetting_type;
  _leftMotorSetting_type leftMotorSetting;

   typedef double _rightMotorSetting_type;
  _rightMotorSetting_type rightMotorSetting;




  typedef boost::shared_ptr< ::fanboat_ll::fanboatLL_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::fanboat_ll::fanboatLL_<ContainerAllocator> const> ConstPtr;

}; // struct fanboatLL_

typedef ::fanboat_ll::fanboatLL_<std::allocator<void> > fanboatLL;

typedef boost::shared_ptr< ::fanboat_ll::fanboatLL > fanboatLLPtr;
typedef boost::shared_ptr< ::fanboat_ll::fanboatLL const> fanboatLLConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::fanboat_ll::fanboatLL_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::fanboat_ll::fanboatLL_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace fanboat_ll

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'fanboat_ll': ['/home/odroid/fanboat/src/fanboat_ll/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::fanboat_ll::fanboatLL_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::fanboat_ll::fanboatLL_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::fanboat_ll::fanboatLL_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::fanboat_ll::fanboatLL_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::fanboat_ll::fanboatLL_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::fanboat_ll::fanboatLL_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::fanboat_ll::fanboatLL_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e72d17966498547a839eeacf572bcdb2";
  }

  static const char* value(const ::fanboat_ll::fanboatLL_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe72d17966498547aULL;
  static const uint64_t static_value2 = 0x839eeacf572bcdb2ULL;
};

template<class ContainerAllocator>
struct DataType< ::fanboat_ll::fanboatLL_<ContainerAllocator> >
{
  static const char* value()
  {
    return "fanboat_ll/fanboatLL";
  }

  static const char* value(const ::fanboat_ll::fanboatLL_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::fanboat_ll::fanboatLL_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
\n\
#Pitch roll and yaw in degrees\n\
float64 roll\n\
float64 pitch\n\
float64 yaw\n\
\n\
#raw 10-it ADC readings\n\
int16 a0\n\
int16 a1\n\
int16 a2\n\
int16 a3\n\
int16 a6\n\
int16 a7\n\
\n\
#Current settings of the motors [-1.0,1.0]\n\
float64 leftMotorSetting\n\
float64 rightMotorSetting\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::fanboat_ll::fanboatLL_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::fanboat_ll::fanboatLL_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.roll);
      stream.next(m.pitch);
      stream.next(m.yaw);
      stream.next(m.a0);
      stream.next(m.a1);
      stream.next(m.a2);
      stream.next(m.a3);
      stream.next(m.a6);
      stream.next(m.a7);
      stream.next(m.leftMotorSetting);
      stream.next(m.rightMotorSetting);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct fanboatLL_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::fanboat_ll::fanboatLL_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::fanboat_ll::fanboatLL_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "roll: ";
    Printer<double>::stream(s, indent + "  ", v.roll);
    s << indent << "pitch: ";
    Printer<double>::stream(s, indent + "  ", v.pitch);
    s << indent << "yaw: ";
    Printer<double>::stream(s, indent + "  ", v.yaw);
    s << indent << "a0: ";
    Printer<int16_t>::stream(s, indent + "  ", v.a0);
    s << indent << "a1: ";
    Printer<int16_t>::stream(s, indent + "  ", v.a1);
    s << indent << "a2: ";
    Printer<int16_t>::stream(s, indent + "  ", v.a2);
    s << indent << "a3: ";
    Printer<int16_t>::stream(s, indent + "  ", v.a3);
    s << indent << "a6: ";
    Printer<int16_t>::stream(s, indent + "  ", v.a6);
    s << indent << "a7: ";
    Printer<int16_t>::stream(s, indent + "  ", v.a7);
    s << indent << "leftMotorSetting: ";
    Printer<double>::stream(s, indent + "  ", v.leftMotorSetting);
    s << indent << "rightMotorSetting: ";
    Printer<double>::stream(s, indent + "  ", v.rightMotorSetting);
  }
};

} // namespace message_operations
} // namespace ros

#endif // FANBOAT_LL_MESSAGE_FANBOATLL_H
