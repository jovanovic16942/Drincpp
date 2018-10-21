LDFLAGS = -lglut -lGLU -lGL -lm -std=c++11

main: main.o camera.o input.o object.o tap.o time.o tavern.o tankard.o usable.o bar.o light.o table.o image.o
	g++ -o main *.o $(LDFLAGS)
main.o: main.cpp Global.h
	g++ -c main.cpp $(LDFLAGS)
camera.o: Camera.cpp Camera.h vector3f.h
	g++ -c Camera.cpp $(LDFLAGS)
input.o: Input.cpp Input.h
	g++ -c Input.cpp $(LDFLAGS)
object.o: GameObject.cpp GameObject.h vector3f.h triangle.h
	g++ -c GameObject.cpp $(LDFLAGS)
tap.o: TapMachine.cpp TapMachine.h
	g++ -c TapMachine.cpp $(LDFLAGS)
time.o: Time.cpp Time.h
	g++ -c Time.cpp $(LDFLAGS)
tavern.o: Tavern.cpp Tavern.h
	g++ -c Tavern.cpp $(LDFLAGS)
tankard.o: Tankard.cpp Tankard.h
	g++ -c Tankard.cpp $(LDFLAGS)
usable.o: UsableObject.cpp UsableObject.h
	g++ -c UsableObject.cpp $(LDFLAGS)
bar.o: Bar.cpp Bar.h
	g++ -c Bar.cpp $(LDFLAGS)
light.o: Light.cpp Light.h
	g++ -c Light.cpp $(LDFLAGS)
table.o: Table.cpp Table.h
	g++ -c Table.cpp $(LDFLAGS) 
image.o: Image.cpp Image.h
	g++ -c Image.cpp $(LDFLAGS)
clean:
	@rm -f *.o
