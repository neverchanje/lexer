
add_executable(DataOutput DataOutput_test.cc)
target_link_libraries(DataOutput logger ${Boost_LIBRARIES})

add_executable(LoggerTest Logger_test.cc)
target_link_libraries(LoggerTest logger ${Boost_LIBRARIES})

add_executable(TimeValue TimeValue_test.cc)