; Auto-generated. Do not edit!


(cl:in-package lab3-msg)


;//! \htmlinclude hasBall.msg.html

(cl:defclass <hasBall> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (hasBall
    :reader hasBall
    :initarg :hasBall
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass hasBall (<hasBall>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <hasBall>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'hasBall)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name lab3-msg:<hasBall> is deprecated: use lab3-msg:hasBall instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <hasBall>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lab3-msg:header-val is deprecated.  Use lab3-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'hasBall-val :lambda-list '(m))
(cl:defmethod hasBall-val ((m <hasBall>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lab3-msg:hasBall-val is deprecated.  Use lab3-msg:hasBall instead.")
  (hasBall m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <hasBall>) ostream)
  "Serializes a message object of type '<hasBall>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'hasBall) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <hasBall>) istream)
  "Deserializes a message object of type '<hasBall>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:slot-value msg 'hasBall) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<hasBall>)))
  "Returns string type for a message object of type '<hasBall>"
  "lab3/hasBall")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hasBall)))
  "Returns string type for a message object of type 'hasBall"
  "lab3/hasBall")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<hasBall>)))
  "Returns md5sum for a message object of type '<hasBall>"
  "1d75b3df123427956724c4e8f977e1a5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'hasBall)))
  "Returns md5sum for a message object of type 'hasBall"
  "1d75b3df123427956724c4e8f977e1a5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<hasBall>)))
  "Returns full string definition for message of type '<hasBall>"
  (cl:format cl:nil "Header header~%~%#has the ball?~%bool hasBall~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'hasBall)))
  "Returns full string definition for message of type 'hasBall"
  (cl:format cl:nil "Header header~%~%#has the ball?~%bool hasBall~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <hasBall>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <hasBall>))
  "Converts a ROS message object to a list"
  (cl:list 'hasBall
    (cl:cons ':header (header msg))
    (cl:cons ':hasBall (hasBall msg))
))
