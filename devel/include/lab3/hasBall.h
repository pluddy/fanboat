// Generated by gencpp from file lab3/hasBall.msg
// DO NOT EDIT!


#ifndef LAB3_MESSAGE_HASBALL_H
#define LAB3_MESSAGE_HASBALL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace lab3
{
template <class ContainerAllocator>
struct hasBall_
{
  typedef hasBall_<ContainerAllocator> Type;

  hasBall_()
    : header()
    , hasBall(false)  {
    }
  hasBall_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , hasBall(false)  {
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint8_t _hasBall_type;
  _hasBall_type hasBall;




  typedef boost::shared_ptr< ::lab3::hasBall_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::lab3::hasBall_<ContainerAllocator> const> ConstPtr;

}; // struct hasBall_

typedef ::lab3::hasBall_<std::allocator<void> > hasBall;

typedef boost::shared_ptr< ::lab3::hasBall > hasBallPtr;
typedef boost::shared_ptr< ::lab3::hasBall const> hasBallConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::lab3::hasBall_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::lab3::hasBall_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace lab3

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'landmark_self_sim': ['/home/odroid/fanboat/src/landmark_self_sim/msg'], 'lab3': ['/home/odroid/fanboat/src/lab3/msg'], 'lab2': ['/home/odroid/fanboat/src/lab2/msg'], 'fanboat_ll': ['/home/odroid/fanboat/src/fanboat_ll/msg'], 'ball_detector': ['/home/odroid/fanboat/src/ball_detector/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::lab3::hasBall_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::lab3::hasBall_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::lab3::hasBall_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::lab3::hasBall_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::lab3::hasBall_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::lab3::hasBall_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::lab3::hasBall_<ContainerAllocator> >
{
  static const char* value()
  {
    return "1d75b3df123427956724c4e8f977e1a5";
  }

  static const char* value(const ::lab3::hasBall_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x1d75b3df12342795ULL;
  static const uint64_t static_value2 = 0x6724c4e8f977e1a5ULL;
};

template<class ContainerAllocator>
struct DataType< ::lab3::hasBall_<ContainerAllocator> >
{
  static const char* value()
  {
    return "lab3/hasBall";
  }

  static const char* value(const ::lab3::hasBall_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::lab3::hasBall_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
\n\
#has the ball?\n\
bool hasBall\n\
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

  static const char* value(const ::lab3::hasBall_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::lab3::hasBall_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.hasBall);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct hasBall_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::lab3::hasBall_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::lab3::hasBall_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "hasBall: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.hasBall);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LAB3_MESSAGE_HASBALL_H
