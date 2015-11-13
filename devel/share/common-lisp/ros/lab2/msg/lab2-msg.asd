
(cl:in-package :asdf)

(defsystem "lab2-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "sensor_msg" :depends-on ("_package_sensor_msg"))
    (:file "_package_sensor_msg" :depends-on ("_package"))
    (:file "angle_msg" :depends-on ("_package_angle_msg"))
    (:file "_package_angle_msg" :depends-on ("_package"))
  ))