include("/home/mdalam/Documents/Coding/QT/Notepad/build/Desktop_Qt_6_11_1_Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/notepad-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "/home/mdalam/Documents/Coding/QT/Notepad/build/Desktop_Qt_6_11_1_Debug/notepad"
    GENERATE_QT_CONF
)
