let
    pkgs = import <nixpkgs> {};
in
pkgs.mkShell {
    nativeBuildInputs = with pkgs.buildPackages; [
        gdb
        parted
        meson
        ninja
    ];
}