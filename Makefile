all: kyria lily58

kb-lily58:
	git submodule update --init --recursive

	rm -rf qmk_firmware/keyboards/lily58/keymaps/pket
	rm -rf qmk_firmware/users/pket

	ln -s $(shell pwd)/lily58 qmk_firmware/keyboards/lily58/keymaps/pket
	ln -s $(shell pwd)/user qmk_firmware/users/pket

	cd qmk_firmware; qmk lint -km pket -kb lily58 --strict

	make BUILD_DIR=$(shell pwd) -j1 -C qmk_firmware lily58:pket

	rm -rf qmk_firmware/keyboards/lily58/keymaps/pket
	rm -rf qmk_firmware/users/pket

kb-kyria:
	git submodule update --init --recursive

	rm -rf qmk_firmware/keyboards/splitkb/kyria/keymaps/pket
	rm -rf qmk_firmware/users/pket

	ln -s $(shell pwd)/kyria qmk_firmware/keyboards/splitkb/kyria/keymaps/pket
	ln -s $(shell pwd)/user qmk_firmware/users/pket

	cd qmk_firmware; qmk lint -km pket -kb splitkb/kyria --strict

	make BUILD_DIR=$(shell pwd) -j1 -C qmk_firmware splitkb/kyria:pket

	rm -rf qmk_firmware/keyboards/splitkb/kyria/keymaps/pket
	rm -rf qmk_firmware/users/pket

clean:
	rm -rf obj_*
	rm -f *.elf
	rm -f *.map
	rm -f *.hex

deep-clean: clean
	cd qmk_firmware; make clean
