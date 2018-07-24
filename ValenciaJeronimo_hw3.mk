ValenciaJeronimo_Resultados_hw3.pdf: ValenciaJeronimo_Resultados_hw3.tex graficasCM_3D.pdf graficasCM_vistas.pdf cortesAbiertas.pdf cortesCerradas.pdf
	pdflatex ValenciaJeronimo_Resultados_hw3.tex
	xdg-open ValenciaJeronimo_Resultados_hw3.pdf

graficasCM_3D.pdf graficasCM_vistas.pdf cortesAbiertas.pdf cortesCerradas.pdf: datosCampoMagnetico.dat ValenciaJeronimo_Plots_hw3.py datosTamborCerradas.dat datosTamborAbiertas.dat
	python3 ValenciaJeronimo_Plots_hw3.py

datosCampoMagnetico.dat : datosCampoMagnetico.exe
	./datosCampoMagnetico.exe > datosCampoMagnetico.dat

datosTamborCerradas.dat datosTamborAbiertas.dat : datosTambor.exe
	./datosTambor.exe

datosCampoMagnetico.exe : ValenciaJeronimo_ODE.cpp
	g++ ValenciaJeronimo_ODE.cpp -o datosCampoMagnetico.exe

datosTambor.exe : ValenciaJeronimo_PDE.cpp
	g++ ValenciaJeronimo_PDE.cpp -o datosTambor.exe
