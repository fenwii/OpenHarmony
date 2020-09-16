cmake_minimum_required(VERSION 3.16.5)
add_definitions(-D _WIN32)

add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/harfbuzz harfbuzz.out)
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/icu icu.out)
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/zlib zlib.out)
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/libpng libpng.out)
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/libjpeg libjpeg.out)
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/freetype freetype.out)

set(UI_DIR "${PROJECT_SOURCE_DIR}/foundation/graphic/lite/frameworks/ui")

include_directories(${PROJECT_SOURCE_DIR}/third_party/bounds_checking_function/include)
include_directories(${PROJECT_SOURCE_DIR}/third_party/harfbuzz/src)
include_directories(${PROJECT_SOURCE_DIR}/third_party/icu/icu4c/source/common)
include_directories(${PROJECT_SOURCE_DIR}/third_party/icu/icu4c/source/common/unicode)
include_directories(${PROJECT_SOURCE_DIR}/third_party/cJSON)
include_directories(${PROJECT_SOURCE_DIR}/third_party/libjpeg)
include_directories(${PROJECT_SOURCE_DIR}/third_party/libpng)
include_directories(${PROJECT_SOURCE_DIR}/third_party/freetype/include)

file(GLOB SECUREC "${PROJECT_SOURCE_DIR}/third_party/bounds_checking_function/src/*.c")

add_library(ui STATIC
 "${PROJECT_SOURCE_DIR}/third_party/bounds_checking_function/src/memset_s.c"
 "${PROJECT_SOURCE_DIR}/third_party/cJSON/cJSON.c"
 "${UI_DIR}/src/animator/animator.cpp"
 "${UI_DIR}/src/animator/easing_equation.cpp"
 "${UI_DIR}/src/animator/interpolation.cpp"
 "${UI_DIR}/src/common/graphic_startup.cpp"
 "${UI_DIR}/src/common/image.cpp"
 "${UI_DIR}/src/common/input_device_manager.cpp"
 "${UI_DIR}/src/common/screen.cpp"
 "${UI_DIR}/src/common/screen_device_proxy.cpp"
 "${UI_DIR}/src/common/task.cpp"
 "${UI_DIR}/src/common/text.cpp"
 "${UI_DIR}/src/common/typed_text.cpp"
 "${UI_DIR}/src/common/ui_text_language.cpp"
 "${UI_DIR}/src/components/root_view.cpp"
 "${UI_DIR}/src/components/ui_button.cpp"
 "${UI_DIR}/src/components/ui_checkbox.cpp"
 "${UI_DIR}/src/components/ui_label_button.cpp"
 "${UI_DIR}/src/components/ui_radiobutton.cpp"
 "${UI_DIR}/src/components/ui_repeat_button.cpp"
 "${UI_DIR}/src/components/ui_toggle_button.cpp"
 "${UI_DIR}/src/components/ui_canvas.cpp"
 "${UI_DIR}/src/components/ui_axis.cpp"
 "${UI_DIR}/src/components/ui_chart.cpp"
 "${UI_DIR}/src/components/ui_abstract_clock.cpp"
 "${UI_DIR}/src/components/ui_analog_clock.cpp"
 "${UI_DIR}/src/components/ui_digital_clock.cpp"
 "${UI_DIR}/src/components/ui_abstract_scroll.cpp"
 "${UI_DIR}/src/components/ui_view.cpp"
 "${UI_DIR}/src/components/ui_view_group.cpp"
 "${UI_DIR}/src/components/ui_image_animator.cpp"
 "${UI_DIR}/src/components/ui_image_view.cpp"
 "${UI_DIR}/src/components/ui_arc_label.cpp"
 "${UI_DIR}/src/components/ui_label.cpp"
 "${UI_DIR}/src/components/text_adapter.cpp"
 "${UI_DIR}/src/components/ui_list.cpp"
 "${UI_DIR}/src/components/ui_picker.cpp"
 "${UI_DIR}/src/components/ui_time_picker.cpp"
 "${UI_DIR}/src/components/ui_abstract_progress.cpp"
 "${UI_DIR}/src/components/ui_box_progress.cpp"
 "${UI_DIR}/src/components/ui_circle_progress.cpp"
 "${UI_DIR}/src/components/ui_scroll_view.cpp"
 "${UI_DIR}/src/components/ui_slider.cpp"
 "${UI_DIR}/src/components/ui_swipe_view.cpp"
 "${UI_DIR}/src/components/ui_texture_mapper.cpp"
 "${UI_DIR}/src/core/render_manager.cpp"
 "${UI_DIR}/src/core/measure_manager.cpp"
 "${UI_DIR}/src/core/task_manager.cpp"
 "${UI_DIR}/src/default_resource/check_box_res.cpp"
 "${UI_DIR}/src/default_resource/radio_button_res.cpp"
 "${UI_DIR}/src/default_resource/toggle_button_res.cpp"
 "${UI_DIR}/src/dfx/ui_dump_dom_tree.cpp"
 "${UI_DIR}/src/dfx/point_event_injector.cpp"
 "${UI_DIR}/src/dfx/event_injector.cpp"
 "${UI_DIR}/src/dfx/ui_screenshot.cpp"
 "${UI_DIR}/src/dock/input_device.cpp"
 "${UI_DIR}/src/dock/key_input_device.cpp"
 "${UI_DIR}/src/dock/pointer_input_device.cpp"
 "${UI_DIR}/src/dock/input_device.cpp"
 "${UI_DIR}/src/events/event.cpp"
 "${UI_DIR}/src/font/ui_dynamic_font.cpp"
 "${UI_DIR}/src/font/ui_font_allocator.cpp"
 "${UI_DIR}/src/font/ui_font_cache.cpp"
 "${UI_DIR}/src/font/ui_font.cpp"
 "${UI_DIR}/src/font/ui_base_font.cpp"
 "${UI_DIR}/src/font/ui_font_vector.cpp"
 "${UI_DIR}/src/imgdecode/cache_manager.cpp"
 "${UI_DIR}/src/imgdecode/file_img_decoder.cpp"
 "${UI_DIR}/src/layout/flex_layout.cpp"
 "${UI_DIR}/src/layout/grid_layout.cpp"
 "${UI_DIR}/src/layout/list_layout.cpp"
 "${UI_DIR}/src/themes/theme.cpp"
 "${UI_DIR}/src/themes/theme_manager.cpp"
 "${UI_DIR}/src/draw/draw_arc.cpp"
 "${UI_DIR}/src/draw/draw_curve.cpp"
 "${UI_DIR}/src/draw/draw_image.cpp"
 "${UI_DIR}/src/draw/draw_label.cpp"
 "${UI_DIR}/src/draw/draw_line.cpp"
 "${UI_DIR}/src/draw/draw_rect.cpp"
 "${UI_DIR}/src/draw/draw_triangle.cpp"
 "${UI_DIR}/src/draw/draw_utils.cpp"
 "${UI_DIR}/../../hals/src/hal_tick.cpp"
 "${UI_DIR}/../../utils/src/win_file.c"
 "${UI_DIR}/../../utils/src/mc_file.c"
 "${UI_DIR}/../../utils/src/linux_file.c"
 "${UI_DIR}/../../utils/src/color.cpp"
 "${UI_DIR}/../../utils/src/file.c"
 "${UI_DIR}/../../utils/src/geometry2d.cpp"
 "${UI_DIR}/../../utils/src/graphic_math.cpp"
 "${UI_DIR}/../../utils/src/mem_api.cpp"
 "${UI_DIR}/../../utils/src/style.cpp"
 "${UI_DIR}/../../utils/src/sys_info.cpp"
 "${UI_DIR}/../../utils/src/transform.cpp"
 "${UI_DIR}/../../utils/src/version.cpp"
)
target_include_directories(ui PUBLIC
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/interfaces/
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/interfaces/ui
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/interfaces/ui/animator
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/interfaces/ui/dfx
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/interfaces/ui/events
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/interfaces/ui/layout
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/interfaces/ui/themes
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/interfaces/ui/window
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/interfaces/ui/components
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/interfaces/ui/common
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/interfaces/utils
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/interfaces/surface
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/frameworks/ui/include
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/frameworks/ui/include/core
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/frameworks/ui/include/font
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/frameworks/ui/include/draw
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/frameworks/ui/include/imgdecode
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/frameworks/ui/include/default_resource
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/frameworks/ui/include/components
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/utils/include
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/services/ims/include
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/services/wms
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/frameworks/ui/src
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/hals/include
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/services/ims/include
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/huawei_proprietary/include/font
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/config
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/utils/include/adapter/linux
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/utils/include/adapter/mc
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/utils/include/adapter/win
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/huawei_proprietary/include/draw
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/huawei_proprietary/include/appfwk
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/huawei_proprietary/include
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/tools
 ${PROJECT_SOURCE_DIR}/foundation/graphic/lite/tools/graphic_test_framework/include
 )

target_link_libraries(ui PUBLIC harfbuzz)
target_link_libraries(ui PUBLIC icuport)
target_link_libraries(ui PUBLIC libjpeg)
target_link_libraries(ui PUBLIC libpng)
target_link_libraries(ui PUBLIC freetype)
