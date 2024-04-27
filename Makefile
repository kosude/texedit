BUILD_DIR := build
SRC_DIR := .

PROJECT_VERS := $(shell "$(SRC_DIR)/util/version.sh" --short)
PROJECT_VERS_LONG := $(shell "$(SRC_DIR)/util/version.sh" --long)

CMAKE := cmake
CMAKEFLAGS = -DTEXEDIT_VERSION="$(PROJECT_VERS_LONG)" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

CARGO := cargo
CARGOCHAN := +nightly
CARGOFLAGS := -Zunstable-options

SPHINX := sphinx-build

BUN := bun
BUNFLAGS := --loader=.mjs:file --outfile=tepdfserver --define="VERSION='$(PROJECT_VERS)'"

# this ensures `all` is run by default despite not being the first target in the Makefile
.DEFAULT_GOAL := all

# check for dependencies

.PHONY: validate_cmake validate_cargo validate_sphinx validate_bun
validate_cmake:
	$(if \
		$(shell which $(CMAKE)),\
		$(info CMake located at $(shell command -v $(CMAKE))),\
		$(error CMake not found in PATH, but is required to build texedit))
	@:
validate_cargo:
	$(if \
		$(shell which $(CARGO)),\
		$(info Cargo located at $(shell command -v $(CARGO))),\
		$(error Cargo not found in PATH, but is required to build tecomp))
	@:
validate_sphinx:
	$(if \
		$(shell which $(SPHINX)),\
		$(info Sphinx located at $(shell command -v $(SPHINX))),\
		$(error Sphinx (sphinx-build) not found in PATH, but is required to build HTML doc))
	@:
validate_bun:
	$(if \
		$(shell which $(BUN)),\
		$(info Bun located at $(shell command -v $(BUN))),\
		$(error Bun not found in PATH, but is required to build tepdfserver))
	@:

# run with DEBUG=1 to use debug configuration

ifeq "$(DEBUG)" "1"
CMAKEFLAGS += -DCMAKE_BUILD_TYPE=Debug
else
CMAKEFLAGS += -DCMAKE_BUILD_TYPE=Release
endif

ifneq "$(DEBUG)" "1"
CARGOFLAGS += --release
endif

.PHONY: tecomp texedit tepdfserver
.PHONY: docs clean predist


#
# All targets
#
all: tecomp texedit tepdfserver


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
# Copy script(s)
#

$(BUILD_DIR)/texpdfc.sh: $(SRC_DIR)/tecomp/texpdfc.sh | $(BUILD_DIR)
	cp $< $@


#
# Compile the TeX compilation CLI
#

COMPILER_TOML := $(SRC_DIR)/tecomp/Cargo.toml

tecomp: $(COMPILER_TOML) $(TEXLIVE_DST) $(BUILD_DIR)/texpdfc.sh | validate_cargo
	$(CARGO) $(CARGOCHAN) build $(CARGOFLAGS) --manifest-path=$(COMPILER_TOML) --target-dir=$(BUILD_DIR)/_$@ --out-dir=$(BUILD_DIR)


#
# Compile the TexEdit GUI frontend
#

FRONTEND_CMAKELISTS := $(SRC_DIR)/texedit/CMakeLists.txt

texedit: $(FRONTEND_CMAKELISTS) | validate_cmake
	$(CMAKE) $(SRC_DIR)/texedit -B$(BUILD_DIR)/_texedit $(CMAKEFLAGS)
	$(CMAKE) --build $(BUILD_DIR)/_texedit
	mv $(BUILD_DIR)/_texedit/texedit $(BUILD_DIR)


#
# Bundle the PDF preview server
#

$(SRC_DIR)/tepdfserver/node_modules:
	$(BUN) install --cwd $(SRC_DIR)/tepdfserver

tepdfserver: | validate_bun $(BUILD_DIR) $(SRC_DIR)/tepdfserver/node_modules
	$(BUN) build --compile $(SRC_DIR)/tepdfserver/server/start.ts $(BUNFLAGS)
	mv $(SRC_DIR)/tepdfserver/server/tepdfserver $(BUILD_DIR)


#
# Compile HTML documentation
#

DOCS_CONF_PY := $(SRC_DIR)/docs/conf.py
DOCS_CONFIG_SH := $(SRC_DIR)/docs/configure.sh

docs: $(DOCS_CONFIG_SH) $(DOCS_CONF_PY) | validate_sphinx
	$(DOCS_CONFIG_SH) "$(SPHINX)" "$(SRC_DIR)/docs" "$(BUILD_DIR)/docs" "$(SRC_DIR)/util" "$(PROJECT_VERS)"


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
	cp $(SRC_DIR)/LICENCE $(BUILD_DIR)
