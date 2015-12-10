
(cl:in-package :asdf)

(defsystem "lab3-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "ballLandInfo" :depends-on ("_package_ballLandInfo"))
    (:file "_package_ballLandInfo" :depends-on ("_package"))
    (:file "hasBall" :depends-on ("_package_hasBall"))
    (:file "_package_hasBall" :depends-on ("_package"))
  ))