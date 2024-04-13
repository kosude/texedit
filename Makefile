BUILD_DIR := build
SRC_DIR := .

CARGO := cargo
CARGOCHAN := +nightly
CARGOFLAGS := -Zunstable-options

ifneq "$(DEBUG)" "1" 	# run with DEBUG=1 to use debug configuration
CARGOFLAGS += --release
endif

.PHONY: compiler frontend clean predist


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

compiler: $(TEXLIVE_DST) $(BUILD_DIR)/texpdfc.sh
	$(CARGO) $(CARGOCHAN) build $(CARGOFLAGS) --manifest-path=$(COMPILER_TOML) --target-dir=$(BUILD_DIR)/_$@ --out-dir=$(BUILD_DIR)


#
# Compile the TexEdit GUI frontend
#

FRONTEND_SRCS := $(shell find $(SRC_DIR)/frontend -name '*.cpp')
FRONTEND_OBJS := $(patsubst %,$(BUILD_DIR)/_frontend/%.o,$(subst $(SRC_DIR)/frontend/,,$(FRONTEND_SRCS)))
FRONTEND_DEPS := $(FRONTEND_OBJS:.o=.d)

frontend: $(BUILD_DIR)/texedit

FRONTEND_INC_DIRS := $(SRC_DIR)/frontend
CXXFLAGS := $(addprefix -I,$(FRONTEND_INC_DIRS)) $(shell wx-config --cxxflags) -MMD -MP -std=c++11 -Wall -Wextra -Wpedantic -Werror \
			-Wno-error=unused-parameter -Wno-error=unused-function -Wno-implicit-fallthrough
LDFLAGS := $(shell wx-config --libs)

ifneq "$(DEBUG)" "1" 	# run with DEBUG=1 to use debug configuration
CXXFLAGS += -O2 -s -DNDEBUG
else
CXXFLAGS += -O0 -g
endif

$(BUILD_DIR)/_frontend:
	mkdir -p $@

# build c++ objects
$(BUILD_DIR)/_frontend/%.cpp.o: $(SRC_DIR)/frontend/%.cpp | $(BUILD_DIR)/_frontend
	$(CXX) $(CXXFLAGS) -c $< -o $@

# link objects to create final binary
$(BUILD_DIR)/texedit: $(FRONTEND_OBJS)
	$(CXX) $(FRONTEND_OBJS) -o $@ $(LDFLAGS)

-include $(FRONTEND_DEPS)


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
