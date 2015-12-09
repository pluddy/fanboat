; Auto-generated. Do not edit!


(cl:in-package project-msg)


;//! \htmlinclude rocket_msg.msg.html

(cl:defclass <rocket_msg> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (timesFired
    :reader timesFired
    :initarg :timesFired
    :type cl:integer
    :initform 0)
   (state
    :reader state
    :initarg :state
    :type cl:integer
    :initform 0))
)

(cl:defclass rocket_msg (<rocket_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <rocket_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'rocket_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name project-msg:<rocket_msg> is deprecated: use project-msg:rocket_msg instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <rocket_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader project-msg:header-val is deprecated.  Use project-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'timesFired-val :lambda-list '(m))
(cl:defmethod timesFired-val ((m <rocket_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader project-msg:timesFired-val is deprecated.  Use project-msg:timesFired instead.")
  (timesFired m))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <rocket_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader project-msg:state-val is deprecated.  Use project-msg:state instead.")
  (state m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <rocket_msg>) ostream)
  "Serializes a message object of type '<rocket_msg>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'timesFired)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'timesFired)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'timesFired)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'timesFired)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'state)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <rocket_msg>) istream)
  "Deserializes a message object of type '<rocket_msg>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'timesFired)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'timesFired)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'timesFired)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'timesFired)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'state)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<rocket_msg>)))
  "Returns string type for a message object of type '<rocket_msg>"
  "project/rocket_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'rocket_msg)))
  "Returns string type for a message object of type 'rocket_msg"
  "project/rocket_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<rocket_msg>)))
  "Returns md5sum for a message object of type '<rocket_msg>"
  "0fa498ef31fff6ad26b97bae2a8ea2c4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'rocket_msg)))
  "Returns md5sum for a message object of type 'rocket_msg"
  "0fa498ef31fff6ad26b97bae2a8ea2c4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<rocket_msg>)))
  "Returns full string definition for message of type '<rocket_msg>"
  (cl:format cl:nil "Header header~%~%uint32 timesFired~%uint32 state~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'rocket_msg)))
  "Returns full string definition for message of type 'rocket_msg"
  (cl:format cl:nil "Header header~%~%uint32 timesFired~%uint32 state~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <rocket_msg>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <rocket_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'rocket_msg
    (cl:cons ':header (header msg))
    (cl:cons ':timesFired (timesFired msg))
    (cl:cons ':state (state msg))
))
