CXX = g++
CXXFLAGS = -D_JUDGE_ -DGLIBXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11
OBJECTS = AreaDeProcesos.o Cluster.o Prioridad.o Proceso.o Procesador.o

program.exe: $(OBJECTS) program.cc
	$(CXX) $(CXXFLAGS) -o program.exe program.cc $(OBJECTS)

AreaDeProcesos.o: AreaDeProcesos.cc AreaDeProcesos.hh
	$(CXX) $(CXXFLAGS) -c AreaDeProcesos.cc

Cluster.o: Cluster.cc Cluster.hh
	$(CXX) $(CXXFLAGS) -c Cluster.cc

Prioridad.o: Prioridad.cc Prioridad.hh
	$(CXX) $(CXXFLAGS) -c Prioridad.cc

Proceso.o: Proceso.cc Proceso.hh
	$(CXX) $(CXXFLAGS) -c Proceso.cc

Procesador.o: Procesador.cc Procesador.hh
	$(CXX) $(CXXFLAGS) -c Procesador.cc

clean:
	rm -f *.o program
