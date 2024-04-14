BUILD_DIR := build
SRC_DIR := .

CMAKE := cmake
CMAKEFLAGS = -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

CARGO := cargo
CARGOCHAN := +nightly
CARGOFLAGS := -Zunstable-options

# run with DEBUG=1 to use debug configuration

ifeq "$(DEBUG)" "1"
CMAKEFLAGS += -DCMAKE_BUILD_TYPE=Debug
else
CMAKEFLAGS += -DCMAKE_BUILD_TYPE=Release
endif

ifneq "$(DEBUG)" "1"
CARGOFLAGS += --release
endif

.PHONY: compiler frontend clean predist


#
# All targets
#
all: compiler frontend


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


#
# Copy TexLive distribution
#

TEXLIVE_SRC := $(SRC_DIR)/vendor/tex
TEXLIVE_DST := $(BUILD_DIR)/vendor/tex

$(TEXLIVE_DST): $(TEXLIVE_SRC)
	mkdir -p $(TEXLIVE_DST)
	cp -r $(TEXLIVE_SRC)/* $(TEXLIVE_DST)


#
# Copy scripts
#

$(BUILD_DIR)/texpdfc.sh: $(SRC_DIR)/compiler/texpdfc.sh | $(BUILD_DIR)
	cp $< $@

$(BUILD_DIR)/start.sh: $(SRC_DIR)/start.sh | $(BUILD_DIR)
	cp $< $@


#
# Compile the TeX compilation CLI
#

COMPILER_TOML := $(SRC_DIR)/compiler/Cargo.toml

compiler: $(COMPILER_TOML) $(TEXLIVE_DST) $(BUILD_DIR)/texpdfc.sh
	$(CARGO) $(CARGOCHAN) build $(CARGOFLAGS) --manifest-path=$(COMPILER_TOML) --target-dir=$(BUILD_DIR)/_$@ --out-dir=$(BUILD_DIR)


#
# Compile the TexEdit GUI frontend
#

FRONTEND_CMAKELISTS := $(SRC_DIR)/frontend/CMakeLists.txt

frontend: $(FRONTEND_CMAKELISTS) $(BUILD_DIR)/start.sh
	$(CMAKE) $(SRC_DIR)/frontend -B$(BUILD_DIR)/_frontend $(CMAKEFLAGS)
	$(CMAKE) --build $(BUILD_DIR)/_frontend
	cp $(BUILD_DIR)/_frontend/texedit $(BUILD_DIR)


#
# Remove build directory
#

clean:
	rm -r $(BUILD_DIR)


#
# Clean build directory (remove unnecessary build artifacts, i.e. prepare for distribution)
#

predist:
	rm -r $(BUILD_DIR)/_*
