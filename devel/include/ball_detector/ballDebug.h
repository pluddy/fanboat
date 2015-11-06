// Generated by gencpp from file ball_detector/ballDebug.msg
// DO NOT EDIT!


#ifndef BALL_DETECTOR_MESSAGE_BALLDEBUG_H
#define BALL_DETECTOR_MESSAGE_BALLDEBUG_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace ball_detector
{
template <class ContainerAllocator>
struct ballDebug_
{
  typedef ballDebug_<ContainerAllocator> Type;

  ballDebug_()
    : sendDebugImages(false)
    , sendDebugTimes(false)  {
    }
  ballDebug_(const ContainerAllocator& _alloc)
    : sendDebugImages(false)
    , sendDebugTimes(false)  {
    }



   typedef uint8_t _sendDebugImages_type;
  _sendDebugImages_type sendDebugImages;

   typedef uint8_t _sendDebugTimes_type;
  _sendDebugTimes_type sendDebugTimes;




  typedef boost::shared_ptr< ::ball_detector::ballDebug_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ball_detector::ballDebug_<ContainerAllocator> const> ConstPtr;

}; // struct ballDebug_

typedef ::ball_detector::ballDebug_<std::allocator<void> > ballDebug;

typedef boost::shared_ptr< ::ball_detector::ballDebug > ballDebugPtr;
typedef boost::shared_ptr< ::ball_detector::ballDebug const> ballDebugConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ball_detector::ballDebug_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ball_detector::ballDebug_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace ball_detector

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'ball_detector': ['/media/psf/Home/Documents/GitHub/fanboat/src/lab3/ball_detector/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::ball_detector::ballDebug_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ball_detector::ballDebug_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ball_detector::ballDebug_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ball_detector::ballDebug_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ball_detector::ballDebug_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ball_detector::ballDebug_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ball_detector::ballDebug_<ContainerAllocator> >
{
  static const char* value()
  {
    return "f0dbcd340db400b8721875b15029f990";
  }

  static const char* value(const ::ball_detector::ballDebug_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xf0dbcd340db400b8ULL;
  static const uint64_t static_value2 = 0x721875b15029f990ULL;
};

template<class ContainerAllocator>
struct DataType< ::ball_detector::ballDebug_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ball_detector/ballDebug";
  }

  static const char* value(const ::ball_detector::ballDebug_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ball_detector::ballDebug_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool sendDebugImages\n\
bool sendDebugTimes \n\
";
  }

  static const char* value(const ::ball_detector::ballDebug_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ball_detector::ballDebug_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.sendDebugImages);
      stream.next(m.sendDebugTimes);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct ballDebug_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ball_detector::ballDebug_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ball_detector::ballDebug_<ContainerAllocator>& v)
  {
    s << indent << "sendDebugImages: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.sendDebugImages);
    s << indent << "sendDebugTimes: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.sendDebugTimes);
  }
};

} // namespace message_operations
} // namespace ros

#endif // BALL_DETECTOR_MESSAGE_BALLDEBUG_H
