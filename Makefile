BUILD_DIR := build
SRC_DIR := .

CARGO := cargo
CARGOCHAN := +nightly
CARGOFLAGS := -Zunstable-options

ifneq "$(DEBUG)" "1" 	# run with DEBUG=1 to use debug configuration
CARGOFLAGS += --release
endif


#
# All targets
#
all: compiler frontend

#
# Copy TexLive distribution
#
TEXLIVE_SRC := $(SRC_DIR)/vendor/tex
TEXLIVE_DST := $(BUILD_DIR)/vendor/tex
$(TEXLIVE_DST): $(TEXLIVE_SRC)
	mkdir -p $(TEXLIVE_DST) && cp -r $(TEXLIVE_SRC)/* $(TEXLIVE_DST)

#
# Copy texpdfc script
#
COMPILER_SCRIPT_SRC := $(SRC_DIR)/compiler
$(BUILD_DIR)/texpdfc.sh: $(COMPILER_SCRIPT_SRC)/texpdfc.sh
	mkdir -p $(BUILD_DIR) && cp $< $@

#
# Compile the TeX compilation CLI
#
COMPILER_TOML := $(SRC_DIR)/compiler/Cargo.toml
.PHONY: compiler
compiler: $(TEXLIVE_DST) $(BUILD_DIR)/texpdfc.sh
	$(CARGO) $(CARGOCHAN) build $(CARGOFLAGS) --manifest-path=$(COMPILER_TOML) --target-dir=$(BUILD_DIR)/_$@ --out-dir=$(BUILD_DIR)

#
# Compile the TexEdit GUI frontend
#
FRONTEND_TOML := $(SRC_DIR)/frontend/Cargo.toml
.PHONY: frontend
frontend: compiler
	$(CARGO) $(CARGOCHAN) build $(CARGOFLAGS) --manifest-path=$(FRONTEND_TOML) --target-dir=$(BUILD_DIR)/_$@ --out-dir=$(BUILD_DIR)

#
# Remove build directory
#
.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

#
# Clean build directory (remove unnecessary build artifacts, i.e. prepare for distribution)
#
.PHONY: predist
predist:
	rm -r $(BUILD_DIR)/_*
