#! /usr/bin/python3

no = int(input("Enter number: "))
frnt = 0.0
end = no
mid = (frnt +end)/2
err = 1.0e-15
while (abs((mid**2)-no)>err):
	if ((mid**2)>no):
		end = mid
	else:
		frnt = mid
	mid = (frnt+end)/2
print("Square Root of " + str(no) + " is " + str(mid))
