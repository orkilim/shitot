CXX = g++
CPPFLAGS = -std=c++1z -static -g

OBJS += Backend/Control.o Backend/EventEngine.o Backend/Graphics.o Source/Source.o Controllers/Label.o Backend/Border/Border.o Backend/Border/None.o Backend/Border/Single.o Backend/Border/Double.o Controllers/Panel.o Controllers/Button.o Controllers/NumericBox.o Controllers/MessageBox.o Controllers/CheckList.o Controllers/TextBox.o Controllers/RadioBox.o Controllers/ComboBox.o
# OBJS += try/try.o

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

all: $(OBJS)
	$(CXX) $(CPPFLAGS) $(OBJS) -o MethodFinal.exe
clean:
	rm -f $(OBJS)
	rm -f *.exe