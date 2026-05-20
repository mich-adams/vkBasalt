{
  pkgs ? import <nixpkgs> { config.allowUnfree = true; },
}:
pkgs.mkShell {
  name = "vkBasalt";
  ENABLE_VKBASALT = 1;
  VKBASALT_CONFIG_FILE = ./config/vkBasalt.conf;
  VKBASALT_LOG_LEVEL = "trace";
  buildInputs = with pkgs; [
    clang
    clang-tools
    pkg-config
    vulkan-loader
    vulkan-headers
    vulkan-validation-layers
    vkmark
    vulkan-tools-lunarg
    spirv-headers
    meson
    glslang
    ninja
    glsl_analyzer
    glslviewer
  ];
}
