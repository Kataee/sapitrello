cmake_minimum_required(VERSION 3.0.0)
project(sapitrello VERSION 1.0.0)

include(CTest)
enable_testing()

add_executable(
  sapitrello
  main.c

  app/app.c
  app/database.c

  commands/add.c
  commands/assign.c
  commands/create.c
  commands/delete.c
  commands/describe.c
  commands/exit.c
  commands/save.c
  commands/select.c
  commands/show.c
  commands/update.c
  commands/use.c

  models/user.c
  models/board.c
  models/card.c

  parser/stql.c

  utils/commandutils.c
  utils/errors.c
  utils/stringutils.c
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
