project := conftools
summary := Helper utilities and conversions for common program configurations

STD := c++20

common.libs := ext++ fmt timber yaml-cpp

library := lib$(project)
$(library).type := shared
$(library).libs := $(common.libs)

install := $(library)
targets := $(install)

test.deps = $(library)
test.libs := $(project) $(common.libs) gtest gtest_main

files := $(include) $(src) Makefile VERSION

include mkbuild/base.mk
