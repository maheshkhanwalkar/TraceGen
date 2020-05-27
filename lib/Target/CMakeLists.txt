project(Target)

set(SOURCES Target.cpp Type.h X86_64/X86_64.cpp X86_64/Prefix.cpp X86_64/SingleOp.cpp)
add_library(Target ${SOURCES})
