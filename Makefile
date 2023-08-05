update-pkgs:
	sudo apt update
	sudo apt upgrade

install-llvm:
	sudo apt install llvm-15 clang-15 sudo apt-get install gcc-multilib

deps: update-pkgs install-llvm