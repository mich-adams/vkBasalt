{
  lib,
  stdenv,
  glslang,
  meson,
  ninja,
  pkg-config,
  libX11,
  spirv-headers,
  vulkan-headers,
  stb,
  pkgsi686Linux,
  callPackage,
  reshade-lib ? (callPackage ./reshade.nix { }),
  vkbasalt32 ? pkgsi686Linux.callPackage ./default.nix { },
}:
stdenv.mkDerivation (finalAttrs: {
  pname = "vkbasalt";
  version = "0.4.0.0";

  src = ./.;

  nativeBuildInputs = [
    glslang
    meson
    ninja
    pkg-config
    stb
  ];
  buildInputs = [
    libX11
    spirv-headers
    vulkan-headers
    stb
    reshade-lib
  ];
  mesonFlags = [ "-Dappend_libdir_vkbasalt=true" ];

  postFetch = ''
    cp -f ${reshade-lib}/* src/reshade/
  '';

  postInstall = lib.optionalString (stdenv.hostPlatform.system == "x86_64-linux") ''
    install -Dm 644 $src/config/vkBasalt.conf $out/share/vkBasalt/vkBasalt.conf
    # Include 32bit layer in 64bit build
    ln -s ${vkbasalt32}/share/vulkan/implicit_layer.d/vkBasalt.json \
      "$out/share/vulkan/implicit_layer.d/vkBasalt32.json"
  '';

  # We need to give the different layers separate names or else the loader
  # might try the 32-bit one first, fail and not attempt to load the 64-bit
  # layer under the same name.
  postFixup = ''
    substituteInPlace "$out/share/vulkan/implicit_layer.d/vkBasalt.json" \
      --replace-fail "VK_LAYER_VKBASALT_post_processing" "VK_LAYER_VKBASALT_post_processing_${toString stdenv.hostPlatform.parsed.cpu.bits}"
  '';

  meta = {
    description = "Vulkan post processing layer for Linux";
    homepage = "https://github.com/DadSchoorse/vkBasalt";
    license = lib.licenses.zlib;
    maintainers = with lib.maintainers; [ ];
    platforms = lib.platforms.linux;
  };
})
