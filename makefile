# ====================================================================
#  SDL2 Smart Cross-Platform Makefile
# ====================================================================

# === Compiler and Source Configuration ===
CXX       = g++
SRC       = main.cpp game.cpp board.cpp track.cpp Movement.cpp piece.cpp take.cpp struct.cpp
OBJDIR    = obj
OBJ       = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
SRC_COUNT = $(words $(SRC))

# === OS Detection and Dependency Mapping ===
ifeq ($(OS),Windows_NT)
    # --- Windows Settings ---
    OUT       = checkers.exe
    
    # 1. Try to automatically detect SDL2 using pkg-config (silenced with Windows 2>nul)
    PKG_FLAGS_C := $(shell pkg-config --cflags sdl2 SDL2_image 2>nul)
    PKG_FLAGS_L := $(shell pkg-config --libs sdl2 SDL2_image 2>nul)

    ifneq ($(PKG_FLAGS_C),)
        # If pkg-config finds SDL2 globally, use it automatically
        CXXFLAGS  = -g $(PKG_FLAGS_C)
        LDFLAGS   = 
        LIBS      = $(PKG_FLAGS_L)
    else
        # 2. Fallback: Adjusted default path to point directly to your real /src folder setup
        SDL_DIR  ?= C:/SDL/SDL2/src
        
        CXXFLAGS  = -g -I$(SDL_DIR)/include
        LDFLAGS   = -L$(SDL_DIR)/lib
        LIBS      = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
    endif

    TIME_CMD  = powershell -Command "$$t = Measure-Command { $(MAKE) --no-print-directory build }; Write-Host 'Built $(SRC_COUNT) source files in' ($$t.TotalSeconds) 'seconds.'"
    RM        = del /Q /F
    MKDIR     = if not exist $(OBJDIR) mkdir $(OBJDIR)
    CLEAN_OBJ = $(OBJDIR)\*.o
else
    # --- Linux / macOS Settings ---
    UNAME_S := $(shell uname -s)
    OUT       = checkers
    
    # Automatically find SDL2 paths using pkg-config
    CXXFLAGS  = -g $(shell pkg-config --cflags sdl2 SDL2_image 2>/dev/null || sdl2-config --cflags)
    LDFLAGS   = 
    LIBS      = $(shell pkg-config --libs sdl2 SDL2_image 2>/dev/null || sdl2-config --libs) -lSDL2_image
    
    TIME_CMD  = sh -c 'echo "Compiling $(SRC_COUNT) source files..."; start=$$(date +%s); $(MAKE) --no-print-directory build; end=$$(date +%s); echo "Built $(SRC_COUNT) source files in $$((end-start)) seconds."'
    RM        = rm -f
    MKDIR     = mkdir -p $(OBJDIR)
    CLEAN_OBJ = $(OBJDIR)/*.o
    
    # Tailored tweak for macOS Apple Silicon (Homebrew paths) if pkg-config drops out
    ifeq ($(UNAME_S),Darwin)
        CXXFLAGS += -I/opt/homebrew/include
        LDFLAGS  += -L/opt/homebrew/lib
    endif
endif

# ====================================================================
#  Build Targets and Rules
# ====================================================================

# === Default Target ===
all:
	@echo "Building..."
	@$(TIME_CMD)
	@echo "Build complete."

# === Trigger Actual Binary Compilation ===
build: $(OUT)

$(OUT): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT) $(LDFLAGS) $(LIBS)

# === Compile Individual Source Files into obj/ Folder ===
$(OBJDIR)/%.o: %.cpp
	@$(MKDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# === Utility: Build and Run Immediate Executable ===
run: all
	@echo "Running game..."
	@./$(OUT)

# === Utility: Wipe Build Cache Clean ===
clean:
	@echo "Cleaning..."
	@$(RM) $(OUT)
	@$(RM) $(CLEAN_OBJ) 2>nul || true
	@echo "Clean complete."