# =============================
#  SDL2 Cross-Platform Makefile
# =============================

# === Compiler and flags ===
CXX       = g++
CXXFLAGS  = -I src/include -L src/lib
LIBS      = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
SRC       = main.cpp  game.cpp board.cpp track.cpp Movement.cpp piece.cpp take.cpp struct.cpp
OBJDIR    = obj
OBJ       = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
OUT       = checkers.exe

# Count how many source files there are
SRC_COUNT = $(words $(SRC))

# === Detect operating system ===
ifeq ($(OS),Windows_NT)
    TIME_CMD = powershell -Command "$$t = Measure-Command { $(MAKE) --no-print-directory build }; Write-Host 'Built $(SRC_COUNT) source files in' ($$t.TotalSeconds) 'seconds.'"
    RM = del /Q
    MKDIR = if not exist $(OBJDIR) mkdir $(OBJDIR)
else
    TIME_CMD = sh -c 'echo "Compiling $(SRC_COUNT) source files..."; start=$$(date +%s); $(MAKE) --no-print-directory build; end=$$(date +%s); echo "Built $(SRC_COUNT) source files in $$((end-start)) seconds."'
    RM = rm -f
    MKDIR = mkdir -p $(OBJDIR)
endif

# === Default target ===
all:
	@echo "Building..."
	@$(TIME_CMD)
	@echo "Build complete."

# === Build object files only if changed ===
build: $(OUT)

$(OUT): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT) $(LIBS)

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
	@$(RM) $(OBJDIR)\*.o 2>nul || true
	@echo "Clean complete."
