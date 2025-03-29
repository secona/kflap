{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { nixpkgs ,... }: let
    system = "x86_64-linux";

    pkgs = import nixpkgs {
      inherit system;
    };

    kflap = pkgs.stdenv.mkDerivation {
      name = "kflap";

      buildInputs = with pkgs; [
        raylib
        meson
        ninja
        pkg-config
        clang-tools
      ];
    };
  in {
    devShells."${system}".default = pkgs.mkShell {
      inputsFrom = [kflap];

      packages = [
        pkgs.libGL

        # X11
        pkgs.xorg.libX11
        pkgs.xorg.libX11.dev
        pkgs.xorg.libXcursor
        pkgs.xorg.libXi
        pkgs.xorg.libXinerama
        pkgs.xorg.libXrandr

        # Wayland
        pkgs.wayland
        pkgs.wayland-protocols
        pkgs.libxkbcommon
        pkgs.glfw-wayland
      ];
    };
  };
}
