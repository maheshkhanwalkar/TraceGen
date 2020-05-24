project(Exec)

set(SOURCES ExecutableFormat.cpp MachO.cpp Metadata.cpp Metadata.h)
add_library(Exec ${SOURCES})
target_link_libraries(Exec PRIVATE Target)
