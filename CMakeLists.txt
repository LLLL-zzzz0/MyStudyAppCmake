cmake_minimum_required(VERSION 3.16)

project(myStudyApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets Sql REQUIRED)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/UI
)

# Windows 资源文件
if(WIN32)
    set(WIN_RESOURCES
        logo.rc
    )
endif()

set(SOURCES
    Controller/applicationcontroller.cpp
    Controller/changepwdcontroller.cpp
    Controller/enrollcontroller.cpp
    Controller/logincontroller.cpp
    Controller/newwordcontroller.cpp
    Controller/reviewcontroller.cpp
    Controller/studycentercontroller.cpp
    Controller/studywordcontroller.cpp
    Controller/userspacecontroller.cpp
    Models/databasemanager.cpp
    Models/usermodel.cpp
    Models/wordmodel.cpp
    View/changepwd.cpp
    View/enroll.cpp
    View/login.cpp
    View/mywidght.cpp
    View/newWord.cpp
    View/review.cpp
    View/studyCenter.cpp
    View/studyWord.cpp
    View/userSpace.cpp
    main.cpp
)

set(HEADERS
    Controller/applicationcontroller.h
    Controller/changepwdcontroller.h
    Controller/enrollcontroller.h
    Controller/logincontroller.h
    Controller/newwordcontroller.h
    Controller/reviewcontroller.h
    Controller/studycentercontroller.h
    Controller/studywordcontroller.h
    Controller/userspacecontroller.h
    Controller/viewData.h
    Models/appdata.h
    Models/databaseManager.h
    Models/usermodel.h
    Models/wordmodel.h
    View/changePwd.h
    View/enroll.h
    View/login.h
    View/mywidght.h
    View/newWord.h
    View/review.h
    View/studyCenter.h
    View/studyWord.h
    View/userSpace.h
)

# 定义UI文件
set(FORMS
    UI/changePwd.ui
    UI/enroll.ui
    UI/login.ui
    UI/newWord.ui
    UI/review.ui
    UI/studyCenter.ui
    UI/studyWord.ui
    UI/userSpace.ui
)

set(RESOURCES
    pic.qrc
    qss.qrc
)

if(WIN32)
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES} ${WIN_RESOURCES})
endif()

# 包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/View
    ${CMAKE_CURRENT_SOURCE_DIR}/Models
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller
    ${CMAKE_CURRENT_SOURCE_DIR}/UI
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Sql
)

# 设置可执行文件图标（Windows平台）
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
