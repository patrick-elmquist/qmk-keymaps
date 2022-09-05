USER = pket
KEYBOARDS = lily58 kyria sweep

# keymap path
PATH_lily58 = lily58
PATH_kyria = splitkb/kyria
PATH_sweep = ferris

# keyboard name
NAME_lily58 = lily58
NAME_kyria = splitkb/kyria
NAME_sweep = ferris/sweep

all: $(KEYBOARDS)

.PHONY: $(KEYBOARDS)
$(KEYBOARDS):
	# init submodule
	git submodule update --init --recursive
	git submodule foreach git pull origin master
	git submodule foreach make git-submodule 

	# cleanup old symlinks
	rm -rf qmk_firmware/keyboards/$(PATH_$@)/keymaps/$(USER)
	rm -rf qmk_firmware/users/$(USER)

	# add new symlinks
	ln -s $(shell pwd)/user qmk_firmware/users/$(USER)
	ln -s $(shell pwd)/$@ qmk_firmware/keyboards/$(PATH_$@)/keymaps/$(USER)

	# run lint check
	cd qmk_firmware; qmk lint -km $(USER) -kb $(NAME_$@) --strict

	# run build
	make BUILD_DIR=$(shell pwd)/build -j1 -C qmk_firmware $(NAME_$@):$(USER)

	# cleanup symlinks
	rm -rf qmk_firmware/keyboards/$(PATH_$@)/keymaps/$(USER)
	rm -rf qmk_firmware/users/$(USER)

clean:
	rm -rf ./qmk_firmware/
	rm -rf ./build/
	rm -rf qmk_firmware/keyboards/$(PATH_lily58)/keymaps/$(USER)
	rm -rf qmk_firmware/keyboards/$(PATH_kyria)/keymaps/$(USER)
	rm -rf qmk_firmware/keyboards/$(PATH_sweep)/keymaps/$(USER)
	rm -rf qmk_firmware/users/$(USER)

