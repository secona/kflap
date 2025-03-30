{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = {nixpkgs, ...}: let
    system = "x86_64-linux";

    pkgs = import nixpkgs {
      inherit system;
    };

    stdenv = pkgs.llvmPackages_20.stdenv;

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
    packages.${system}.default = kflap;

    formatter.${system} = pkgs.alejandra;

    devShells.${system}.default = pkgs.mkShell.override {inherit stdenv;} {
      inputsFrom = [kflap];
    };
  };
}
