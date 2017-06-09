from aStar import *

def main():
	inputFile = open("input.txt", "r")
	outputFile = open("output.txt", "w")

	i=0
	Map = []
	for ligne in inputFile:
		Map[i] = []
		j=0
		for c in ligne:
			Map[i][j] = c
			j = j+1
		i = i+1

	Init = {}
	Target = {}

	ligne = inputFile.readLine().rstrip('\n')
	Init["x"] = ligne.split(':')[0]
	Init["y"] = ligne.split(':')[1]
	ligne = inputFile.readLine().rstrip('\n')
	Init["x"] = ligne.split(':')[0]
	Init["y"] = ligne.split(':')[1]

	path = pathfinding(Map,Init, Target)

	if path[0] == "UP":
		outputFile.write("0")
	if path[0] == "RIGHT":
		outputFile.write("1")
	if path[0] == "DOWN":
		outputFile.write("2")
	if path[0] == "LEFT":
		outputFile.write("3")

	inputFile.close()
	outputFile.close()

if __main__=="__main__":
	main()
main()