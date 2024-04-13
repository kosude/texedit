BUILD_DIR := build
SRC_DIR := .
DEPS_DIR := deps

CMAKE := cmake
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
# Copy scripts
#

$(BUILD_DIR)/texpdfc.sh: $(SRC_DIR)/compiler/texpdfc.sh
	mkdir -p $(BUILD_DIR) && cp $< $@

$(BUILD_DIR)/start.sh: $(SRC_DIR)/start.sh
	mkdir -p $(BUILD_DIR) && cp $< $@


#
# Compile the TeX compilation CLI
#

COMPILER_TOML := $(SRC_DIR)/compiler/Cargo.toml

compiler: $(TEXLIVE_DST) $(BUILD_DIR)/texpdfc.sh
	$(CARGO) $(CARGOCHAN) build $(CARGOFLAGS) --manifest-path=$(COMPILER_TOML) --target-dir=$(BUILD_DIR)/_$@ --out-dir=$(BUILD_DIR)


#
# Compile frontend dependencies
#

DEPS_CUTILS := $(DEPS_DIR)/cutils
DEPS_CUTILS_LDLIBS := -lcutils

$(BUILD_DIR)/lib/libcutils.so:
	mkdir -p $(BUILD_DIR)/lib
	$(CMAKE) $(DEPS_DIR)/cutils -B$(DEPS_DIR)/cutils/build -DCMAKE_BUILD_TYPE=Release -DCUTILS_CLIST=OFF -DCUTILS_CARRAY=OFF
	$(CMAKE) --build $(DEPS_DIR)/cutils/build
	cp $(DEPS_DIR)/cutils/build/libcutils.so $(BUILD_DIR)/lib


#
# Compile the TexEdit GUI frontend
#

FRONTEND_SRCS := $(shell find $(SRC_DIR)/frontend -name '*.cpp')
FRONTEND_OBJS := $(patsubst %,$(BUILD_DIR)/_frontend/%.o,$(subst $(SRC_DIR)/frontend/,,$(FRONTEND_SRCS)))
FRONTEND_DEPS := $(FRONTEND_OBJS:.o=.d)

frontend: $(BUILD_DIR)/texedit $(BUILD_DIR)/start.sh

FRONTEND_INC_DIRS := $(SRC_DIR)/frontend $(DEPS_DIR)/cutils
CXXFLAGS := $(addprefix -I,$(FRONTEND_INC_DIRS)) $(shell wx-config --cxxflags) -MMD -MP -std=c++17 -Wall -Wextra -Wpedantic -Werror \
			-Wno-error=unused-parameter -Wno-error=unused-function -Wno-implicit-fallthrough
LDFLAGS := $(shell wx-config --libs) -L$(BUILD_DIR)/lib ${DEPS_CUTILS_LDLIBS}

ifneq "$(DEBUG)" "1" 	# run with DEBUG=1 to use debug configuration
CXXFLAGS += -O2 -s -DNDEBUG
else
CXXFLAGS += -O0 -g
endif

# build c++ objects
$(BUILD_DIR)/_frontend/%.cpp.o: $(SRC_DIR)/frontend/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# link objects to create final binary
$(BUILD_DIR)/texedit: $(FRONTEND_OBJS) $(BUILD_DIR)/lib/libcutils.so
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
