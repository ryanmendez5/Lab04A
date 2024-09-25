all:  user.c calculator.c go.c 
	gcc user.c 			-o user
	gcc calculator.c 	-o calculator
	gcc go.c			-o go

clean:
	rm user calculator go