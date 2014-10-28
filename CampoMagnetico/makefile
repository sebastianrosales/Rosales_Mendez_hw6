#Variable: Se definen acá y se usan con $(NOMBRE)
enrg=1
alpha=45
all: particle_in_field.x particle_in_field.c trayectoria_$(enrg).000000_$(alpha).000000.dat trayectoria_$(enrg).000000_$(alpha).000000.pdf

# $@ significa el archivo target
# $^ significa todos los prerrequistos 
particle_in_field.x:particle_in_field.c
	cc $^ -lm -o $@
trayectoria_$(enrg).000000_$(alpha).000000.dat:particle_in_field.x
	./$^ $(enrg) $(alpha)
trayectoria_$(enrg).000000_$(alpha).000000.pdf:trayectoria_$(enrg).000000_$(alpha).000000.dat
	python plot_trayectoria.py $^
