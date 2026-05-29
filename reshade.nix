{
  lib,
  stdenvNoCC,
  fetchFromGitHub,
}:
stdenvNoCC.mkDerivation {
  name = "reshade";
  src = fetchFromGitHub {
    owner = "crosire";
    repo = "reshade";
    rev = "v6.7.3";
    hash = "sha256-fFPSFkBM1lP2y1H0MGPLpZRffs9ETlbEPivv2bJ4Wmo=";
  };

  installPhase = ''
    mkdir -p $out
    cp $src/source/effect_* $out/
  '';

}
