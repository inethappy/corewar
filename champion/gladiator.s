.name "Gladiator"
.comment "Gladiator debet mori stans"

verystart:
		sti r1, %:live, %1
		sti r1, %:lives, %1
live:
		live %42
continue:
		fork %511
lives:
		live %42
fork2:
		fork %:start
refresh:
        ld %0, r4
		ld %0, r4
		ld %0, r4
		ld %0, r4
		ld %0, r4
		ld %0, r4
		ldi %64, %1, r4
		xor r1, r4, r4
		zjmp %:end
		sti r1, %:live2, %1
		sti r1, %:live3, %1
lives2:
		live %42
		sti r1, %:lives2, %1
		ld %0, r4
		zjmp %:refresh
start:
		sti r1, %:live2, %1
		ld %1, r3
live2:
		live %42
forking:
		fork %:start
		sti r1, %:live3, %1
		add r2, r3, r2
		xor %5, r2, r4
		zjmp %:start

live3:
		live %42
		ld %0, r4
		zjmp %:live3
end:
		zjmp %0
		

