; Auto-generated. Do not edit!


(cl:in-package project-msg)


;//! \htmlinclude angle.msg.html

(cl:defclass <angle> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (angle
    :reader angle
    :initarg :angle
    :type cl:float
    :initform 0.0)
   (state
    :reader state
    :initarg :state
    :type cl:integer
    :initform 0)
   (forward
    :reader forward
    :initarg :forward
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass angle (<angle>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <angle>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'angle)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name project-msg:<angle> is deprecated: use project-msg:angle instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <angle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader project-msg:header-val is deprecated.  Use project-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <angle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader project-msg:angle-val is deprecated.  Use project-msg:angle instead.")
  (angle m))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <angle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader project-msg:state-val is deprecated.  Use project-msg:state instead.")
  (state m))

(cl:ensure-generic-function 'forward-val :lambda-list '(m))
(cl:defmethod forward-val ((m <angle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader project-msg:forward-val is deprecated.  Use project-msg:forward instead.")
  (forward m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <angle>) ostream)
  "Serializes a message object of type '<angle>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'forward) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <angle>) istream)
  "Deserializes a message object of type '<angle>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'state)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'forward) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<angle>)))
  "Returns string type for a message object of type '<angle>"
  "project/angle")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'angle)))
  "Returns string type for a message object of type 'angle"
  "project/angle")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<angle>)))
  "Returns md5sum for a message object of type '<angle>"
  "885f619283918674d5c6ac31b80b0c28")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'angle)))
  "Returns md5sum for a message object of type 'angle"
  "885f619283918674d5c6ac31b80b0c28")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<angle>)))
  "Returns full string definition for message of type '<angle>"
  (cl:format cl:nil "Header header~%~%#Angle (-180.0, 180, 0 is forward)~%float64 angle~%~%#State is the current defensive state~%uint32 state~%~%#Forward~%bool forward~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'angle)))
  "Returns full string definition for message of type 'angle"
  (cl:format cl:nil "Header header~%~%#Angle (-180.0, 180, 0 is forward)~%float64 angle~%~%#State is the current defensive state~%uint32 state~%~%#Forward~%bool forward~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <angle>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     8
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <angle>))
  "Converts a ROS message object to a list"
  (cl:list 'angle
    (cl:cons ':header (header msg))
    (cl:cons ':angle (angle msg))
    (cl:cons ':state (state msg))
    (cl:cons ':forward (forward msg))
))
