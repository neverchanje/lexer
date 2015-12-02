
add_executable(DataOutput DataOutput_test.cc)
target_link_libraries(DataOutput logger ${Boost_LIBRARIES})

add_executable(LoggerTest Logger_test.cc)
target_link_libraries(LoggerTest logger ${Boost_LIBRARIES})

add_executable(TimeValue TimeValue_test.cc)
target_link_libraries(TimeValue logger ${Boost_LIBRARIES})

add_executable(ThisThread ThisThread_test.cc.cc)
target_link_libraries(ThisThread logger ${Boost_LIBRARIES})
