cmake_minimum_required(VERSION 3.0)

project(cpp_project_eshop)

add_executable(cpp_project_eshop)
target_sources(cpp_project_eshop PRIVATE
    src/user.cpp
    src/owner.cpp
    src/shoppingcart.cpp
    src/buyer.cpp
    src/item.cpp
    src/pen.cpp
    src/pencil.cpp
    src/notebook.cpp
    src/paper.cpp
    src/eshop.cpp
    src/menu.cpp
    src/main.cpp
)
set_property(TARGET cpp_project_eshop PROPERTY CXX_STANDARD 20)

