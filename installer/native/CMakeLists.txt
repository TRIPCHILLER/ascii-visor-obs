add_executable(visor-setup MACOSX_BUNDLE main.cpp)
target_link_libraries(visor-setup PRIVATE Qt6::Widgets)
target_compile_features(visor-setup PRIVATE cxx_std_17)
set_target_properties(visor-setup PROPERTIES
  OUTPUT_NAME "ASCII VISOR Setup"
  MACOSX_BUNDLE_GUI_IDENTIFIER "com.tripchiller.ascii-visor.setup"
  XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "-"
  XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED YES)
