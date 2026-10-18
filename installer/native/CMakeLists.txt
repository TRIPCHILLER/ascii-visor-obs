add_executable(visor-setup MACOSX_BUNDLE main.cpp)
target_link_libraries(visor-setup PRIVATE Qt6::Widgets)
target_compile_features(visor-setup PRIVATE cxx_std_17)
set_target_properties(visor-setup PROPERTIES
  OUTPUT_NAME "ASCII VISOR Setup"
  MACOSX_BUNDLE_GUI_IDENTIFIER "com.tripchiller.ascii-visor.setup"
  XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "-"
  XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED YES)
if(APPLE)
  # OBS's minimal Qt SDK omits macdeployqt. Build the upstream deployment tool
  # against that SDK rather than mixing Qt frameworks from Homebrew.
  set(deploy_source "${CMAKE_CURRENT_BINARY_DIR}/macdeployqt-src")
  foreach(entry IN ITEMS
      "macdeployqt/main.cpp|D7863367A3758F153F36AA88649E57682DB702C29C7DECBC73DB2B6BE76070F5"
      "shared/shared.cpp|2922B37844C50CDFE6653704CF12F49ADC1D75CE12CDA65D9EC23CFCB9E172B0"
      "shared/shared.h|F67C06D429452E52FB07D6B302C9BE80820C0D672D606572B95DEED4FC39AC5A")
    string(REPLACE "|" ";" fields "${entry}")
    list(GET fields 0 path)
    list(GET fields 1 checksum)
    get_filename_component(folder "${deploy_source}/${path}" DIRECTORY)
    file(MAKE_DIRECTORY "${folder}")
    file(DOWNLOAD "https://raw.githubusercontent.com/qt/qtbase/v6.8.3/src/tools/macdeployqt/${path}"
      "${deploy_source}/${path}" EXPECTED_HASH "SHA256=${checksum}" TLS_VERIFY ON)
  endforeach()
  add_executable(visor-macdeployqt "${deploy_source}/macdeployqt/main.cpp" "${deploy_source}/shared/shared.cpp")
  target_compile_features(visor-macdeployqt PRIVATE cxx_std_17)
  target_compile_definitions(visor-macdeployqt PRIVATE QT_NO_FOREACH)
  target_link_libraries(visor-macdeployqt PRIVATE Qt6::Core "-framework CoreFoundation")
  set_target_properties(visor-macdeployqt PROPERTIES MACOSX_BUNDLE FALSE)
endif()
