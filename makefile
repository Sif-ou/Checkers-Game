# =============================
#  SDL2 Cross-Platform Makefile
# =============================

# === Compiler and Source ===
CXX       = g++
SRC       = main.cpp game.cpp board.cpp track.cpp Movement.cpp piece.cpp take.cpp struct.cpp
OBJDIR    = obj
OBJ       = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
SRC_COUNT = $(words $(SRC))

# === Detect operating system ===
ifeq ($(OS),Windows_NT)
	# --- Windows Settings ---
	OUT       = checkers.exe
	CXXFLAGS  = -g -I src/include
	LDFLAGS   = -L src/lib
	LIBS      = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	TIME_CMD  = powershell -Command "$$t = Measure-Command { $(MAKE) --no-print-directory build }; Write-Host 'Built $(SRC_COUNT) source files in' ($$t.TotalSeconds) 'seconds.'"
	RM        = del /Q /F
	MKDIR     = if not exist $(OBJDIR) mkdir $(OBJDIR)
	CLEAN_OBJ = $(OBJDIR)\*.o
else
	# --- Linux / macOS Settings ---
	UNAME_S := $(shell uname -s)
	OUT       = checkers
	
	# Automatically find SDL2 paths using pkg-config (standard for Linux/macOS)
	CXXFLAGS  = -g $(shell pkg-config --cflags sdl2 SDL2_image 2>/dev/null || sdl2-config --cflags)
	LDFLAGS   = 
	LIBS      = $(shell pkg-config --libs sdl2 SDL2_image 2>/dev/null || sdl2-config --libs) -lSDL2_image
	
	TIME_CMD  = sh -c 'echo "Compiling $(SRC_COUNT) source files..."; start=$$(date +%s); $(MAKE) --no-print-directory build; end=$$(date +%s); echo "Built $(SRC_COUNT) source files in $$((end-start)) seconds."'
	RM        = rm -f
	MKDIR     = mkdir -p $(OBJDIR)
	CLEAN_OBJ = $(OBJDIR)/*.o
	
	# Optional tweak for macOS Apple Silicon (Homebrew) if pkg-config is missing
	ifeq ($(UNAME_S),Darwin)
		CXXFLAGS += -I/opt/homebrew/include
		LDFLAGS  += -L/opt/homebrew/lib
	endif
endif

# === Default target ===
all:
	@echo "Building..."
	@$(TIME_CMD)
	@echo "Build complete."

# === Build object files only if changed ===
build: $(OUT)

$(OUT): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT) $(LDFLAGS) $(LIBS)

# === Compile each .cpp into obj/ folder ===
$(OBJDIR)/%.o: %.cpp
	@$(MKDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# === Run the game ===
run: all
	@echo "Running game..."
	@./$(OUT)

# === Clean build files ===
clean:
	@echo "Cleaning..."
	@$(RM) $(OUT)
	@$(RM) $(CLEAN_OBJ) 2>nul || true
	@echo "Clean complete."