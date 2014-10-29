#Variable: Se definen acá y se usan con $(NOMBRE)
enrg=1
alpha=30
all:  trayectoria_$(enrg)_$(alpha).pdf

# $@ significa el archivo target
# $^ significa todos los prerrequistos 
particle_in_field.x:particle_in_field.c
	echo "Creando archivo .x "
	cc $^ -lm -o $@
trayectoria_$(enrg)_$(alpha).dat:particle_in_field.x
	echo "Creando archivo .dat"
	./$^ $(enrg) $(alpha)
trayectoria_$(enrg)_$(alpha).pdf:trayectoria_$(enrg)_$(alpha).dat
	echo "Creando archivo .pdf  "
	python plot_trayectoria.py $^
