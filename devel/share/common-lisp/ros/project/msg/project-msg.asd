
(cl:in-package :asdf)

(defsystem "project-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "rocket_msg" :depends-on ("_package_rocket_msg"))
    (:file "_package_rocket_msg" :depends-on ("_package"))
  ))