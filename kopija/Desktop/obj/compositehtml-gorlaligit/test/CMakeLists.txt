add_executable("testComposite" testComposite.cpp ../src/composite.cpp)
target_link_libraries("testComposite" googletest pthread)

add_test(
  NAME testComposite
  COMMAND testComposite
)
