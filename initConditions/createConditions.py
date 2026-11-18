from math import inf

class Point:
    def __init__(self, mass, x, y, z, xVel, yVel, zVel):
        self.mass = mass
        self.x, self.y, self.z = x, y, z
        self.xVel, self.yVel, self.zVel = xVel, yVel, zVel

    def asData(self):
        return "{0},{1},{2},{3},{4},{5},{6}".format(
            self.x, self.y, self.z,
            self.xVel, self.yVel, self.zVel,
            self.mass
        )

def enterValidInt(prompt, m1=-inf, m2=inf):
    valid = False
    while not valid:
        try:
            x = int(input(prompt))
            if x < m1:
                print("Value is less than minimum (" + str(m1) + ")")
            elif x > m2:
                print("Value is greater than maximum (" + str(m2) + ")")
            else:
                valid = True
        except ValueError:
            print("Not a valid integer")
    return x

def enterValidFloat(prompt, m1=-inf, m2=inf):
    valid = False
    while not valid:
        try:
            x = float(input(prompt))
            if x < m1:
                print("Value is less than minimum (" + str(m1) + ")")
            elif x > m2:
                print("Value is greater than maximum (" + str(m2) + ")")
            else:
                valid = True
        except ValueError:
            print("Not a valid float")
    return x

sepChars = [" ", ",", "(", ")", ":"]
def enterValidXYZ(prompt, separator = " ", m1=-inf, m2=inf):
    valid = False
    while not valid:
        xyz = input(prompt)
        for c in sepChars:
            if c != separator:
                xyz = xyz.replace(c, "")
        try:
            strX, strY, strZ = xyz.split(" ")
        except ValueError:
            print(f"Please enter three values, separated by '{separator}'")
        else:
            try:
                x = float(strX)
                y = float(strY)
                z = float(strZ)
                # print(f"x:{x}, y:{y}, z:{z}")
                if x < m1 or y < m1 or z < m1:
                    print(f"Value is less than minimum ({m1})")
                elif x > m2 or y > m2 or z > m2:
                    print(f"Value is greater than maximum ({m2})")
                else:
                    valid = True
            except ValueError:
                print("Error of some kind, try again")
    return (x, y, z)

outputFilename = "../src/initConditions.csv"
if __name__ == "__main__":
    outFile = open(outputFilename, "w")
    outFile.write("NBIC\n")
    n = enterValidInt("How many particles? ", 2)
    outputFile.write(str(n) + "\n")
    for i in range(1, 1 + n):
        p = Point(
            enterValidFloat(f"\nMass of particle {i} : ", 0),
            *enterValidXYZ(f"Position of particle {i} : "),
            *enterValidXYZ(f"Velocity of particle {i} : ")
        )
        outFile.write(p.asData() + "\n")

