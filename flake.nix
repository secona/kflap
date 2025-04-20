{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-parts.url = "github:hercules-ci/flake-parts";
  };

  outputs = inputs @ {flake-parts, ...}:
    flake-parts.lib.mkFlake {inherit inputs;} {
      systems = [
        "x86_64-linux"
        "aarch64-linux"
      ];

      perSystem = {pkgs, ...}: let
        stdenv = pkgs.llvmPackages_20.stdenv;
        mkShell = pkgs.mkShell.override {inherit stdenv;};

        kflap = stdenv.mkDerivation {
          name = "kflap";
          version = "0.1.0";
          src = ./.;

          buildInputs = with pkgs; [
            raylib
            meson
            ninja
            pkg-config
            gtest
            clang-tools
            pugixml
          ];

          buildPhase = ''
            meson setup build $src
            meson compile -C build
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp build/kflap $out/bin/
          '';
        };
      in {
        formatter = pkgs.alejandra;

        packages.default = kflap;
        devShells.default = mkShell {
          inputsFrom = [kflap];
        };
      };
    };
}
