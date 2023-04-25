USER = pket
KEYBOARDS = lily58 kyria sweep totem

# keyboard name
NAME_lily58 = lily58
NAME_kyria = splitkb/kyria
NAME_sweep = ferris/sweep
NAME_totem = totem

all: $(KEYBOARDS)

.PHONY: $(KEYBOARDS)
$(KEYBOARDS):
	# init submodule
	git submodule update --init --recursive
	git submodule update --remote
	# git submodule foreach make git-submodule 

	# cleanup old symlinks
	rm -rf qmk-config-totem/totem/keymaps/$(USER)
	rm -rf qmk_firmware/keyboards/totem
	rm -rf qmk_firmware/keyboards/lily58/keymaps/$(USER)
	rm -rf qmk_firmware/keyboards/splitkb/kyria/keymaps/$(USER)
	rm -rf qmk_firmware/keyboards/ferris/keymaps/$(USER)
	rm -rf qmk_firmware/users/$(USER)

	# add new symlinks
	ln -s $(shell pwd)/qmk-config-totem/totem qmk_firmware/keyboards/totem
	ln -s $(shell pwd)/totem qmk-config-totem/totem/keymaps/$(USER)
	ln -s $(shell pwd)/lily58 qmk_firmware/keyboards/lily58/keymaps/$(USER)
	ln -s $(shell pwd)/kyria qmk_firmware/keyboards/splitkb/kyria/keymaps/$(USER)
	ln -s $(shell pwd)/sweep qmk_firmware/keyboards/ferris/keymaps/$(USER)
	ln -s $(shell pwd)/user qmk_firmware/users/$(USER)

	# run lint check
	# cd qmk_firmware; qmk lint -km $(USER) -kb $(NAME_$@)

	# run build
	make BUILD_DIR=$(shell pwd)/build -j1 -C qmk_firmware $(NAME_$@):$(USER)

	# cleanup symlinks
	rm -rf qmk-config-totem/totem/keymaps/$(USER)
	rm -rf qmk_firmware/keyboards/lily58/keymaps/$(USER)
	rm -rf qmk_firmware/keyboards/splitkb/kyria/keymaps/$(USER)
	rm -rf qmk_firmware/keyboards/ferris/keymaps/$(USER)
	rm -rf qmk_firmware/keyboards/totem
	rm -rf qmk_firmware/users/$(USER)

clean:
	rm -rf qmk-config-totem/totem/keymaps/$(USER)
	rm -rf qmk_firmware/keyboards/lily58/keymaps/$(USER)
	rm -rf qmk_firmware/keyboards/splitkb/kyria/keymaps/$(USER)
	rm -rf qmk_firmware/keyboards/ferris/keymaps/$(USER)
	rm -rf qmk_firmware/keyboards/totem
	rm -rf qmk_firmware/users/$(USER)
	rm -rf ./build/
	rm -rf ./qmk-config-totem/
	rm -rf ./qmk_firmware/

