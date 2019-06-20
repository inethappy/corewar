.name "name"
.comment "fjf"
#ffkfk

loop:
        sti r1,%:live,%1
		st r1, 2
		ld 98, r1
live:
        live %0
        ld %1, r1
        zjmp %:loop
