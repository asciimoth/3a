with import <nixpkgs> {};
{
     testEnv = stdenv.mkDerivation {
       name = "3a_build";
       buildInputs = [stdenv ncurses];
     };
}
