set(LOGGER_LIBRARY_SOURCES
    cool_logger.h
    cool_logger.cpp
)

# Add a shared library target
add_library(logger_lib SHARED ${LOGGER_LIBRARY_SOURCES})