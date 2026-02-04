{
  pkgs ? import <nixpkgs> { },
}:
pkgs.mkShell {
  name = "vkBasalt";
  buildInputs = with pkgs; [
    clang
    clang-tools
    pkg-config
    vulkan-loader
    vulkan-headers
    vulkan-validation-layers
    spirv-headers
    meson
    glslang
    ninja
    glsl_analyzer
    glslviewer
  ];
}
