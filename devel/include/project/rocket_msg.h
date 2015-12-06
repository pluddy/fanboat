// Generated by gencpp from file project/rocket_msg.msg
// DO NOT EDIT!


#ifndef PROJECT_MESSAGE_ROCKET_MSG_H
#define PROJECT_MESSAGE_ROCKET_MSG_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace project
{
template <class ContainerAllocator>
struct rocket_msg_
{
  typedef rocket_msg_<ContainerAllocator> Type;

  rocket_msg_()
    : header()
    , angle(0.0)
    , fire(0)
    , stop(0)  {
    }
  rocket_msg_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , angle(0.0)
    , fire(0)
    , stop(0)  {
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef double _angle_type;
  _angle_type angle;

   typedef uint32_t _fire_type;
  _fire_type fire;

   typedef uint32_t _stop_type;
  _stop_type stop;




  typedef boost::shared_ptr< ::project::rocket_msg_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::project::rocket_msg_<ContainerAllocator> const> ConstPtr;

}; // struct rocket_msg_

typedef ::project::rocket_msg_<std::allocator<void> > rocket_msg;

typedef boost::shared_ptr< ::project::rocket_msg > rocket_msgPtr;
typedef boost::shared_ptr< ::project::rocket_msg const> rocket_msgConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::project::rocket_msg_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::project::rocket_msg_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace project

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'project': ['/home/odroid/fanboat/src/project/msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::project::rocket_msg_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::project::rocket_msg_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::project::rocket_msg_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::project::rocket_msg_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::project::rocket_msg_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::project::rocket_msg_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::project::rocket_msg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d208c55ccb41466fbd6177970c3286aa";
  }

  static const char* value(const ::project::rocket_msg_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd208c55ccb41466fULL;
  static const uint64_t static_value2 = 0xbd6177970c3286aaULL;
};

template<class ContainerAllocator>
struct DataType< ::project::rocket_msg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "project/rocket_msg";
  }

  static const char* value(const ::project::rocket_msg_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::project::rocket_msg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
\n\
float64 angle\n\
uint32 fire\n\
uint32 stop\n\
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

  static const char* value(const ::project::rocket_msg_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::project::rocket_msg_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.angle);
      stream.next(m.fire);
      stream.next(m.stop);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct rocket_msg_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::project::rocket_msg_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::project::rocket_msg_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "angle: ";
    Printer<double>::stream(s, indent + "  ", v.angle);
    s << indent << "fire: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.fire);
    s << indent << "stop: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.stop);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PROJECT_MESSAGE_ROCKET_MSG_H
