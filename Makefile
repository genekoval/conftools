project := conftools
summary := Helper utilities and conversions for common program configurations

STD := c++20

define common.libs
 ext++
 fmt
 timber
 yaml-cpp
endef

library := lib$(project)
$(library).type := shared
define $(library).libs
 $(common.libs)
endef

install := $(library)
targets := $(install)

test.deps = $(library)
define test.libs
 $(project)
 $(common.libs)
 gtest
 gtest_main
endef

include mkbuild/base.mk
