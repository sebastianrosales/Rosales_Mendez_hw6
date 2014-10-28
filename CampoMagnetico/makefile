all: particle_in_field.x particle_in_field.c trayectoria_10.000000_10.000000.dat
# $@ significa el archivo target
# $^ significa todos los prerrequistos 
particle_in_field.x:particle_in_field.c
	cc $^ -lm -o $@
trayectoria_10.000000_10.000000.dat:particle_in_field.x
	./$^ 10 10
