cmake_minimum_required(VERSION 3.0.0)
project(sapitrello VERSION 1.0.0)

include(CTest)
enable_testing()

add_executable(
  sapitrello
  main.c

  app/app.c
  app/database.c

  models/user.c
        models/board.c models/card.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
