; Auto-generated. Do not edit!


(cl:in-package lab3-msg)


;//! \htmlinclude hasBall.msg.html

(cl:defclass <hasBall> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (left
    :reader left
    :initarg :left
    :type cl:integer
    :initform 0)
   (right
    :reader right
    :initarg :right
    :type cl:integer
    :initform 0))
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

(cl:ensure-generic-function 'left-val :lambda-list '(m))
(cl:defmethod left-val ((m <hasBall>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lab3-msg:left-val is deprecated.  Use lab3-msg:left instead.")
  (left m))

(cl:ensure-generic-function 'right-val :lambda-list '(m))
(cl:defmethod right-val ((m <hasBall>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader lab3-msg:right-val is deprecated.  Use lab3-msg:right instead.")
  (right m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <hasBall>) ostream)
  "Serializes a message object of type '<hasBall>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'left)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'right)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'right)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'right)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'right)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <hasBall>) istream)
  "Deserializes a message object of type '<hasBall>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'left)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'right)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'right)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'right)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'right)) (cl:read-byte istream))
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
  "59437992e25943984d5d6ec090addab9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'hasBall)))
  "Returns md5sum for a message object of type 'hasBall"
  "59437992e25943984d5d6ec090addab9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<hasBall>)))
  "Returns full string definition for message of type '<hasBall>"
  (cl:format cl:nil "Header header~%~%#has the ball?~%uint32 left~%uint32 right~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'hasBall)))
  "Returns full string definition for message of type 'hasBall"
  (cl:format cl:nil "Header header~%~%#has the ball?~%uint32 left~%uint32 right~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <hasBall>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <hasBall>))
  "Converts a ROS message object to a list"
  (cl:list 'hasBall
    (cl:cons ':header (header msg))
    (cl:cons ':left (left msg))
    (cl:cons ':right (right msg))
))
