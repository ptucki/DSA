
add_executable(${PROJECT_NAME}
  main.cpp
  Examples/Examples.cpp
  Common/Utilities.cpp
  )

include_directories(${PROJECT_NAME} PRIVATE
  .
  Algorithms
  DataStructures
  Examples
  )

install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
  )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}.pdb
  DESTINATION ${CMAKE_INSTALL_PREFIX}
  CONFIGURATIONS Debug
  )
